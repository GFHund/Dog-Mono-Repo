using System;
namespace TelemetryWsServerCs{
    class ConvertWebsocketMessageException: Exception{
        public ConvertWebsocketMessageException(){
        }
        public ConvertWebsocketMessageException(string message)
        : base(message){
            
        }
        public ConvertWebsocketMessageException(string message,Exception inner)
        :base(message,inner){
            
        }
    }
}