
use std::{thread::{self, sleep}, sync::{mpsc, Arc, atomic::{AtomicBool, Ordering}},time};


use acc_shared_memory::init;
use sqlite::{Statement, BindableWithIndex};
use sqlite3_sys;
use std::ffi::CString;
use libc::c_char;//c_int

#[derive(Clone)]
struct TransmitAccTelemetry{
    lap:i32,
    time:i32,
    gas:f32,
    brake:f32,
    fuel:f32,
    gear:i32,
    rpms:i32,
    steer_angle:f32,
    speed_kmh:f32,
    velocity:[f32;3],
    acc_g:[f32;3],
}

pub fn record_start(output:String,frequence:i32,rate_full_frame:i32)->Result<(),String>{
    
    let(tx_db,rx_db) = mpsc::channel();
    let (tx_speed, rx_speed) = mpsc::channel();
    // let(tx_stop,rx_stop) = mpsc::channel();
    // let(tx_db_stop,rx_db_stop) = mpsc::channel();
    let run_arc = Arc::new(AtomicBool::new(true));
    let run_arc2 = run_arc.clone();
    let run_arc3 = run_arc.clone();
    let run_arc4 = run_arc.clone();

    let _ = ctrlc::set_handler(move || {
        run_arc3.store(false, Ordering::Relaxed);
    });


    let producer_thread = thread::spawn(move ||{
        let acc_result_obj = init(true,true,false);
        if let Err(error) = acc_result_obj{
            print!("Error at init shared object: {}",error);
            return;
        }
        let mut acc_obj = acc_result_obj.unwrap();
        let run = run_arc.clone();
        
        while run.load(Ordering::Relaxed) {
            let physics_option = acc_obj.get_physics();
            let graphics = acc_obj.get_graphics();
            if let None = physics_option{
                continue;
            }
            let physics = physics_option.unwrap();
            //print!("hallo welt speed:{}\r",physics.speed_kmh);
            //print!("gear:{}\r",physics.gear);
            let transmit_data = TransmitAccTelemetry{
                lap:graphics.completed_laps,
                time:graphics.i_current_time,
                gas:physics.gas,
                brake:physics.brake,
                fuel:physics.fuel,
                gear:physics.gear,
                rpms:physics.rpms,
                steer_angle:physics.steer_angle,
                speed_kmh:physics.speed_kmh,
                velocity:physics.velocity,
                acc_g:physics.acc_g
            };
            tx_db.send(transmit_data.clone()).unwrap();
            tx_speed.send(physics.speed_kmh).unwrap();
            let duration = time::Duration::from_millis(frequence as u64);
            sleep(duration);
            //run = rx_stop.recv().unwrap();
        }
        acc_obj.dismiss().unwrap();
    });
    let consumer_db_thread = thread::spawn(move ||{
        let db_result = sqlite::open(":memory:");
        if let Err(_error) = db_result{
            return;
        }
        let db = db_result.unwrap();
        db.execute("CREATE TABLE data_point(id INTEGER PRIMARY KEY,type INTEGER,lap INTEGER,time_in_ms REAL)").unwrap();
        db.execute("CREATE TABLE data_point_int_value(data_point_id INTEGER,legend_id INTEGER,value INTEGER)").unwrap();
        db.execute("CREATE TABLE data_point_float_value(data_point_id INTEGER,legend_id INTEGER,value REAL)").unwrap();
        db.execute("CREATE TABLE data_point_vec3_value(data_point_id INTEGER,legend_id INTEGER,value_x REAL,value_y REAL,value_z REAL)").unwrap();
        db.execute("CREATE TABLE legend(id INTEGER PRIMARY KEY AUTOINCREMENT,name TEXT,type TEXT)").unwrap();
        db.execute("INSERT INTO legend(id,name,type) VALUES 
        (1,\"gas\",\"data_point_float_value\"),
        (2,\"brake\",\"data_point_float_value\"),
        (3,\"fuel\",\"data_point_float_value\"),
        (4,\"gear\",\"data_point_int_value\"),
        (5,\"rpms\",\"data_point_int_value\"),
        (6,\"steer_angle\",\"data_point_float_value\"),
        (7,\"speed_kmh\",\"data_point_float_value\"),
        (8,\"velocity\",\"data_point_vec3_value\"),
        (9,\"acc_g\",\"data_point_vec3_value\");").unwrap();
        let mut prepare_data_point_insert_stmt = db.prepare("INSERT INTO data_point(type,lap,time_in_ms) VALUES (?,?,?)").unwrap();
        let mut prepare_data_point_float_insert_stmt = db.prepare("INSERT INTO data_point_float_value(data_point_id,legend_id,value) VALUES (?,?,?)").unwrap();
        let mut prepare_data_point_int_insert_stmt = db.prepare("INSERT INTO data_point_int_value(data_point_id,legend_id,value) VALUES (?,?,?)").unwrap();
        let mut prepare_data_point_vec3_insert_stmt = db.prepare("INSERT INTO data_point_vec3_value(data_point_id,legend_id,value_x,value_y,value_z) VALUES (?,?,?,?,?)").unwrap();
        let mut first = true;
        let counter = 0;
        let mut delta_frame:bool;
        let mut full_telemetry = TransmitAccTelemetry{speed_kmh:0.0,lap:0,gear:0,time:0,gas:0.0,brake:0.0,fuel:0.0,rpms:0,steer_angle:0.0,velocity:[0.0,0.0,0.0],acc_g:[0.0,0.0,0.0]};
        while run_arc2.load(Ordering::Relaxed){
            let telemetry_result = rx_db.recv();
            if let Err(_error) = telemetry_result {
                continue;
            }
            let telemetry = telemetry_result.unwrap();
            if first {
                full_telemetry = telemetry.clone();
                first = false;
            }
            if counter > rate_full_frame{
                let _ = prepare_data_point_insert_stmt.bind((1,1));
                delta_frame = false;
            } else {
                let _ = prepare_data_point_insert_stmt.bind((1,0));
                delta_frame = true;
            }
            
            let _ = prepare_data_point_insert_stmt.bind((2,telemetry.lap as i64));
            let _ = prepare_data_point_insert_stmt.bind((3,telemetry.time as i64));
            prepare_data_point_insert_stmt.next().unwrap();
            prepare_data_point_insert_stmt.reset().unwrap();

            let mut insert_id = 0;
            let _id = db.iterate("SELECT last_insert_rowid();", |row|->bool{
                let insert_id_str = row[0].1.unwrap();
                //println!("Result insert Id Str:{}",insert_id_str);
                insert_id = insert_id_str.parse::<i32>().unwrap();
                return false;
            });

            set_point::<f64>(delta_frame, full_telemetry.speed_kmh as f64, telemetry.speed_kmh as f64, Box::new(|rv,v|{rv != *v}), &mut prepare_data_point_float_insert_stmt, insert_id, 7);
            set_point::<f64>(delta_frame, full_telemetry.gas as f64, telemetry.gas as f64, Box::new(|rv,v|{rv != *v}), &mut prepare_data_point_float_insert_stmt, insert_id, 1);
            set_point::<f64>(delta_frame, full_telemetry.brake as f64, telemetry.brake as f64, Box::new(|rv,v|{rv != *v}), &mut prepare_data_point_float_insert_stmt, insert_id, 2);
            set_point::<f64>(delta_frame, full_telemetry.fuel as f64, telemetry.fuel as f64, Box::new(|rv,v|{rv != *v}), &mut prepare_data_point_float_insert_stmt, insert_id, 3);
            set_point::<i64>(delta_frame, full_telemetry.gear as i64, telemetry.gear as i64, Box::new(|rv,v|{rv != *v}), &mut prepare_data_point_int_insert_stmt, insert_id, 4);
            set_point::<i64>(delta_frame, full_telemetry.rpms as i64, telemetry.rpms as i64, Box::new(|rv,v|{rv != *v}), &mut prepare_data_point_int_insert_stmt, insert_id, 5);
            set_point::<f64>(delta_frame, full_telemetry.steer_angle as f64, telemetry.steer_angle as f64, Box::new(|rv,v|{rv != *v}), &mut prepare_data_point_float_insert_stmt, insert_id, 6);
            set_vec_point(delta_frame, full_telemetry.velocity, telemetry.velocity, &mut prepare_data_point_vec3_insert_stmt, insert_id, 8);
            set_vec_point(delta_frame, full_telemetry.acc_g, telemetry.acc_g, &mut prepare_data_point_vec3_insert_stmt, insert_id, 9);
        }
        let name = "main";
        let c_str = CString::new(name).unwrap();
        let main: *const c_char = c_str.as_ptr() as *const c_char;
        let target_db = sqlite::open(output).unwrap();
        //let rc: c_int = 0;
        unsafe {
            let backup = sqlite3_sys::sqlite3_backup_init(target_db.as_raw(), main, db.as_raw(), main);
            sqlite3_sys::sqlite3_backup_step(backup, -1);
            sqlite3_sys::sqlite3_backup_finish(backup);
        }
    });

    while run_arc4.load(Ordering::Relaxed) {
        let speed_result = rx_speed.recv();
        if let Err(_error) = speed_result{
            continue;
        }
        let speed = speed_result.unwrap();
        //print!("Speed: {}\r",speed);
    }
    producer_thread.join().unwrap();
    consumer_db_thread.join().unwrap();
    
    return Ok(());
}


fn set_point<T:std::cmp::PartialEq + BindableWithIndex>(delta_frame:bool,reference_value:T,value:T,compare_function:Box<dyn Fn(T,&T)->bool>,stmt:&mut Statement,data_point_id:i32,legend_id:i32){
    if delta_frame{
        if compare_function(reference_value,&value) {
            let _ = stmt.bind((1,data_point_id as i64));
            let _ = stmt.bind((2,legend_id as i64));
            let _ = stmt.bind((3,value));
            stmt.next().unwrap();
            stmt.reset().unwrap();
        }
    } else {
        if compare_function(reference_value,&value) {
            let _ = stmt.bind((1,data_point_id as i64));
            let _ = stmt.bind((2,legend_id as i64));
            let _ = stmt.bind((3,value));
            stmt.next().unwrap();
            stmt.reset().unwrap();
        }
    }
}
fn set_vec_point(delta_frame:bool,reference_value:[f32;3],value:[f32;3],stmt:&mut Statement,data_point_id:i32,legend_id:i32){
    if delta_frame {
        if (reference_value[0] - value[0]).abs() > f32::EPSILON 
        && (reference_value[1] - value[1]).abs() > f32::EPSILON 
        && (reference_value[2] - value[2]).abs() > f32::EPSILON {
            let _ = stmt.bind((1,data_point_id as i64));
            let _ = stmt.bind((2,legend_id as i64));
            let _ = stmt.bind((3,value[0] as f64));
            let _ = stmt.bind((4,value[1] as f64));
            let _ = stmt.bind((5,value[2] as f64));
            stmt.next().unwrap();
            stmt.reset().unwrap();
        }
    } else {
        let _ = stmt.bind((1,data_point_id as i64));
        let _ = stmt.bind((2,legend_id as i64));
        let _ = stmt.bind((3,value[0] as f64));
        let _ = stmt.bind((4,value[1] as f64));
        let _ = stmt.bind((5,value[2] as f64));
        stmt.next().unwrap();
        stmt.reset().unwrap();
    }
}