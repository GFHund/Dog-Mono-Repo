using System;

namespace StateMachineCs{
    public class Transition<T>{
        protected uint mFromId;
        protected uint mToId;
        protected Func<T,bool> mTrigger;
        protected Action<T> mTransition;

        public Transition(uint fromState,uint toState,Func<T,bool> trigger,Action<T> transition){
            this.mFromId = fromState;
            this.mToId = toState;
            this.mTrigger = trigger;
            this.mTransition = transition;
        }
        public uint getFrom(){
            return this.mFromId;
        }
        public uint getTo(){
            return this.mToId;
        }
        public bool callTrigger(T data){
            return this.mTrigger(data);
        }
        public void callTransition(T data){
            this.mTransition(data);
        }
    }
}