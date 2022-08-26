import { AbstractPluginClass } from "./AbstractPluginClass";

export class DiagramPlugin extends AbstractPluginClass{
    protected ctx: CanvasRenderingContext2D;

    init(): void {
        this.ctx = (this.el as HTMLCanvasElement).getContext("2d");
        this.ctx.fillStyle = "rgb(200,0,0)";
        this.ctx.fillRect(10,10,55,50);

    }
}