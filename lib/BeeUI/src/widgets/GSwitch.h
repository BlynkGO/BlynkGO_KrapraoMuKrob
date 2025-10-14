/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GSwitch.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GSWITCH_H__
#define __GSWITCH_H__


#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GSwitch : public GObject {
  public:
    GSwitch(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GSwitch(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GSwitch();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    bool isON();
    inline bool isOFF()                                     { return !isON();   }
    inline void state(bool st)                              { st? ON(): OFF();  }
    inline bool state()                                     { return isON();    }

    void on();
    void off();

    inline void ON()                                        { this->on();   this->event_send(EVENT_VALUE_CHANGED);  }
    inline void OFF()                                       { this->off();  this->event_send(EVENT_VALUE_CHANGED);  }

    /*=====================
    * Setter functions
    *====================*/

    /**
     * Set the orientation of switch.
     * @param orientation   switch orientation from `switch_orientation_t`
     */
    void orientation(switch_orientation_t orientation);

    /*=====================
    * Getter functions
    *====================*/

    /**
     * Get the orientation of switch.
     * @return          switch orientation from ::switch_orientation_t
     */
    switch_orientation_t orientation();

    /*=====================
    * Design functions
    *====================*/
    inline void color( color_t color )                                  { GObject::bg_color(color, (gstate_t)((int)GPART_INDICATOR | (int) (GSTATE_ON)));  }
    using GObject::color;

    inline void knob_color( color_t color)                              { GObject::bg_color(color, GPART_KNOB);  }
    inline void knob_color( color_t color, gstate_t gstate )            { GObject::bg_color(color, (gstate_t)((int)GPART_KNOB | (int) ((gstate==GSTATE_ON )? GSTATE_ON: GSTATE_OFF))); }
    inline void radius( int32_t r)                                      { GObject::radius(r); GObject::radius(r, GPART_INDICATOR);  GObject::radius(r, GPART_KNOB); }
    using GObject::radius;

  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GSWITCH_H__
