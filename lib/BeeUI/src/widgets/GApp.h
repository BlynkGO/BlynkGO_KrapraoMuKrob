/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GApp.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GAPP_H__
#define __GAPP_H__


#include "GObject.h"
#include "GMessageBox.h"


#define DEFAULT_GAPP_ICON    img_icon_beenext
IMG_DECLARE(DEFAULT_GAPP_ICON);

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------


class GApp : public GMessageBox {
  public:
    GApp(GWidget& parent=GScreen)                          : GMessageBox(&parent) {}
    GApp(GWidget* parent)                                  : GMessageBox(parent)  {}
    virtual ~GApp();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    obj_t* icon_button(const void* icon);
    obj_t* icon_button(const img_t& icon);
    // obj_t* close_button();

    obj_t* _close_btn = NULL;
    obj_t* _icon_btn = NULL;
    obj_t* _minimize_btn = NULL;
  private:

};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GAPP_H__
