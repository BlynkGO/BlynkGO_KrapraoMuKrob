/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GLottie.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GLOTTIE_H__
#define __GLOTTIE_H__


#include "GObject.h"

#if LV_USE_LOTTIE
//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GLottie : public GObject {
  public:
    GLottie(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GLottie(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GLottie();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    /**
     * Set a buffer for the animation. It also defines the size of the animation
     * @param w         width of the animation and buffer
     * @param h         height of the animation and buffer
     * @param buf       a static buffer with `width x height x 4` byte size
     */
    void buffer(int32_t w, int32_t h, void * buf);

    /**
     * Set a draw buffer for the animation. It also defines the size of the animation
     * @param draw_buf  an initialized draw buffer with ARGB8888 color format
     */
    void draw_buf(draw_buf_t * draw_buf);

    /**
     * Set the source for the animation as an array
     * @param src       the lottie animation converted to an nul terminated array
     * @param src_size  size of the source array in bytes
     */
    void src_data(const void * src, size_t src_size);

    /**
     * Set the source for the animation as a path.
     * Lottie doesn't use LVGL's File System API.
     * @param src       path to a json file, e.g. "path/to/file.json"
     */
    void src_file(const char * src);

    /**
     * Get the LVGL animation which controls the lottie animation
     * @return          the LVGL animation
     */
    anim_t * anim();


  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif // LV_USE_LOTTIE
#endif //__GLOTTIE_H__
