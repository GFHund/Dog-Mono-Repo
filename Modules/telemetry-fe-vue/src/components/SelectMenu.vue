<script lang="ts">
import { defineComponent } from 'vue'

export default defineComponent({
    setup() {
        
    },
    data(){
        return {menuOpen:false};
    },
    methods:{
        onOpenMenu(){
            this.menuOpen = !this.menuOpen;
        },
        onClickSingleTelemetry(){
            this.menuOpen = false;
            this.$router.push({name:'singleTelemetry'})
        },
        onClickStackedTelemetry(){
            this.menuOpen = false;
            this.$router.push({name:'stackedTelemetry'})
        },
        onClickCircuitTelemetry(){
            this.menuOpen = false;
            this.$router.push({name:'circuitTelemetry'})
        }
    }
})
</script>
<template>
    <div class="select-component">
        <div class="select-component--title" @click="onOpenMenu">Menu</div>
        <ul :class="{menu_open:menuOpen}">
            <li @click="onClickSingleTelemetry">Single Telemetry</li>
            <li @click="onClickStackedTelemetry">Stacked Telemetry</li>
            <li @click="onClickCircuitTelemetry">Circuit Telemetry</li>
        </ul>

    </div>
</template>

<style lang="scss">
$width: 150px;
.select-component{
    position:relative;
    background-color:#e05c00;
    color:#fff;
    min-width:$width;
    border-radius: 5px;
    
}
.select-component--title{
    padding: 0 5px;
    cursor: pointer;
}
.select-component ul{
    display:none;
    position:absolute;
    top:100%;
    left:0;
    list-style: none;
    min-width: $width;
    padding:0;
    margin:0;
    &.menu_open{
        display:block;
    }
    li {
        background-color:#e05c00;
        color:#fff;
        border-bottom: 1px solid #fff;
        padding: 0 5px;
    
        cursor: pointer;
    }
    li:last-of-type{
        border-bottom:none;
    }
}

</style>