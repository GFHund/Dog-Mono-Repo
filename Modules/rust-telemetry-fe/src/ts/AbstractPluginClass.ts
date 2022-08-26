export abstract class AbstractPluginClass{
    protected el:HTMLElement;
    public constructor(element: HTMLElement){
        this.el = element;
    }
    abstract init():void;
}