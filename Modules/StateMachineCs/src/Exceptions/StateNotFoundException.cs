using System;

namespace StateMachineCs{
    class StateNotFoundException:Exception{
        private uint mId{get;}
        public StateNotFoundException(uint id){
            this.mId = id;
        }
        public StateNotFoundException(uint id, string message)
        : base(message){
            this.mId = id;
        }
        public StateNotFoundException(uint id,string message,Exception inner)
        :base(message,inner){
            this.mId = id;
        }
        
    }
}