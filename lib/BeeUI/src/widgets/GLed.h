/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GLed.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GLED_H__
#define __GLED_H__


#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GLed : public GObject {
  public:
    GLed(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GLed(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GLed();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    bool isON();
    inline bool isOFF()                                     { return !isON();   }
    inline void state(bool st)                              { st? ON(): OFF();  }
    inline bool state()                                     { return isON();    }

    /**
     * Set the color of the LED
     * @param color     the color of the LED
     */
    void color(color_t color);

    color_t color();

    /**
     * Set the brightness of a LED object
     * @param bright    LV_LED_BRIGHT_MIN (max. dark) ... LV_LED_BRIGHT_MAX (max. light)
     */
    void brightness(uint8_t bright);

    /**
     * Light on a LED
     */
    void on();

    /**
     * Light off a LED
     */
    void off();

    inline void ON()                    { this->on();  if(this->checkable()) this->checked(true);   }
    inline void OFF()                   { this->off(); if(this->checkable()) this->checked(false);  }

    inline void checkable(bool en)      { GObject::checkable(en);  if(this->checkable()) this->checked(this->isON()); }
    inline bool checkable()             { return GObject::checkable(); }

    /**
     * Toggle the state of a LED
     */
    void toggle();

    /**
     * Get the brightness of a LED object
     * @return bright   0 (max. dark) ... 255 (max. light)
     */
    uint8_t brightness();

  private:

};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GLED_H__
