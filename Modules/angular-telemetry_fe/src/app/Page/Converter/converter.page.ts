import {Component} from '@angular/core';
import { open } from '@tauri-apps/api/dialog';
import { WebsocketService } from 'src/app/Service/Websocket/websocket.service';

@Component({
    selector:'app-converter',
    templateUrl:'./converter.page.html'
})
export class Converter{
    sourceFile:string|string[] = '';

    constructor(public websocketService:WebsocketService){}

    onChooseSourceFile(){
        open({title:'File Open Dialog'}).then((path) => {
            if(path == null){
                return;
            }
            if(typeof path === 'string' || path instanceof String){
                this.sourceFile = path;
                this.websocketService.send(this.sourceFile as string);
            }
        });
    }
}