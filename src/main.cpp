#include <BlynkGOv5.h>

WinSerial COM_PORT("COM3");

GGaugeRainbow gauge;

void setup(){
  Serial.begin(9600); Serial.println();
  BlynkGO.begin();
  BlynkGO.window_title("My App");

  COM_PORT.begin(9600);
  static SoftTimer timer;
  timer.setInterval(10,[](){
    if(COM_PORT.available()){
      String raw = COM_PORT.readStringUntil('\n');
      if(raw.startsWith("[TEMP]")){
        raw.replace("[TEMP]", ""); raw.trim();
        float temp = raw.toFloat();
        Serial.println(temp);
        gauge = temp;
      }
    }
  });
}

void loop(){
  BlynkGO.update();
}

