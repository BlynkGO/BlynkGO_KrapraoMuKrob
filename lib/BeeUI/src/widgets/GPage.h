/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GPage.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GPAGE_H__
#define __GPAGE_H__


#include "GObject.h"
#include "GContainer.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GPage : public GContainer {
  public:
    GPage(GWidget& parent=GScreen)                          : GContainer(&parent) {}
    GPage(GWidget* parent)                                  : GContainer(parent)  {}
    GPage(layout_t layout, GWidget& parent=GScreen)         : GContainer(layout, &parent)  {}
    GPage(layout_t layout, GWidget* parent)                 : GContainer(layout,  parent)  {}

    GPage(layout_t layout, int32_t padding, GWidget& parent=GScreen) 
      : GContainer(layout, padding, &parent) 
    {}

    GPage(layout_t layout, int32_t padding, GWidget* parent)
      : GContainer(layout, padding, parent) 
    {}

    GPage(layout_t layout, int32_t p_top, int32_t p_bottom, int32_t p_left, int32_t p_right, GWidget& parent=GScreen) 
      : GContainer(layout, p_top, p_bottom, p_left, p_right, &parent) 
    {}

    GPage(layout_t layout, int32_t p_top, int32_t p_bottom, int32_t p_left, int32_t p_right, GWidget* parent)
      : GContainer(layout, p_top, p_bottom, p_left, p_right,  parent) 
    {}

    GPage(layout_t layout, int32_t p_top, int32_t p_bottom, int32_t p_left, int32_t p_right, int32_t p_inner, GWidget& parent=GScreen) 
      : GContainer(layout, p_top, p_bottom, p_left, p_right, p_inner, &parent) 
    {}

    GPage(layout_t layout, int32_t p_top, int32_t p_bottom, int32_t p_left, int32_t p_right, int32_t p_inner, GWidget* parent)
      : GContainer(layout, p_top, p_bottom, p_left, p_right, p_inner, parent) 
    {}

    GPage(layout_t layout, int32_t p_top, int32_t p_bottom, int32_t p_left, int32_t p_right, int32_t p_row, int32_t p_column, GWidget& parent=GScreen)
      : GContainer(layout, p_top, p_bottom, p_left, p_right, p_row, p_column,  &parent) 
    {}

    GPage(layout_t layout, int32_t p_top, int32_t p_bottom, int32_t p_left, int32_t p_right, int32_t p_row, int32_t p_column, GWidget* parent)
      : GContainer(layout, p_top, p_bottom, p_left, p_right, p_row, p_column,  parent) 
    {}

    GPage(GRID_COL col_dsc, GRID_ROW row_dsc, GWidget& parent=GScreen)
    : GContainer(col_dsc, row_dsc, &parent)
    {}

    GPage(GRID_COL col_dsc, GRID_ROW row_dsc, GWidget* parent)
    : GContainer(col_dsc, row_dsc,  parent)
    {}


    virtual ~GPage();
 
    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();   }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();   }

    void layout(layout_t layout);
    inline layout_t layout()                                { return GContainer::layout();            }
    
    inline void layout(layout_t layout, uint16_t padding) {
      this->layout(layout); this->padding(padding);
    }

    inline void layout(layout_t layout, uint16_t p_top, uint16_t p_bottom, uint16_t p_left, uint16_t p_right) {
      this->layout(layout); this->padding(p_top,p_bottom,p_left,p_right);
    }

    inline void layout(layout_t layout, uint16_t p_top, uint16_t p_bottom, uint16_t p_left, uint16_t p_right, uint16_t p_inner) {
      this->layout(layout); this->padding(p_top,p_bottom,p_left,p_right, p_inner);      
    }

    inline void layout(layout_t layout, uint16_t p_top, uint16_t p_bottom, uint16_t p_left, uint16_t p_right, uint16_t p_row, uint16_t p_column) {
      this->layout(layout); this->padding(p_top,p_bottom,p_left,p_right, p_row,p_column);       
    }

    using GObject::scroll_dir; 
    using GObject::grid_align;

    using GObject::operator=;

    // ----- API compatable กับ BlynkGOv2, v3 ---------------
    // inline void scrollbar(scrollbar_mode_t mode, bool scroll_hor , bool scroll_ver ){ 
    //   GObject::scrollbar_mode(mode); GObject::scroll_dir( (dir_t) ((int)(scroll_ver? DIR_VER : DIR_NONE ) | (int)(scroll_hor? DIR_HOR : DIR_NONE )));
    // }

    inline void scrollbar(scrollbar_mode_t mode, bool scroll_hor , bool scroll_ver )  { GObject::scrollbar(mode, scroll_hor, scroll_ver); }

    inline void scroll_pos(int32_t posX, int32_t posY)      { GObject::scroll_to(posX, posY, false);                      }
    inline void scroll_posX(int32_t pos)                    { GObject::scroll_to_x(pos, false);                           }
    inline void scroll_posY(int32_t pos)                    { GObject::scroll_to_y(pos, false);                           }
    inline int32_t scroll_posX()                            { return GObject::scroll_x();                                 }
    inline int32_t scroll_posY()                            { return GObject::scroll_y();                                 }
    
    inline void scrollTop()                                 { GObject::scroll_to_y(0, false);                             } // เลื่อนไปบนสุดของ GPage
    // inline void scrollBottom();                          { GObject::scroll_to_y(, false);                              } // เลื่อนไปล่างสุดของ GPage
    inline void scrollLeft()                                { GObject::scroll_to_x(0, false);                             } // เลื่อนไปซ้ายสุดของ GPage
    inline void scrollRight()                               { /*GObject::scroll_to_x(0, false);*/                         } // เลื่อนไปขวาสุดของ GPage

    
  private:

};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GPAGE_H__
