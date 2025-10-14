/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GCircle.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GCIRCLE_H__
#define __GCIRCLE_H__


#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GCircle : public GObject {
  public:
    GCircle(GWidget& parent=GScreen)                    : GObject(&parent) {}
    GCircle(GWidget* parent)                            : GObject(parent)  {}
    virtual ~GCircle();

    virtual void    create();
    inline  void    create(GWidget& parent)             { this->_par = &parent; this->create(); }
    inline  void    create(GWidget* parent)             { this->_par =  parent; this->create(); }

    void            size(int32_t w, int32_t h);
    void            radius(int32_t r);
    inline void     radius(int32_t r, color_t color)    { this->radius(r); this->color(color);  }
    inline int32_t  radius()                            { return this->width()/2;               }

  private:

};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GCIRCLE_H__
