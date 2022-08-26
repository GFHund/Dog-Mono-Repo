import { PluginManager } from './../PluginManager';
import { AbstractPluginClass } from "../AbstractPluginClass";
import { EventManager } from "../EventManager";

export class ConnectionIndicatorPlugin extends AbstractPluginClass{
    protected isConnected = false;
    init(): void {
        this.el.addEventListener('click',this.onClick.bind(this));
        EventManager.getInstance().subscribe('WEBSOCKET_CONNECTED',this.onWebserverConnected.bind(this));
        EventManager.getInstance().subscribe('WEBSOCKET_DISCONNECTED',this.onWebserverDisconnected.bind(this));
        let menuEntry = this.el.querySelector('.telemetry-connection-menu li');
        if(menuEntry){
            menuEntry.addEventListener('click',this.onClickMenuEntry.bind(this));
        }
    }

    onClick(evt:Event){
        let menu = this.el.querySelector('.telemetry-connection-menu');
        menu?.classList.toggle('telemetry-connection-menu-open');
    }
    onClickMenuEntry(evt:Event){
        console.log('On Click Menu Entry');
        if(this.isConnected){
            EventManager.getInstance().dispatch('WEBSOCKET_DISCONNECT');
        } else {
            EventManager.getInstance().dispatch('WEBSOCKET_CONNECT');
        }
        
    }
    onWebserverConnected(){
        let indicator = this.el.querySelector('.telemetry-connection-indicator');
        indicator?.classList.add('telemetry-backend-connected');
        this.isConnected = true;
        let menuEntry = this.el.querySelector('telemetry-connection-menu li');
    }
    onWebserverDisconnected(){
        let indicator = this.el.querySelector('.telemetry-connection-indicator');
        indicator?.classList.remove('telemetry-backend-connected');
        this.isConnected = false;
        let menuEntry = this.el.querySelector('telemetry-connection-menu li');
    }
}