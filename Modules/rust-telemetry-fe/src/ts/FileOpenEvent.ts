export class FileOpenEvent{
    protected url;

    public constructor(url:string){
        this.url = url;
    }

    public getUrl(){
        return this.url;
    }
}