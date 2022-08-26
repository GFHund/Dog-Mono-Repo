namespace StateMachineCs
{
    public abstract class StateMachineStateInterface{
        protected uint mStateMachineId;
        public void setStateMachineId(uint id){
            this.mStateMachineId = id;
        }
        public uint getStateMachineId(){
            return this.mStateMachineId;
        }
        public abstract void enterState();
        public abstract void leaveState();
        public abstract void updateState();
    }
}