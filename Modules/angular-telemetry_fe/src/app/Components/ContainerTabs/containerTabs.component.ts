import { TabElement } from './../TabElement/tabElement.component';
import { Component,ContentChildren, QueryList } from "@angular/core";

@Component({
    selector:'app-tabs',
    templateUrl:'./containerTabs.component.html',
    styleUrls:['./containerTabs.component.scss']
})
export class ContainerTabs{
    @ContentChildren(TabElement,{descendants:true}) elements!: QueryList<TabElement>;
    activeTab:number = 0;

    
    get paneTitles(): string[]{
        return this.elements? this.elements.map(p =>p.title):['Nichts gefunden'];
    }

    onTabClick(elementId:number){
        let elementsFiltered = this.elements.filter((item) => parseInt(item.id) == elementId);
        let element = elementsFiltered[0];
        element.active = true;

        elementsFiltered = this.elements.filter((item) => parseInt(item.id) == this.activeTab);
        elementsFiltered[0].active = false;
        this.activeTab = elementId;
    }
}