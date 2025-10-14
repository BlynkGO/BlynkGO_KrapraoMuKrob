/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GDropdownList.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GDROPDOWLIST_H__
#define __GDROPDOWLIST_H__


#include "GObject.h"
#include <vector>

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

#define DROPDOWN_POS_LAST 0xFFFF

class GDropdownList : public GObject {
  public:
    GDropdownList(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GDropdownList(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GDropdownList();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }
 
    inline String toString()    { return selected_str();                }
    inline int    toInt()       { return this->toString().toInt();      }
    inline float  toFloat()     { return this->toString().toFloat();    }
    inline double toDouble()    { return this->toString().toDouble();   }
    inline void toCharArray(char *buf, unsigned int bufsize, unsigned int index = 0){
      this->toString().toCharArray(buf, bufsize, index);
    }

    /**
     * Set text of the drop-down list's button.
     * If set to `NULL` the selected option's text will be displayed on the button.
     * If set to a specific text then that text will be shown regardless of the selected option.
     * @param txt       the text as a string (Only its pointer is saved)
     */
    void text(const char * txt);

    /**
     * Set the options in a drop-down list from a string.
     * The options will be copied and saved in the object so the `options` can be destroyed after calling this function
     * @param options   a string with '\n' separated options. E.g. "One\nTwo\nThree"
     */
    void options(const char * options);                       // ตัวอย่าง "aaa\nbbb\nccc\nddd"
 
    void options(int from, int to, bool zero_front=false);    // ใส่ options ด้วยตัวเลข ตั้งแต่ จนถึงค่าสุดท้าย
    void options(String* option, int32_t option_num);         // ใส่ options ด้วย String Array
    void options(std::vector<String> options);                // ใส่ options ด้วย std::vector<String>

    /**
     * Set the options in a drop-down list from a static string (global, static or dynamically allocated).
     * Only the pointer of the option string will be saved.
     * @param options   a static string with '\n' separated options. E.g. "One\nTwo\nThree"
     */
    void options_static( const char * options);

    /**
     * Add an options to a drop-down list from a string.  Only works for non-static options.
     * @param option    a string without '\n'. E.g. "Four"
     * @param pos       the insert position, indexed from 0, DROPDOWN_POS_LAST = end of string
     */
    void add_option(const char * option, uint32_t pos=DROPDOWN_POS_LAST);

    inline void add_option(String option, uint32_t pos=DROPDOWN_POS_LAST){
      this->add_option(option.c_str(), pos);
    }

    inline void addOption(const char * option, uint32_t pos=DROPDOWN_POS_LAST){
      this->add_option(option, pos);
    }

    inline void addOption(String option, uint32_t pos= DROPDOWN_POS_LAST){
      this->add_option(option.c_str(), pos);
    }

    /**
     * Clear all options in a drop-down list.  Works with both static and dynamic options.
     */
    void clear_options();

    /**
     * Set the selected option
     * @param option_id   id of the selected option (0 ... number of option - 1);
     */
    void selected(uint32_t option_id);

    /**
     * Set the direction of the a drop-down list
     * @param dir       LV_DIR_LEFT/RIGHT/TOP/BOTTOM
     */
    void dir(dir_t dir);

    /**
     * Set an arrow or other symbol to display when on drop-down list's button. Typically a down caret or arrow.
     * @param symbol    a text like `SYMBOL_DOWN`, an image (pointer or path) or NULL to not draw symbol icon
     * @note angle and zoom transformation can be applied if the symbol is an image.
     * E.g. when drop down is checked (opened) rotate the symbol by 180 degree
     */
    void symbol(const void * symbol);

    /**
     * Set whether the selected option in the list should be highlighted or not
     * @param en        true: highlight enabled; false: disabled
     */
    void selected_highlight(bool en);

    void height_open(int32_t value);

    /*=====================
    * Getter functions
    *====================*/

    /**
     * Get the list of a drop-down to allow styling or other modifications
     * @return          pointer to the list of the drop-down
     */
    obj_t * list_obj();

    /**
     * Get text of the drop-down list's button.
     * @return      the text as string, `NULL` if no text
     */
    const char * text();

    /**
     * Get the options of a drop-down list
     * @return          the options separated by '\n'-s (E.g. "Option1\nOption2\nOption3")
     */
    const char * options();

    /**
     * Get the index of the selected option
     * @return          index of the selected option (0 ... number of option - 1);
     */
    inline uint32_t selected_id()                     { return this->_selected(); }

    /**
     * Get the current selected option as a string
     * @return          the string of selected option
     */
    String selected_str(); 
    inline String selected()                          { return selected_str();  }

    /**
     * Get the total number of options
     * @return          the total number of options in the list
     */
    uint32_t option_count();


    /**
     * Get the index of an option.
     * @param option    an option as string
     * @return          index of `option` in the list of all options. -1 if not found.
     */
    int32_t option_index(const char * option);

    /**
     * Get the symbol on the drop-down list. Typically a down caret or arrow.
     * @return          the symbol or NULL if not enabled
     */
    const char * symbol();

    /**
     * Get whether the selected option in the list should be highlighted or not
     * @return          true: highlight enabled; false: disabled
     */
    bool selected_highlight();

    /**
     * Get the direction of the drop-down list
     * @return          LV_DIR_LEF/RIGHT/TOP/BOTTOM
     */
    dir_t dir();

    int32_t height_open();

    /*=====================
    * Other functions
    *====================*/

    /**
     * Open the drop.down list
     */
    void open();
    inline void OPEN()          { this->open();             }

    /**
     * Close (Collapse) the drop-down list
     */
    void close();
    inline void CLOSE()         { this->close();            }

    /**
     * Tells whether the list is opened or not
     * @return          true if the list os opened
     */
    bool is_open();

    inline bool isOPEN()        { return this->is_open();   }
    inline bool isCLOSE()       { return !this->is_open();  }

    /************************
     * Style
     ************************/
    inline void font(const font_t& font)                        { button_font(font);        list_font(font);        selected_font(font);          }
    inline void font(const font_t& font, color_t color)         { button_font(font,color);  list_font(font,color);  selected_font(font, color);   }
    inline void font_color(color_t color)                       { button_font_color(color); list_font_color(color); selected_font_color(color);   }
    inline void color(color_t color)                            { button_color(color);      selected_color(color);                                }
    inline void text_align(text_align_t text_align)             { list_text_align(text_align);                                                    }

    // using GObject::color;
    // using GObject::font;
    // using GObject::font_color;
    // using GObject::text_align;

    inline void symbol_font(const font_t&font)                      { GObject::font(font, GPART_INDICATOR);                         }
    
    // ปุ่มที่ไว้กด ก่อน list จะแสดงขึ้นมา
    inline void button_font(const font_t&font)                      { GObject::font(font,GPART_MAIN);                               }
    inline void button_font(const font_t&font,color_t color)        { GObject::font(font,color,GPART_MAIN);                         }
    inline void button_font_color(color_t color)                    { GObject::font_color(color,GPART_MAIN);                        }
    inline void button_border(int32_t value)                        { GObject::border(value,GPART_MAIN);                            }
    inline void button_border(int32_t value, color_t color)         { GObject::border(value, color,GPART_MAIN);                     }
    inline void button_radius(int32_t value)                        { GObject::radius(value,GPART_MAIN);                            }
    inline void button_border_opa(opa_t value)                      { GObject::border_opa(value,GPART_MAIN);                        }
    inline void button_color(color_t color)                         { GObject::bg_color(color,GPART_MAIN);                          }
    inline void button_grad_color(color_t color)                    { GObject::grad_color(color,GPART_MAIN);                        }
    inline void button_color(color_t bg_color, color_t grad_color)  { GObject::color(bg_color, grad_color,GPART_MAIN);              }

    inline void list_width(int32_t value, gstate_t gstate=GPART_MAIN)                       { lv_obj_set_style_width( list_obj(), value, gstate);                                 }
    inline void list_height(int32_t value, gstate_t gstate=GPART_MAIN)                      { lv_obj_set_style_height( list_obj(), value, gstate);                                }
    inline void list_font(const font_t& font, gstate_t gstate=GPART_MAIN)                   { lv_obj_set_style_text_font (list_obj(),&font, gstate);                              }
    inline void list_font_color(color_t color, gstate_t gstate=GPART_MAIN)                  { lv_obj_set_style_text_color(list_obj(),TFT_COLOR(color), gstate);                   }
    inline void list_font(const font_t& font,color_t color, gstate_t gstate=GPART_MAIN)     { list_font(font, gstate); list_font_color(color, gstate);                            }
    inline void list_border(int32_t value, gstate_t gstate=GPART_MAIN)                      { lv_obj_set_style_border_width( list_obj(), value, gstate);                          } 
    inline void list_border_color(int32_t color, gstate_t gstate=GPART_MAIN)                { lv_obj_set_style_border_color( list_obj(), TFT_COLOR(color), gstate);               } 
    inline void list_border(int32_t value, color_t color, gstate_t gstate=GPART_MAIN)       { list_border(value, gstate); list_border_color(color, gstate);                       } 
    inline void list_color(color_t color, gstate_t gstate=GPART_MAIN)                       { lv_obj_set_style_bg_color( list_obj(), TFT_COLOR(color), gstate);                   }
    inline void list_pad_left(int32_t value, gstate_t gstate=GPART_MAIN)                    { lv_obj_set_style_pad_left( list_obj(), value, gstate);                              }
    inline void list_pad_right(int32_t value, gstate_t gstate=GPART_MAIN)                   { lv_obj_set_style_pad_right( list_obj(), value, gstate);                             }
    inline void list_pad_top(int32_t value, gstate_t gstate=GPART_MAIN)                     { lv_obj_set_style_pad_top( list_obj(), value, gstate);                               }
    inline void list_pad_bottom(int32_t value, gstate_t gstate=GPART_MAIN)                  { lv_obj_set_style_pad_bottom( list_obj(), value, gstate);                            }
    inline void list_pad_gap(int32_t value, gstate_t gstate=GPART_MAIN)                     { lv_obj_set_style_pad_gap( list_obj(), value, gstate);                               }
    inline void list_pad_hor(int32_t value, gstate_t gstate=GPART_MAIN)                     { lv_obj_set_style_pad_hor( list_obj(), value, gstate);                               }
    inline void list_pad_ver(int32_t value, gstate_t gstate=GPART_MAIN)                     { lv_obj_set_style_pad_ver( list_obj(), value, gstate);                               }
    inline void list_pad_row(int32_t value, gstate_t gstate=GPART_MAIN)                     { lv_obj_set_style_pad_row( list_obj(), value, gstate);                               }
    inline void list_pad_column(int32_t value, gstate_t gstate=GPART_MAIN)                  { lv_obj_set_style_pad_column( list_obj(), value, gstate);                            }
    inline void list_padding_left(int32_t value, gstate_t gstate=GPART_MAIN)                { this->list_pad_left(value, gstate);   } 
    inline void list_padding_right(int32_t value, gstate_t gstate=GPART_MAIN)               { this->list_pad_right(value, gstate);  }
    inline void list_padding_top(int32_t value, gstate_t gstate=GPART_MAIN)                 { this->list_pad_top(value, gstate);    } 
    inline void list_padding_bottom(int32_t value, gstate_t gstate=GPART_MAIN)              { this->list_pad_bottom(value, gstate); }
    inline void list_padding_hor(int32_t value, gstate_t gstate=GPART_MAIN)                 { this->list_pad_hor(value, gstate);    } 
    inline void list_padding_ver(int32_t value, gstate_t gstate=GPART_MAIN)                 { this->list_pad_ver(value, gstate);    }
    inline void list_pad_inner(int32_t value, gstate_t gstate=GPART_MAIN)                   { this->list_pad_gap(value, gstate);    }
    inline void list_padding(int32_t p_top, int32_t p_bottom, int32_t p_left, int32_t p_right, gstate_t gstate=GPART_MAIN) {
      this->list_pad_top(p_top, gstate); this->list_pad_bottom(p_bottom, gstate); this->list_pad_left(p_left, gstate); this->list_pad_right(p_right, gstate);
    }
    inline void list_padding(int32_t p_top, int32_t p_bottom, int32_t p_left, int32_t p_right, int32_t p_inner, gstate_t gstate=GPART_MAIN) {
      this->list_pad_top(p_top, gstate); this->list_pad_bottom(p_bottom, gstate); this->list_pad_left(p_left, gstate); this->list_pad_right(p_right, gstate); this->list_pad_inner(p_inner, gstate);
    }
    inline void list_padding(int32_t p_top, int32_t p_bottom, int32_t p_left, int32_t p_right, int32_t p_row, int32_t p_col, gstate_t gstate=GPART_MAIN) {
      this->list_pad_top(p_top, gstate); this->list_pad_bottom(p_bottom, gstate); this->list_pad_left(p_left, gstate); this->list_pad_right(p_right, gstate); this->list_pad_row(p_row, gstate); this->list_pad_column(p_col, gstate);
    }
    inline void list_radius(int32_t value, gstate_t gstate=GPART_MAIN)                      { lv_obj_set_style_radius(list_obj(), value, gstate);                               }
    inline void list_text_align(text_align_t text_align, gstate_t gstate=GPART_MAIN)        { lv_obj_set_style_text_align(list_obj(), (lv_text_align_t) text_align, gstate);    }

    // ใน list ที่มีการเลือกไว้อยู่เดิม
    inline void selected_color(color_t color)                   { this->list_color( color,          (gstate_t)(GPART_SELECTED | GSTATE_CHECKED) );  }
    inline void selected_font_color(color_t color)              { this->list_font_color( color,     (gstate_t)(GPART_SELECTED | GSTATE_CHECKED) );  }
    inline void selected_font(const font_t&font)                { this->list_font(font,             (gstate_t)(GPART_SELECTED | GSTATE_CHECKED) );  }
    inline void selected_font(const font_t&font, color_t color) { this->list_font(font, color,      (gstate_t)(GPART_SELECTED | GSTATE_CHECKED) );  }
    inline void selected_border(int32_t value)                  { this->list_border( value,         (gstate_t)(GPART_SELECTED | GSTATE_CHECKED) );  }
    inline void selected_border_color(color_t color)            { this->list_border_color( color,   (gstate_t)(GPART_SELECTED | GSTATE_CHECKED) );  }
    inline void selected_border(int32_t value, color_t color)   { this->list_border( value, color,  (gstate_t)(GPART_SELECTED | GSTATE_CHECKED) );  }
    inline void selected_radius(int32_t value)                  { this->list_radius( value,         (gstate_t)(GPART_SELECTED | GSTATE_CHECKED) );  }

    //-------------------------------------
    // [list], GPART_MAIN);                       // ตอนปกติ ใน list ขณะที่ไม่ถูกเลือก
    // [list], GPART_SELECTED);                   // ตอนมีการกำลัง กด select
    // [list], GPART_SELECTED | GSTATE_CHECKED);  // ตอนที่ถุก check เลือกอยู่เดิใ
    //-------------------------------------

  private:
    /**
     * Get the index of the selected option
     * @return          index of the selected option (0 ... number of option - 1);
     */
    uint32_t _selected();

    /**
     * Get the current selected option as a string
     * @param buf       pointer to an array to store the string
     * @param buf_size  size of `buf` in bytes. 0: to ignore it.
     */
    void _selected_str(char * buf, uint32_t buf_size);



};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GDROPDOWLIST_H__
