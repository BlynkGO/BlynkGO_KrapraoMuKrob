/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GGaugeRainbow.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GGAUGERAINBOW_H__
#define __GGAUGERAINBOW_H__

#include "GObject.h"
#include "widgets_extra/gaugerainbow/lv_gaugerainbow.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GGaugeRainbow : public GObject {
  public:
    GGaugeRainbow(GWidget& parent=GScreen)                  : GObject(&parent) {}
    GGaugeRainbow(GWidget* parent)                          : GObject(parent)  {}
    virtual ~GGaugeRainbow();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    // gauge_type_t : GAUGE_TYPE_ARC (defaut) , GAUGE_TYPE_FULL
    inline void   gauge_type(gauge_type_t type)             { this->create(); lv_gaugerainbow_set_type(this->obj, (gauge_type_t) type);   }
    inline gauge_type_t  gauge_type()                       { this->create(); return (gauge_type_t) lv_gaugerainbow_get_type(this->obj);  }

    inline void   range(float val_min, float val_max)       { this->create(); lv_gaugerainbow_set_range(this->obj, val_min, val_max);     }
    inline void   value(float val , int8_t decimal_num=-1)  { this->create(); lv_gaugerainbow_set_value(this->obj, val); if(decimal_num>=0) lv_gaugerainbow_set_decimal(this->obj,(uint8_t) decimal_num); }
    inline float  value()                                   { this->create(); return lv_gaugerainbow_get_value(this->obj);                }
    inline float  value_max()                               { this->create(); return lv_gaugerainbow_get_max_value(this->obj);            }
    inline float  value_min()                               { this->create(); return lv_gaugerainbow_get_min_value(this->obj);            }

    inline int    toInt()                                   { return (int) this->value();     }
    inline float  toFloat()                                 { return this->value();           }

    inline void    decimal(uint8_t decimal_num)             { this->create(); lv_gaugerainbow_set_decimal(this->obj, decimal_num);        }
    inline uint8_t decimal()                                { this->create(); return lv_gaugerainbow_get_decimal(this->obj);              }

    inline void   angle_offset(float a)                     { this->create(); lv_gaugerainbow_set_angle_offset(this->obj, a);             }
    inline float  angle_offset()                            { this->create(); return lv_gaugerainbow_get_angle_offset(this->obj);         }

    inline void   angle_total(float a)                      { this->create(); lv_gaugerainbow_set_angle_total(this->obj, a);              }
    inline float  angle_total()                             { this->create(); return lv_gaugerainbow_get_angle_total(this->obj);          }

    GGaugeRainbow& operator =(float num);

    // using GObject::color;
    using GObject::font;
    using GObject::font_color;

    inline void      color(color_t color_begin, color_t color_end)                   { this->create(); lv_gaugerainbow_set_color_begin(this->obj, TFT_COLOR(color_begin)); lv_gaugerainbow_set_color_end(this->obj, TFT_COLOR(color_end)); }
    inline void      color(color_t color_begin, color_t color_end, color_t color_bg) { this->create(); lv_gaugerainbow_set_color(this->obj, TFT_COLOR(color_begin), TFT_COLOR(color_end), TFT_COLOR(color_bg)); }
    inline void      color_bg(color_t color_bg)             { this->create(); lv_gaugerainbow_set_color_bg(this->obj, TFT_COLOR(color_bg)); }
    inline color_t   color_begin()                          { this->create(); return COLOR16(lv_gaugerainbow_get_color_begin(this->obj));   }
    inline color_t   color_end()                            { this->create(); return COLOR16(lv_gaugerainbow_get_color_end(this->obj));     }
    inline color_t   color_bg()                             { this->create(); return COLOR16(lv_gaugerainbow_get_color_bg(this->obj));      }

    inline void      thickness(int32_t thick)               { GObject::arc_width(thick, GPART_ITEMS);       }
    inline int32_t   thickness()                            { return GObject::arc_width(GPART_ITEMS);       }
    inline void      thick(int32_t thick)                   { this->thickness(thick);                       }
    inline int32_t   thick()                                { return this->thickness();                     }

    inline void    gauge_translate(int32_t x, int32_t y)    { GObject::translate(x,y, GPART_ITEMS);         }
    inline void    gauge_translate_x(int32_t x)             { GObject::translate_x(x, GPART_ITEMS);         }
    inline void    gauge_translate_y(int32_t y)             { GObject::translate_y(y, GPART_ITEMS);         }
    inline int32_t gauge_translate_x()                      { return GObject::translate_x(GPART_ITEMS);     }
    inline int32_t gauge_translate_y()                      { return GObject::translate_y(GPART_ITEMS);     }
    inline void    value_translate(int32_t x, int32_t y)    { GObject::translate(x,y, GPART_INDICATOR);     }
    inline void    value_translate_x(int32_t x)             { GObject::translate_x(x, GPART_INDICATOR);     }
    inline void    value_translate_y(int32_t y)             { GObject::translate_y(y, GPART_INDICATOR);     }
    inline int32_t value_translate_x()                      { return GObject::translate_x(GPART_INDICATOR); }
    inline int32_t value_translate_y()                      { return GObject::translate_y(GPART_INDICATOR); }

    inline void  font(const font_t& font)                   { GObject::font(font, GPART_INDICATOR);         }
    inline void  font(const font_t& font, color_t color)    { GObject::font(font, color, GPART_INDICATOR);  }
    inline void  font_color(color_t color)                  { GObject::font_color(color, GPART_INDICATOR);  }
    inline const font_t* font()                             { return GObject::font(GPART_INDICATOR);        }
    inline color_t font_color()                             { return GObject::font_color(GPART_INDICATOR);  }

};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GGAUGERAINBOW_H__
