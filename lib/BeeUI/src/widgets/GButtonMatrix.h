/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GButtonMatrix.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GBUTTONMATRIX_H__
#define __GBUTTONMATRIX_H__

#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GButtonMatrix : public GObject {
  public:
    GButtonMatrix(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GButtonMatrix(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GButtonMatrix();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }


    inline void button_checked(uint32_t btn_id, bool checked) {
      this->button_ctrl(btn_id, BUTTONMATRIX_CTRL_CHECKABLE);
      if(checked) {this->button_ctrl(btn_id, BUTTONMATRIX_CTRL_CHECKED); this->selected_id(btn_id); }
      else        { this->clear_button_ctrl(btn_id, BUTTONMATRIX_CTRL_CHECKED); }
    }


    /*=====================
    * Setter functions
    *====================*/
    /**
     * Set a new map. Buttons will be created/deleted according to the map. The
     * button matrix keeps a reference to the map and so the string array must not
     * be deallocated during the life of the matrix.
     * @param map       pointer a string array. The last string has to be: "". Use "\n" to make a line break.
     */
    void map(const char * map[]);

    /**
     * Set the button control map (hidden, disabled etc.) for a button matrix.
     * The control map array will be copied and so may be deallocated after this
     * function returns.
     * @param ctrl_map  pointer to an array of `lv_button_ctrl_t` control bytes. The
     *                  length of the array and position of the elements must match
     *                  the number and order of the individual buttons (i.e. excludes
     *                  newline entries).
     *                  An element of the map should look like e.g.:
     *                 `ctrl_map[0] = width | BUTTONMATRIX_CTRL_NO_REPEAT |  BUTTONMATRIX_CTRL_TGL_ENABLE`
     */
    void ctrl_map(const buttonmatrix_ctrl_t ctrl_map[]);

    /**
     * Set the selected buttons
     * @param btn_id     0 based index of the button to modify. (Not counting new lines)
     */
    void selected_button(uint32_t btn_id);

    /**
     * Set the selected buttons
     * @param btn_id     0 based index of the button to modify. (Not counting new lines)
     */
    inline void selected_id(uint32_t btn_id)                { this->selected_button(btn_id);   }

    /**
     * Set the attributes of a button of the button matrix
     * @param btn_id    0 based index of the button to modify. (Not counting new lines)
     * @param ctrl      OR-ed attributes. E.g. `BUTTONMATRIX_CTRL_NO_REPEAT | BUTTONMATRIX_CTRL_CHECKABLE`
     */
    void button_ctrl(uint32_t btn_id, buttonmatrix_ctrl_t ctrl);

    /**
     * Clear the attributes of a button of the button matrix
     * @param btn_id    0 based index of the button to modify. (Not counting new lines)
     * @param ctrl      OR-ed attributes. E.g. `BUTTONMATRIX_CTRL_NO_REPEAT | BUTTONMATRIX_CTRL_CHECKABLE`
     */
    void clear_button_ctrl(uint32_t btn_id, buttonmatrix_ctrl_t ctrl);

    /**
     * Set attributes of all buttons of a button matrix
     * @param ctrl      attribute(s) to set from `buttonmatrix_ctrl_t`. Values can be ORed.
     */
    void button_ctrl_all(buttonmatrix_ctrl_t ctrl);

    /**
     * Clear the attributes of all buttons of a button matrix
     * @param ctrl      attribute(s) to set from `buttonmatrix_ctrl_t`. Values can be ORed.
     * @param en        true: set the attributes; false: clear the attributes
     */
    void clear_button_ctrl_all(buttonmatrix_ctrl_t ctrl);

    /**
     * Set a single button's relative width.
     * This method will cause the matrix be regenerated and is a relatively
     * expensive operation. It is recommended that initial width be specified using
     * `ctrl_map` and this method only be used for dynamic changes.
     * @param btn_id    0 based index of the button to modify.
     * @param width     relative width compared to the buttons in the same row. [1..15]
     */
    void button_width(uint32_t btn_id, uint32_t width);

    void button_width(uint32_t width);  // button width all

    /**
     * Make the button matrix like a selector widget (only one button may be checked at a time).
     * `BUTTONMATRIX_CTRL_CHECKABLE` must be enabled on the buttons to be selected using
     * `ctrl()` or `button_ctrl_all()`.
     * @param en        whether "one check" mode is enabled
     */
    void one_checked(bool en);

    void button_checkable(uint32_t btn_id, bool en);
    void button_checkable_all(bool en);

    void button_checked(uint32_t btn_id);
    int32_t button_checked();

    inline void    checked_id(uint32_t btn_id)    { this->button_checked(btn_id);   }
    inline int32_t checked_id()                   { return this->button_checked();  }

    /*=====================
    * Getter functions
    *====================*/

    /**
     * Get the current map of a button matrix
     * @return          the current map
     */
    const char ** map();

    uint32_t button_cnt();

    /**
     * Get the index of the lastly "activated" button by the user (pressed, released, focused etc)
     * Useful in the `event_cb` to get the text of the button, check if hidden etc.
     * @return          index of the last released button (LV_BUTTONMATRIX_BUTTON_NONE: if unset)
     */
    uint32_t selected_id();

    inline uint32_t pressed_button_id()                     { return this->selected_id();                     } // ให้ compatible กับ BlynkGOv2/v3

    /**
     * Get the button's text
     * @param btn_id    the index a button not counting new line characters.
     * @return          text of btn_index` button
     */
    // const char * button_text(uint32_t btn_id);
    String button_text(uint32_t btn_id);

    inline String selected_button()                         { return this->button_text(this->selected_id());  } 
    inline String active_button()                           { return this->selected_button();                 } // ให้ compatible กับ BlynkGOv2/v3

    /**
     * Get the whether a control value is enabled or disabled for button of a button matrix
     * @param btn_id    the index of a button not counting new line characters.
     * @param ctrl      control values to check (ORed value can be used)
     * @return          true: the control attribute is enabled false: disabled
     */
    bool has_button_ctrl(uint32_t btn_id, buttonmatrix_ctrl_t ctrl);

    /**
     * Tell whether "one check" mode is enabled or not.
     * @return          true: "one check" mode is enabled; false: disabled
     */
    bool one_checked();

    using GObject::color;
    using GObject::radius;
    using GObject::opa;
    using GObject::border;
    using GObject::border_opa;
    using GObject::border_color;
    using GObject::padding;

    inline void     bg_color(color_t color)                             { GObject::bg_color(color );        }       // สีพื้นหลัง
    inline color_t  bg_color()                                          { return GObject::bg_color();       }       // สีพื้นหลัง
    inline void     bg_radius(int32_t r)                                { GObject::radius(r);               }       // รัศมีมุม พื้นหลัง
    inline int32_t  bg_radius()                                         { return GObject::radius();         }       // รัศมีมุม พื้นหลัง
    inline void     bg_opa(uint8_t opa)                                 { GObject::bg_opa(opa);             }       // ความโปร่งใสพื้นหลัง
    inline uint8_t  bg_opa()                                            { return GObject::bg_opa();         }       // ความโปร่งใสพื้นหลัง
    inline void     bg_border(int32_t width)                            { GObject::border(width);           }       // ความหนาขอบพื้นหลัง
    inline int32_t  bg_border()                                         { return GObject::border();         }       // ความหนาขอบพื้นหลัง
    inline void     bg_border(int32_t width, color_t color)             { GObject::border(width, color);    }       // ความหนาขอบพื้นหลัง พร้อมกำหนดสี
    inline void     bg_border_opa(uint8_t opa)                          { GObject::border_opa(opa);         }       // ความโปร่งใส ขอบพื้นหลัง
    inline uint8_t  bg_border_opa()                                     { return GObject::border_opa();     }       // ความโปร่งใส ขอบพื้นหลัง
    inline void     bg_border_color(color_t color)                      { GObject::border_color(color);     }       // สีขอบพื้นหลัง
    inline color_t  bg_border_color()                                   { return GObject::border_color();   }       // สีขอบพื้นหลัง

    inline void     button_color(color_t color)                         { GObject::bg_color(color, (gstate_t)(GPART_ITEMS | GSTATE_DEFAULT));           }       // สี ปุ่มกด ขณะปล่อย
    inline color_t  button_color()                                      { return GObject::bg_color((gstate_t)(GPART_ITEMS | GSTATE_DEFAULT));           }       // สี ปุ่มกด ขณะปล่อย
    inline void     button_radius(int32_t r)                            { GObject::radius(r, (gstate_t)(GPART_ITEMS | GSTATE_DEFAULT));              }       // รัศมีมุม ปุ่มกด ขณะปล่อย
    inline int32_t  button_radius()                                     { return GObject::radius((gstate_t)(GPART_ITEMS | GSTATE_DEFAULT));          }       // รัศมีมุม ปุ่มกด ขณะปล่อย
    inline void     button_opa(uint8_t opa)                             { GObject::opa(opa, (gstate_t)(GPART_ITEMS | GSTATE_DEFAULT));               }       // ความโปร่งใสขอบ ปุ่มกด ขณะปล่อย
    inline uint8_t  button_opa()                                        { return GObject::opa((gstate_t)(GPART_ITEMS | GSTATE_DEFAULT));             }       // ความโปร่งใสขอบ ปุ่มกด ขณะปล่อย
    inline void     button_border(int32_t width)                        { GObject::border(width, (gstate_t)(GPART_ITEMS | GSTATE_DEFAULT));          }       // ความหนาขอบ ปุ่มกด ขณะปล่อย
    inline void     button_border(int32_t width, color_t color)         { GObject::border(width, color, (gstate_t)(GPART_ITEMS | GSTATE_DEFAULT));   }       // ความหนาขอบ ปุ่มกด ขณะปล่อย พร้อมกำหนดสี
    inline int32_t  button_border()                                     { return GObject::border((gstate_t)(GPART_ITEMS | GSTATE_DEFAULT));          }       // ความหนาขอบ ปุ่มกด ขณะปล่อย
    inline void     button_border_opa(uint8_t opa)                      { GObject::border_opa(opa, (gstate_t)(GPART_ITEMS | GSTATE_DEFAULT));        }       // ความโปร่งใส ปุ่มกด ขณะปล่อย
    inline uint8_t  button_border_opa()                                 { return GObject::border_opa((gstate_t)(GPART_ITEMS | GSTATE_DEFAULT));      }       // ความโปร่งใส ปุ่มกด ขณะปล่อย
    inline void     button_border_color(color_t color)                  { GObject::border_color(color, (gstate_t)(GPART_ITEMS | GSTATE_DEFAULT));    }       // สีขอบ ปุ่มกด ขณะปล่อย
    inline color_t  button_border_color()                               { return GObject::border_color((gstate_t)(GPART_ITEMS | GSTATE_DEFAULT));    }       // สีขอบ ปุ่มกด ขณะปล่อย
    inline void     button_padding(int32_t pad)                         { GObject::padding(pad, (gstate_t)(GPART_ITEMS | GSTATE_DEFAULT));               } 
    inline int32_t  button_padding()                                    { return GObject::padding((gstate_t)(GPART_ITEMS | GSTATE_DEFAULT));             } 
    inline void     button_border_side(border_side_t value)             { GObject::border_side(value, (gstate_t)(GPART_ITEMS | GSTATE_DEFAULT));     } 
    inline border_side_t button_border_side()                           { return GObject::border_side((gstate_t)(GPART_ITEMS | GSTATE_DEFAULT));     } 

    inline void     button_pressed_color(color_t color)                 { GObject::bg_color(color, (gstate_t)(GPART_ITEMS | GSTATE_PRESSED));           }       // สี ปุ่มกด ขณะกด
    inline color_t  button_pressed_color()                              { return GObject::bg_color((gstate_t)(GPART_ITEMS | GSTATE_PRESSED));           }       // สี ปุ่มกด ขณะกด
    inline void     button_pressed_radius(int32_t r)                    { GObject::radius(r, (gstate_t)(GPART_ITEMS | GSTATE_PRESSED));              }       // รัศมีมุม ปุ่มกด ขณะกด
    inline int32_t  button_pressed_radius()                             { return GObject::radius((gstate_t)(GPART_ITEMS | GSTATE_PRESSED));          }       // รัศมีมุม ปุ่มกด ขณะกด
    inline void     button_pressed_opa(uint8_t opa)                     { GObject::opa(opa, (gstate_t)(GPART_ITEMS | GSTATE_PRESSED));               }       // ความโปร่งใสขอบ ปุ่มกด ขณะกด
    inline uint8_t  button_pressed_opa()                                { return GObject::opa((gstate_t)(GPART_ITEMS | GSTATE_PRESSED));             }       // ความโปร่งใสขอบ ปุ่มกด ขณะกด
    inline void     button_pressed_border(int32_t width)                { GObject::border(width, (gstate_t)(GPART_ITEMS | GSTATE_PRESSED));          }       // ความหนาขอบ ปุ่มกด ขณะกด
    inline void     button_pressed_border(int32_t width,color_t color)  { GObject::border(width, color, (gstate_t)(GPART_ITEMS | GSTATE_PRESSED));   }       // ความหนาขอบ ปุ่มกด ขณะกด พร้อมกำหนดสี
    inline int32_t  button_pressed_border()                             { return GObject::border((gstate_t)(GPART_ITEMS | GSTATE_PRESSED));          }       // ความหนาขอบ ปุ่มกด ขณะกด
    inline void     button_pressed_border_opa(uint8_t opa)              { GObject::border_opa(opa, (gstate_t)(GPART_ITEMS | GSTATE_PRESSED));        }       // ความโปร่งใส ปุ่มกด ขณะกด
    inline uint8_t  button_pressed_border_opa()                         { return GObject::border_opa((gstate_t)(GPART_ITEMS | GSTATE_PRESSED));      }       // ความโปร่งใส ปุ่มกด ขณะกด
    inline void     button_pressed_border_color(color_t color)          { GObject::border_color(color, (gstate_t)(GPART_ITEMS | GSTATE_PRESSED));    }       // สีขอบ ปุ่มกด ขณะกด
    inline color_t  button_pressed_border_color()                       { return GObject::border_color((gstate_t)(GPART_ITEMS | GSTATE_PRESSED));    }       // สีขอบ ปุ่มกด ขณะกด

    inline void     font(const font_t &font)                            { GObject::font(font, GPART_ITEMS);                                          }
    inline const font_t* font()                                         { return GObject::font(GPART_ITEMS);                                         }
    inline void     font(const font_t &font, color_t color)             { GObject::font(font, color, GPART_ITEMS);                                   }
    inline void     font_color(color_t color)                           { GObject::font_color(color, GPART_ITEMS);                                   }
    inline color_t  font_color()                                        { return GObject::font_color(GPART_ITEMS);                                   }

    inline void     ctrl_color(color_t color)                           { GObject::bg_color(color, (gstate_t)(GPART_ITEMS | GSTATE_CHECKED));        } 
    inline color_t  ctrl_color()                                        { return GObject::bg_color((gstate_t)(GPART_ITEMS | GSTATE_CHECKED));        } 
    inline void     ctrl_radius(int32_t r)                              { GObject::radius(r, (gstate_t)(GPART_ITEMS | GSTATE_CHECKED));              }       // รัศมีมุม ปุ่ม ctrl ขณะปล่อย
    inline int32_t  ctrl_radius()                                       { return GObject::radius((gstate_t)(GPART_ITEMS | GSTATE_CHECKED));          }       // รัศมีมุม ปุ่ม ctrl ขณะปล่อย
    inline void     ctrl_opa(uint8_t opa)                               { GObject::opa(opa, (gstate_t)(GPART_ITEMS | GSTATE_CHECKED));               }       // ความโปร่งใส ปุ่ม ctrl ขณะปล่อย
    inline uint8_t  ctrl_opa()                                          { return GObject::opa((gstate_t)(GPART_ITEMS | GSTATE_CHECKED));             }       // ความโปร่งใส ปุ่ม ctrl ขณะปล่อย
    inline void     ctrl_border(int32_t width)                          { GObject::border(width, (gstate_t)(GPART_ITEMS | GSTATE_CHECKED));          }       // ความหนาขอบ ปุ่ม ctrl ขณะปล่อย
    inline void     ctrl_border(int32_t width, color_t color)           { GObject::border(width, color, (gstate_t)(GPART_ITEMS | GSTATE_CHECKED));   }       // ความหนาขอบ ปุ่ม ctrl ขณะปล่อย
    inline int32_t  ctrl_border()                                       { return GObject::border((gstate_t)(GPART_ITEMS | GSTATE_CHECKED));          }       // ความหนาขอบ ปุ่ม ctrl ขณะปล่อย
    inline void     ctrl_border_opa(uint8_t opa)                        { GObject::border_opa(opa, (gstate_t)(GPART_ITEMS | GSTATE_CHECKED));        }       // ความโปร่งใสขอบ ปุ่ม ctrl ขณะปล่อย
    inline uint8_t  ctrl_border_opa()                                   { return GObject::border_opa((gstate_t)(GPART_ITEMS | GSTATE_CHECKED));      }       // ความโปร่งใสขอบ ปุ่ม ctrl ขณะปล่อย
    inline void     ctrl_border_color(color_t color)                    { GObject::border_color(color, (gstate_t)(GPART_ITEMS | GSTATE_CHECKED));    }       // สีขอบ ปุ่ม ctrl ขณะปล่อย
    inline color_t  ctrl_border_color()                                 { return GObject::border_color((gstate_t)(GPART_ITEMS | GSTATE_CHECKED));    }       // สีขอบ ปุ่ม ctrl ขณะปล่อย
    inline void     ctrl_font(const font_t &font)                       { GObject::font(font, (gstate_t)(GPART_ITEMS | GSTATE_CHECKED));             }       // ความหน้าขอบ ปุ่ม ctrl ขณะปล่อย
    inline void     ctrl_font(const font_t &font, color_t color)        { GObject::font(font, color, (gstate_t)(GPART_ITEMS | GSTATE_CHECKED));      }       // ความหน้าขอบ ปุ่ม ctrl ขณะปล่อย
    inline const font_t* ctrl_font()                                    { return GObject::font((gstate_t)(GPART_ITEMS | GSTATE_CHECKED));            }       // ความหน้าขอบ ปุ่ม ctrl ขณะปล่อย
    inline void     ctrl_font_color(color_t color)                      { GObject::font_color(color, (gstate_t)(GPART_ITEMS | GSTATE_CHECKED));      }       // ความหน้าขอบ ปุ่ม ctrl ขณะปล่อย
    inline color_t  ctrl_font_color()                                   { return GObject::font_color((gstate_t)(GPART_ITEMS | GSTATE_CHECKED));      }       // ความหน้าขอบ ปุ่ม ctrl ขณะปล่อย

    // inline void   ctrl_inactive_color(color_t color)                    { GObject::color(color, (gstate_t)(GPART_ITEMS | GSTATE_CHECKED | GSTATE_DISABLED)); } 
    // inline void   ctrl_inactive_radius(uint16_t r)                      { GObject::radius(r, (gstate_t)(GPART_ITEMS | GSTATE_CHECKED | GSTATE_DISABLED));    }       // รัศมีมุม ปุ่ม ctrl ขณะปล่อย


  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GBUTTONMATRIX_H__
