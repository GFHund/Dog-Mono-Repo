<script lang="ts">
import Vue from 'vue'
import { appWindow } from '@tauri-apps/api/window'
import SelectMenu from './SelectMenu.vue';
export default {
  components: { SelectMenu },
    setup(){},
    methods: {
        onClickMaximize(){
            appWindow.toggleMaximize();
        },
        onClickMinimize(){
            appWindow.minimize();
        },
        onClickClose(){
            appWindow.close();
        }
    }
}
</script>
<template>
    <div class="window-header">
        <div class="select-container"><select-menu/></div>
        <div class="window-drag-bar" data-tauri-drag-region></div>
        <div class="window-operations">
            <button @click="onClickMinimize">Minimize</button>
            <button @click="onClickMaximize">Maximize</button>
            <button @click="onClickClose">Close</button>
        </div>
    </div>
</template>

<style lang="scss">
    .window-header{
        display:flex;
    }
    .window-drag-bar{
        flex:1 0 auto;
    }
</style>