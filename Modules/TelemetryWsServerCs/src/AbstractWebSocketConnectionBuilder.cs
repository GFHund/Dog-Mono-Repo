using System;
using System.Net.Sockets;

namespace TelemetryWsServerCs{
    abstract class AbstractWebSocketConnectionBuilder{
        public abstract AbstractWebSocketConnection build(TcpClient client);
    }
}