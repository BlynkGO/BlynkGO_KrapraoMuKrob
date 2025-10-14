/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GStep.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GSTEP_H__
#define __GSTEP_H__


#include "GObject.h"
#include "GContainer.h"
#include "GButton.h"
#include "GLabel.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------
#define DEFAULT_STEP    -1

class GStep : public GContainer {
  public:
    GStep(GWidget& parent=GScreen)                          : GContainer(&parent) {}
    GStep(GWidget* parent)                                  : GContainer(parent)  {}

    virtual ~GStep();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    void    range(double val_min, double val_max);
    void    value(double val);
    double  value();
    double  value_min();
    double  value_max();
    void    step(double step);
    double  step();
    void    decimal(uint8_t decimal);
    uint8_t decimal();

    void    inactive(bool en);
    bool    inactive();

    inline void active(bool en)                             { this->inactive(!en);            }
    inline bool active()                                    { return !this->inactive();       }

    inline void plus(double step  = DEFAULT_STEP)           { this->value(this->value()+ (step)? step : this->_step );  }
    inline void minus(double step = DEFAULT_STEP)           { this->value(this->value()- (step)? step : this->_step );  }

    GStep&  operator =(double value);
    inline int toInt()                                      { return (int) this->value();     }
    inline float toFloat()                                  { return (float) this->value();   }
    inline double toDouble()                                { return (double) this->value();  }


    /*=====================
    * Design functions
    *====================*/
   
    inline void font(const font_t * font)                   { if(!this->isCreated()) create(); GContainer::font(font); this->refresh_size();  }
    inline void font(const font_t  &font)                   { if(!this->isCreated()) create(); GContainer::font(font); this->refresh_size();  }
    inline void font(const font_t * font, color_t color)    { this->font(font); this->text_color(color);                                      }
    inline void font(const font_t  &font, color_t color)    { this->font(font, color);                                                        }
    // inline void font_color(color_t color)                   { this->font_color(color);                                                        }
    
    void button_size(int32_t w, int32_t h);
    void button_radius(int32_t r, gstate_t gstate= GSTATE_DEFAULT);
    void button_border(int32_t w, color_t color, gstate_t gstate= GSTATE_DEFAULT);
    void button_color(color_t color, gstate_t gstate= GSTATE_DEFAULT);
    void button_font(font_t &font, gstate_t gstate= GSTATE_DEFAULT);
    void button_font(font_t &font, color_t color, gstate_t gstate= GSTATE_DEFAULT);
    void button_font_color(color_t color, gstate_t gstate= GSTATE_DEFAULT);

    inline void color(color_t color, gstate_t gstate= GSTATE_DEFAULT)     { this->button_color(color, gstate);  }

    std::unique_ptr<GButton> _u_button[2];
    std::unique_ptr<GLabel> _u_label;
    double   _step_internal=1;
    double   _step=1;
    uint8_t _decimal=0;

  private:
    double   _val=0, _val_min=0, _val_max=100;
    void    refresh_size();

};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GSTEP_H__
