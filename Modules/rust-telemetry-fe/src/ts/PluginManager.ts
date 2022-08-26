import { AbstractPluginClass } from './AbstractPluginClass';

interface PluginInfo{
    obj: AbstractPluginClass[];
    selector: string;
}

export class PluginManager{
    protected plugins: Map<string,PluginInfo> =new Map<string,PluginInfo>();

    register(name: string,pluginClass: any,selector:string):void{
        let htmlElements = document.querySelectorAll<HTMLElement>(selector);
        let pluginClasses:AbstractPluginClass[] = [];
        for(let i in htmlElements){
            if(!htmlElements.hasOwnProperty(i)) continue;
            let classObj = new pluginClass(htmlElements[i]);
            classObj.init();
            pluginClasses.push(classObj);
        }
        
        this.plugins.set(name,{obj:pluginClasses,selector});
    }
}