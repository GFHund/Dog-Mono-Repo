
use std::{thread, sync::mpsc};


use acc_shared_memory::{init};

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

pub fn record_start()->Result<(),String>{
    
    let(tx_db,rx_db) = mpsc::channel();
    let(tx_stop,rx_stop) = mpsc::channel();
    let(tx_db_stop,rx_db_stop) = mpsc::channel();
    
    let producer_thread = thread::spawn(move ||{
        let acc_result_obj = init(true,false,false);
        if let Err(error) = acc_result_obj{
            return;
        }
        let mut acc_obj = acc_result_obj.unwrap();
        let run = true;
        while run {
            let physics = acc_obj.get_physics();
            let graphics = acc_obj.get_graphics();
            let transmitData = TransmitAccTelemetry{
                lap:graphics.completed_laps,
                time:graphics.i_current_time,
                gas:physics.gas,
                brake:physics.brake,
                fuel:physics.fuel,
                gear:physics.gear,
                rpms:physics.rpms,
                steer_angle:physics.steer_angle,
                speed_kmh:physics.steer_angle,
                velocity:physics.velocity,
                acc_g:physics.acc_g
            };
            tx_db.send(transmitData.clone()).unwrap();
        
            run = rx_stop.recv().unwrap();
        }
        
    });
    let consumer_db_thread = thread::spawn(move ||{
        let db_result = sqlite::open(":memory:");
        if let Err(error) = db_result{
            return;
        }
        let db = db_result.unwrap();
        db.execute("CREATE TABLE data_point(id INTEGER PRIMARY KEY,type INTEGER,lap INTEGER,time_in_ms REAL)").unwrap();
        db.execute("CREATE TABLE data_point_int_value(data_point_id INTEGER,legend_id INTEGER,value INTEGER)").unwrap();
        db.execute("CREATE TABLE data_point_float_value(data_point_id INTEGER,legend_id INTEGER,value REAL)").unwrap();
        db.execute("CREATE TABLE data_point_vec3_value(data_point_id INTEGER,,legend_id INTEGERvalue_x REAL,value_y REAL,value_z REAL)").unwrap();
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
        let mut prepare_data_point_insert_stmt = db.prepare("INSERT INTO data_point(type,lap,time_in_ms) VALUE (?,?,?)").unwrap();
        let first = true;
        let counter = 0;
        let run = true;
        while run{
            let telemetry = rx_db.recv().unwrap();
            if first {
                let full_telemetry = telemetry.clone();
            }
            if counter == 0{
                //let sql = format!("INSERT INTO data_point(type,lap,time_in_ms) VALUE (1,{},{})",telemetry.lap,telemetry.time);
                //db.execute(sql).unwrap();
                prepare_data_point_insert_stmt.bind((1,1));
                prepare_data_point_insert_stmt.bind((2,telemetry.lap));
                prepare_data_point_insert_stmt.bind((3,telemetry.time));

            } else {
                //let sql = format!("INSERT INTO data_point(type,lap,time_in_ms) VALUE (2,{},{})",telemetry.lap,telemetry.time);
                //db.execute(sql).unwrap();
                prepare_data_point_insert_stmt.bind((2,telemetry.lap,telemetry.time));
            }
            prepare_data_point_insert_stmt.next().unwrap();
            let id = db.iterate("SELECT last_insert_rowid();", callback);

            
        }
    });
    
    return Ok(());
}
pub fn record_end(){

}