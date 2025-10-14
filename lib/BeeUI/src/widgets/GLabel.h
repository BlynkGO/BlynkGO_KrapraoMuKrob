/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GLabel.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GLABEL_H__
#define __GLABEL_H__


#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

#define LABEL_TEXT_SELECTION_OFF          (0xFFFF)
#define TEXT_SELECTION_OFF                (LABEL_TEXT_SELECTION_OFF)
#define STRINGX_PRINTF_BUFFER_SIZE        256

#define StringX     GLabel

class GLabel : public GObject, public String {
  public:
    GLabel(GWidget& parent=GScreen)                         : String("")  , GObject(&parent) {}
    GLabel(GWidget* parent)                                 : String("")  , GObject(parent)  {}
    GLabel(const char  *cstr, GWidget& parent=GScreen)      : String(cstr), GObject(&parent) {}
    GLabel(const String &str, GWidget& parent=GScreen)      : String(str) , GObject(&parent) {}
    GLabel(const char  *cstr, GWidget* parent)              : String(cstr), GObject(parent ) {}
    GLabel(const String &str, GWidget* parent)              : String(str) , GObject(parent ) {}
    virtual ~GLabel();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();                     }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();                     }

    inline void   text(String txt)                          { this->text((const char *) txt.c_str());                   }
    inline String text()                                    { return this->_text();                                     }
    inline String toString()                                { return this->text();                                      }
    inline void   text_static(String &text)                 { this->text_static(text.c_str());                          }

    void          rolling(bool enable, int32_t rolling_width=200, int32_t speed=0);
    inline bool   rolling()                                 { return (this->long_mode() == LABEL_LONG_SCROLL_CIRCULAR); }

    GLabel& operator =(GLabel& gLabel);
#if LABEL_USE_TEXTAREA
    GLabel& operator =(GTextArea& ta);
#endif
    GLabel& operator =(const String &label);
    GLabel& operator =(const char* cstr);
    GLabel& operator =(int num);
    // GLabel& operator =(float num);
    GLabel& operator +=(const String label);
    GLabel& operator +=(const char *cstr);
    GLabel& operator +=(char c);
    GLabel& operator +=(unsigned char num);
    GLabel& operator +=(int num);
    GLabel& operator +=(unsigned int num);
    GLabel& operator +=(long num);
    GLabel& operator +=(unsigned long num);
    GLabel& operator +=(float num);
    GLabel& operator +=(double num);
    GLabel& operator += (const __FlashStringHelper *str);

    using String::operator==;
    using String::operator!=;

    void    operator = (obj_t* obj);

    int32_t text_width();                         // ความกว้างเฉพาะ text กี่ pixel; ถ้าเป็น label.width() บางทีไปปรับ 100% ขนาดความกว้างเฉพาะข้อความเลย ไม่ใช่ เพราะเป็นความกว้างของวิตเจ็ตแทนไปแล้ว
    uint32_t letter_num();                        // จน.ตัวอักษรตามจริง (ไม่ใช่ความยาว byte)
    static uint32_t letter_num(const char* text); // จน.ตัวอักษรตามจริง (ไม่ใช่ความยาว byte)
    static uint32_t letter_num(String text);      // จน.ตัวอักษรตามจริง (ไม่ใช่ความยาว byte)
    static String printf(const char* fmt, ...)  __attribute__((format(printf, 1, 2))); 

    inline void    color(color_t color, gstate_t state=GSTATE_DEFAULT)                    { GObject::text_color(color,state);                                         }
    inline color_t color(gstate_t state=GSTATE_DEFAULT)                                   { return GObject::text_color(state);                                        }
    inline void    opa(uint8_t opa, gstate_t state=GSTATE_DEFAULT)                        { GObject::text_opa(opa,state);                                             }
    inline uint8_t opa(gstate_t state=GSTATE_DEFAULT)                                     { return GObject::text_opa(state);                                          }
    inline void    letter_space(int16_t letter_space, gstate_t state=GSTATE_DEFAULT)      { GObject::text_letter_space(letter_space,state);                           }
    inline int16_t letter_space(gstate_t state=GSTATE_DEFAULT)                            { return GObject::text_letter_space(state);                                 }
    inline void    line_space(int16_t line_space, gstate_t state=GSTATE_DEFAULT)          { GObject::text_line_space(line_space,state);                               }
    inline int16_t line_space(gstate_t state=GSTATE_DEFAULT)                              { return GObject::text_line_space(state);                                   }
    inline void    decor(text_decor_t value, gstate_t state=GSTATE_DEFAULT)               { GObject::text_decor(value,state);                                         }
    inline text_decor_t decor(gstate_t state=GSTATE_DEFAULT)                              { return GObject::text_decor(state);                                        }
    inline void    underline(bool enable, gstate_t state=GSTATE_DEFAULT)                  { this->decor((enable)? TEXT_DECOR_UNDERLINE : TEXT_DECOR_NONE,state);      }
    inline bool    underline(gstate_t state=GSTATE_DEFAULT)                               { return ( this->decor(state)== TEXT_DECOR_UNDERLINE);                      }
    inline void    strikethrough(bool enable, gstate_t state=GSTATE_DEFAULT)              {  this->decor((enable)? TEXT_DECOR_STRIKETHROUGH : TEXT_DECOR_NONE,state); }
    inline bool    strikethrough(gstate_t state=GSTATE_DEFAULT)                           { return ( this->decor(state)== TEXT_DECOR_STRIKETHROUGH);                  }
    inline void    text_align(text_align_t text_align, gstate_t state=GSTATE_DEFAULT)     { GObject::text_align(text_align,state);                                    }
    inline text_align_t text_align(gstate_t state=GSTATE_DEFAULT)                         { return GObject::text_align(state);                                        }

    inline void    reset_color()                            { GObject::remove_text_color();                                         }
    inline void    reset_font()                             { GObject::remove_text_font();                                          }

    using GObject::invalidate;

    /**
     * Set font from a font list by the size.
     * @param size_width         max width of the label.
     * @param size_height        max height of the label.
     * @param fonts[]            font pointer list from the smallest to the biggest font.
     * @param font_num           num of font pointer list.
     */
    void   adjust_font(int32_t size_width, int32_t size_height, const font_t* fonts[], size_t font_num);


    /*=====================
    * Setter functions
    *====================*/

    /**
     * Set a new text for a label. Memory will be allocated to store the text by the label.
     * @param text          '\0' terminated character string. NULL to refresh with the current text.
     */
    void text(const char * text);

    /**
     * Set a static text. It will not be saved by the label so the 'text' variable
     * has to be 'alive' while the label exists.
     * @param text          pointer to a text. NULL to refresh with the current text.
     */
    void text_static(const char * text);


    /**
     * Set the behavior of the label with text longer than the object size
     * @param long_mode     the new mode from 'lv_label_long_mode' enum.
     *                      In LABEL_LONG_WRAP/DOT/SCROLL/SCROLL_CIRC the size of the label should be set AFTER this function
     */
    void long_mode( long_mode_t long_mode);

    inline void long_mode(long_mode_t long_mode, int32_t width, uint32_t speed_pps=25){
      this->long_mode(long_mode);
      this->width(width);
      this->anim_speed(speed_pps);
    }

    /**
     * Set where text selection should start
     * @param index     character index from where selection should start. `LV_LABEL_TEXT_SELECTION_OFF` for no selection
     */
    void selection_start(uint32_t index);

    /**
     * Set where text selection should end
     * @param index     character index where selection should end. `LV_LABEL_TEXT_SELECTION_OFF` for no selection
     */
    void selection_end(uint32_t index);

    inline void selection(uint32_t index_start, uint32_t index_end=LABEL_TEXT_SELECTION_OFF){
      this->selection_start(index_start);
      this->selection_end(index_end);
    }

    /* BlynkGO */
    String text_selected();

    /*=====================
    * Getter functions
    *====================*/

    /**
     * Get the text of a label
     * @return          the text of the label
     */
    char * _text();

    /**
     * Get the long mode of a label
     * @return          the current long mode
     */
    long_mode_t long_mode();

    /**
     * Get the relative x and y coordinates of a letter
     * @param char_id   index of the character [0 ... text length - 1].
     *                  Expressed in character index, not byte index (different in UTF-8)
     * @param pos       store the result here (E.g. index = 0 gives 0;0 coordinates if the text if aligned to the left)
     */
    void letter_pos(uint32_t char_id, point_t * pos);

    /**
     * Get the index of letter on a relative point of a label.
     * @param pos_in    pointer to point with coordinates on a the label
     * @param bidi      whether to use bidi processed
     * @return          The index of the letter on the 'pos_p' point (E.g. on 0;0 is the 0. letter if aligned to the left)
     *                  Expressed in character index and not byte index (different in UTF-8)
     */
    uint32_t letter_on(point_t * pos_in, bool bidi=false);

    /**
     * Check if a character is drawn under a point.
     * @param pos       Point to check for character under
     * @return          whether a character is drawn under the point
     */
    bool is_char_under_pos(point_t * pos);

    /**
     * @brief Get the selection start index.
     * @return          selection start index. `LV_LABEL_TEXT_SELECTION_OFF` if nothing is selected.
     */
    uint32_t selection_start();

    /**
     * @brief Get the selection end index.
     * @return          selection end index. `LV_LABEL_TXT_SEL_OFF` if nothing is selected.
     */
    uint32_t selection_end();

    /*=====================
    * Other functions
    *====================*/

    /**
     * Insert a text to a label. The label text can not be static.
     * @param pos       character index to insert. Expressed in character index and not byte index.
     *                  0: before first char. LV_LABEL_POS_LAST: after last char.
     * @param txt       pointer to the text to insert
     */
    void insert_text(uint32_t pos, const char * txt);

    inline void insert_text(uint32_t pos, String txt)     { this->insert_text(pos, txt.c_str());    }

    /**
     * Delete characters from a label. The label text can not be static.
     * @param pos       character index from where to cut. Expressed in character index and not byte index.
     *                  0: start in from of the first character
     * @param cnt       number of characters to cut
     */
    void cut_text(uint32_t pos, uint32_t cnt);



  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GLABEL_H__
