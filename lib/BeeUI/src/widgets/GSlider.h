/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GSlider.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GSLIDER_H__
#define __GSLIDER_H__


#include "GObject.h"
#include "GBar.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GSlider : public GBar {
  public:
    GSlider(GWidget& parent=GScreen)                        : GBar(&parent) {}
    GSlider(GWidget* parent)                                : GBar(parent)  {}
    virtual ~GSlider();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    area_t &left_knob_area();
    area_t &right_knob_area();

    /**
     * Set a new value on the gauge
     * @param value     new value
     */
    GSlider& operator=(int32_t value);

    /**
     * Set the mode of slider.
     * @param mode      the mode of the slider. See :: slider_mode_t : SLIDER_MODE_NORMAL, SLIDER_MODE_SYMMETRICAL, SLIDER_MODE_RANGE
     */
    inline void  mode(slider_mode_t mode)                           { GBar::mode(mode);                             }

    /**
     * Get the mode of the slider.
     * @return          see :: slider_mode_t
     */
    inline slider_mode_t mode()                                     { return GBar::mode();                          }

    /**
     * Set a new value for the left knob of a slider
     * @param value     new value
     * @param anim      true: set the value with an animation; false: change the value immediately
     */
    inline void left_value(int32_t value, bool anim_enable=true)    { GBar::start_value(value, anim_enable);        }

    /**
     * Get the value of the left knob of a slider
     * @return          the value of the left knob of the slider
     */
    inline int32_t left_value()                                     { return GBar::start_value();                   }

    inline void     knob_color(color_t color)                       { GObject::bg_color(color, GPART_KNOB);         }
    inline color_t  knob_color()                                    { return GObject::bg_color(GPART_KNOB);         }
    inline void     knob_opa(opa_t opa)                             { GObject::bg_opa(opa, GPART_KNOB);             }
    inline opa_t    knob_opa()                                      { return GObject::bg_opa(GPART_KNOB);           }
    inline void     knob_border(int32_t width)                      { GObject::border(width, GPART_KNOB);           }
    inline void     knob_border(int32_t width, color_t color)       { GObject::border(width, color, GPART_KNOB);    }
    inline int32_t  knob_border()                                   { return GObject::border(GPART_KNOB);           }
    inline void     knob_border_color(color_t color)                { GObject::border_color(color, GPART_KNOB);     }
    inline opa_t    knob_border_color()                             { return GObject::border_color(GPART_KNOB);     }
    inline void     knob_padding(int32_t padding)                   { GObject::padding(padding, GPART_KNOB);        }
    inline int32_t  knob_padding()                                  { return GObject::padding(GPART_KNOB);          }
    inline void     knob_pad(int32_t padding)                       { this->knob_padding(padding);                  }
    inline int32_t  knob_pad()                                      { return this->knob_padding();                  }
    inline void     knob_radius(int32_t r)                          { GObject::radius(r, GPART_KNOB);               }
    inline int32_t  knob_radius()                                   { return GObject::radius(GPART_KNOB);           }
    
  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GSLIDER_H__
