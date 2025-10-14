/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GSpan.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GSPAN_H__
#define __GSPAN_H__


#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GParagraph : public GObject {
  public:
    GParagraph(GWidget& parent=GScreen)                     : GObject(&parent) {}
    GParagraph(GWidget* parent)                             : GObject(parent)  {}
    virtual ~GParagraph();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    /**
     * Create a span string descriptor and add to spangroup.
     * @return          pointer to the created span.
     */
    span_t * new_span();

    span_t * span(String txt);
    span_t * span(const char* txt);
    span_t * span(int n);

    /**
     * Remove the span from the spangroup and free memory.
     * @param span  pointer to a span.
     */
    void delete_span(span_t * span);

    /*=====================
    * Setter functions
    *====================*/

    // /**
    //  * Set a new text for a span. Memory will be allocated to store the text by the span.
    //  * @param span  pointer to a span.
    //  * @param text  pointer to a text.
    //  */
    // void lv_span_set_text(lv_span_t * span, const char * text);

    // /**
    //  * Set a static text. It will not be saved by the span so the 'text' variable
    //  * has to be 'alive' while the span exist.
    //  * @param span  pointer to a span.
    //  * @param text  pointer to a text.
    //  */
    // void lv_span_set_text_static(lv_span_t * span, const char * text);

    /**
     * Set the align of the spangroup.
     * @param align see lv_text_align_t for details.
     */
    void text_align(text_align_t align);

    /**
     * Set the overflow of the spangroup.
     * @param overflow  see lv_span_overflow_t for details.
     */
    void overflow(span_overflow_t overflow);

    /**
     * Set the indent of the spangroup.
     * @param indent    the first line indentation
     */
    void indent(int32_t indent);

    /**
     * Set the mode of the spangroup.
     * @param mode      see span_mode_t for details.
     */
    void mode(span_mode_t mode);

    /**
     * Set maximum lines of the spangroup.
     * @param lines     max lines that can be displayed in SPAN_MODE_BREAK mode. < 0 means no limit.
     */
    void max_lines(int32_t lines);

    /*=====================
    * Getter functions
    *====================*/

    /**
     * Get a spangroup child by its index.
     *
     * @param id    the index of the child.
     *              0: the oldest (firstly created) child
     *              1: the second oldest
     *              child count-1: the youngest
     *              -1: the youngest
     *              -2: the second youngest
     * @return      The child span at index `id`, or NULL if the ID does not exist
     */
    span_t * get_child(int32_t id);

    inline span_t * get_span(int32_t id)                      { return this->get_child(id);     }

    /**
     * Get number of spans
     * @return      the span count of the spangroup.
     */
    uint32_t span_count();

    /**
     * Get the align of the spangroup.
     * @return      the align value.
     */
    text_align_t text_align();

    /**
     * Get the overflow of the spangroup.
     * @return      the overflow value.
     */
    span_overflow_t overflow();

    /**
     * Get the indent of the spangroup.
     * @return      the indent value.
     */
    int32_t indent();

    /**
     * Get the mode of the spangroup.
     */
    span_mode_t mode();

    /**
     * Get maximum lines of the spangroup.
     * @return      the max lines value.
     */
    int32_t max_lines();

    /**
     * Get max line height of all span in the spangroup.
     */
    int32_t max_line_height();

    /**
     * Get the text content width when all span of spangroup on a line.
     * @param max_width if text content width >= max_width, return max_width
     * to reduce computation, if max_width == 0, returns the text content width.
     * @return text     content width or max_width.
     */
    uint32_t expand_width(uint32_t max_width);

    /**
     * Get the text content height with width fixed.
     * @param width     the width of the span group.

    */
    int32_t expand_height(int32_t width);

    /*=====================
    * Other functions
    *====================*/

    /**
     * Update the mode of the spangroup.
     */
    void refr_mode();

    inline void refresh()                               { this->refr_mode();    }

  private:
};

class GSpan {
  public:
    GSpan(span_t* span)  { *this = span; }
    GSpan() {}

    GSpan& operator =(span_t *span);

    void operator =(const String &txt);
    void operator =(const char* txt);
    void operator =(int num);

    /**
     * Set a new text for a span. Memory will be allocated to store the text by the span.
     * @param text  pointer to a text.
     */
    void text(const char * text);

    /**
     * Set a static text. It will not be saved by the span so the 'text' variable
     * has to be 'alive' while the span exist.
     * @param text  pointer to a text.
     */
    void text_static(const char * text);

    inline void    font(const font_t &font)                   { this->style.font(font);                                           }
    inline void    font(const font_t &font, color_t color)    { this->style.font(font, color);                                    }
    inline void    color(color_t color)                       { this->style.text_color(color);                                    }
    inline void    font_color(color_t color)                  { this->color(color);                                               }
    inline void    text_color(color_t color)                  { this->color(color);                                               }
    // inline color_t color(gstate_t state=GSTATE_DEFAULT)                                   { return GObject::text_color(state);                                        }
    inline void    opa(uint8_t opa)                           { this->style.text_opa(opa);                                        }
    // inline uint8_t opa(gstate_t state=GSTATE_DEFAULT)                                     { return GObject::text_opa(state);                                          }
    inline void    letter_space(int16_t letter_space)         { this->style.text_letter_space(letter_space);                      }
    // inline int16_t letter_space(gstate_t state=GSTATE_DEFAULT)                            { return GObject::text_letter_space(state);                                 }
    inline void    line_space(int16_t line_space)             { this->style.text_line_space(line_space);                          }
    // inline int16_t line_space(gstate_t state=GSTATE_DEFAULT)                              { return GObject::text_line_space(state);                                   }
    inline void    decor(text_decor_t value)                  { this->style.text_decor(value);                                    }
    // inline text_decor_t decor(gstate_t state=GSTATE_DEFAULT)                              { return GObject::text_decor(state);                                        }
    inline void    underline(bool enable)                     { this->decor((enable)? TEXT_DECOR_UNDERLINE : TEXT_DECOR_NONE);    }
    // inline bool    underline(gstate_t state=GSTATE_DEFAULT)                               { return ( this->decor(state)== TEXT_DECOR_UNDERLINE);                      }
    inline void    strikethrough(bool enable)                 { this->decor((enable)? TEXT_DECOR_STRIKETHROUGH : TEXT_DECOR_NONE);}
    // inline bool    strikethrough(gstate_t state=GSTATE_DEFAULT)                           { return ( this->decor(state)== TEXT_DECOR_STRIKETHROUGH);                  }
    inline void    text_align(text_align_t text_align)        { this->style.text_align(text_align);                               }
    // inline text_align_t text_align(gstate_t state=GSTATE_DEFAULT)                         { return GObject::text_align(state);    


    GStyle style;
  private:
    span_t *_span;
};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GSPAN_H__
