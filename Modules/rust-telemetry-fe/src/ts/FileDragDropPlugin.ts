import { AbstractPluginClass } from "./AbstractPluginClass";

export class FileDragDropPlugin extends AbstractPluginClass{
    public init(): void {
        this.el.addEventListener('drop',this.onDrop.bind(this));
        this.el.addEventListener('dragover',this.onDragOver.bind(this));
        this.el.addEventListener('dragleave',this.onDragLeave.bind(this));
    }
    public onDrop(evt: DragEvent){
        evt.preventDefault();
        if(evt.dataTransfer.items){
            for (let i = 0; i < evt.dataTransfer.items.length; i++) {
                if (evt.dataTransfer.items[i].kind === 'file') {
                    const file = evt.dataTransfer.items[i].getAsFile();
                    //console.log(`… file[${i}].name = ${file.name}`);
                    console.log(file);
                  }
            }
        } else {
            // Use DataTransfer interface to access the file(s)
            for (let i = 0; i < evt.dataTransfer.files.length; i++) {
              console.log(`… file[${i}].name = ${evt.dataTransfer.files[i].name}`);
            }
        }
        this.el.classList.remove('file-over-zone');
    }
    public onDragOver(evt:DragEvent){
        evt.preventDefault();
        this.el.classList.add('file-over-zone');
    }
    public onDragLeave(evt:DragEvent){
        evt.preventDefault();
        this.el.classList.remove('file-over-zone');
    }
}