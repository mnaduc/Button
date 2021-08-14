#include "Button.h"

Button btn(7);

void nhanGiu(uint32_t time){
  Serial.print("Nhan giu: ");
  Serial.println(time);
}
void setup() {
  Serial.begin(9600);
  btn.setOnDown([] {
    Serial.println("-------------------------------------");
    Serial.println("Da nhan!");
    });
  btn.setOnUp([](uint32_t time) {
    Serial.print("Da tha! ");
    Serial.println(time);
    });
  btn.setOnPress(nhanGiu);
}

void loop() { 
  btn.loop();
}
