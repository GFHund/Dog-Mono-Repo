import { AppModule } from './app/app.module';
import { enableProdMode } from "@angular/core";
import { bootstrapApplication } from "@angular/platform-browser";
import { platformBrowserDynamic } from "@angular/platform-browser-dynamic";
import { AppComponent } from "./app/app.component";

import { environment } from "./environments/environment";

if (environment.production) {
  enableProdMode();
}

//bootstrapApplication(AppComponent).catch((err) => console.error(err));
platformBrowserDynamic().bootstrapModule(AppModule)
.catch(err => console.error(err));