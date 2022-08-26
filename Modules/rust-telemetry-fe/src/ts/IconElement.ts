
export class IconElement extends HTMLElement{
    public constructor(){
        super();
        const shadow = this.attachShadow({mode:'open'});
        const wrapper = document.createElement('div');
        wrapper.classList.add('icon');

        let src = this.getAttribute('src');
        let width =this.getAttribute('width');
        let height = this.getAttribute('height');
        let fill = this.getAttribute('fill');
        let stroke = this.getAttribute('stroke');
        fetch(src).then((response) => {
            //wrapper.innerHTML = icon;
            //console.log(icon);
            let reader = response.body.getReader();
            reader.read().then((text) => {
                wrapper.innerHTML = new TextDecoder().decode(text.value);
            })
            
        });

        let styleElement = document.createElement('style');
        let stylings = 'svg{width:'+width+';height:'+height+';fill:'+fill+';stroke:'+stroke+'}';
        styleElement.textContent = stylings;

        shadow.appendChild(styleElement);
        shadow.appendChild(wrapper);
    }
}