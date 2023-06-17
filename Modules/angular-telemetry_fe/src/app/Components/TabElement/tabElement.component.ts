import { Component, Input } from "@angular/core";

@Component({
    selector:'app-tab-element',
    templateUrl:'./tabElement.component.html'
})
export class TabElement{
    @Input() id!: string;
    @Input() title!: string;
    @Input() active = false;

    get content():string | null{
        return 'Hallo 123'
    }
}