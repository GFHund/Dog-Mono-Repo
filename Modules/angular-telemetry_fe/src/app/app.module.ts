import { Converter } from './Page/Converter/converter.page';
import { Telemetry } from './Page/Telemetry/telemetry.page';
import { ToolBar } from './Components/ToolBar/toolBar.component';
import { StatusBar } from './Components/StatusBar/statusBar.component';
import { AppComponent } from './app.component';
import {NgModule } from '@angular/core';
import { ContainerTabs } from './Components/ContainerTabs/containerTabs.component';
import { TabElement } from './Components/TabElement/tabElement.component';
import { BrowserModule } from '@angular/platform-browser';
import { ContainerTwoElements } from './Components/ContainerTwoElements/containerTwoElements.component';

@NgModule({
    declarations: [
        AppComponent,
        ContainerTabs,
        TabElement,
        StatusBar,
        ToolBar,
        ContainerTwoElements,
        Telemetry,
        Converter
    ],
    imports:[
        BrowserModule
    ],
    bootstrap: [AppComponent]
})
export class AppModule{}