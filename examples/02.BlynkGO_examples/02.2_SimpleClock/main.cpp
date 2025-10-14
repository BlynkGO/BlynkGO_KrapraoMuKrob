#include <BlynkGOv5.h>

GLabel lb_clock;

void setup(){
  Serial.begin(9600); Serial.println();
  BlynkGO.begin();

  static SoftTimer t;
  t.setInterval(1000,[](){
    lb_clock = StringX::printf("%02d:%02d:%02d", hour(), minute(), second());
  });
}

void loop(){
  BlynkGO.update();
}