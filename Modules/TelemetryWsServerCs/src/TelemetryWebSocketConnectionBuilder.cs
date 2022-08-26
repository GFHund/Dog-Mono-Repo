using System;
using System.Net.Sockets;

namespace TelemetryWsServerCs{
    class TelemetryWebSocketConnectionBuilder:AbstractWebSocketConnectionBuilder{
        public override AbstractWebSocketConnection build(TcpClient client){
            return new TelemetryWebSocketConnection(client);
        }
    }
}