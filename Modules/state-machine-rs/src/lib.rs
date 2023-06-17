pub trait State{
    fn enter_state(&self);
    fn leave_state(&self);
    fn update_state(&self);
    fn set_state_machine_id(&mut self,id:u32);
    fn get_state_machine_id(&self) -> u32;
}

struct EmptyState {
    state_machine_id:u32
}
impl EmptyState{
    fn new(id:u32)->EmptyState{
        Self {
            state_machine_id: id
        }
    }
}
impl State for EmptyState{
    fn enter_state(&self) {
        
    }
    fn leave_state(&self) {
        
    }
    fn update_state(&self) {
        
    }
    fn set_state_machine_id(&mut self,id:u32) {
        self.state_machine_id = id;
    }
    fn get_state_machine_id(&self)->u32 {
        self.state_machine_id
    }
}

pub struct SimpleState<T>{
    state_machine_id:u32,
    value:T
}
impl<T> SimpleState<T>{
    pub fn new(id:u32,value:T)->SimpleState<T>{
        Self {
            value: value,
            state_machine_id: id
        }
    }
    pub fn set_value(&mut self,value:T){
        self.value = value;
    }
    pub fn get_value(&self)->&T{
        &self.value
    }
    pub fn get_value_as_mut(&mut self)->&mut T{
        &mut self.value
    }
}
impl<T> State for SimpleState<T>{
    fn enter_state(&self) {
        
    }
    fn get_state_machine_id(&self) -> u32 {
        self.state_machine_id
    }
    fn leave_state(&self) {
        
    }
    fn set_state_machine_id(&mut self,id:u32) {
        self.state_machine_id = id;
    }
    fn update_state(&self) {
        
    }
}
struct Transition<T>{
    from_id:u32,
    to_id:u32,
    trigger: Box<dyn Fn(&T,&Vec<T>)->bool>,
    transition: Box<dyn Fn(&T,&mut Vec<T>)>
}
impl<T> Transition<T>{
    fn get_from(&self)->u32{
        return self.from_id;
    }
    fn get_to(&self)->u32{
        return self.to_id;
    }
    fn call_trigger(&self, data: &T,buffer:&Vec<T>)->bool{
        return (self.trigger)(data,buffer);
    }
    fn call_transition(&self,data: &T,buffer:&mut Vec<T>){
        (self.transition)(data,buffer);
    }
}

#[derive(Debug)]
pub enum StateMachineError {
    StateNotFound,
    TransitionNotFound
}

pub struct StateMachine<T:Clone>{
    states:Vec<Box<dyn State>>,
    transitions:Vec<Transition<T>>,
    current_state_id:u32,
    id_counter:u32,
    buffer: Vec<T>
}
impl<T:Clone> StateMachine<T>{
    pub fn new()->StateMachine<T>{
        Self {
            states : Vec::new(),
            transitions: Vec::new(),
            current_state_id: 0,
            id_counter: 0,
            buffer: Vec::new()
        }
    }
    /*
    fn addState(&mut self)->i32{
        //
    }*/

    pub fn add_state(&mut self,data:Option<Box<dyn State>>)->u32{
        let id = self.id_counter;
        self.id_counter += 1;
        if data.is_some() {
            let mut real_data = data.unwrap();
            real_data.set_state_machine_id(id);
            self.states.push(real_data);
        } else {
            self.states.push(Box::new(EmptyState::new(id)));
        }
        return id;
    }
    
    pub fn get_state(&self,id:u32)->Result<&Box<dyn State>,StateMachineError>{
        for state in &self.states{
            if state.get_state_machine_id() == id {
                return Ok(state);
            }
        }
        return Err(StateMachineError::StateNotFound);
    }
     
    pub fn get_current_state_id(&self)->u32{
        self.current_state_id
    }
    pub fn get_current_state_data(&self) -> Result<&Box<dyn State>,StateMachineError>{
        self.get_state(self.current_state_id)
    }
    pub fn add_transition(&mut self, from_state:u32,to_state:u32,trigger:Box<dyn Fn(&T,&Vec<T>)->bool>,transition: Box<dyn Fn(&T,&mut Vec<T>)>){
        self.transitions.push(Transition { from_id: from_state, to_id: to_state, trigger: trigger, transition: transition })
    }
    pub fn get_buffer(&self)->Vec<T>{
        self.buffer.clone()
    }
    pub fn transition(&mut self,data: &T)->Result<(),StateMachineError>{
        for transition in &self.transitions {
            if transition.get_from() == self.current_state_id {
                if transition.call_trigger(data,&self.buffer) {
                    match self.get_current_state_data() {
                        Ok(state) => {
                            state.leave_state();
                            self.current_state_id = transition.get_to();
                            self.buffer.push(data.clone());
                            transition.call_transition(data,&mut self.buffer);
                            let current_state_data = self.get_current_state_data();
                            if let Ok(state2) = current_state_data {
                                state2.enter_state();
                                return Ok(());
                            } else if let Err(error) = current_state_data {
                                return Err(error);
                            }
                        },
                        Err(error) => {
                            return Err(error);
                        }
                    }
                }
            }
        }
        return Err(StateMachineError::TransitionNotFound);
    }
    pub fn reset(&mut self){
        self.buffer.clear();
        self.current_state_id = 0;
    }
}

#[cfg(test)]
mod tests {
    use crate::{StateMachine, SimpleState, StateMachineError};

    #[test]
    fn constructor_test() {
        let sm: StateMachine<i32> = StateMachine::new();
        assert_eq!(sm.get_current_state_id(),0)
    }

    #[test]
    fn add_state_1(){
        let mut sm: StateMachine<i32> = StateMachine::new();
        let id = sm.add_state(None);
        let state_result = sm.get_state(id);
        let state = state_result.unwrap();
        assert_eq!(state.get_state_machine_id(),0)
    }
    #[test]
    fn add_state_2(){
        let mut sm: StateMachine<i32> = StateMachine::new();
        let test_state = SimpleState::new(0, 5);
        let id = sm.add_state(Some(Box::new(test_state)));
        let state_result = sm.get_state(id);
        let state = state_result.as_ref().unwrap();
        assert_eq!(state.get_state_machine_id(),0)
    }
    #[test]
    fn transition(){
        let mut sm: StateMachine<i32> = StateMachine::new();
        let state1 = SimpleState::new(0,3);
        let state2 = SimpleState::new(0, 6);
        let id1 = sm.add_state(Some(Box::new(state1)));
        let id2 = sm.add_state(Some(Box::new(state2)));
        sm.add_transition(id1, id2, Box::new(|i:&i32,_buffer|->bool{return (*i)==1;}), Box::new(|_i:&i32,_buffer|{}));
        sm.add_transition(id2,id1, Box::new(|i:&i32,_buffer|->bool{return (*i)==2;}), Box::new(|_i:&i32,_buffer|{}));
        match sm.transition(&1) {
            Err(err) => {
                match err {
                    StateMachineError::StateNotFound => assert!(false,"State Not Found"),
                    StateMachineError::TransitionNotFound => assert!(false,"Transition Not Found")
                }
            },
            Ok(_) => assert!(true)
        }
        assert_eq!(sm.get_current_state_id(),id2);
        match sm.transition(&2){
            Err(err) => {
                match err {
                    StateMachineError::StateNotFound => assert!(false,"State Not Found"),
                    StateMachineError::TransitionNotFound => assert!(false,"Transition Not Found")
                }
            },
            Ok(_) => assert!(true)
        }
        assert_eq!(sm.get_current_state_id(),id1);
    }
}
