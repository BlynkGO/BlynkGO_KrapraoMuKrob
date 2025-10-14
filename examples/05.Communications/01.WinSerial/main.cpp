#include <BlynkGOv5.h>

GLabel label;

WinSerial COM3("COM3");

void setup(){
  Serial.begin(9600); Serial.println();
  BlynkGO.begin();

  COM3.begin(9600);
  static SoftTimer t;
  t.setInterval(10,[](){
    if( COM3.available()){
      int c = COM3.readStringUntil('\n').toInt();
      Serial.println(c);
      label = c;
    }
  });

}

void loop(){
  BlynkGO.update();
}
