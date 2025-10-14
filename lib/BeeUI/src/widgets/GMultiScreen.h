/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GMultiScreen.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GMULTISCREEN_H__
#define __GMULTISCREEN_H__


#include "GObject.h"
#include "GTileView.h"
#include "GContainer.h"
#include <vector>

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

#define MAX_MULTISCREEN   10

class GMultiScreen : public GTileView {
  public:
    GMultiScreen(GWidget& parent=GScreen)                          : GTileView(&parent) {}
    GMultiScreen(GWidget* parent)                                  : GTileView(parent)  {}
    virtual ~GMultiScreen();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }


    void addScreen(uint8_t num=1);

    GRect* screen(uint8_t screen_id);
    GRect* operator [](uint8_t screen_id);
    uint16_t num();  // จำนวน screens ทั้งหมดขณะนี้

    void   current_screen(uint16_t screen_id, bool anim=true);
    GRect* current_screen();
    int16_t current_screen_id();

    inline   void selected_id(uint16_t screen_id, bool anim=false)    { this->current_screen( screen_id, anim); }
    inline   void selected(uint16_t screen_id, bool anim=false)       { this->current_screen( screen_id, anim); }
    inline   uint16_t selected_id()                                   { return this->current_screen_id();       }
    inline   GRect* selected()                                        { return this->current_screen();          }

    void     hidden_indic(bool enable);
    bool     hidden_indic();
    inline void     show_indic(bool enable)                           { this->hidden_indic(!enable);            }
    inline bool     show_indic()                                      { return !this->hidden_indic();           }
    inline void indic_color(color_t color_active, color_t color_inactive)   { GObject::bg_color(color_active , GPART_SELECTED); GObject::bg_color(color_inactive, GPART_ITEMS); }
    void     indic_opa(uint8_t opa_active, uint8_t opa_inactive)            { GObject::bg_opa(opa_active , GPART_SELECTED);     GObject::bg_opa(opa_inactive, GPART_ITEMS);     }

    GContainer& indic();

    inline void     anim_time(int32_t time)                           { this->anim_speed(time);                 }
    inline int32_t  anim_time()                                       { return this->anim_speed();              }

    std::vector<std::unique_ptr<GTile>> _v_screen;
    std::unique_ptr<GContainer> _u_cont_indics;

  private:
    uint8_t _num=0;

};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GMULTISCREEN_H__
