/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GList.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GLIST_H__
#define __GLIST_H__


#include "GObject.h"
#include "GPage.h"
#include <vector>

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------
struct list_option_t{
  const void*  img;
  const char*  str;
};

typedef std::vector<list_option_t> list_options_t;

class GList : public GPage {
  public:
    GList(GWidget& parent=GScreen)                          : GPage(&parent) {}
    GList(GWidget* parent)                                  : GPage(parent)  {}
    virtual ~GList();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }


           obj_t * add(const void * icon, String item_name);
    inline obj_t * add(const img_t* img, String item_name)  { return add((const void*) img, item_name);                   }
    inline obj_t * add(const img_t& img, String item_name)  { return add(&img, item_name);                                }
    inline obj_t * add(String item_name)                    { return add((const void*) NULL, item_name);                  }
    inline obj_t * add(list_option_t item_option)           { return add((const void*) item_option.img, item_option.str); }
           void    options(list_options_t options);

    String button_text(GWidget*widget);
    String selected();
    void   selected(String item);
    inline obj_t* button_selected()                         { return this->_btn_clicked;                          }


    inline String item_selected()                           { return this->selected();                            }
    uint32_t item_num();
    inline uint32_t num()                                   { return this->item_num();                            }

    // clear all items
    inline void clear()                                     { GObject::clean();                                   }

    //-----------------------------------------------------------------
    /**
     * Add text to a list
     * @param txt       text of the new label
     * @return          pointer to the created label
     */
    obj_t * add_text(const char * txt);

    /**
     * Add button to a list
     * @param icon      icon for the button, when NULL it will have no icon
     * @param txt       text of the new button, when NULL no text will be added
     * @return          pointer to the created button
     */
    obj_t * add_button(const void * icon, const char * txt);

    /**
     * Get text of a given list button
     * @param btn       pointer to the button
     * @return          text of btn, if btn doesn't have text "" will be returned
     */
    const char * button_text(obj_t * btn);


    /**
     * Set text of a given list button
     * @param btn       pointer to the button
     * @param txt       pointer to the text
     * @return          text of btn, if btn doesn't have text "" will be returned
     */
    void button_text(obj_t * btn, const char * txt);

    //-----------------------------------------------------------------

    bool     operator = (obj_t* list_obj);

    inline void bg_opa(opa_t value)           { lv_obj_set_style_bg_opa(obj, value, LV_STATE_DEFAULT);   this->button_bg_opa(value);     }
    inline void font_color(color_t value)     { GObject::font_color(value,GSTATE_DEFAULT);  this->button_font_color(value); }
    void button_bg_opa(opa_t value);
    void button_font_color(color_t value);

    obj_t* _btn_clicked = NULL;
  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GLIST_H__
