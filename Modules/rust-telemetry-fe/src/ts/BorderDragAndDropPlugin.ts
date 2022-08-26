import { AbstractPluginClass } from "./AbstractPluginClass";

export class BorderDragAndDropPlugin extends AbstractPluginClass{
    protected initX = 0;
    protected initY = 0;
    protected targetElement:HTMLElement;
    protected targetElementInitSize=0; 
    init(): void {
        let targetElementSelector = this.el.dataset.target;
        this.targetElement = document.querySelector<HTMLElement>(targetElementSelector);
        this.el.addEventListener('mousedown',this.onMouseDown.bind(this));
        document.addEventListener('mouseup',this.onMouseUp.bind(this));
    }

    onMouseDown(evt:MouseEvent){
        console.log('mouseDown');
        if(this.targetElement){
            this.targetElementInitSize = this.targetElement.clientWidth;
        }
        this.initX = evt.clientX;
        this.initY = evt.clientY;
        document.addEventListener('mousemove',this.onMouseMove.bind(this));
    }

    onMouseUp(evt:Event){
        console.log('mouseUp');
        document.removeEventListener('mousemove',this.onMouseMove.bind(this));
    }

    onMouseMove(evt:MouseEvent){
        //console.log(evt.buttons);
        if(evt.buttons != 1){
            return;
        }
        
        
        if(this.targetElement){
            let targetElementWidth = this.targetElementInitSize;
            let delta = this.initX - evt.clientX;
            let newSize = targetElementWidth - delta;
            console.log(targetElementWidth);
            console.log(delta);
            console.log(newSize);
            this.targetElement.style.flexBasis = ''+newSize+'px';
            this.targetElement.style.maxWidth = ''+newSize+'px';
        } else {
            console.error('targetElement not found.Searching with Selector ');
        }
        

    }
}