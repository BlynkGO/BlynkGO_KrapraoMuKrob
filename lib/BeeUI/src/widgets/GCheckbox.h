/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GCheckbox.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GCHECKBOX_H__
#define __GCHECKBOX_H__


#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GCheckbox : public GObject {
  public:
    GCheckbox(GWidget& parent=GScreen)                       : GObject(&parent) {}
    GCheckbox(GWidget* parent)                               : GObject(parent)  {}
    virtual ~GCheckbox();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    void          radio_design();
    void          choice_design(const void* choice);
    void          symbol(const void* symbol);

    inline  bool  isON()                                    { return this->checked();                                       }
    inline  bool  isOFF()                                   { return !this->isON();                                         }
    inline  void  ON()                                      { this->checked(true);   this->event_send(EVENT_VALUE_CHANGED); }
    inline  void  OFF()                                     { this->checked(false);  this->event_send(EVENT_VALUE_CHANGED); }
    inline  void  on()                                      { this->checked(true);                                          }
    inline  void  off()                                     { this->checked(false);                                         }

    /*=====================
    * Setter functions
    *====================*/

    /**
     * Set the text of a check box. `txt` will be copied and may be deallocated
     * after this function returns.
     * @param txt   the text of the check box. NULL to refresh with the current text.
     */
    void text(const char * txt);

    /**
     * Set the text of a check box. `txt` will be copied and may be deallocated
     * after this function returns.
     * @param txt   the text of the check box. NULL to refresh with the current text.
     */
    GCheckbox& operator =(const char* txt);
    GCheckbox& operator =(String txt);

    /**
     * Set the text of a check box. `txt` must not be deallocated during the life
     * of this checkbox.
     * @param txt   the text of the check box.
     */
    void text_static(const char * txt);

    /*=====================
    * Getter functions
    *====================*/

    /**
     * Get the text of a check box
     * @param obj   pointer to check box object
     * @return      pointer to the text of the check box
     */
    String text();

    using GObject::color;
    
    inline void     color(color_t color)                        { GObject::bg_color( color, (gstate_t) ( GPART_INDICATOR|GSTATE_CHECKED)); GObject::border_color( color, GPART_INDICATOR);          }
    inline color_t  color()                                     { return GObject::bg_color( (gstate_t) ( GPART_INDICATOR|GSTATE_CHECKED));                                                          }



  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GCHECKBOX_H__
