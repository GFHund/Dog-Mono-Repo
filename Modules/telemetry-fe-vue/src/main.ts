import { createApp } from "vue";
import {createRouter,createWebHashHistory,RouteRecordRaw} from "vue-router";
import "./styles.css";
import App from "./App.vue";
import SingleTelemetry from "./pages/SingleTelemetry.vue";
import StackedTelemetry from "./pages/StackedTelemetry.vue";
import CircuitTelemetry from "./pages/CircuitTelemetry.vue";
import { DiagramService } from "./services/DiagramService";

const routes:RouteRecordRaw[] = [
    {path: '/',name:'singleTelemetry', component: SingleTelemetry},
    {path: '/stacked-telemetry',name:'stackedTelemetry',component:StackedTelemetry},
    {path: '/circuit-telemetry',name:'circuitTelemetry',component:CircuitTelemetry}
]

const router = createRouter({
    history: createWebHashHistory(),
    routes
})

createApp(App).provide('diagramService',new DiagramService()).use(router).mount("#app");
