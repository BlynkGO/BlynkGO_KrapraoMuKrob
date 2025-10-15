#include <BlynkGOv5.h>

WinSerial COM_PORT("COM4");

GContainer  cont_led;
  GLed led[5];

void setup(){
  Serial.begin(9600); Serial.println();
  BlynkGO.begin();
  BlynkGO.window_title("My App");

  // COM_PORT.begin(9600);
  cont_led.bg_opa(0);
  cont_led.layout(LAYOUT_ROW_M, 10,10,10,10,20);
  for(int i=0; i<5; i++){
    led[i].parent(cont_led);
  }

}

void loop(){
  BlynkGO.update();
}

