#include <BlynkGOv5.h>

GButton btn;

void setup() {
  Serial.begin(9600);
  BlynkGO.begin();

  btn = "Notepad";
  btn.onClicked(GWIDGET_CB{
    BeeExec::start("notepad.exe");

    // run python script and receive python output
    // BeeExec::start(R"(python C:/your_path/test.py)", [](const String& msg){
    //   Serial.println(msg);
    // });

  });
}

void loop() {
  BlynkGO.update();
}
