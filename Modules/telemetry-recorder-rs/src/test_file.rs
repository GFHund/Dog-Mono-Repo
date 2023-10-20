use sqlite3_sys;
use std::ffi::CString;
use libc::{c_char, c_int};

pub fn create_test_file(output:&String,laps:i32,data_per_lap:i32){
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
    (1,\"sin\",\"data_point_float_value\"),
    (2,\"cosine\",\"data_point_float_value\"),
    (3,\"rectangle\",\"data_point_float_value\"),
    (4,\"linear1\",\"data_point_int_value\"),
    (5,\"linear2\",\"data_point_int_value\");").unwrap();
    let mut prepare_data_point_insert_stmt = db.prepare("INSERT INTO data_point(type, lap, time_in_ms) VALUES (?,?,?)").unwrap();
    let mut prepare_data_point_float_insert_stmt = db.prepare("INSERT INTO data_point_float_value(data_point_id,legend_id,value) VALUES (?,?,?)").unwrap();
    let mut prepare_data_point_int_insert_stmt = db.prepare("INSERT INTO data_point_int_value(data_point_id,legend_id,value) VALUES (?,?,?)").unwrap();
    let mut _prepare_data_point_vec3_insert_stmt = db.prepare("INSERT INTO data_point_vec3_value(data_point_id,legend_id,value_x,value_y,value_z) VALUES (?,?,?,?,?)").unwrap();
    let mut last_sin_value = 0.0;
    let mut last_cos_value = 0.0;
    let mut last_rectangle_value = 0;
    let mut last_linear_value = 0;
    let mut last_linear2_value = 0;
    let mut counter = 0;
    let full_counter = 20;
    let mut delta_frame:bool;
    for lap_counter in 0..laps{
        let sin_offset = fastrand::f32() * 2.0 - 1.0;
        let cos_offset = fastrand::f32() * 2.0 - 1.0;
        let rectangle_offset = fastrand::i32(0..6);
        let linear_value = fastrand::i32(0..6);
        let linear2_value = fastrand::i32(0..100);
        for data_point_counter in 0..data_per_lap{
            //print!("counter: {}\n",counter);
            //print!("lap_counter: {}\n",lap_counter);
            //print!("data_point_counter: {}\n",data_point_counter);
            if counter > full_counter{
                let _ = prepare_data_point_insert_stmt.bind((1,1));
                counter = 0;
                delta_frame = false;
            } else {
                let _ = prepare_data_point_insert_stmt.bind((1,0));
                counter += 1;
                delta_frame = true;
            }
            
            
            let _ = prepare_data_point_insert_stmt.bind((2,lap_counter as i64));
            let _ = prepare_data_point_insert_stmt.bind((3,data_point_counter as f64));
            prepare_data_point_insert_stmt.next().unwrap();
            prepare_data_point_insert_stmt.reset().unwrap();

            let mut insert_id = 0;
            let _id = db.iterate("SELECT last_insert_rowid();", |row|->bool{
                let insert_id_str = row[0].1.unwrap();
                //println!("Result insert Id Str:{}",insert_id_str);
                insert_id = insert_id_str.parse::<i32>().unwrap();
                return false;
            });
            //println!("insert_id: {}",insert_id);
            let sin_value = ((data_point_counter/100) as f32).sin() + sin_offset;
            let cos_value = ((data_point_counter/100) as f32).cos()+cos_offset;
            let mut rectangle_value = if (data_point_counter/10) as i32 %2 == 0 {0} else {1};
            rectangle_value += rectangle_offset;

            if delta_frame{
                if (sin_value-last_sin_value).abs() > f32::MIN_POSITIVE{
                    let _ = prepare_data_point_float_insert_stmt.bind((1,insert_id as i64));
                    let _ = prepare_data_point_float_insert_stmt.bind((2,1));
                    let _ = prepare_data_point_float_insert_stmt.bind((3,sin_value as f64));
                    prepare_data_point_float_insert_stmt.next().unwrap();
                    prepare_data_point_float_insert_stmt.reset().unwrap();
                }
            } else {
                let _ = prepare_data_point_float_insert_stmt.bind((1,insert_id as i64));
                    let _ = prepare_data_point_float_insert_stmt.bind((2,1));
                    let _ = prepare_data_point_float_insert_stmt.bind((3,sin_value as f64));
                    prepare_data_point_float_insert_stmt.next().unwrap();
                    prepare_data_point_float_insert_stmt.reset().unwrap();
            }
            last_sin_value = sin_value;

            if delta_frame {
                if (cos_value-last_cos_value).abs() > f32::MIN_POSITIVE {
                    let _ = prepare_data_point_float_insert_stmt.bind((1,insert_id as i64));
                    let _ = prepare_data_point_float_insert_stmt.bind((2,2));
                    let _ = prepare_data_point_float_insert_stmt.bind((3,cos_value as f64));
                    prepare_data_point_float_insert_stmt.next().unwrap();
                    prepare_data_point_float_insert_stmt.reset().unwrap();
                }
            } else {
                let _ = prepare_data_point_float_insert_stmt.bind((1,insert_id as i64));
                let _ = prepare_data_point_float_insert_stmt.bind((2,2));
                let _ = prepare_data_point_float_insert_stmt.bind((3,cos_value as f64));
                prepare_data_point_float_insert_stmt.next().unwrap();
                prepare_data_point_float_insert_stmt.reset().unwrap();
            }
            last_cos_value = cos_value;

            if delta_frame{
                if rectangle_value != last_rectangle_value{
                    let _ = prepare_data_point_float_insert_stmt.bind((1,insert_id as i64));
                    let _ = prepare_data_point_float_insert_stmt.bind((2,3));
                    let _ = prepare_data_point_float_insert_stmt.bind((3,rectangle_value as i64));
                    prepare_data_point_float_insert_stmt.next().unwrap();
                    prepare_data_point_float_insert_stmt.reset().unwrap();
                }
            } else {
                let _ = prepare_data_point_float_insert_stmt.bind((1,insert_id as i64));
                let _ = prepare_data_point_float_insert_stmt.bind((2,3));
                let _ = prepare_data_point_float_insert_stmt.bind((3,rectangle_value as i64));
                prepare_data_point_float_insert_stmt.next().unwrap();
                prepare_data_point_float_insert_stmt.reset().unwrap();
            }
            last_rectangle_value = rectangle_value;
            
            if delta_frame{
                if last_linear_value != linear_value {
                    let _ = prepare_data_point_int_insert_stmt.bind((1,insert_id as i64));
                    let _ = prepare_data_point_int_insert_stmt.bind((2,4));
                    let _ = prepare_data_point_int_insert_stmt.bind((3,linear_value as f64));
                    prepare_data_point_int_insert_stmt.next().unwrap();
                    prepare_data_point_int_insert_stmt.reset().unwrap();
                }
            } else {
                let _ = prepare_data_point_int_insert_stmt.bind((1,insert_id as i64));
                let _ = prepare_data_point_int_insert_stmt.bind((2,4));
                let _ = prepare_data_point_int_insert_stmt.bind((3,linear_value as f64));
                prepare_data_point_int_insert_stmt.next().unwrap();
                prepare_data_point_int_insert_stmt.reset().unwrap();
            }
            last_linear_value = linear_value;

            if delta_frame{
                if last_linear2_value != linear2_value {
                    let _ = prepare_data_point_int_insert_stmt.bind((1,insert_id as i64));
                    let _ = prepare_data_point_int_insert_stmt.bind((2,5));
                    let _ = prepare_data_point_int_insert_stmt.bind((3,linear2_value as f64));
                    prepare_data_point_int_insert_stmt.next().unwrap();
                    prepare_data_point_int_insert_stmt.reset().unwrap();
                }
            } else {
                let _ = prepare_data_point_int_insert_stmt.bind((1,insert_id as i64));
                let _ = prepare_data_point_int_insert_stmt.bind((2,5));
                let _ = prepare_data_point_int_insert_stmt.bind((3,linear2_value as f64));
                prepare_data_point_int_insert_stmt.next().unwrap();
                prepare_data_point_int_insert_stmt.reset().unwrap();
            }
            last_linear2_value = linear2_value;
            
        }
    }

    let name = "main";
    let c_str = CString::new(name).unwrap();
    let main: *const c_char = c_str.as_ptr() as *const c_char;
    let target_db = sqlite::open(output).unwrap();
    let mut rc: c_int = 0;
    unsafe {
        let backup = sqlite3_sys::sqlite3_backup_init(target_db.as_raw(), main, db.as_raw(), main);
        sqlite3_sys::sqlite3_backup_step(backup, -1);
        sqlite3_sys::sqlite3_backup_finish(backup);
        /*
        loop {
            rc = sqlite3_sys::sqlite3_backup_step(backup, 100);
            if rc == sqlite3_sys::SQLITE_OK || rc == sqlite3_sys::SQLITE_BUSY || rc == sqlite3_sys::SQLITE_LOCKED {
                sqlite3_sys::sqlite3_sleep(250);
            } else {
                break;
            }
        }
         */
    }
    
    
}