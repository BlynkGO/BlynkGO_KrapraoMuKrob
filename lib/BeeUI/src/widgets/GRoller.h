/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GRoller.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GROLLER_H__
#define __GROLLER_H__


#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GRoller : public GObject {
  public:
    GRoller(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GRoller(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GRoller();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    inline void visible_rows(uint32_t row_cnt)              { this->visible_row_count(row_cnt);     }
    String      selected();
    inline void option_align(text_align_t align)            { GObject::text_align(align);           }

    inline String toString()                                { return selected();                    }
    inline int    toInt()                                   { return this->toString().toInt();      }
    inline float  toFloat()                                 { return this->toString().toFloat();    }
    inline double toDouble()                                { return this->toString().toDouble();   }
    inline void toCharArray(char *buf, unsigned int bufsize, unsigned int index = 0){
      this->toString().toCharArray(buf, bufsize, index);
    }

    /*=====================
    * Setter functions
    *====================*/

    /**
     * Set the options on a roller
     * @param options   a string with '\n' separated options. E.g. "One\nTwo\nThree"
     * @param mode      `ROLLER_MODE_NORMAL` or `ROLLER_MODE_INFINITE`
     */
    void options(const char * options, roller_mode_t mode=ROLLER_MODE_INFINITE);

    void options(String* option, uint16_t option_num, roller_mode_t mode=ROLLER_MODE_INFINITE);

    void options(int from, int to, bool zero_front=false, roller_mode_t mode=ROLLER_MODE_INFINITE);

    /**
     * Set the selected option
     * @param sel_opt   index of the selected option (0 ... number of option - 1);
     * @param anim      ANIM_ON: set with animation; ANOM_OFF set immediately
     */
    void selected(uint32_t sel_opt, anim_enable_t anim=false);

    /**
     * Set the height to show the given number of rows (options)
     * @param row_cnt   number of desired visible rows
     */
    void visible_row_count(uint32_t row_cnt);



    /*=====================
    * Getter functions
    *====================*/

    /**
     * Get the index of the selected option
     * @return          index of the selected option (0 ... number of option - 1);
     */
    uint32_t selected_id();



    /**
     * Get the current selected option as a string.
     * @param buf       pointer to an array to store the string
     * @param buf_size  size of `buf` in bytes. 0: to ignore it.
     */
    void selected_str(char * buf, uint32_t buf_size);


    /**
     * Get the options of a roller
     * @return          the options separated by '\n'-s (E.g. "Option1\nOption2\nOption3")
     */
    const char * options();

    /**
     * Get the total number of options
     * @return      the total number of options
     */
    uint32_t option_count();

    // inline void font(const font_t&font)                     { GObject::font(font, GPART_SELECTED);          }
    // inline void font(const font_t&font, color_t color)      { GObject::font(font, color, GPART_SELECTED);   }
    // inline void font_color(color_t color)                   { GObject::font_color(color, GPART_SELECTED);   }
    inline void color(color_t color)                        { GObject::color(color, GPART_SELECTED);        }
    inline void bg_color(color_t color)                     { GObject::color(color, GPART_MAIN);            }
    inline void bg_color(color_t color,color_t grad_color)  { GObject::color(color, grad_color, GPART_MAIN);}
    inline void bg_opa(opa_t value)                         { GObject::bg_opa(value, GPART_MAIN);           }
    inline void bg_font(const font_t& font)                 { GObject::font(font, GPART_MAIN);              }
    inline void bg_font(const font_t& font, color_t color)  { GObject::font(font, color, GPART_MAIN);       }
    inline void bg_font_color(color_t color)                { GObject::font_color(color, GPART_MAIN);       }

    inline void font(const font_t&font_selected, const font_t&font_main){
      GObject::font(font_selected, GPART_SELECTED); 
      GObject::font(font_main    , GPART_MAIN);
    }

  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GROLLER_H__
