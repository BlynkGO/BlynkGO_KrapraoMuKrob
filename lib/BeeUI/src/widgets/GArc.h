/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GArc.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GARC_H__
#define __GARC_H__


#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

typedef enum{
  ARC_CLOCKWISE,
  ARC_ANTICLOCKWISE,
} arc_direction_t;


enum {
  ARC_MODE_NORMAL,
  ARC_MODE_SYMMETRICAL,
  ARC_MODE_REVERSE
};
typedef uint8_t arc_mode_t;

class GArc : public GObject {
  public:
    GArc(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GArc(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GArc();

    virtual void  create();
    inline  void  create(GWidget& parent)                                 { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                                 { this->_par =  parent; this->create();               }

    inline void  direction(arc_direction_t dir) {
      this->_dir = dir;
      switch(dir){
        case ARC_CLOCKWISE:
          this->mode(ARC_MODE_NORMAL);
          break;
        case ARC_ANTICLOCKWISE:
          this->mode(ARC_MODE_REVERSE);
          break;
      }
    }
    inline arc_direction_t direction()                                  { return this->_dir;          }
    inline void radius(int32_t r)                                       { GObject::size(2*r, 2*r);    }
    inline int32_t radius()                                             { return GObject::width()/2;  }

    //---------------------------------------------
    /**
     * Set the start angle of an arc. 0 deg: right, 90 bottom, etc.
     * @param start     the start angle.
     */
    void start_angle(value_precise_t start);

    /**
     * Get the start angle of an arc.
     * @return          the start angle [0..360]  (if `LV_USE_FLOAT` is enabled it can be fractional too.)
     */
    value_precise_t start_angle();

    /**
     * Set the stop/end angle of an arc. 0 deg: right, 90 bottom, etc.
     * @param stop       the stop/end angle
     */
    void stop_angle(value_precise_t stop);

    /**
     * Get the stop/end angle of an arc.
     * @return          the stop/end angle [0..360]
     */
    value_precise_t stop_angle();


    /**
     * Set the stop/end angle of an arc. 0 deg: right, 90 bottom, etc.
     * @param end       the end angle
     */
    inline void end_angle(value_precise_t end)                          { this->stop_angle(end);    }

    /**
     * Get the stop/end angle of an arc.
     * @return          the stop/end angle [0..360]
     */
    inline value_precise_t end_angle()                                  { return this->stop_angle();  }

    /**
     * Set the start and end angles
     * @param start     the start angle
     * @param end       the end angle
     */
    void set_angle(value_precise_t start, value_precise_t end);  // มุมของ arc ด้านบน  (คู่กับ bg_angle )

    inline void angle(value_precise_t start, value_precise_t end){
      this->set_angle(start, end);
      this->bg_angle(start, end);
    }


    inline void angle_range(value_precise_t end)                        { this->angle(0, end);          }
    inline value_precise_t angle_range()                                { return this->bg_end_angle();  }
  
    /**
     * Set the start angle of an arc background. 0 deg: right, 90 bottom, etc.
     * @param start     the start angle of an arc background
     */
    void bg_start_angle(value_precise_t start);

    value_precise_t bg_start_angle();

    /**
     * Set the stop/end angle of an arc background. 0 deg: right, 90 bottom etc.
     * @param stop       the stop/end angle of an arc background
     */
    void bg_stop_angle(value_precise_t stop);

    /**
     * Get the stop/end angle of an arc background.
     * @return          the stop/end angle [0..360]
     */
    value_precise_t bg_stop_angle();

    /**
     * Set the stop/end angle of an arc background. 0 deg: right, 90 bottom etc.
     * @param end       the stop/end angle
     */
    inline void bg_end_angle(value_precise_t end)                       { this->bg_stop_angle(end); }

    /**
     * Get the stop/end angle of an arc background.
     * @return          the stop/end angle [0..360]
     */
    value_precise_t bg_end_angle()                                      { return this->bg_stop_angle(); }

    /**
     * Set the start and end angles of the arc background
     * @param start     the start angle
     * @param end       the end angle
     */
    void bg_angle(value_precise_t start, value_precise_t end);

    /**
     * Set the rotation for the whole arc from math x-axis clockwise
     * @param rotation      rotation angle
     */
    void rotation(int32_t rotation);

    /**
     * Get the rotation for the whole arc
     * @return          arc's current rotation
     */
    int32_t rotation();

    /**
     * Set the angle_offset for the whole arc from math x-axis clockwise
     * @param angle_offset      angle offset 
     */
    inline void angle_offset(int32_t angle_offset)                                { this->rotation(angle_offset);     }

    /**
     * Get the rotation for the whole arc
     * @return          arc's current rotation
     */
    inline int32_t angle_offset()                                                 { return this->rotation();          }

    
    /**
     * Set the mode of arc.
     * @param mode      arc's mode :   ARC_MODE_NORMAL, ARC_MODE_SYMMETRICAL, ARC_MODE_REVERSE
     */
    void mode(arc_mode_t mode);

    arc_mode_t mode();

    /**
     * Set a new value on the arc
     * @param value     new value
     */
    void value(int32_t value);

    /**
     * Get the value of an arc
     * @return          the value of the arc
     */
    int32_t value();

    /**
     * Get the value of an arc
     * @return          the value of the arc
     */
    inline int32_t toInt()                       { return this->value(); }

    /**
     * Set a new value on the arc
     * @param value     new value
     */
    GArc& operator=(int32_t value);

    /**
     * Set minimum and the maximum values of an arc
     * @param min_value       minimum value
     * @param max_value       maximum value
     */
    void range(int32_t  min_value, int32_t max_value);

    /**
     * Get the minimum value of an arc
     * @return          the minimum value of the arc
     */
    int32_t min_value();

    /**
     * Get the maximum value of an arc
     * @return          the maximum value of the arc
     */
    int32_t max_value();

    /**
     * Set a change rate to limit the speed how fast the arc should reach the pressed point.
     * @param rate      the change rate
     */
    void rate(uint32_t rate);

    inline void     bg_enable(bool enable)                        { GObject::arc_opa(enable? 255:0, GPART_MAIN);                                }
    inline bool     bg_enable()                                   { return (GObject::arc_opa(GPART_MAIN)==0)? false : true;                     }
    inline void     bg_color(color_t color)                       { GObject::arc_color(color, GSTATE_DEFAULT);                                  }
    inline color_t  bg_color()                                    { return GObject::arc_color(GSTATE_DEFAULT);                                  }
    inline void     bg_opa(uint8_t opa)                           { GObject::arc_opa  (opa  , GSTATE_DEFAULT);                                  }
    inline uint8_t  bg_opa()                                      { return GObject::arc_opa  (GSTATE_DEFAULT);                                  }
    inline void     color(color_t color)                          { GObject::arc_color(color, (gstate_t) (GPART_INDICATOR | GSTATE_DEFAULT));   }
    inline color_t  color()                                       { return GObject::arc_color((gstate_t) (GPART_INDICATOR | GSTATE_DEFAULT));   }
    inline void     opa(uint8_t opa)                              { GObject::arc_opa  (opa  , (gstate_t) (GPART_INDICATOR | GSTATE_DEFAULT));   }
    inline uint8_t  opa()                                         { return GObject::arc_opa((gstate_t) (GPART_INDICATOR | GSTATE_DEFAULT));     }
    inline void     rounded(bool enable)                          { GObject::arc_rounded(enable, GSTATE_DEFAULT); GObject::arc_rounded(enable, (gstate_t) (GPART_INDICATOR | GSTATE_DEFAULT));}
    inline bool     rounded()                                     { return GObject::arc_rounded((gstate_t) (GPART_INDICATOR | GSTATE_DEFAULT)); }
    inline void     thickness(int16_t thick)                      { GObject::arc_width(thick , GSTATE_DEFAULT); GObject::arc_width(thick , (gstate_t) (GPART_INDICATOR | GSTATE_DEFAULT));}
    inline void     thickness(int16_t thick, color_t color)       { this->thickness(thick); this->color(color);                                 }
    inline int16_t  thickness()                                   { return GObject::arc_width((gstate_t) (GPART_INDICATOR | GSTATE_DEFAULT));   }
    inline void     bg_thickness(int16_t thick)                   { GObject::arc_width(thick , GSTATE_DEFAULT);                                 }
    inline int16_t  bg_thickness()                                { return GObject::arc_width( GSTATE_DEFAULT);                                 }

    class knob_class {
      public:
        knob_class(GArc *arc)                                     { _arc = arc;                       }
        inline void enable(bool enable)                           { _arc->knob_enable(enable);        }
        inline bool enable()                                      { return _arc->knob_enable();       }
        inline void clickable(bool enable)                        { _arc->clickable(enable);          }
        inline bool clickable()                                   { return _arc->clickable();         }
        inline void offset(int32_t offset)                        { _arc->knob_offset(offset);        }
        inline int32_t offset()                                   { return _arc->knob_offset();       }
        inline void color(color_t color)                          { _arc->knob_color(color);          }
        inline color_t color()                                    { return _arc->knob_color();        }
        inline void opa(uint8_t opa)                              { _arc->knob_opa(opa);              }
        inline uint8_t opa()                                      { return _arc->knob_opa();          }
        inline void padding(uint16_t padding)                     { _arc->knob_padding(padding);      }
        inline uint16_t padding()                                 { return _arc->knob_padding();      }
        inline void border(uint16_t w)                            { _arc->knob_border(w);             }
        inline uint16_t border()                                  { return _arc->knob_border();       }
        inline void border_color(color_t color)                   { _arc->knob_border_color(color);   }
        inline color_t border_color()                             { return _arc->knob_border_color(); }
        inline void border(uint16_t w,color_t color)              { _arc->knob_border(w,color);       }
        inline void border_opa(uint8_t opa)                       { _arc->knob_border_opa(opa);       }
        inline uint8_t border_opa()                               { return _arc->knob_border_opa();   }
      private:
        GArc* _arc;
    };
    knob_class knob= knob_class(this);

    /**
     * Set an offset angle for the knob
     * @param offset    knob offset from main arc in degrees
     */
    void knob_offset(int32_t offset);

    int32_t knob_offset();

    /**
     * Set the knob enable
     * @param enable    knob enable
     */
    inline void knob_enable(bool enable)                          { _knob_enable = enable; GObject::opa((enable)? 255:0, (gstate_t) (GPART_KNOB | GSTATE_DEFAULT)); this->clickable(enable);  }
    inline bool knob_enable()                                     { return _knob_enable; }

    inline void     knob_color(color_t color)                     { GObject::bg_color(color, (gstate_t) (GPART_KNOB | GSTATE_DEFAULT));       }
    inline color_t  knob_color()                                  { return GObject::bg_color((gstate_t) (GPART_KNOB | GSTATE_DEFAULT));       }
    inline void     knob_opa(uint8_t opa)                         { GObject::opa(opa, (gstate_t) (GPART_KNOB | GSTATE_DEFAULT));              }
    inline uint8_t  knob_opa()                                    { return GObject::opa((gstate_t) (GPART_KNOB | GSTATE_DEFAULT));            }
    inline void     knob_padding(uint16_t padding)                { GObject::padding( padding, (gstate_t) (GPART_KNOB | GSTATE_DEFAULT));     }
    inline uint16_t knob_padding()                                { return GObject::padding( (gstate_t) (GPART_KNOB | GSTATE_DEFAULT));       }
    inline void     knob_border(uint16_t border)                  { GObject::border( border, (gstate_t) (GPART_KNOB | GSTATE_DEFAULT));       }
    inline void     knob_border(uint16_t border,color_t color)    { this->knob_border(border); this->knob_border_color(color);                }
    inline uint16_t knob_border()                                 { return GObject::border( (gstate_t) (GPART_KNOB | GSTATE_DEFAULT));        }
    inline void     knob_border_color(color_t color)              { GObject::border_color( color, (gstate_t) (GPART_KNOB | GSTATE_DEFAULT));  }
    inline color_t  knob_border_color()                           { return GObject::border_color((gstate_t) (GPART_KNOB | GSTATE_DEFAULT));   }
    inline void     knob_border_opa(uint8_t opa)                  { GObject::border_opa( opa, (gstate_t) (GPART_KNOB | GSTATE_DEFAULT));      }
    inline uint8_t  knob_border_opa()                             { return GObject::border_opa( (gstate_t) (GPART_KNOB | GSTATE_DEFAULT));    }
    // inline void     knob_radius(uint16_t r)                       { GObject::radius( r, (gstate_t) (GPART_KNOB | GSTATE_DEFAULT)); }
    // inline uint16_t knob_radius()                                 { return GObject::radius( (gstate_t) (GPART_KNOB | GSTATE_DEFAULT)); }


    /**
     * Align an object to the current position of the arc (knob)
     * @param widget         pointer to an GWidget to rotate
     * @param r_offset       consider the radius larger with this value (< 0: for smaller radius)
     */
    void align_GWidget_to_angle(GWidget*widget, int32_t r_offset);
    inline void align_GWidget_to_angle(GWidget&widget, int32_t r_offset)    { this->align_GWidget_to_angle(&widget, r_offset); }

    /**
     * Rotate an object to the current position of the arc (knob)
     * @param widget         pointer to an GWidget to rotate
     * @param r_offset       consider the radius larger with this value (< 0: for smaller radius)
     */
    void rotate_GWidget_to_angle(GWidget *widget, int32_t r_offset);
    inline void rotate_GWidget_to_angle(GWidget&widget, int32_t r_offset)    { this->rotate_GWidget_to_angle(&widget, r_offset); }

  protected:
    bool _knob_enable = false;
    arc_direction_t _dir;

};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GARC_H__
