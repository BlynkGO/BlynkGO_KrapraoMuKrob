/* ตัวอย่างเพิ่มเติม : https://github.com/BlynkGO/BlynkGOv5_examples  */

#include <BlynkGOv5.h>

GContainer cont;
  GButton btn[3];
    String btn_str[3] = { "10 บาท", "20 บาท", "30 บาท"};

GLabel label;

void setup(){
  Serial.begin(9600); Serial.println();
  BlynkGO.begin();

  cont.bg_opa(0);   // โปร่งใส
  cont.layout(LAYOUT_ROW_M, 2,2,2,2, 30);  // จัด layout แบบแถว ห่างกัน 30px ระหว่าง ลูกๆในนั้น
  for(int i=0; i<3; i++) {
    btn[i].parent(cont);
    btn[i] = btn_str[i];
    btn[i].onClicked(GWIDGET_CB{
      int ii = (GButton*)widget-&btn[0];
      label = btn[ii].text();
    });
  }

  label.font(prasanmit_40);
  label.align(cont, ALIGN_BOTTOM, 0, 50);
}

void loop(){
  BlynkGO.update();
}