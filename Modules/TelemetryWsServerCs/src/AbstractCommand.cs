namespace TelemetryWsServerCs{
    abstract class AbstractCommand{

        public enum COMMAND_TYPE{
            OPEN_FILE,
            DRAW_DIAGRAM,
            GET_POINTS,
            CONVERT,
            GET_CONVERT_OPTIONS,
            QUIT,
            CLOSE_FILE,
            NOT_INITIALIZED
        };
        public abstract COMMAND_TYPE getCommandType();
    } 
}