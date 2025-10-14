/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GTileView.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GTILEVIEW_H__
#define __GTILEVIEW_H__


#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GTileView : public GObject {
  public:
    GTileView(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GTileView(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GTileView();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    obj_t * add_tile(uint8_t col_id, uint8_t row_id, dir_t dir);

    void tile(obj_t * tile_obj, anim_enable_t anim_en=false);
    void tile_by_index(uint32_t col_id, uint32_t row_id, anim_enable_t anim_en=false);

    obj_t * tile_active();

    void anim_speed(uint32_t value);
    uint32_t anim_speed();

  private:
    uint32_t _anim_speed=400;
};


// GTile ห้ามกำหนดขนาด ขนาดจะไปเท่ากับขนาดของ GTileView ที่เป็น parent ให้เอง
class GTile : public GObject {
  public:
    GTile(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GTile(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GTile();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();             }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();             }

    void tileview_pos(uint8_t col_id, uint8_t row_id);
    Point tileview_pos();

    void tileview_direction(dir_t dir);
    dir_t tileview_direction();

    inline void tileview_pos(uint8_t col_id, uint8_t row_id, dir_t dir) {
      this->tileview_pos(col_id, row_id);
      this->tileview_direction(dir);
    }

    void operator = (obj_t* obj);

  private:
    uint8_t _col_id = 0;
    uint8_t _row_id = 0;
};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GTILEVIEW_H__
