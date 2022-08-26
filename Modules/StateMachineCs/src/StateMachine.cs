using System;
using System.Collections.Generic;

namespace StateMachineCs
{
    public class StateMachine<T>
    {
        //private List<EmptyState> mInstanciatedStates;
        private List<StateMachineStateInterface> mStates = new List<StateMachineStateInterface>();
        private List<Transition<T>> mTransitions = new List<Transition<T>>();
        private uint mCurrentStateId;
        private uint mIdCounter;
        
        public StateMachine(){
            this.mIdCounter = 0;
            this.mCurrentStateId = 0;
        }
        
        public uint addState(){
            EmptyState es = new EmptyState();
            uint id = mIdCounter;
            mIdCounter++;
            es.setStateMachineId(id);
            this.mStates.Add(es);
            return id;
        }
        public uint addState(StateMachineStateInterface newState){
            uint id = mIdCounter;
            mIdCounter++;
            newState.setStateMachineId(id);
            mStates.Add(newState);
            return id;
        }
        
        
        public StateMachineStateInterface getState(uint id){
            foreach(var state in mStates) {
                if(state.getStateMachineId() == id){
                    return state;
                }
            }
            throw new StateNotFoundException(id);
        }
        
        
        public uint getCurrentStateId(){
            return this.mCurrentStateId;
        }
        
        public StateMachineStateInterface getCurrentStateData(){
            //this.mCurrentStateId++;
            return this.getState(this.mCurrentStateId);
        }
        
        public void addTransition(uint fromState,uint toState,Func<T,bool> trigger,Action<T> transition){
            this.mTransitions.Add(new Transition<T>(fromState,toState,trigger,transition));
        }
        
        
        public void updateCurrentState(){
            StateMachineStateInterface currentState = this.getCurrentStateData();
            currentState.updateState();
        }

        public void transition(T data){
            foreach(var transition in this.mTransitions){
                if(transition.getFrom() == this.mCurrentStateId){
                    if(transition.callTrigger(data)){
                        StateMachineStateInterface state = this.getCurrentStateData();
                        state.leaveState();
                        Console.WriteLine("FromState:"+mCurrentStateId);
                        mCurrentStateId = transition.getTo();
                        Console.WriteLine("ToState:"+mCurrentStateId);
                        state = this.getCurrentStateData();
                        transition.callTransition(data);
                        state.enterState();
                        return;
                    }
                }
            }
            throw new TransitionNotFoundException<T>(mCurrentStateId,data,"Transition not Found. from:"+mCurrentStateId+"\n");
        }
        
    }
}
