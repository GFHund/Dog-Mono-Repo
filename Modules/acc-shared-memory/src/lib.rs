use win_sys::{FileMapping,ViewOfFile,CreateFileMapping,MapViewOfFile,CloseHandle,INVALID_HANDLE_VALUE,PAGE_READWRITE,FILE_MAP_READ };
use std::error::Error;
//use crate::windo::core::error;
use std::mem::size_of;
use std::convert::TryFrom;
mod shared_file_out;
use shared_file_out::{SPageFilePhysics, SPageFileGraphic};

struct SMElement{
    map_file:FileMapping,
    view_of_file:ViewOfFile
}
pub struct AccSharedMemory{
    acc_physics:Option<SMElement>,
    acc_graphics:Option<SMElement>,
    acc_static:Option<SMElement>
}
impl AccSharedMemory{
    pub fn get_physics(&mut self)->SPageFilePhysics{
        if let None = self.acc_physics{
            //Fehler
        }
        let acc_physics = self.acc_physics.as_ref().unwrap();
        //let ret:Result<SPageFilePhysics,_> = acc_physics.view_of_file.try_into();
        unsafe{
            let a = acc_physics.view_of_file.as_mut_ptr() as *const SPageFilePhysics;
            let b = (*a).clone();
            return b;
        };  
    }
    pub fn get_graphics(&mut self) -> SPageFileGraphic{
        if let None = self.acc_physics{
            //Fehler
        }
        let acc_graphics = self.acc_graphics.as_ref().unwrap();
        unsafe{
            let a = acc_graphics.view_of_file.as_mut_ptr() as *const SPageFileGraphic;
            let b = (*a).clone();
            return b;
        };
    }
    pub fn dismiss(&mut self)->Result<(),String>{
        let mut bError = false;
        if let Some(physics) = &mut self.acc_physics{
            let error = CloseHandle(physics.map_file.as_handle());
            if let Err(e) = error{
                bError = true;
            }
        }
        if let Some(graphics) = &mut self.acc_graphics{
            let error = CloseHandle(graphics.map_file.as_handle());
            if let Err(e) = error{
                bError = true;
            }
        }
        if let Some(acc_static) = &mut self.acc_static{
            let error = CloseHandle(acc_static.map_file.as_handle());
            if let Err(e) = error{
                bError = true;
            }
        }
        if bError{
            return Err("Error at Close Handle".to_string());
        }
        Ok(())
    }
}
/*
establish a connection to the shared memory of Assetto Corsa Competizione. if one of the choosen connection failed the function returns an error
*/
pub fn init(init_physics:bool,init_graphics:bool,init_static:bool)->Result<AccSharedMemory,String>{
    let mut ret = AccSharedMemory{acc_graphics:None,acc_physics:None,acc_static:None};
    //init physics
    if init_physics {
        let result = init_shared_memory("Local\\acpmf_physics".to_string());
        if let Ok(element) = result{
            ret.acc_physics = Option::Some(element);
        } else {
            return Err("Physics could not established".to_string());
        }
    }
    if init_graphics{
        let result = init_shared_memory("Local\\acpmf_graphics".to_string());
        if let Ok(element) = result{
            ret.acc_graphics = Option::Some(element);
        } else {
            return Err("Graphics could not established".to_string());
        }
    }
    if init_static {
        let result = init_shared_memory("Local\\acpmf_static".to_string());
        if let Ok(element) = result {
            ret.acc_static = Some(element);
        } else {
            return Err("Static could not established".to_string());
        }
    }
    
    Ok(ret)
}
fn init_shared_memory(sz_name:String)->Result<SMElement,String>{
    //let sz_name = "Local\\acpmf_physics".to_string();
    let size = size_of::<SPageFilePhysics>();
    let size_int = u32::try_from(size).unwrap();
    let create_result = CreateFileMapping(INVALID_HANDLE_VALUE, 
        None, 
        PAGE_READWRITE, 
        0, 
        size_int, 
        sz_name);
    if let Err(error) = create_result{
        return Err("CreateFileMapping failed".to_string());
    }
    let create_file_mapping = create_result.unwrap();
    let map_file_buffer_result = MapViewOfFile(
        create_file_mapping.as_handle(), 
        FILE_MAP_READ, 
        0, 
        0, 
        size);
    if let Err(error) = map_file_buffer_result{
        return Err("MapViewOfFile failed".to_string());
    }
    let map_file_buffer = map_file_buffer_result.unwrap();
    let ret = SMElement{map_file:create_file_mapping,view_of_file:map_file_buffer};
    return Ok(ret);
}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        let result = 2 + 2;
        assert_eq!(result, 4);
    }
}
