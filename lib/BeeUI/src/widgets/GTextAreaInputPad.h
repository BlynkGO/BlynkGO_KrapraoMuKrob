/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GTextAreaInputPad.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
 *   สร้างโดย BlynkGO
 *   
 *   2.ไม่อนุญาต ให้แจกจ่าย สำเนา หรือแก้ไข โดยไม่ได้รับอนุญาต 
 *   
 *   3.สำหรับผู้ได้รับ ลิขสิทธิ์ สามารถนำไปใช้สร้าง firmware/rom 
 *   สำหรับ บอร์ด ESP32 ที่ระบุเท่านั้น เพื่อใช้ทางการค้าต่างๆได้
 *   โดยห้ามแจกจ่าย จำหน่าย ดัดแปลง แก้ไขใดๆ ในตัว source ไลบรารี่ออกไป
 *
 *   4.หากมีการนำไปใช้คอมไพล์ถือว่าได้ยอมรับ ตามเงื่อนไขลิขสิทธิ์ดังกล่าว
 *   เป็นที่เรียบร้อยแล้ว
 * 
 * Version 5.0
 * 
 *********************************************************************************
 */

#ifndef __GTEXTAREA_INPUTPAD_H__
#define __GTEXTAREA_INPUTPAD_H__


#include "GObject.h"
#include "GKeyboard.h"
#include "GButton.h"
#include "GTextArea.h"
#include "GLabel.h"
#include "GContainer.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GTextAreaInputPad : public GObject {
  public:
    GTextAreaInputPad(GWidget& parent=GScreen)              : GObject(&parent) {}
    GTextAreaInputPad(GWidget* parent)                      : GObject(parent)  {}
    virtual ~GTextAreaInputPad();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }


    void textarea(GTextArea* ta);
    inline void textarea(GTextArea& ta)                     { this->textarea(&ta); }

    void label(GLabel* lb);
    inline void label(GLabel& lb)                           { this->label(&lb); }

    inline String text()                                    { if(!isCreated()) create(); return _u_ta_input_box->toString(); }
    void keyboard_mode(keyboard_mode_t mode);
    keyboard_mode_t keyboard_mode();

    std::unique_ptr<GContainer> _u_cont_input_box;
        std::unique_ptr<GTextArea>  _u_ta_input_box;
        std::unique_ptr<GButton>    _u_btn_eye;
    std::unique_ptr<GKeyboard>  _u_kbd;
  
    GTextArea *_ta_outside=NULL;
    GLabel *_lb_outside=NULL;
    keyboard_mode_t _keyboard_mode = KEYBOARD_MODE_EN;
  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GTEXTAREA_INPUTPAD_H__
