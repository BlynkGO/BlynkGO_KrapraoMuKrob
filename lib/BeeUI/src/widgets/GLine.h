/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GLine.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GLINE_H__
#define __GLINE_H__


#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

// typedef std::vector<point_precise_t> points_t;

class GLine : public GObject {
  public:
    GLine(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GLine(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GLine();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    virtual void  del(); 

    void          setPoints(Points& points);
    void          setPoints(Point p1, Point p2);
    inline void   setPoints(Point p1, int32_t w, dir_t dir= DIR_HOR) {  this->setPoints(p1, (dir == DIR_VER)? p1+ Point(0,w-1) : p1 + Point(w-1,0)); }

    void          setPoints(Point* points, int32_t point_num);
    void          setPoints(point_precise_t* points, int32_t point_num);
    void          setPoints(uint16_t arm_len, float angle_deg, float angle_deg_offset, Point c, rotate_direction_t rotate= CLOCKWISE); 

    void          addPoint(Point p);
    inline void   addPoint(float x, float y)                { this->addPoint(Point(x,y)); }
    void          addPoints(Points& points);
    void          addPoints(Point* points, int32_t point_num);
    void          resetPoints();

    point_precise_t* getPoints()                            { return this->_p_points;     }
    inline size_t num()                                     { return this->_point_num;    }


    /*=====================
    * Setter functions
    *====================*/

    /**
     * Set an array of points. The line object will connect these points.
     * @param points        an array of points. Only the address is saved, so the array needs to be alive while the line exists
     * @param point_num     number of points in 'point_a'
     */
    void points(const point_precise_t points[], uint32_t point_num);

    /**
     * Enable (or disable) the y coordinate inversion.
     * If enabled then y will be subtracted from the height of the object,
     * therefore the y = 0 coordinate will be on the bottom.
     * @param en        true: enable the y inversion, false:disable the y inversion
     */
    void y_invert(bool en);

    /*=====================
    * Getter functions
    *====================*/

    /**
     * Get the y inversion attribute
     * @return          true: y inversion is enabled, false: disabled
     */
    bool y_invert();


    inline void     thickness(int32_t thick)                  { GObject::line_width(thick);                           }
    inline void     thickness(int32_t thick, color_t color)   { GObject::line_width(thick); this->color(color);       }
    inline int32_t  thickness()                               { return GObject::line_width();                         }
    inline void     thick(int32_t thick)                      { this->thickness(thick);                               }
    inline void     thick(int32_t thick, color_t color)       { this->thickness(thick, color);                        }
    inline void     thick(int32_t thick, color_t color, bool rounded)  { this->thickness(thick, color);  this->rounded(rounded);  }
    inline int32_t  thick()                                   { return this->thickness();                             }
    inline void     color(color_t color)                      { GObject::line_color(color);                           }
    inline color_t  color()                                   { return GObject::line_color();                         }
    inline void     rounded(bool enable)                      { GObject::line_rounded(enable);                        }
    inline bool     rounded()                                 { return GObject::line_rounded();                       }
    inline void     opa(opa_t opa)                            { GObject::line_opa(opa);                               }
    inline opa_t    opa()                                     { return GObject::line_opa();                           }
    inline void     dash_width(int32_t dash_w)                { GObject::line_dash_width(dash_w);                     }
    inline int32_t  dash_width()                              { return GObject::line_dash_width();                    }
    inline void     dash_gap(int32_t dash_gap)                { GObject::line_dash_gap(dash_gap);                     }
    inline int32_t  dash_gap()                                { return GObject::line_dash_gap();                      }
    inline void     dash(int32_t dash_w, int32_t dash_gap)    { this->dash_width(dash_w); this->dash_gap(dash_gap);   }

  private:
    void free_alloc();

    point_precise_t* _p_points;
    int32_t  _point_num=0;

};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GLINE_H__
