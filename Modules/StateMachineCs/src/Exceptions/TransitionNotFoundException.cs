using System;
namespace StateMachineCs{
    public class TransitionNotFoundException<T> : Exception{
        private T mTransitionTrigger;
        private uint mFrom;

        public TransitionNotFoundException(uint from,T data){
            this.mTransitionTrigger = data;
            this.mFrom = from;
        }
        public TransitionNotFoundException(uint from,T data,string message)
        :base(message){
            this.mTransitionTrigger = data;
            this.mFrom = from;
        }
        public TransitionNotFoundException(uint from,T data,string message,Exception innerException)
        :base(message,innerException){
            this.mTransitionTrigger = data;
            this.mFrom = from;
        }
        public string GetMessage(){
            return "Transition not Found. from:"+this.mFrom+"\n";
        }
    }
}