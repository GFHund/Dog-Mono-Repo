using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Collections.Generic;

namespace TelemetryWsServerCs{
    class WebSocket{//<T> where T:AbstractWebSocketConnection{
        protected TcpListener mServer;
        protected bool mRun = true;
        protected AbstractWebSocketConnectionBuilder mConnectionBuilder;
        public WebSocket(AbstractWebSocketConnectionBuilder builder){
            this.mConnectionBuilder = builder;
        }

        public void init(){
            mServer = new TcpListener(IPAddress.Parse("127.0.0.1"),80);
            mServer.Start();
            
        }
        public void listen(){
            List<Thread> threads = new List<Thread>();
            while(mRun){
                TcpClient client = mServer.AcceptTcpClient();
                var th = new Thread(handleWebsocket);
                th.Start(client);
                threads.Add(th);
            }
        }
        public void handleWebsocket(object obj){
            TcpClient client = (TcpClient) obj;
            
            //T connection = T.createNew(client);
            AbstractWebSocketConnection connection = this.mConnectionBuilder.build(client);
            NetworkStream stream = client.GetStream();
            while(true){
                connection.handleIncomingMessage();
                /*
                while(!stream.DataAvailable);
                while(client.Available < 3){
                    //
                }
                */
                /*
                Byte[] bytes = new Byte[client.Available];
                stream.Read(bytes,0,bytes.Length);
                String data = Encoding.UTF8.GetString(bytes);
                if(Regex.IsMatch(data,"^GET",RegexOptions.IgnoreCase)){
                    string swk = Regex.Match(data,"Sec-WebSocket-Key:(.*)").Groups[1].Value.Trim();
                    string swka = swk + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
                    byte[] swkaSha1 = System.Security.Cryptography.SHA1.Create().ComputeHash(Encoding.UTF8.GetBytes(swka));
                    string swkaSha1Base64 = Convert.ToBase64String(swkaSha1);
                    byte[] response = Encoding.UTF8.GetBytes(
                        "HTTP/1.1 101 Switching Protocols\r\n"+
                        "Connection: Upgrade\r\n"+
                        "Upgrade: websocket\r\n"+
                        "Sec-WebSocket-Accept:" + swkaSha1Base64 +"\r\n\r\n" 
                    );
                    stream.Write(response,0,response.Length);
                } else {
                    bool fin = (bytes[0] & 0b10000000) != 0,
                    mask = (bytes[1] & 0b10000000) != 0;
                    int opcode = bytes[0] & 0b00001111, offset = 2;
                    ulong msglen = (ulong)(bytes[1] & 0b01111111);
                    if(msglen == 126){
                        msglen = BitConverter.ToUInt16(new byte[]{bytes[3],bytes[2]},0);
                        offset = 4;

                    } else if(msglen == 127){
                        msglen = BitConverter.ToUInt64(new byte[]{bytes[9],bytes[8],bytes[7],bytes[6],bytes[5],bytes[4],bytes[3],bytes[2]},0);
                        offset = 10;
                    }
                    if(msglen == 0){
                        Console.WriteLine("msglen == 0");
                    } else if(mask){
                        byte[] decode = new byte[msglen];
                        byte[] masks = new byte[4] {bytes[offset],bytes[offset+1],bytes[offset+2],bytes[offset+3]};
                        offset += 4;
                        for(ulong i = 0;i< msglen ;++i){
                            decode[i] = (byte)(bytes[((ulong)offset) +i] ^ masks[i%4]);
                        }
                        string text = Encoding.UTF8.GetString(decode);
                        Console.WriteLine(text);
                    } else {
                        Console.WriteLine("maks Bit not set");
                    }
                    Console.WriteLine();
                    /*
                    byte[] response = Encoding.UTF8.GetBytes("Hallo Welt");
                    Console.WriteLine(data);
                    for(int i = 0;i< bytes.Length;i++){
                        Console.WriteLine(bytes[i]);
                    }
                    stream.Write(response,0,response.Length);
                    */
                //}
            }
        }
    }
    
}