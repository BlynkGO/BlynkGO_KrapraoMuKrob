/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GButton.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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
 *  Version 5.0
 * 
 *********************************************************************************
 */

#ifndef __GBUTTON_H__
#define __GBUTTON_H__


#include "GObject.h"
#include "GContainer.h"
#include "GLabel.h"
#include "GImage.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GButton : public GContainer {
  public:
    GButton(GWidget& parent=GScreen)                    : GContainer(&parent) {}
    GButton(GWidget* parent)                            : GContainer(parent)  {}
    GButton(String label, GWidget& parent=GScreen)      : _btn_str(label), GContainer(&parent) {}
    GButton(const char* label, GWidget& parent=GScreen) : _btn_str(label), GContainer(&parent) {}
    GButton(const char* label, GWidget* parent)         : _btn_str(label), GContainer(parent)  {}
    GButton(const img_t & src_img, String label, GWidget& parent=GScreen)   : _btn_img(&src_img), _btn_str(label), GContainer(&parent) {}   

    // button_type_t : BUTTON_PUSH (แบบปุ่มกด), BUTTON_SWITCH(แบบทำ switch)
    GButton(button_type_t type, GWidget& parent=GScreen)                    : _btn_type(type), GContainer(&parent) {}
    GButton(button_type_t type, GWidget* parent)                            : _btn_type(type), GContainer(parent)  {}
    GButton(button_type_t type, const char* label, GWidget& parent=GScreen) : _btn_type(type), _btn_str(label), GContainer(&parent) {}
    GButton(button_type_t type, const char* label, GWidget* parent)         : _btn_type(type), _btn_str(label), GContainer(parent)  {}

    virtual ~GButton();

    virtual void    create();
    inline  void    create(GWidget& parent)             { this->_par = &parent; this->create(); }
    inline  void    create(GWidget* parent)             { this->_par =  parent; this->create(); }

    /*  button_type_t : BUTTON_PUSH, BUTTON_SWITCH */
    void    button_type(button_type_t type);
    button_type_t button_type();

    /*  button_mode_t : BUTTON_MODE_NORMAL,  BUTTON_MODE_TOGGLE,  BUTTON_MODE_INACTIVE,*/
    void          mode(button_mode_t mode);  
    button_mode_t mode();

                      //สวิทซ์ ปล่อย  กด       สวิทซ์ปล่อย  ในโหมด Toggle
    /* button_state_t : RELEASED,  PRESSED,  TOGGLE_RELEASED,  TOGGLE_PRESSED,  INACTIVE, */
    void     state(button_state_t button_state); 
    button_state_t state();

    void    text(String txt);
    String  text();
    inline void setImage(const img_t &icon)             { this->setImage(&icon);                  }
    void setImage(const img_t* icon);
    inline const img_t* getImage()                      { return this->_btn_img;                  }
    inline void setSymbol(const void* symbol)  { 
      this->setImage((const img_t*) symbol); 
      _u_icon->font( this->font(GPART_INDICATOR), this->font_color(GPART_INDICATOR)); 
      _u_icon->translate(this->translate_x(GPART_INDICATOR), this->translate_y(GPART_INDICATOR));
    }
    inline const void* getSymbol()                      { return (const void*) this->_btn_img;    }

    using GObject::color;
    color_t      color();

    GButton& operator =(const String txt);
    GButton& operator =(GButton& btn_src);
    GButton& operator =(const img_t& btn_img);
    GButton& operator =(const img_t* btn_img);
    // GButton& operator =(GButton btn_copy);
    bool     operator = (obj_t* obj);

    // สำหรับ BUTTON_SWITCH ให้สลับ toggle เปิด->ปิด, หรือ ปิด->เปิด
    void toggle();
    inline bool isON()                                  { return this->checked();   }
    inline bool isOFF()                                 { return !this->checked() ; }
    inline void ON()                                    { this->checked(true);  this->event_send(EVENT_VALUE_CHANGED);   }
    inline void OFF()                                   { this->checked(false); this->event_send(EVENT_VALUE_CHANGED);   }
    inline void on()                                    { this->checked(true);  }
    inline void off()                                   { this->checked(false); }

    inline void round_design(){
      this->size(50,50);
      this->radius(RADIUS_CIRCLE);
      this->color(TFT_PALETTE_LIGHTEN(TFT_PALETTE_GREY,2));
      this->border(1, TFT_PALETTE_DARKEN(TFT_PALETTE_GREY,2));
      this->bg_opa(10 , GSTATE_DEFAULT);
      this->bg_opa(100, GSTATE_PRESSED);
      this->shadow_offset(0,0);
    }

    inline void long_mode(long_mode_t long_mode )       { create(); if(_u_label !=NULL) { _u_label->long_mode(long_mode); } }
    inline long_mode_t long_mode()                      { create(); return _u_label->long_mode();                           }
    // inline void parent(GWidget&parent)                  { GObject::parent(parent); this->event_send(EVENT_SIZE_CHANGED);    }
    // inline void parent(GWidget*parent)                  { GObject::parent(parent); this->event_send(EVENT_SIZE_CHANGED);    }

    inline void label_translate(int32_t x, int32_t y)   { create(); if(_u_label !=NULL) { _u_label->translate(x, y); }      }
    inline void icon_translate(int32_t x, int32_t y)    { create(); if(_u_icon !=NULL)  { _u_icon->translate(x, y);  }      }

    inline void label_show(bool enable)                 { create(); this->_u_label->show(enable);                           }
    inline bool label_show()                            { create(); return this->_u_label->show();                          }

    inline void label_width(int32_t w)                  { create(); this->_u_label->width(w);                               }
    inline void label_height(int32_t h)                 { create(); this->_u_label->height(h);                              }
    inline int32_t label_width()                        { create(); return this->_u_label->width();                         }
    inline int32_t label_height()                       { create(); return this->_u_label->height();                        }
    inline void label_size(int32_t w, int32_t h)        { create(); this->_u_label->size(w,h);                              }

    inline void icon_show(bool enable)                  { create(); if(_u_icon !=NULL) this->_u_icon->show(enable);         }
    inline bool icon_show()                             { create(); return (_u_icon !=NULL)? this->_u_icon->show() : false; }

    inline void icon_width(int32_t w)                   { create(); if(_u_icon !=NULL) this->_u_icon->width(w);             }
    inline void icon_height(int32_t h)                  { create(); if(_u_icon !=NULL) this->_u_icon->height(h);            }
    inline int32_t icon_width()                         { create(); return (_u_icon !=NULL)? this->_u_icon->width() : 0;    }
    inline int32_t icon_height()                        { create(); return (_u_icon !=NULL)? this->_u_icon->height() : 0;   }
    inline void icon_size(int32_t w, int32_t h)         { create(); if(_u_icon !=NULL) this->_u_icon->size(w,h);            }

    inline void symbol_font(const font_t* font)            { create(); if(_u_icon !=NULL) this->_u_icon->font(font);        this->font(font, GPART_INDICATOR);        }
    inline void symbol_font(const font_t& font)            { create(); if(_u_icon !=NULL) this->_u_icon->font(font);        this->font(font, GPART_INDICATOR);        }
    inline void symbol_font_color(color_t color)           { create(); if(_u_icon !=NULL) this->_u_icon->font_color(color); this->font_color(color, GPART_INDICATOR); }
    inline void symbol_font(const font_t* font, color_t c) { create(); if(_u_icon !=NULL) this->_u_icon->font(font, c);     this->font(font, c, GPART_INDICATOR);     }
    inline void symbol_font(const font_t& font, color_t c) { create(); if(_u_icon !=NULL) this->_u_icon->font(font, c);     this->font(font, c, GPART_INDICATOR);     }
    inline void symbol_translate_x(int32_t v)              { create(); if(_u_icon !=NULL) this->_u_icon->translate_x(v);    this->translate_x(v, GPART_INDICATOR);    }
    inline void symbol_translate_y(int32_t v)              { create(); if(_u_icon !=NULL) this->_u_icon->translate_y(v);    this->translate_y(v, GPART_INDICATOR);    }
    inline void symbol_translate(int32_t x, int32_t y)     { create(); if(_u_icon !=NULL) this->_u_icon->translate(x, y);   this->translate(x,y, GPART_INDICATOR);    }

    void link(obj_t* obj);

    std::unique_ptr<GImage> _u_icon;
    std::unique_ptr<GLabel> _u_label;
    button_type_t _btn_type = BUTTON_PUSH;
    button_mode_t _btn_mode = BUTTON_MODE_NORMAL;
    button_state_t _btn_state = RELEASED;
  private:
    String _btn_str = "button";
    const img_t * _btn_img = NULL;   /* pointer img_t ไปยัง c file */

};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GBUTTON_H__
