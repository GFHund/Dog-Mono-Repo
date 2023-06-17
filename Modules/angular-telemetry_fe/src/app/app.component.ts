import { Component } from "@angular/core";
import { invoke } from "@tauri-apps/api/tauri";

@Component({
  selector: "app-root",
  templateUrl:'./app.component.html',
})
export class AppComponent {
  greetingMessage = "";

  greet(name: string): void {
    invoke<string>("greet", { name }).then((text) => {
      this.greetingMessage = text;
    });
  }
}
