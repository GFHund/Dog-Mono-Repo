import {Injectable} from '@angular/core';
import {Observable} from 'rxjs';
@Injectable({
    providedIn:'root'
})
export class WebsocketService{
    ws:WebSocket|null =  null;
    messageObserver:Observable<string|undefined>|null = null;
    connected = false;
    
    connect(address:string){
        return new Observable<void>(subscriber => {
            this.ws = new WebSocket(address);
            this.ws.onopen = (evt:Event) => {
                subscriber.next();
                console.log('setze connected auf true');
                this.connected = true;
                this.messageObserver = new Observable<string|undefined>((subscriber) => {
                    if(this.ws){
                        this.ws.onmessage = (evt:MessageEvent) => {
                            subscriber.next(evt.data);
                        }
                        this.ws.onclose = (evt) => {
                            this.connected = false;
                            console.warn('Connection is closed');
                            subscriber.complete;
                        }
                        this.ws.onerror = (evt:Event) => {
                            console.error('Connection has Error');
                            console.error(evt);
                            subscriber.error(JSON.stringify(evt));
                        } 
                    }
                });
            }
        });
         
    }
    getObserver():Observable<string|undefined>{
        if(this.messageObserver){
            return this.messageObserver;
        }
        throw new Error('Websocket not initialized');
    }
    isConnected():boolean{
        return this.connected;
    }
    send(message:string){
        this.ws?.send(message);
    }
    close(){
        this.ws?.close();
    }
}