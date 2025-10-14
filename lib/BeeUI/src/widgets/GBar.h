/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 *
 *   1. โคดไฟล์ GBar.h นี้เป็นไลบรารี่ลิขลิทธิ์
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

#ifndef __GBAR_H__
#define __GBAR_H__


#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5
{
//----------------------------------------

class GBar : public GObject
{
  public:
    GBar(GWidget & parent = GScreen)                        : GObject(&parent) {}
    GBar(GWidget* parent)                                   : GObject(parent)  {}
    virtual ~GBar();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    /**
     * Get the value of a bar
     * @return          the value of the bar
     */
    inline  int   toInt()                                   { return this->value();                               }

    using GObject::color;
    using GObject::radius;
    using GObject::corner_radius;
    using GObject::border;
 
    // inline void color(color_t color)                     { GObject::bg_color(color, GPART_INDICATOR);  GObject::bg_color(TFT_COLOR_MIX(color, TFT_WHITE, 200), GPART_MAIN);  }
    inline void color(color_t color)                        { GObject::bg_color(color, GPART_INDICATOR);                                  }
    inline void color(color_t color, color_t grad_color)    { GObject::bg_color(color, GPART_INDICATOR);  GObject::grad_color( grad_color, GPART_INDICATOR);  }
    inline color_t color()                                  { return GObject::bg_color(GPART_INDICATOR);                                  }
    inline color_t grad_color()                             { return GObject::bg_grad_color(GPART_INDICATOR);                             }
    inline void grad_dir(grad_dir_t grad_dir)               { GObject::bg_grad_dir(grad_dir, GPART_INDICATOR);                            }
    inline grad_dir_t grad_dir()                            { return GObject::bg_grad_dir();                                              }
    inline void opa(uint8_t opa)                            { GObject::opa(opa, GPART_INDICATOR);                                         }
    inline uint8_t  opa()                                   { return GObject::opa(GPART_INDICATOR);                                       }

    inline void bg_color(color_t color)                     { GObject::bg_color(color, GPART_MAIN);                                       }
    inline color_t  bg_color()                              { return GObject::bg_color(GPART_MAIN);                                       }
    inline void bg_opa(uint8_t opa)                         { GObject::bg_opa(opa, GPART_MAIN);                                           }
    inline uint8_t  bg_opa()                                { return GObject::bg_opa(GPART_MAIN);                                         }

    inline void image(const img_t& img)                     { GObject::bg_image_src(&img, GPART_INDICATOR);                               }
    inline void image(const img_t* img)                     { GObject::bg_image_src(img, GPART_INDICATOR);                                }
    inline const img_t* image()                             { return (const img_t*) GObject::bg_image_src( GPART_INDICATOR);              }
    inline void image_opa(uint8_t opa)                      { return GObject::bg_image_opa(opa, GPART_INDICATOR);                         }
    inline void image_tiled(bool enable)                     { return GObject::bg_image_tiled(enable, GPART_INDICATOR);                   }

    inline void rounded(bool en)                            { GObject::rounded(en, GPART_INDICATOR);   GObject::rounded(en, GPART_MAIN);  }
    inline void radius(uint16_t r)                          { GObject::radius(r, GPART_INDICATOR);     GObject::radius(r, GPART_MAIN);    }
    inline void corner_radius(uint16_t r)                   { this->radius(r); }

    inline void direction(base_dir_t direction)             { GObject::base_dir(direction);  }

    //----------------------------------------------------
    /**
     * Set a new value on the bar
     * @param value         new value
     * @param anim_enable   true: set the value with an animation; false: change the value immediately
     */
    void value(int32_t value, bool anim_enable = true);

    /**
     * Set a new start value on the bar
     * @param start_value     new start value
     * @param anim_enable   true: set the value with an animation; false: change the value immediately
     */
    void start_value(int32_t start_value, bool anim_enable = true);

    inline void value_range(int32_t start_value, int32_t value)
    {
      this->value(value, false);
      this->start_value(start_value);
    }


    /**
     * Set a new value on the gauge
     * @param value     new value
     */
    GBar & operator=(int32_t value);

    /**
     * Set minimum and the maximum values of a bar
     * @param min       minimum value
     * @param max       maximum value
     * @note If min is greater than max, the drawing direction becomes to the oppsite direction.
     */
    void range(int32_t min, int32_t max);

    /**
     * Set the type of bar.
     * @param mode      bar type from :: bar_mode_t : BAR_MODE_NORMAL,  BAR_MODE_SYMMETRICAL,  BAR_MODE_RANGE
     */
    void mode(bar_mode_t mode);   //   BAR_MODE_NORMAL,  BAR_MODE_SYMMETRICAL,  BAR_MODE_RANGE

    /**
     * Set the orientation of bar.
     * @param orient    bar orientation from ::lv_bar_orientation_t
     */
    void orientation(bar_orientation_t orient);

    /**
     * Get the value of a bar
     * @return          the value of the bar
     */
    int32_t value();


    /**
     * Get the start value of a bar
     * @return          the start value of the bar
     */
    int32_t start_value();

    /**
     * Get the minimum value of a bar
     * @return          the minimum value of the bar
     */
    int32_t min_value();

    /**
     * Get the maximum value of a bar
     * @return          the maximum value of the bar
     */
    int32_t max_value();

    /**
     * Get the type of bar.
     * @return          bar type from ::lv_bar_mode_t
     */
    bar_mode_t mode();

    /**
     * Get the orientation of bar.
     * @return          bar orientation from ::lv_bar_orientation_t
     */
    bar_orientation_t orientation();

    /**
     * Give the bar is in symmetrical mode or not
     * @return          true: in symmetrical mode false : not in
    */
    bool isSymmetrical();

    /**
     * Get the indic area of a bar
     * @return          the indic area of a bar
     */
    area_t indic_area();



  private:
};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GBAR_H__
