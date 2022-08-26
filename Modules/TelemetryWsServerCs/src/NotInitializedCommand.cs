namespace TelemetryWsServerCs{
    class NotInitializedCommand: AbstractCommand{
        public override COMMAND_TYPE getCommandType(){
            return COMMAND_TYPE.NOT_INITIALIZED;
        }
    }
}