/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GScale.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GSCALE_H__
#define __GSCALE_H__


#include "GObject.h"
#include "GLine.h"
#include "GImage.h"
#include "GArc.h"
#include "GBar.h"
#include <vector>

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GScaleSection;

class GScale : public GObject {
  public:
    GScale(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GScale(GWidget* parent)                                  : GObject(parent)  {}

    GScale(scale_mode_t mode, GWidget& parent=GScreen)
     : GObject(&parent), _mode(mode)
    {}

    GScale(scale_mode_t mode, GWidget* parent)
     : GObject(parent), _mode(mode)
    {}

    GScale(scale_mode_t mode, int32_t total_tick_count, GWidget& parent=GScreen)
     : GObject(&parent), _mode(mode), _total_tick_count(total_tick_count)
    {}

    GScale(scale_mode_t mode, int32_t total_tick_count, GWidget* parent)
     : GObject(parent), _mode(mode), _total_tick_count(total_tick_count)
    {}

    GScale(scale_mode_t mode, int32_t total_tick_count, int32_t major_tick_every, GWidget& parent=GScreen)
     : GObject(&parent), _mode(mode), _total_tick_count(total_tick_count), _major_tick_every(major_tick_every)
    {}
    GScale(scale_mode_t mode, int32_t total_tick_count, int32_t major_tick_every, GWidget* parent)
     : GObject(parent), _mode(mode), _total_tick_count(total_tick_count), _major_tick_every(major_tick_every)
    {}

    virtual ~GScale();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }
    virtual void  del();

    inline  void  mode(scale_mode_t mode, int32_t scale_min, int32_t scale_max, int32_t total_tick_count,int32_t major_tick_every)
    {
      this->mode(mode);
      this->range(scale_min, scale_max);
      this->total_tick_count(total_tick_count);
      this->major_tick_every(major_tick_every);
    }

    inline  void  mode(scale_mode_t mode, int32_t total_tick_count,int32_t major_tick_every=1)
    {
      this->mode(mode);
      this->total_tick_count(total_tick_count);
      this->major_tick_every(major_tick_every);
    }

    inline  void  showLabel(bool en)                        { this->label_show(en);       }
    inline  bool  showLabel()                               { return this->label_show();  }

    void line_needle_value(GLine &line, int32_t line_length, int32_t value);
    void image_needle_value(GImage &image, int32_t value);

    inline  void  angle_offset(int32_t angle)               { this->rotation(angle);                  }
    inline  void  angle_offset(GArc &arc)                   { this->angle_offset(arc.angle_offset()); }
    inline  int32_t angle_offset()                          { return this->rotation();                }

    GScaleSection* addSection();
    void           clearSection();
    
    int32_t rotation();

    // GScaleSection new_section();

    /*=====================
    * Setter functions
    *====================*/

    /**
     * Set scale mode. See @ref scale_mode_t
     * @param mode      the new scale mode :  
     *                    SCALE_MODE_TOP, 
     *                    SCALE_MODE_BOTTOM, 
     *                    SCALE_MODE_LEFT, 
     *                    SCALE_MODE_RIGHT, 
     *                    SCALE_MODE_INNER, 
     *                    SCALE_MODE_OUTER,
     *                    SCALE_MODE_ROUND,
     *                    SCALE_MODE_ROUND_OUTER,
     */
    void mode(scale_mode_t mode);

    /**
     * Set scale total tick count (including minor and major ticks)
     * @param total_tick_count    New total tick count
     */
    void total_tick_count(uint32_t total_tick_count);

    inline void tick( uint32_t total_tick_count, uint32_t major_tick_every ){
      this->total_tick_count(total_tick_count);
      this->major_tick_every(major_tick_every);
    }

    /**
     * Sets how often the major tick will be drawn
     * @param major_tick_every    the new count for major tick drawing
     */
    void major_tick_every(uint32_t major_tick_every);

    /**
     * Sets label visibility
     * @param show_label    true/false to enable tick label
     */
    void label_show(bool show_label);

    /**
     * Set the minimal and maximal values on a scale
     * @param min       minimum value of the scale
     * @param max       maximum value of the scale
     */
    void range(int32_t min, int32_t max);

    inline void range(GArc &arc)            { this->range(arc.min_value(), arc.max_value());  }
    inline void range(GBar &bar)            { this->range(bar.min_value(), bar.max_value());  }

    /**
     * Set properties specific to round scale
     * @param angle_range   the angular range of the scale
     */
    void angle_range(uint32_t angle_range);

    inline void angle_range(GArc &arc)      { this->angle_range( arc.bg_enable()? (arc.bg_end_angle()- arc.bg_start_angle()) : (arc.end_angle()- arc.start_angle())); }

    /**
     * Set properties specific to round scale
     * @param rotation  the angular offset from the 3 o'clock position (clock-wise)
     */
    void rotation(int32_t rotation);

    /**
     * Point the needle to the corresponding value through the line
     * @param needle_line      needle_line of the scale
     * @param needle_length    length of the needle
     *                         needle_length>0 needle_length=needle_length;
     *                         needle_length<0 needle_length=radius-|needle_length|;
     * @param value            needle to point to the corresponding value
     */
    void line_needle_value(obj_t * needle_line, int32_t needle_length, int32_t value);

    /**
     * Point the needle to the corresponding value through the image,
       image must point to the right. E.g. -O------>
    * @param needle_img       needle_img of the scale
    * @param value            needle to point to the corresponding value
    */
    void image_needle_value(obj_t * needle_img, int32_t value);

    /**
     * Set custom text source for major ticks labels
     * @param txt_src   pointer to an array of strings which will be display at major ticks
     */
    void text_src(const char * txt_src[]);

    // void text_src(std::vector<const char*> txt_list);
    void text_src(std::vector<String> txt_list);

    /**
     * Draw the scale after all the children are drawn
     * @param en        true: enable post draw
     */
    void post_draw(bool en);

    /**
     * Add a section to the given scale
     * @return          pointer to the new section
     */
    scale_section_t * add_section();

    void clear_sections();

    uint32_t sections_num();

    /**
     * Set the range for the given scale section
     * @param section       pointer to a scale section object
     * @param minor_range   section new minor range
     * @param major_range   section new major range
     */
    void section_set_range(scale_section_t * section, int32_t minor_range, int32_t major_range);

    /**
     * Set the style of the part for the given scale section
     * @param section   pointer to a scale section object
     * @param part      the part for the section, e.g. PART_INDICATOR
     * @param section_part_style Pointer to the section part style
     */
    void section_set_style(scale_section_t * section, uint32_t part, style_t * section_part_style);

    /*=====================
    * Getter functions
    *====================*/

    /**
     * Get scale mode. See @ref scale_mode_t
     * @return      Scale mode
     */
    scale_mode_t mode();

    /**
     * Get scale total tick count (including minor and major ticks)
     * @return      Scale total tick count
     */
    int32_t total_tick_count();

    /**
     * Gets how often the major tick will be drawn
     * @return      Scale major tick every count
     */
    int32_t major_tick_every();

    /**
     * Gets label visibility
     * @return      true if tick label is enabled, false otherwise
     */
    bool label_show();

    /**
     * Get angle range of a round scale
     * @return      Scale angle_range
     */
    uint32_t angle_range();

    /**
     * Get the min range for the given scale section
     * @return      section minor range
     */
    int32_t range_min_value();

    /**
     * Get the max range for the given scale section
     * @return      section max range
     */
    int32_t range_max_value();

    /************************
     * Style
     ************************/
    inline void     color(color_t color)                                                { this->axis_color(color); this->major_color(color); this->minor_color(color);              }
    inline void     color(color_t axis_color, color_t major_color, color_t minor_color) { this->axis_color(axis_color); this->major_color(major_color); this->minor_color(minor_color);              }
    inline void     color(color_t axis_color, color_t tick_color)                       { this->axis_color(axis_color); this->major_color(tick_color); this->minor_color(tick_color);              }
    inline void     thickness(int32_t value)                                            { this->axis_thickness(value); this->major_thickness(value); this->minor_thickness(value);  }
    inline void     thickness(int32_t axis_thick, int32_t major_thick, int32_t minor_thick) { this->axis_thickness(axis_thick); this->major_thickness(major_thick); this->minor_thickness(minor_thick); }
    inline void     thickness(int32_t thick, color_t color )                            { this->thickness(thick); this->color(color);     }

    inline void     tick_length(int32_t major_tick_length, int32_t minor_tick_length)   { this->major_length(major_tick_length); this->minor_length(minor_tick_length); }
    inline void     tick_length(int32_t major_tick_length)                              { this->major_length(major_tick_length);          }
    inline void     tick_color(color_t color)                                           { this->major_color(color); this->minor_color(color); }
    inline color_t  tick_color()                                                        { return this->major_color();                     }
    inline void     tick_opa(opa_t value)                                               { this->major_opa(value); this->minor_opa(value); }
    inline opa_t    tick_opa()                                                          { return this->major_opa();                       }


    inline void     axis_color(color_t color)                                           { GObject::line_color(color, GPART_MAIN ); GObject::arc_color(color, GPART_MAIN );  }
    inline color_t  axis_color()                                                        { return GObject::line_color(GPART_MAIN );                                          }
    inline void     axis_thickness(int32_t value)                                       { GObject::line_width(value, GPART_MAIN ); GObject::arc_width(value, GPART_MAIN );  }
    inline void     axis_thickness(int32_t value, color_t color)                        { this->axis_thickness(value); this->axis_color(color);                             }
    inline int32_t  axis_thickness()                                                    { return GObject::line_width(GPART_MAIN );                                          }
    inline void     axis_opa(opa_t value)                                               { GObject::line_opa(value, GPART_MAIN ); GObject::arc_opa(value, GPART_MAIN );      }
    inline opa_t    axis_opa()                                                          { return GObject::line_opa(GPART_MAIN );                                            }

    inline void     major_color(color_t color)                                          { GObject::line_color(color, GPART_INDICATOR );   }
    inline color_t  major_color()                                                       { return GObject::line_color(GPART_INDICATOR );   }
    inline void     major_thickness(int32_t value)                                      { GObject::line_width(value, GPART_INDICATOR );   }
    inline void     major_thickness(int32_t value, color_t color)                       { this->major_thickness(value); this->major_color(color);  }
    inline int32_t  major_thickness()                                                   { return GObject::line_width(GPART_INDICATOR );   }
    inline void     major_opa(opa_t value)                                              { GObject::line_opa(value, GPART_INDICATOR );     }
    inline opa_t    major_opa()                                                         { return GObject::line_opa(GPART_INDICATOR );     }
    inline void     major_length(int32_t value)                                         { GObject::style_length(value, GPART_INDICATOR);  }
    inline int32_t  major_length()                                                      { return GObject::style_length(GPART_INDICATOR);  }

    inline void     minor_color(color_t color)                                          { GObject::line_color(color ,GPART_ITEMS );       }
    inline color_t  minor_color()                                                       { return GObject::line_color(GPART_ITEMS );       }
    inline void     minor_thickness(int32_t value)                                      { GObject::line_width(value, GPART_ITEMS );       }
    inline void     minor_thickness(int32_t value, color_t color)                       { this->minor_thickness(value); this->minor_color(color);  }
    inline int32_t  minor_thickness()                                                   { return GObject::line_width(GPART_ITEMS );       }
    inline void     minor_opa(opa_t value)                                              { GObject::line_opa(value, GPART_ITEMS );         }
    inline opa_t    minor_opa()                                                         { return GObject::line_opa(GPART_ITEMS );         }
    inline void     minor_length(int32_t value)                                         { GObject::style_length(value, GPART_ITEMS);  }
    inline int32_t  minor_length()                                                      { return GObject::style_length(GPART_ITEMS);  }

    std::vector<std::unique_ptr<GScaleSection>> sections;

  private:
    scale_mode_t _mode = SCALE_MODE_HOR_BOTTOM;
    int32_t _total_tick_count = -1;
    int32_t _major_tick_every = -1;
    std::vector<const char*> cstr_list;
    std::vector<String> str_list;
};

enum { SECT_LABEL, SECT_MAIN, SECT_MINOR };

class GScaleSection {
  public:
    GScaleSection() {}

    GScaleSection& operator = (scale_section_t * section);
    void set(scale_section_t * section);

    void range(int32_t minor_range, int32_t major_range);
    void update_style();

    inline void     color(color_t color)                                                { this->axis_color(color); this->major_color(color); this->minor_color(color);                  }
    inline void     color(color_t axis_color, color_t major_color, color_t minor_color) { this->axis_color(axis_color); this->major_color(major_color); this->minor_color(minor_color); }
    inline void     color(color_t axis_color, color_t tick_color)                       { this->axis_color(axis_color); this->major_color(tick_color); this->minor_color(tick_color);   }
    inline void     thickness(int32_t value)                                            { this->axis_thickness(value); this->major_thickness(value); this->minor_thickness(value);      }
    inline void     thickness(int32_t axis_thick, int32_t major_thick, int32_t minor_thick) { this->axis_thickness(axis_thick); this->major_thickness(major_thick); this->minor_thickness(minor_thick); }
    inline void     thickness(int32_t thick, color_t color )                            { this->thickness(thick); this->color(color);     }

    /* font เหมือนมีปัญหา !!! */
    inline void     font(const font_t&font)                                             { style[SECT_LABEL].font(font); update_style();           }
    inline void     font(const font_t&font, color_t color)                              { style[SECT_LABEL].font(font,color); update_style();     }
    inline void     font_color(color_t color)                                           { style[SECT_LABEL].font_color(color); update_style();    }

    inline void     major_color(color_t color)                                          { style[SECT_LABEL].line_color(color); update_style();    }
    inline void     major_thickness(int32_t value)                                      { style[SECT_LABEL].line_width(value);  update_style();   }
    inline void     major_thickness(int32_t value, color_t color)                       { this->major_thickness(value); this->major_color(color); }
    inline void     major_opa(opa_t value)                                              { style[SECT_LABEL].line_opa(value); update_style();      }
    inline void     major_length(int32_t value)                                         { style[SECT_LABEL].length(value); update_style();        }

    inline void     minor_color(color_t color)                                          { style[SECT_MINOR].line_color(color); update_style();    }
    inline void     minor_thickness(int32_t value)                                      { style[SECT_MINOR].line_width(value); update_style();    }
    inline void     minor_thickness(int32_t value, color_t color)                       { this->minor_thickness(value); this->minor_color(color); }
    inline void     minor_opa(opa_t value)                                              { style[SECT_MINOR].line_opa(value); update_style();      }
    inline void     minor_length(int32_t value)                                         { style[SECT_MINOR].length(value); update_style();        }

    inline void     axis_color(color_t color)                                           { style[SECT_MAIN].line_color(color); style[SECT_MAIN].arc_color(color); update_style();  }
    inline void     axis_thickness(int32_t value)                                       { style[SECT_MAIN].line_width(value); style[SECT_MAIN].arc_width(value); update_style();  }
    inline void     axis_thickness(int32_t value, color_t color)                        { this->axis_thickness(value); this->axis_color(color);                                   }
    inline void     axis_opa(opa_t value)                                               { style[SECT_MAIN].line_opa(value); style[SECT_MAIN].arc_opa(value);                      }


    GStyle style[3];    // SECT_LABEL, SECT_MAIN, SECT_MINOR 
    scale_section_t *_section=NULL;

};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GSCALE_H__
