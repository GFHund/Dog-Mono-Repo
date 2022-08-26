import { FileSaveEvent } from './../FileSaveEvent';
import { EventManager } from './../EventManager';
import { save } from "@tauri-apps/api/dialog";
import { AbstractPluginClass } from "../AbstractPluginClass";

export class FileSaveBtnPlugin extends AbstractPluginClass{
    init(): void {
        this.el.addEventListener('click',this.onBtnClick.bind(this));
    }

    onBtnClick(evt:Event){
        save({title:'Save File'}).then((value:string) =>{
            let eventName = this.el.dataset.event;
            let fileSaveEvent = new FileSaveEvent(value);
            if(eventName){
                EventManager.getInstance().dispatch(eventName,fileSaveEvent);
            }
            else {
                console.error('Event Name not defined');
            }
        });
    }
}