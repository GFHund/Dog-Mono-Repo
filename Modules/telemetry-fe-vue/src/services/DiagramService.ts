import { Diagram } from "./Diagram";

export class DiagramService{
    public initDiagram(canvas: HTMLCanvasElement):Diagram{
        return new Diagram(canvas);
    }
}