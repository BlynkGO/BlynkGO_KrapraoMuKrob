/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GContainer.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GMASK_H__
#define __GMASK_H__

#include "GObject.h"
#include "GContainer.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GMask : public GContainer {
  public:
    GMask(GWidget& parent=GScreen)                          : GContainer(&parent) {}
    GMask(GWidget* parent)                                  : GContainer(parent)  {}
    GMask(const img_t*src, GWidget& parent=GScreen)         : GContainer(&parent), _mask_src(src)   {}
    GMask(const img_t&src, GWidget& parent=GScreen)         : GContainer(&parent), _mask_src(&src)  {}
    GMask(const img_t*src, GWidget* parent)                 : GContainer(parent), _mask_src(src)    {}
    GMask(const img_t&src, GWidget* parent)                 : GContainer(parent), _mask_src(&src)   {}

    virtual ~GMask();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    GMask& operator =(const img_t * src_img);
    GMask& operator =(const img_t & src_img);

  private:
    const img_t *_mask_src=NULL;

};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GMASK_H__
