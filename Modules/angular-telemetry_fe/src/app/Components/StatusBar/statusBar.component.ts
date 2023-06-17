import { ElementRef } from '@angular/core';
import { ViewChild } from '@angular/core';
import { WebsocketService } from './../../Service/Websocket/websocket.service';
import {Component} from '@angular/core';
import { environment } from 'src/environments/environment';
@Component({
    selector:'app-status-bar',
    templateUrl: './statusBar.component.html',
    styleUrls:['./statusBar.component.scss']
})
export class StatusBar{

    showMenu = false;
    isConnected = false;
    buttonValue = 'Connect';
    constructor(public websocketService:WebsocketService){}

    onStatusIndicatorClick(){
        this.showMenu = !this.showMenu;
    }
    onConnectClick(){
        console.log('Connect to Server');
        let isConnected = this.websocketService.isConnected();
        if(isConnected){
            console.log('is mit Server verbunden');
            this.websocketService.close();
            this.buttonValue = 'Connect'
            this.isConnected = false;
        } else {
            //console.log('is nicht mit server verbunden');
            this.websocketService.connect(environment.websocketTarget).subscribe(() => {
                this.isConnected = true;
                this.buttonValue = 'Close';
                this.websocketService.getObserver().subscribe(this.updateStatus);
            });
        }
        this.showMenu = !this.showMenu;
    }
    updateStatus(){

    }
}