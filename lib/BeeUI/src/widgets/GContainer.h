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

#ifndef __GCONTAINER_H__
#define __GCONTAINER_H__


#include "GObject.h"
#include <vector>

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------



class GContainer : public GObject {
  public:
    GContainer(GWidget& parent=GScreen)                           : GObject(parent)  { this->_layout= LAYOUT_COL_M; }
    GContainer(GWidget* parent)                                   : GObject(parent)  { this->_layout= LAYOUT_COL_M; }
    GContainer(GContainer& parent)                                : GObject(parent)  { this->_layout= LAYOUT_COL_M; }
    GContainer(GContainer* parent)                                : GObject(parent)  { this->_layout= LAYOUT_COL_M; }
    GContainer(layout_t layout, GWidget& parent=GScreen)          : GObject(parent)  { this->_layout= layout;       }
    GContainer(layout_t layout, GWidget* parent)                  : GObject(parent)  { this->_layout= layout;       }

    GContainer(layout_t layout, int32_t padding, GWidget& parent=GScreen) 
      : GObject(&parent), _p_top(padding), _p_bottom(padding), _p_left(padding), _p_right(padding), _p_row(padding), _p_column(padding)
    { this->_layout= layout; }

    GContainer(layout_t layout, int32_t padding, GWidget* parent)
      : GObject(parent), _p_top(padding), _p_bottom(padding), _p_left(padding), _p_right(padding), _p_row(padding), _p_column(padding)
    { this->_layout= layout; }

    GContainer(layout_t layout, int32_t p_top, int32_t p_bottom, int32_t p_left, int32_t p_right, GWidget& parent=GScreen) 
      : GObject(&parent), _p_top(p_top), _p_bottom(p_bottom), _p_left(p_left), _p_right(p_right)
    { this->_layout= layout; }

    GContainer(layout_t layout, int32_t p_top, int32_t p_bottom, int32_t p_left, int32_t p_right, GWidget* parent)
      : GObject(parent), _p_top(p_top), _p_bottom(p_bottom), _p_left(p_left), _p_right(p_right)
    { this->_layout= layout; }

    GContainer(layout_t layout, int32_t p_top, int32_t p_bottom, int32_t p_left, int32_t p_right, int32_t p_inner, GWidget& parent=GScreen) 
      : GObject(&parent), _p_top(p_top), _p_bottom(p_bottom), _p_left(p_left), _p_right(p_right), _p_row(p_inner), _p_column(p_inner)
    { this->_layout= layout; }

    GContainer(layout_t layout, int32_t p_top, int32_t p_bottom, int32_t p_left, int32_t p_right, int32_t p_inner, GWidget* parent)
      : GObject(parent), _p_top(p_top), _p_bottom(p_bottom), _p_left(p_left), _p_right(p_right), _p_row(p_inner), _p_column(p_inner)
    { this->_layout= layout; }

    GContainer(layout_t layout, int32_t p_top, int32_t p_bottom, int32_t p_left, int32_t p_right, int32_t p_row, int32_t p_column, GWidget& parent=GScreen)
      : GObject(&parent), _p_top(p_top), _p_bottom(p_bottom), _p_left(p_left), _p_right(p_right), _p_row(p_row), _p_column(p_column)
    { this->_layout= layout; }

    GContainer(layout_t layout, int32_t p_top, int32_t p_bottom, int32_t p_left, int32_t p_right, int32_t p_row, int32_t p_column, GWidget* parent)
      : GObject(parent), _p_top(p_top), _p_bottom(p_bottom), _p_left(p_left), _p_right(p_right), _p_row(p_row), _p_column(p_column)
    { this->_layout= layout; }

    GContainer(GRID_COL col_dsc, GRID_ROW row_dsc, GWidget& parent=GScreen)
    : GObject(&parent)
    {
      this->_layout= LAYOUT_GRID_CELL; 
      this->_u_col_dsc.reset(new GRID_COL(col_dsc)); _u_col_dsc->push_back(LV_GRID_TEMPLATE_LAST);
      this->_u_row_dsc.reset(new GRID_ROW(row_dsc)); _u_row_dsc->push_back(LV_GRID_TEMPLATE_LAST);
    }

    GContainer(GRID_COL col_dsc, GRID_ROW row_dsc, GWidget* parent)
    : GObject(parent)
    {
      this->_layout= LAYOUT_GRID_CELL; 
      this->_u_col_dsc.reset(new GRID_COL(col_dsc)); _u_col_dsc->push_back(LV_GRID_TEMPLATE_LAST);
      this->_u_row_dsc.reset(new GRID_ROW(row_dsc)); _u_row_dsc->push_back(LV_GRID_TEMPLATE_LAST);
    }

    GContainer(GRID_COL col_dsc, GRID_ROW row_dsc, opa_t bg_opa, GWidget& parent=GScreen)
    : GObject(&parent), _bg_opa(bg_opa)
    {
      this->_layout= LAYOUT_GRID_CELL; 
      this->_u_col_dsc.reset(new GRID_COL(col_dsc)); _u_col_dsc->push_back(LV_GRID_TEMPLATE_LAST);
      this->_u_row_dsc.reset(new GRID_ROW(row_dsc)); _u_row_dsc->push_back(LV_GRID_TEMPLATE_LAST);
    }

    GContainer(GRID_COL col_dsc, GRID_ROW row_dsc, opa_t bg_opa, GWidget* parent)
    : GObject(parent), _bg_opa(bg_opa)
    {
      this->_layout= LAYOUT_GRID_CELL; 
      this->_u_col_dsc.reset(new GRID_COL(col_dsc)); _u_col_dsc->push_back(LV_GRID_TEMPLATE_LAST);
      this->_u_row_dsc.reset(new GRID_ROW(row_dsc)); _u_row_dsc->push_back(LV_GRID_TEMPLATE_LAST);
    }

    virtual ~GContainer();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    using GObject::operator=;
    using GObject::layout;
    using GObject::FLEX;
    using GObject::GRID_CELL;

  protected:
    opa_t    _bg_opa = OPA_100;
    int32_t  _p_top=13, _p_bottom=13, _p_left=13, _p_right=13, _p_row=8, _p_column=8;
};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GCONTAINER_H__
