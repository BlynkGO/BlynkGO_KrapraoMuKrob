/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GPasscodeLock.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GPASSCODELOCK_H__
#define __GPASSCODELOCK_H__


#include "GObject.h"
#include "widgets_extra/passcodelock/lv_passcodelock.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

enum {
  GPASSCODELOCK_MODE_LOCK,
  GPASSCODELOCK_MODE_SETTING,
};
typedef uint8_t GPasscodeLock_mode_t;

class GPasscodeLock : public GObject {
  public:
    GPasscodeLock(GWidget& parent=GScreen)                      : GObject(&parent) {}
    GPasscodeLock(GWidget* parent)                              : GObject(parent)  {}
    virtual ~GPasscodeLock();

    virtual void  create();
    inline  void  create(GWidget& parent)                       { this->_par = &parent; this->create(); }
    inline  void  create(GWidget* parent)                       { this->_par =  parent; this->create(); }

    inline void btn_size(int32_t w, int32_t h)                  { GObject::style_size(w,h, GPART_ITEMS);      this->event_send(EVENT_STYLE_CHANGED);              }
    inline void btn_color(color_t c, gstate_t s=GSTATE_DEFAULT) { GObject::color(c, (gstate_t)((int)GPART_ITEMS|(int)s)); this->event_send(EVENT_STYLE_CHANGED);  }
    inline void btn_opa(opa_t opa, gstate_t s=GSTATE_DEFAULT)   { GObject::opa(opa, (gstate_t)((int)GPART_ITEMS|(int)s)); this->event_send(EVENT_STYLE_CHANGED);  }
    inline void btn_font(const font_t& font)                    { GObject::font(font, GPART_ITEMS );          this->event_send(EVENT_STYLE_CHANGED);              }
    inline void btn_font(const font_t& font, color_t c)         { GObject::font(font, c, GPART_ITEMS );       this->event_send(EVENT_STYLE_CHANGED);              }
    inline void btn_gap(int32_t gap)                            { GObject::pad_gap(gap, GPART_MAIN);          this->event_send(EVENT_STYLE_CHANGED);              }
    inline void dot_size(int32_t w, int32_t h)                  { GObject::style_size(w,h, GPART_INDICATOR);  this->event_send(EVENT_STYLE_CHANGED);              }
    inline void dot_gap(int32_t gap)                            { GObject::pad_column(gap, GPART_INDICATOR);  this->event_send(EVENT_STYLE_CHANGED);              }
    inline void cancel_font(const font_t& font)                 { GObject::font(font, GPART_SELECTED);        this->event_send(EVENT_STYLE_CHANGED);              }
    inline void cancel_font(const font_t& font, color_t c)      { GObject::font(font, c, GPART_SELECTED);     this->event_send(EVENT_STYLE_CHANGED);              }

    /*=====================

    * Setter functions
    *====================*/

    /**
     * Set the value of a passcodelock
     * @param passcode     : the passcode for the passcodelock
     */
    void passcode(uint32_t passcode);

    /**
     * Set the authentication callback for a passcodelock
     * @param fn          Function to call when authentication succeeds
     */
    void auth_cb(void (*fn)(void));

    /**
     * Set the authentication failure callback for a passcodelock
     * @param fn          Function to call when authentication is canceled or failed
     */
    void cancel_cb(void (*fn)(void));

    /**
     * Set the mode of a passcodelock
     * @param mode     : the mode for the passcodelock ;   GPASSCODELOCK_MODE_LOCK โหมดล็อค หรือ GPASSCODELOCK_MODE_SETTING โหมดเปลี่ยนตั้งรหัสใหม่
     */
    void mode(GPasscodeLock_mode_t mode );

    
    /*=====================
    * Getter functions
    *====================*/

    /**
     * Get the value of a passcodelock
     * @return the value of the passcodelock's passcode
     */
    
    uint32_t passcode();

  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GPASSCODELOCK_H__
