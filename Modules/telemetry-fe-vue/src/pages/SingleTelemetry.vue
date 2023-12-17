<script lang="ts">
import { inject, onMounted, ref } from 'vue';
import Database from "tauri-plugin-sql-api";
import {open} from '@tauri-apps/api/dialog';
import { DiagramService } from '../services/DiagramService';
import { Diagram } from '../services/Diagram';
export default {
    setup(){
        let telemetryTableDialog = ref<HTMLDialogElement>();
        let telemetryDiagram = ref<HTMLCanvasElement>();
        let diagramService = inject<DiagramService>('diagramService');
        let diagramObj:Diagram|undefined;
        let databases = [];
        onMounted(() => {
            if(typeof telemetryDiagram !== undefined){
                diagramObj = diagramService?.initDiagram(telemetryDiagram);
            } else {
                console.error('telemetry Diagram not set');
            }
        });
        return {
            telemetryTableDialog,
            telemetryDiagram,
            diagramService,
            diagramObj,
            databases
        }
        
    },
    onMounted(){
        console.log('onMounted');
    },
    mounted(){
        console.log('mounted');
    },
    methods:{
        onClickTable(){
            this.telemetryTableDialog?.showModal();
        },
        onCloseDialog(){
            this.telemetryTableDialog?.close();
        },
        async onAddDatabase(){
            let path = await open({filters:[{
                name: 'Telemetry',
                extensions:['sqlite','sqlite3']
            }]});//.then((path)=>{return path;})
            if(path === null){
                return;
            }
            let db = await Database.load('sqlite:'+path);
            db.select()
        },
        initCanvas(){
            /*
            if(this.telemetryDiagram){
                this.diagramObj = this.diagramService?.initDiagram(this.telemetryDiagram);
            }
            */
        },
        async onOpenDatabase(){
            const selected = await open({
                filters: [{
                    name: 'Telemetry',
                    extensions: ['sqlite3','sqlite']
                }]
            });
            const db = await Database.load('sqlite:'+selected);
            await db.select('SELECT * FROM ')
        }
    },
    created(){
        if(this.telemetryDiagram){
            this.diagramObj = this.diagramService?.initDiagram(this.telemetryDiagram);
        } else {
            console.error('telemetry Diagram not set');
        }
    }
}
</script>
<template>
    <div class="single-telemetry">
        <div class="navigation-left">
            <button @click="onClickTable">
                <svg width="40" height="20" style="stroke:#fff;">
                    <line x1="0" y1="0" x2="40" y2="0" />
                    <line x1="0" y1="10" x2="40" y2="10" />
                    <line x1="0" y1="20" x2="40" y2="20" />
                </svg>
            </button>
        </div>
        <div class="main-window">
            <canvas ref="telemetryDiagram"></canvas>
            <button @click="initCanvas">Init canvas</button>
        </div>
    </div>
    <dialog ref="telemetryTableDialog">
        <div class="telemetry-table-dialog--header">
            <button @click="onCloseDialog">close</button>
        </div>
        <div class="telemetry-table-dialog--content">
            <button @click="onOpenDatabase">add Database</button>
            <ul></ul>
        </div>
    </dialog>
</template>

<style lang="scss">
.single-telemetry{
    display:flex;
}
.main-window canvas{
    width:100%;
    height:100%;
}
</style>