using System;
using System.Net.Sockets;
using System.Text;
using System.Text.RegularExpressions;
using System.Collections.Generic;
using System.Security.Cryptography;

namespace TelemetryWsServerCs{
    abstract class AbstractWebSocketConnection{ 
        protected TcpClient mClient;
        public AbstractWebSocketConnection(TcpClient client){
            this.mClient = client;
        }
        /*
        public static AbstractWebSocketConnection createNew(TcpClient client){
            return new AbstractWebSocketConnection(client);
        }
        */

        public void handleIncomingMessage(){
            NetworkStream stream = this.mClient.GetStream();
            while(!stream.DataAvailable);
            while(this.mClient.Available < 3){
                //
            }
            byte[] bytes = new byte[this.mClient.Available];
            stream.Read(bytes,0,bytes.Length);
            string data = Encoding.UTF8.GetString(bytes);
            if(Regex.IsMatch(data,"^GET",RegexOptions.IgnoreCase)){
                this.handleHandshake(stream,data);
            } else {
                this.reciveMessage(bytes);
                /*
                byte[] response = Encoding.UTF8.GetBytes("Hallo Welt");
                Console.WriteLine(data);
                for(int i = 0;i< bytes.Length;i++){
                    Console.WriteLine(bytes[i]);
                }
                stream.Write(response,0,response.Length);
                */
            }
        }
        protected abstract void reciveMessage(byte[] incomingByte);

        public void handleHandshake(NetworkStream stream,string data){
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
        }
        public string convertIncomingMessageToString(byte[] bytes){
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
                //Console.WriteLine("msglen == 0");
                throw new ConvertWebsocketMessageException("msglen == 0");
            } else if(mask){
                byte[] decode = new byte[msglen];
                byte[] masks = new byte[4] {bytes[offset],bytes[offset+1],bytes[offset+2],bytes[offset+3]};
                offset += 4;
                for(ulong i = 0;i< msglen ;++i){
                    decode[i] = (byte)(bytes[((ulong)offset) +i] ^ masks[i%4]);
                }
                string text = Encoding.UTF8.GetString(decode);
                //Console.WriteLine(text);
                return text;
            } else {
                //Console.WriteLine("maks Bit not set");
                throw new ConvertWebsocketMessageException("maks Bit not set");
            }
            //Console.WriteLine();
        }
        public void sendString(string message,bool mask = false){
            byte firstByte = 0b10000001;
            List<byte> sendingByte = new List<byte>();
            sendingByte.Add(firstByte);
            int messageLength = message.Length;
            byte secondByte = (byte)messageLength;
            if(messageLength > 125 && messageLength < UInt16.MaxValue){
                secondByte = 126;   
            } else if(messageLength > UInt16.MaxValue){
                secondByte = 127;
            }
            if(mask){
                Console.WriteLine("SecondByte beforeMask:"+secondByte);
                
                secondByte = (byte)(secondByte | 0b10000000);
                Console.WriteLine("SecondByte afterMask:"+secondByte);
            }
            
            sendingByte.Add(secondByte);
            if(secondByte == 126){
                sendingByte.Add((byte)(messageLength >> 8));
                sendingByte.Add((byte)(messageLength & 0x000F));
            } else if(secondByte == 127) {
                sendingByte.Add((byte)(messageLength >> 24));
                sendingByte.Add((byte)(messageLength >> 16));
                sendingByte.Add((byte)(messageLength >> 8));
                sendingByte.Add((byte)(messageLength & 0x000F));
            }
            byte[] rngNumberByte = {0,0,0,0};
            if(mask){
                RandomNumberGenerator gen = RandomNumberGenerator.Create();
                gen.GetBytes(rngNumberByte);
                //int rngNumber = RandomNumberGenerator.GetInt32(Int32.MaxValue);
                //BinaryPrimitives ???
                //rngNumberByte = BitConverter.GetBytes(rngNumber);
                for(int i = 0;i< rngNumberByte.Length;i++){
                    sendingByte.Add(rngNumberByte[i]);
                }
            }
            byte[] stringByteArr = Encoding.UTF8.GetBytes(message);
            for(int i = 0;i < stringByteArr.Length;i++){
                byte b = stringByteArr[i];
                if(mask){
                    b = (byte)(b ^ rngNumberByte[i%4]);
                }
                sendingByte.Add(b);
            }

            byte[] sendingByteArray = sendingByte.ToArray();
            /*
            Console.WriteLine("send:");
            for(int i=0;i<sendingByteArray.Length;i++){
                Console.WriteLine(sendingByteArray[i]);
            }
            */
            NetworkStream stream = this.mClient.GetStream();
            stream.Write(sendingByteArray,0,sendingByteArray.Length);
            
        }
    }
}