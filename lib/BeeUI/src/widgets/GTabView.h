/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GTabView.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GTABVIEW_H__
#define __GTABVIEW_H__


#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GTabView : public GObject {
  public:
    GTabView(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GTabView(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GTabView();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }


    /**
     * Add a tab to the tabview
     * @param name      the name of the tab, it will be displayed on the tab bar
     * @return          the widget where the content of the tab can be created
     */
    obj_t * add_tab(const char * name);

    /**
     * Change the name of the tab
     * @param idx       the index of the tab to rename
     * @param new_name  the new name as a string
     */
    void rename_tab(uint32_t idx, const char * new_name);

    /**
     * Show a tab
     * @param idx       the index of the tab to show
     * @param anim_en   ANIM_ON/OFF
     */
    void active(uint32_t idx, anim_enable_t anim_en);

    /**
     * Set the position of the tab bar
     * @param dir       DIR_TOP/BOTTOM/LEFT/RIGHT
     */
    void tab_bar_position(dir_t dir);

    /**
     * Set the width or height of the tab bar
     * @param size      size of the tab bar in pixels or percentage.
     *                  will be used as width or height based on the position of the tab bar)
     */
    void tab_bar_size(int32_t size);

    /**
     * Get the number of tabs
     * @return          the number of tabs
     */
    uint32_t tab_count();

    /**
     * Get the current tab's index
     * @return          the zero based index of the current tab
     */
    uint32_t tab_active();

    /**
     * Get the widget where the container of each tab is created
     * @return          the main container widget
     */
    obj_t * content();

    /**
     * Get the tab bar where the buttons are created
     * @return          the tab bar
     */
    obj_t * tab_bar();

};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GTABVIEW_H__
