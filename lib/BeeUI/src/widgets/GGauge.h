/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GGauge.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GGAUGE_H__
#define __GGAUGE_H__


#include "GObject.h"
#include "GArc.h"
#include "GLabel.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------
enum {
  GAUGE_MODE_NORMAL,
  GAUGE_MODE_FULL,
};
typedef uint8_t gauge_mode_t;

class GGauge : public GArc {
  public:
    GGauge(GWidget& parent=GScreen)                          : GArc(&parent) {}
    GGauge(GWidget* parent)                                  : GArc(parent)  {}
    virtual ~GGauge();

    virtual void    create();
    inline  void    create(GWidget& parent)                   { this->_par = &parent; this->create(); }
    inline  void    create(GWidget* parent)                   { this->_par =  parent; this->create(); }

    inline void     decimal(uint32_t decimal)                 { this->_decimal = decimal;             }
    inline uint32_t decimal()                                 { return this->_decimal;                }

    void mode(gauge_mode_t mode);

    // /**
    //  * Set a new value on the gauge
    //  * @param value     new value
    //  */
    void value(float value);

    /**
     * Set a new value on the gauge
     * @param value     new value
     */
    GGauge& operator=(float value);


    /**
     * Get the value of an arc
     * @return          the value of the arc
     */
    // inline float value()                          { return _value;              }
    float value();

    /**
     * Get the value of an arc
     * @return          the value of the arc
     */
    inline float  toFloat()                       { return this->value();       }
    inline int    toInt()                         { return (int) this->value(); }


    class knob_class {
      public:
        knob_class(GGauge *gauge)                                 { _gauge = gauge;                     }
        inline void enable(bool enable)                           { _gauge->knob_enable(enable);        }
        inline bool enable()                                      { return _gauge->knob_enable();       }
        inline void clickable(bool enable)                        { _gauge->clickable(enable);          }
        inline bool clickable()                                   { return _gauge->clickable();         }
        inline void offset(int32_t offset)                        { _gauge->knob_offset(offset);        }
        inline int32_t offset()                                   { return _gauge->knob_offset();       }
        inline void color(color_t color)                          { _gauge->knob_color(color);          }
        inline color_t color()                                    { return _gauge->knob_color();        }
        inline void opa(uint8_t opa)                              { _gauge->knob_opa(opa);              }
        inline uint8_t opa()                                      { return _gauge->knob_opa();          }
        inline void padding(uint16_t padding)                     { _gauge->knob_padding(padding);      }
        inline uint16_t padding()                                 { return _gauge->knob_padding();      }
        inline void border(uint16_t w)                            { _gauge->knob_border(w);             }
        inline uint16_t border()                                  { return _gauge->knob_border();       }
        inline void border_color(color_t color)                   { _gauge->knob_border_color(color);   }
        inline color_t border_color()                             { return _gauge->knob_border_color(); }
        inline void border(uint16_t w,color_t color)              { _gauge->knob_border(w,color);       }
        inline void border_opa(uint8_t opa)                       { _gauge->knob_border_opa(opa);       }
        inline uint8_t border_opa()                               { return _gauge->knob_border_opa();   }
      private:
        GGauge* _gauge;
    };
    knob_class knob= knob_class(this);

    inline void knob_enable(bool enable)                          { _knob_enable = enable; GObject::opa((enable)? 255:0, (gstate_t) (GPART_KNOB | GSTATE_DEFAULT)); this->clickable(enable);  if(enable) this->rounded(true);  }
    inline bool knob_enable()                                     { return _knob_enable; }

    std::unique_ptr<GLabel> _u_label;
    float    _value;
    uint32_t _decimal = 2;
  private:
};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GGAUGE_H__
