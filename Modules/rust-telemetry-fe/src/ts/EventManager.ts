class Event{

}

export class EventManager{
    private static instance?:EventManager = null; 
    private events:Map<string,Function[]> = new Map<string,Function[]>();
    private constructor(){}

    public static getInstance():EventManager{
        if(this.instance == null){
            this.instance = new EventManager();
        }
        return this.instance;
    }
    public subscribe(eventName:string,eventFunction:Function){
        if(!this.events.has(eventName)){
            this.events.set(eventName,[]);
            
        } 
        this.events.get(eventName).push(eventFunction);
    }
    public dispatch(eventName:string,param?:Object){
        if(this.events.has(eventName)){
            let eventFunctions = this.events.get(eventName)
            for(let i in eventFunctions){
                if(!eventFunctions.hasOwnProperty(i)) continue;
                eventFunctions[i](param);
            }
        }
    }
}