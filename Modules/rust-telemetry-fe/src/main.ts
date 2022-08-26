import { FileSaveBtnPlugin } from './ts/Plugins/FileSaveBtnPlugin';
import { FileDragDropPlugin } from './ts/FileDragDropPlugin';
import { FileOpenBtnPlugin } from './ts/Plugins/FileOpenBtnPlugin';
import { ConnectionIndicatorPlugin } from './ts/Plugins/ConnectionIndicatorPlugin';
import "./styles/base.scss";
import { PluginManager } from './ts/PluginManager';
import { BorderDragAndDropPlugin } from './ts/BorderDragAndDropPlugin';
import { TabElements } from './ts/TabElement';
import { IconElement } from './ts/IconElement';

import { EventManager } from './ts/EventManager';
import { FileOpenEvent } from './ts/FileOpenEvent';

(function(){
  let pluginManager = new PluginManager();
  pluginManager.register('telemetryWindow',BorderDragAndDropPlugin,'.telemetry-area-seperator');
  pluginManager.register('tabElements',TabElements,'.telemetry-areas');
  pluginManager.register('ConnectionIndicator',ConnectionIndicatorPlugin,'.telemetry-connection-indicator-container');
  pluginManager.register('fileOpenBtn',FileOpenBtnPlugin,'.file-open-btn');
  pluginManager.register('fileSaveBtn',FileSaveBtnPlugin,'.file-save-btn');

  customElements.define('icon-lazy-loader',IconElement);
})();
(function(){
  if(window.Worker){
    const webSocketWorker = new Worker(new URL('./ts/Worker.ts',import.meta.url));
    EventManager.getInstance().subscribe("FILE_OPEN_EVENT",(obj:FileOpenEvent) => {
        console.log(obj.getUrl());
        webSocketWorker.postMessage({type:"FileOpen",url:obj.getUrl()});
    });
    EventManager.getInstance().subscribe('CONVERTER-FILE-SOURCE',(obj:FileOpenEvent) => {
        let converterSource = document.querySelector<HTMLElement>('#converter-source-file');
        if(converterSource){
            converterSource.dataset.file = obj.getUrl();
        }
        webSocketWorker.postMessage({type:'getConverterOptions',file:obj.getUrl()});
    });
    EventManager.getInstance().subscribe('CONVERTER-FILE-TARGET',(obj:FileOpenEvent) => {
        let converterTarget = document.querySelector<HTMLElement>('#converter-target-file');
        if(converterTarget){
            converterTarget.dataset.file = obj.getUrl();
        }
        let converterStartBtn = document.querySelector<HTMLButtonElement>('#converter-start-btn');
        if(converterStartBtn){
            converterStartBtn.disabled = false;
        }
    });
    window.setTimeout(()=>{
        webSocketWorker.postMessage({type:"WebsocketOpen"})
    },1000);


    let testBtn = document.querySelector<HTMLElement>('#wsTest');
    if(testBtn){
        testBtn.addEventListener('click',(evt)=>{
            webSocketWorker.postMessage({type:"test"});
        });
    }

    webSocketWorker.onmessage = (evt:MessageEvent) => {
        if(evt.data.type){
            if(evt.data.type === 'websocket-close'){
                EventManager.getInstance().dispatch('WEBSOCKET_DISCONNECTED');
            }
            if(evt.data.type === 'websocket-open'){
                EventManager.getInstance().dispatch('WEBSOCKET_CONNECTED');
            }
            if(evt.data.type === 'convertOptions'){
                let converterSelect = document.querySelector<HTMLSelectElement>('#converter-selector');
                if(converterSelect){
                    converterSelect.removeAttribute('disabled');
                }
                let targetFileBtn = document.querySelector<HTMLButtonElement>('#converter-target-file');
                if(targetFileBtn){
                    targetFileBtn.removeAttribute('disabled');
                }
                let options = evt.data.data;
                
                for(let i in options){
                    if(!options.hasOwnProperty(i)) continue;
                    let selectOption = document.createElement('option');
                    selectOption.value = options[i];
                    selectOption.innerText = options[i];
                    converterSelect?.appendChild(selectOption);
                }
            }
        }
    }
    
    EventManager.getInstance().subscribe('WEBSOCKET_CONNECT',() => {
        webSocketWorker.postMessage({type:"WebsocketOpen"})
    });
    EventManager.getInstance().subscribe('WEBSOCKET_DISCONNECT',() => {
        webSocketWorker.postMessage({type:"WebsocketClose"})
    });
}
})();