import { EventManager } from '../EventManager';
import { FileOpenEvent } from '../FileOpenEvent';
import { AbstractPluginClass } from "../AbstractPluginClass";
import { open } from '@tauri-apps/api/dialog';

export class FileOpenBtnPlugin extends AbstractPluginClass{
    protected fileOpenElement: HTMLInputElement;

    init(): void {
        /*
        let fileOpenElement = document.createElement('input');
        fileOpenElement.type = 'file';
        fileOpenElement.style.display = 'none';
        fileOpenElement.classList.add('hidden-file-open-input');
        fileOpenElement.addEventListener('change',this.onFileChanged.bind(this));
        this.fileOpenElement = fileOpenElement;
        this.el.parentElement?.appendChild(fileOpenElement);
        */
        this.el.addEventListener('click',this.onBtnClick.bind(this));
    }

    onBtnClick(evt:Event){
        /*
        let inputElement = this.fileOpenElement;
        if(inputElement){
            inputElement.click();
        }
        */
        open({title:'File Open Dialog'}).then((path) => {
            if(path == null){
                return;
            }
            if(typeof path === 'string' || path instanceof String){
                let fileOpenEvent = new FileOpenEvent(path);
                let eventName = this.el.dataset.event;
                if(eventName){
                    EventManager.getInstance().dispatch(eventName,fileOpenEvent);
                }
                else {
                    console.error('Event Name not defined');
                }
            }
        });
    }

    onFileChanged(evt:Event){
        let url = this.fileOpenElement.value;
        let fileOpenEvent = new FileOpenEvent(url);
        EventManager.getInstance().dispatch('FILE_OPEN_EVENT',fileOpenEvent);
    }
}