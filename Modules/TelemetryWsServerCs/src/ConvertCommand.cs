namespace TelemetryWsServerCs{
    class ConvertCommand:AbstractCommand{
        public string file1{set;get;}
        public string file2{set;get;}
        public string convertMethod{set;get;}
        public string convertConfig{set;get;}
        
        public ConvertCommand(){
            this.file1 = "";
            this.file2 = "";
            this.convertMethod = "";
            this.convertConfig = "";
        }

        public override COMMAND_TYPE getCommandType(){
            return COMMAND_TYPE.CONVERT;
        }
    } 
}