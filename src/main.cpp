#include <BlynkGOv5.h>

GRect rect;

void setup(){
  Serial.begin(9600); Serial.println();
  BlynkGO.begin();
  BlynkGO.window_title("My App");

  rect.size(300,80);
  rect.radius(20);
  rect.border(5, TFT_WHITE);

}

void loop(){
  BlynkGO.update();
}

