/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GTextArea.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GTEXTAREA_H__
#define __GTEXTAREA_H__


#include "GObject.h"
#include "GLabel.h"
// #include "GTextAreaInputPad.h"


//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

#define GPART_PLACEHOLDER_FLOAT         (gstate_t) (GPART_TEXTAREA_PLACEHOLDER | (int) GSTATE_EDITED)

void textarea_event_cb(lv_event_t * event);

class GTextArea : public GObject {
  public:
    GTextArea(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GTextArea(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GTextArea();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();                     }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();                     }

    // inline String toString()                                { return (this->text()==nullptr)? "": String(this->text()); }
    inline String toString()                                { return this->text();                                      }
    inline int    toInt()                                   { return this->toString().toInt();                          }
    inline float  toFloat()                                 { return this->toString().toFloat();                        }
    inline double toDouble()                                { return this->toString().toDouble();                       }
    const char*   c_str();

    GTextArea& operator =(GLabel& gLabel);
    GTextArea& operator =(GTextArea& ta);
    GTextArea& operator =(const String &txt);
    GTextArea& operator =(const char* cstr);
    GTextArea& operator =(char c);
    GTextArea& operator =(int num);
    GTextArea& operator +=(const String label);
    GTextArea& operator +=(const char *cstr);
    GTextArea& operator +=(char c);
    GTextArea& operator +=(unsigned char num);
    GTextArea& operator +=(int num);
    GTextArea& operator +=(unsigned int num);
    GTextArea& operator +=(long num);
    GTextArea& operator +=(unsigned long num);
    GTextArea& operator +=(float num);
    GTextArea& operator +=(double num);

    char operator [](unsigned int index);
    inline uint32_t length()                          { return this->toString().length(); }

    void show_cursor(bool enable);

    void    selection_color(color_t color);
    color_t selection_color();
    void    selection_font_color(color_t color);
    color_t selection_font_color();

    void selection_start(uint32_t index);  // TEXT_SELECTION_OFF = ไม่กำหนด
    void selection_end(uint32_t index);    // TEXT_SELECTION_OFF = ไม่กำหนด
    inline void selection(uint32_t start, uint32_t end) {  
      this->selection_start(start); 
      this->selection_end(end);
    }

    uint32_t selection_start();   /* encoded char id ที่เริ่ม selection */
    uint32_t selection_end();     /* encoded char id ที่สิ้นสุด selection */

    event_handler_t fn_ontextselected;
    inline void onTextSelected(event_handler_t fn)              { if(!this->isCreated()) this->create();  fn_ontextselected = fn;     }
    String text_selected();

    inline void placeholder_float(bool en)                      { GObject::flag_widget1(en);                            }
    inline bool placeholder_float()                             { return GObject::flag_widget1();                       }

    inline void placeholder_color(color_t color)                { GObject::color( color, GPART_TEXTAREA_PLACEHOLDER);   }
    inline void placeholder_color(color_t color, opa_t opa)     { GObject::color( color, GPART_TEXTAREA_PLACEHOLDER );  GObject::text_opa( opa, GPART_TEXTAREA_PLACEHOLDER); }
    inline color_t placeholder_color()                          { return GObject::color(GPART_TEXTAREA_PLACEHOLDER);    }

    inline void placeholder_opa(opa_t opa)                      { GObject::text_opa( opa, GPART_TEXTAREA_PLACEHOLDER);  }
    inline opa_t placeholder_opa()                              { return GObject::text_opa( GPART_TEXTAREA_PLACEHOLDER);}

    inline void placeholder_font(const font_t& font)            { GObject::font( font, GPART_TEXTAREA_PLACEHOLDER);     }
    inline void placeholder_font(const font_t* font)            { GObject::font( font, GPART_TEXTAREA_PLACEHOLDER);     }
    inline const font_t* placeholder_font()                     { return GObject::font( GPART_TEXTAREA_PLACEHOLDER);    }

    inline void placeholder_font(const font_t& font, color_t c) { GObject::font( font, c, GPART_TEXTAREA_PLACEHOLDER);  }
    inline void placeholder_font(const font_t* font, color_t c) { GObject::font( font, c, GPART_TEXTAREA_PLACEHOLDER);  }

    /*======================
    * Add/remove functions
    *=====================*/

    /**
     * Insert a character to the current cursor position.
     * To add a wide char, e.g. 'Á' use `_lv_text_encoded_conv_wc('Á')`
     * @param c         a character (e.g. 'a')
     */
    void add(uint32_t c);  // wide char

    /**
     * Insert a text to the current cursor position
     * @param txt       a '\0' terminated string to insert
     */
    void add(const char * txt);

    inline void add(String txt)                           { this->add(txt.c_str());     }

    /**
     * Delete a the left character from the current cursor position
     */
    void backspace();

    /**
     * Delete the right character from the current cursor position
     */
    void del_forward();

    /*=====================
    * Setter functions
    *====================*/

    /**
     * Set the text of a text area
     * @param txt       pointer to the text
     */
    void text(const char * txt);

    inline void text(String txt)                                  { this->text(txt.c_str()); }

    /**
     * Set the placeholder text of a text area
     * @param txt       pointer to the text
     */
    void placeholder(const char * txt);

    inline void placeholder(String txt)                           { this->placeholder(txt.c_str());                                       }
    inline void placeholder(String txt, bool placeholder_float)   { this->placeholder(txt);  this->placeholder_float(placeholder_float);  }
  
    /**
     * Set the cursor position
     * @param pos       the new cursor position in character index
     *                  < 0 : index from the end of the text
     *                  TEXTAREA_CURSOR_LAST: go after the last character
     */
    void cursor_pos(int32_t pos);

    /**
     * Enable/Disable the positioning of the cursor by clicking the text on the text area.
     * @param obj       pointer to a text area object
     * @param en        true: enable click positions; false: disable
     */
    void cursor_click_pos(bool en);

    /**
     * Enable/Disable password mode
     * @param en        true: enable, false: disable
     */
    void password_mode(bool en);

    /**
     * Set the replacement characters to show in password mode
     * @param bullet    pointer to the replacement text
     */
    void password_bullet(const char * bullet);

    /**
     * Configure the text area to one line or back to normal
     * @param en        true: one line, false: normal
     */
    void one_line(bool en);

    /**
     * Set a list of characters. Only these characters will be accepted by the text area
     * @param list      list of characters. Only the pointer is saved. E.g. "+-.,0123456789"
     */
    void accepted_chars(const char * list);

    /**
     * Set max length of a Text Area.
     * @param num       the maximal number of characters can be added (`textarea_set_text` ignores it)
     */
    void max_length(uint32_t num);

    /**
     * In `EVENT_INSERT` the text which planned to be inserted can be replaced by an other text.
     * It can be used to add automatic formatting to the text area.
     * @param txt       pointer to a new string to insert. If `""` no text will be added.
     *                  The variable must be live after the `event_cb` exists. (Should be `global` or `static`)
     */
    void insert_replace(const char * txt);

    /**
     * Enable/disable selection mode.
     * @param en        true or false to enable/disable selection mode
     */
    void text_selection(bool en);

    /**
     * Set how long show the password before changing it to '*'
     * @param time      show time in milliseconds. 0: hide immediately.
     */
    void password_show_time(uint32_t time);

    /**
     * Deprecated: use the normal text_align style property instead
     * Set the label's alignment.
     * It sets where the label is aligned (in one line mode it can be smaller than the text area)
     * and how the lines of the area align in case of multiline text area
     * @param align     the align mode from ::lv_text_align_t
     */
    void text_align(text_align_t align);

    void cursor_show(bool en);
    inline void cursor_visible(bool en)         { this->cursor_show(en);  }
    inline void cursor_hidden(bool en)          { this->cursor_show(!en); }


    /*=====================
    * Getter functions
    *====================*/

    /**
     * Get the text of a text area. In password mode it gives the real text (not '*'s).
     * @return          pointer to the text
     */
    // const char * text() ;
    String text();

    /**
     * Get the placeholder text of a text area
     * @return          pointer to the placeholder text
     */
    // const char * placeholder();
    String placeholder();

    /**
     * Get the label of a text area
     * @return          pointer to the label object
     */
    lv_obj_t * label();

    /**
     * Get the current cursor position in character index
     * @return          the cursor position
     */
    uint32_t cursor_pos();

    /**
     * Get whether the cursor click positioning is enabled or not.
     * @return          true: enable click positions; false: disable
     */
    bool cursor_click_pos();

    /**
     * Get the password mode attribute
     * @return          true: password mode is enabled, false: disabled
     */
    bool password_mode();

    /**
     * Get the replacement characters to show in password mode
     * @return          pointer to the replacement text
     */
    const char * password_bullet();

    /**
     * Get the one line configuration attribute
     * @return          true: one line configuration is enabled, false: disabled
     */
    bool one_line();

    /**
     * Get a list of accepted characters.
     * @return          list of accented characters.
     */
    const char * accepted_chars();

    /**
     * Get max length of a Text Area.
     * @return          the maximal number of characters to be add
     */
    uint32_t max_length();

    /**
     * Find whether text is selected or not.
     * @return          whether text is selected or not
     */
    bool is_selected();

    /**
     * Find whether selection mode is enabled.
     * @return          true: selection mode is enabled, false: disabled
     */
    bool text_selection();

    /**
     * Set how long show the password before changing it to '*'
     * @return          show time in milliseconds. 0: hide immediately.
     */
    uint32_t password_show_time();

    /**
     * Get a the character from the current cursor position
     * @return          a the character or 0
     */
    uint32_t current_char();

    /*=====================
    * Other functions
    *====================*/

    /**
     * Clear the selection on the text area.
     */
    void clear_selection();

    /**
     * Move the cursor one character right
     */
    void cursor_right();

    /**
     * Move the cursor one character left
     */
    void cursor_left();

    /**
     * Move the cursor one line down
     */
    void cursor_down();

    /**
     * Move the cursor one line up
     */
    void cursor_up();

    // EVENT API
    event_handler_t  fn_onready = NULL;
    inline void onReady(event_handler_t fn)           { if(!this->isCreated()) this->create();  fn_onready = fn;            }

    void  default_keyboard(bool en, keyboard_mode_t keyboard_mode = KEYBOARD_MODE_EN)   { if(!this->isCreated()) this->create();  _use_default_keyboard = en; _keyboard_mode = keyboard_mode;}
    bool _use_default_keyboard = true;
    bool _cursor_show = true;
    keyboard_mode_t _keyboard_mode = KEYBOARD_MODE_EN;
  private:
};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GTEXTAREA_H__
