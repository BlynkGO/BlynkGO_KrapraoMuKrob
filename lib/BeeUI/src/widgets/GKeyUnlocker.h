/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GKeyUnlocker.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GKEYUNLOCKER_H__
#define __GKEYUNLOCKER_H__


#include "GObject.h"
#include "widgets_extra/keyunlocker/lv_keyunlocker.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

enum {
  GKEYUNLOCKER_MODE_LOCK,
  GKEYUNLOCKER_MODE_SETTING,
};
typedef uint8_t GKeyUnlocker_mode_t;

class GKeyUnlocker : public GObject {
  public:
    GKeyUnlocker(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GKeyUnlocker(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GKeyUnlocker();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }


    /*=====================
    * Setter functions
    *====================*/

    /**
     * Set the value of a keyunlocker
     * @param secretkey     : the secretkey for the keyunlocker
     */
    void secretkey(uint32_t secretkey);

    /**
     * Set the authentication callback for a keyunlocker
     * @param fn          Function to call when authentication succeeds
     */
    void auth_cb(void (*fn)(void));

    /**
     * Set the authentication failure callback for a keyunlocker
     * @param fn          Function to call when authentication is canceled or failed
     */
    void cancel_cb(void (*fn)(void));

    /**
     * Set the mode of a keyunlocker
     * @param mode     : the mode for the keyunlocker ;   GKEYUNLOCKER_MODE_LOCK โหมดล็อค หรือ GKEYUNLOCKER_MODE_SETTING โหมดเปลี่ยนตั้งรหัสใหม่
     */
    void mode(GKeyUnlocker_mode_t mode );

    
    /*=====================
    * Getter functions
    *====================*/

    /**
     * Get the value of a keyunlocker
     * @return the value of the keyunlocker's secretkey
     */
    
    uint32_t secretkey();

  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GKEYUNLOCKER_H__
