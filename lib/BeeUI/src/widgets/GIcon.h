/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GIcon.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GICON_H__
#define __GICON_H__


#include "GObject.h"
#include "GContainer.h"
#include "GImage.h"
#include "GLabel.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GIcon : public GContainer {
  public:
    GIcon(GWidget& parent=GScreen)                          : GContainer(&parent) {}
    GIcon(GWidget* parent)                                  : GContainer(parent)  {}

    GIcon(const img_t& image_src, String text, GWidget& parent=GScreen) 
     : GContainer(&parent), _image(&image_src), _text(text ) 
    {}

    GIcon(const img_t& image_src, String text, GWidget* parent) 
     : GContainer(parent), _image(&image_src), _text(text ) 
    {}

    virtual ~GIcon();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    inline  void   text(String txt)                         { if(!this->isCreated()) this->create(); this->_u_label->text(txt);     }
    inline  String text()                                   { if(!this->isCreated()) this->create(); return this->_u_label->text(); }

    GIcon& operator =(const String txt);
    GIcon& operator =(const img_t * src_img);
    GIcon& operator =(const img_t & src_img);

    inline  void  image_zoom(float zoom)                    { if(!this->isCreated()) this->create(); this->_u_icon->zoom(zoom);    }
    inline  float image_zoom()                              { if(!this->isCreated()) this->create(); return this->_u_icon->zoom(); }

    std::unique_ptr<GImage> _u_icon;
    std::unique_ptr<GLabel> _u_label;

  private:
    const img_t *_image =NULL;
    String _text = "ไอคอน";


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GICON_H__
