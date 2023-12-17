

export class Diagram{
    private gl:WebGL2RenderingContext;
    constructor(private canvas:HTMLCanvasElement){
        let gl = canvas.getContext('webgl2');
        if(gl === null){
            throw new Error('could not create gl context');
        }
        this.gl = gl;
        /*
        let program = this.gl.createProgram();
        if(program){
            program.
        }
        */
        this.gl.viewport(0,0,gl.drawingBufferWidth,gl.drawingBufferHeight);
        this.gl.clearColor(0.0,1.0,0.0,1.0);
        this.gl.clear(this.gl.COLOR_BUFFER_BIT);
        
    }
}