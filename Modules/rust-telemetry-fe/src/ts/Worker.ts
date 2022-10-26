//export {};
let ws:WebSocket;
onmessage = function(ev:MessageEvent){
    console.log("Message recived");
    console.log(ev.data);
    if(ev.data.type == "FileOpen"){
        console.log(ev.data.url);
        ws.send(ev.data.url);
    }
    if(ev.data.type == 'getConverterOptions'){
        ws.send('CONVERT OPTIONS '+ev.data.file);
    }
    if(ev.data.type === "WebsocketOpen"){
        ws = new WebSocket("ws://127.0.0.1:8080");
        ws.onerror = (evt) => {
            console.error(evt);
        };
        ws.onclose = (evt) => {
            console.log("close Connection");
            console.log(evt);
            this.postMessage({type:'websocket-close'})
        }
        ws.onmessage = (evt:MessageEvent) => {
            let obj = JSON.parse(evt.data);
            if(obj.type == 'convertOptions'){
                this.postMessage({type:'convertOptions',data:obj.data});
            }
            console.log(evt.data);
        }
        ws.onopen = (evt:Event)=> {
            this.postMessage({type:'websocket-open'})
        }
    }
    if(ev.data.type === 'WebsocketClose'){
        ws.close();
    }
    if(ev.data.type === 'test'){
        console.log("call test");
        ws.send("CONVERT OPTIONS D:\\Projekte\\ABC.sqlite;");
    }
}