#include <BlynkGOv5.h>

GLabel label;

void setup(){
  Serial.begin(9600); Serial.println();
  BlynkGO.begin();

  label = "Hello BlynkGO.\nทดสอบภาษาไทย";
}

void loop(){
  BlynkGO.update();
}
