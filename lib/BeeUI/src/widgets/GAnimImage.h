/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GAnimImage.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GANIMIMAGE_H__
#define __GANIMIMAGE_H__


#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GAnimImage : public GObject {
  public:
    GAnimImage(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GAnimImage(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GAnimImage();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    inline  void  init(const void * dsc[], size_t num, uint32_t duration, uint32_t count = ANIM_REPEAT_INFINITE ) {
      this->set_src(dsc, num);
      this->duration(duration);
      this->repeat_count(count);
    }

    inline  void  init(const img_t * dsc[], size_t num, uint32_t duration, uint32_t count = ANIM_REPEAT_INFINITE ) {
      this->set_src(dsc, num);
      this->duration(duration);
      this->repeat_count(count);
    }

    inline  void  start(const void * dsc[], size_t num, uint32_t duration, uint32_t count = ANIM_REPEAT_INFINITE ) {
      this->init(dsc, num, duration, count);
      this->start();
    }

    inline  void  start(const img_t * dsc[], size_t num, uint32_t duration, uint32_t count = ANIM_REPEAT_INFINITE ) {
      this->init(dsc, num, duration, count);
      this->start();
    }

    /*=====================
    * Setter functions
    *====================*/

    /**
     * Set the image animation images source.
     * @param dsc   pointer to a series images
     * @param num   images' number
     */
    void set_src(const void * dsc[], size_t num);

    inline void set_src(const img_t * dsc[], size_t num)    { this->set_src((const void **) dsc, num);            }

    /**
     * Startup the image animation.
     */
    void start();

    /**
     * Set the image animation duration time. unit:ms
     * @param duration  the duration in milliseconds
     */
    void duration(uint32_t duration);

    /**
     * Set the image animation repeatedly play times.
     * @param count     the number of times to repeat the animation
     */
    void repeat_count(uint32_t count);

    /*=====================
    * Getter functions
    *====================*/

    /**
     * Get the image animation images source.
     * @return a    pointer that will point to a series images
     */
    const void ** get_src();

    /**
     * Get the image animation images source.
     * @return      the number of source images
     */
    uint8_t src_count();

    /**
     * Get the image animation duration time. unit:ms
     * @return      the animation duration time
     */
    uint32_t duration();

    /**
     * Get the image animation repeat play times.
     * @return      the repeat count
     */
    uint32_t repeat_count();
  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GANIMIMAGE_H__
