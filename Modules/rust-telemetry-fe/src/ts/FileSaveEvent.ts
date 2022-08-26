export class FileSaveEvent{
    protected url;

    public constructor(url:string){
        this.url = url;
    }

    public getUrl(){
        return this.url;
    }
}