import { AfterViewInit, Component, HostListener, OnInit, ViewChild,ElementRef } from "@angular/core";
@Component({
    selector:'app-container-2',
    templateUrl:'./containerTwoElements.component.html',
    styleUrls:['./containerTwoElements.component.scss']
})
export class ContainerTwoElements implements AfterViewInit{
    protected initX = 0;
    protected initY = 0;
    protected currentWidth = 100;
    @ViewChild('seperator') seperatorElement!:ElementRef<HTMLDivElement>;
    @ViewChild('column2') column2Element!: ElementRef<HTMLDivElement>;
    @ViewChild('column1') column1Element!: ElementRef<HTMLDivElement>;
    //protected targetElement:HTMLElement;
    protected targetElementInitSize = 0;
    protected drag = false;
    

    ngAfterViewInit(){

    }

    onStartDrag(evt:MouseEvent){
        //if(this.tar)
        this.initX = evt.clientX;
        this.initY = evt.clientY;
        this.drag = true;
        console.log('Start Drag');
    }

    @HostListener('document:pointerup',['$event'])
    onEndDrag(evt:MouseEvent){
        this.drag = false;
        console.log('Stop Drag');
    }

    @HostListener('document:pointermove',['$event'])
    onMouseMove(evt:MouseEvent){
        if(!this.drag){
            return;
        }
        if(evt.buttons != 1){
            return;
        }
        let delta = this.initX - evt.clientX;
        //console.log(this.column2Element);
        let currentElementWidth = this.column1Element.nativeElement.clientWidth;
        //console.log(this.currentWidth);
        //console.log(currentElementWidth);
        let deltaPercent = (currentElementWidth / this.currentWidth)*(delta);
        this.currentWidth -= deltaPercent;
        console.log(this.currentWidth);
    }
}