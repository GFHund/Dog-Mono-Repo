import { AbstractPluginClass } from "./AbstractPluginClass";

export class TabElements extends AbstractPluginClass{
    init(): void {
        let children = this.el.children;
        for(let i in children){
            if(!children.hasOwnProperty(i)) continue;
            children[i].addEventListener('click',this.onTabClick.bind(this));
        }
    }

    onTabClick(evt:Event){
        let children = this.el.children;
        for(let i in children){
            if(!children.hasOwnProperty(i)) continue;
            children[i].classList.remove('active');
            let mainSegments = document.querySelectorAll<HTMLElement>((children[i] as HTMLElement).dataset.target);
            for(let i in mainSegments){
                if(!mainSegments.hasOwnProperty(i))continue;
                mainSegments[i].style.display = 'none';
            }
        }
        let target = evt.target as HTMLElement;
        target.classList.add('active');
        let content = document.querySelectorAll<HTMLElement>(target.dataset.target);
        for(let i in content){
            if(!content.hasOwnProperty(i))continue;
            content[i].style.display='';
        }
        //target.style.display = '';

    }
}