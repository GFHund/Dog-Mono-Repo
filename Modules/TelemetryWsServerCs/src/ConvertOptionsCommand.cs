namespace TelemetryWsServerCs{
    class ConvertOptionsCommand:AbstractCommand{

        public string file1{set;get;}
        public override COMMAND_TYPE getCommandType(){
            return COMMAND_TYPE.GET_CONVERT_OPTIONS;
        }
        public ConvertOptionsCommand(){
            this.file1 = "";
        }
    }
}