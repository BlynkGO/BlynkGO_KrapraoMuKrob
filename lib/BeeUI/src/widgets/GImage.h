/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GImage.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GIMAGE_H__
#define __GIMAGE_H__


#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GImage : public GObject {
  public:
    GImage(GWidget& parent=GScreen)                           : GObject(&parent) {}
    GImage(GWidget* parent)                                   : GObject(parent)  {}
    GImage(const img_t & src_img, GWidget& parent=GScreen)    : img(&src_img), GObject(&parent) {}
    GImage(const img_t & src_img, GWidget* parent)            : img(&src_img), GObject(parent)  {}
    GImage(const img_t * src_img, GWidget& parent=GScreen)    : img(src_img) , GObject(&parent) {}
    GImage(const img_t * src_img, GWidget* parent)            : img(src_img) , GObject(parent)  {}
    GImage(const void* symbol, GWidget& parent=GScreen)       : img(symbol), GObject(&parent) {}

    virtual ~GImage();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    /*=====================
    * Setter functions
    *====================*/

    /**
     * Set the image data to display on the object
     * @param src       1) pointer to an :: image_t descriptor (e.g. &my_img) or
     *                  2) path to an image file (e.g. "S:/dir/img.bin")or
     *                  3) a SYMBOL (e.g. SYMBOL_OK)
     */
    void src(const void * src);

    inline void setImage(const img_t *src_img)          { this->src((const void*) src_img);               }
    inline void setImage(const img_t & src_img)         { this->setImage(&src_img);                       }
    inline void setSymbol(const void* symbol)           { this->src( symbol);                             }

    /**
     * Set an offset for the source of an image so the image will be displayed from the new origin.
     * @param x         the new offset along x axis.
     */
    void offset_x(int32_t x);

    /**
     * Set an offset for the source of an image.
     * so the image will be displayed from the new origin.
     * @param y         the new offset along y axis.
     */
    void offset_y(int32_t y);

    inline void offset(int32_t x, int32_t y)              { if(!isCreated()) create(); this->offset_x(x); this->offset_y(y);    }
    inline void oiffet(Point p)                           { this->offset(p.x,p.y);  }

    /**
     * Set the rotation angle of the image.
     * The image will be rotated around the set pivot set by `lv_image_set_pivot()`
     * Note that indexed and alpha only images can't be transformed.
     * @param angle     rotation in degree with 0.1 degree resolution (0..360.0: clock wise)
     * @note            if image_align is `IMAGE_ALIGN_STRETCH` or `IMAGE_ALIGN_FIT`
     *                  rotation will be set to 0 automatically.
     *
     */
    void rotation(float angle);  // 0 .. 360.0

    inline void angle(float angle)                      { this->rotation(angle);    }

    /**
     * Set the rotation center of the image.
     * The image will be rotated around this point.
     * x, y can be set with value of PCT(..), pivot(...) will return the true pixel coordinate of pivot in this case.
     * @param x         rotation center x of the image
     * @param y         rotation center y of the image
     */
    void pivot(int32_t x, int32_t y);

    inline void pivot(Point p)                          { this->pivot(p.x,p.y);   }

    /**
     * Set the scale factor of the image.
     * Note that indexed and alpha only images can't be transformed.
     * @param scale      the scale factor.  scale : 0 .. 128(half) ..256(no zoom).. 512(double)
     */
    void scale(uint32_t scale);

    /**
     * Set the zoom factor of the image.
     * Note that indexed and alpha only images can't be transformed.
     * @param z      the scale factor.  scale : 0 .. 50(half) ..100(no zoom).. 200(double)
     */
    inline void zoom(float z)                           { this->scale(z*256/100.0); }   // z : 0 .. 50( half) .. 100 (no zoom)... 200 (double)

    /**
     * Set the horizontal scale factor of the image.
     * Note that indexed scale alpha only images can't be transformed.
     * @param scale      the horizontal scale factor.
     * @example 256 or ZOOM_IMAGE_NONE for no zoom
     * @example <256: scale down
     * @example >256 scale up
     * @example 128 half size
     * @example 512 double size
     */
    void scale_x(uint32_t scale); // 0 .. 128(half) ..256(no zoom).. 512(double)

    /**
     * Set the vertical scale factor of the image.
     * Note that indexed and alpha only images can't be transformed.
     * @param scale      the vertical scale factor.
     * @example 256 or ZOOM_IMAGE_NONE for no zoom
     * @example <256: scale down
     * @example >256 scale up
     * @example 128 half size
     * @example 512 double size
     */
    void scale_y(uint32_t vertical);

    inline void scale(uint32_t scale_x, uint32_t scale_y)                      { this->scale_x(scale_x); this->scale_y(scale_y);   }

    /**
     * Set the blend mode of an image.
     * @param blend_mode    the new blend mode
     */
    void blend_mode(blend_mode_t blend_mode);

    /**
     * Enable/disable anti-aliasing for the transformations (rotate, zoom) or not.
     * The quality is better with anti-aliasing looks better but slower.
     * @param antialias true: anti-aliased; false: not anti-aliased
     */
    void antialias(bool antialias);

    /**
     * Set the image object size mode.
     * @param align     the new align mode.
     * @note            if image_align is `IMAGE_ALIGN_STRETCH` or `IMAGE_ALIGN_FIT`
     *                  rotation, scale and pivot will be overwritten and controlled internally.
     */
    void image_align(image_align_t align);

    /*=====================
    * Getter functions
    *====================*/

    /**
     * Get the source of the image
     * @return          the image source (symbol, file name or ::lv-img_dsc_t for C arrays)
     */
    const void * src();
    inline const void* getSource()                { return this->src();                                       }

    /**
     * Get the offset's x attribute of the image object.
     * @return          offset X value.
     */
    int32_t offset_x();

    /**
     * Get the offset's y attribute of the image object.
     * @return          offset Y value.
     */
    int32_t offset_y();

    inline Point offset()                           { return Point(this->offset_x(), this->offset_y());       }

    /**
     * Get the rotation of the image.
     * @return          rotation in degrees (0..360.0)
     * @note            if image_align is `LV_IMAGE_ALIGN_STRETCH` or  `LV_IMAGE_ALIGN_FIT`
     *                  rotation will be set to 0 automatically.
     */
    float rotation();

    inline float angle()                            { return this->rotation();    }

    /**
     * Get the pivot (rotation center) of the image.
     * If pivot is set with PCT, convert it to px before return.
     * @param pivot     store the rotation center here
     */
    Point pivot();

    /**
     * Get the zoom factor of the image.
     * @return          zoom factor (256: no zoom)
     */
    int32_t scale();    // 0 .. 256 ().. 512 (double)

    /**
     * Get the zoom factor of the image.
     * @return          zoom factor (100: no zoom)
     */
    inline float zoom()                   { return scale()*100.0/256.0; }

    /**
     * Get the horizontal zoom factor of the image.
     * @return          zoom factor (256: no zoom)
     */
    int32_t scale_x();

    /**
     * Get the vertical zoom factor of the image.
     * @return          zoom factor (256: no zoom)
     */
    int32_t scale_y();

    /**
     * Get the current blend mode of the image
     * @return          the current blend mode
     */
    blend_mode_t blend_mode();

    /**
     * Get whether the transformations (rotate, zoom) are anti-aliased or not
     * @return          true: anti-aliased; false: not anti-aliased
     */
    bool antialias();

    /**
     * Get the size mode of the image
     * @return          element of @ref lv_image_align_t
     */
    image_align_t image_align();


    GImage& operator =(const img_t * src_img);
    GImage& operator =(const img_t & src_img);
    GImage& operator =(const void * symbol);
    GImage& operator =(draw_buf_t * grap);

    inline bool operator ==(const img_t * src_img) {
      if(!this->isCreated()) this->create();
      return (src_img ==(const img_t*) this->getSource() );
    }

    inline bool operator ==(const img_t & src_img) {
      if(!this->isCreated()) this->create();
      return (&src_img ==(const img_t*) this->getSource() );
    }

    /*=====================
    * Style functions
    *====================*/
    inline void     color(color_t color, gstate_t state=GSTATE_DEFAULT)                         { GObject::image_recolor(color,state);  }
    inline color_t  color(gstate_t state=GSTATE_DEFAULT)                                        { return GObject::image_recolor(state); }
    inline void     filter(color_t color, uint8_t opa=255, gstate_t state=GSTATE_DEFAULT)       { GObject::image_recolor(color, state); GObject::image_recolor_opa(opa,state); }
    inline void     recolor(color_t color, uint8_t opa=255, gstate_t state=GSTATE_DEFAULT)      { this->filter(color, opa, state);      }
    inline void     opa(uint8_t opa, gstate_t state=GSTATE_DEFAULT)                             { GObject::opa(opa,state);              }
    inline uint8_t  opa(gstate_t state=GSTATE_DEFAULT)                                          { return GObject::opa(state);           }

  private:
    const void* img = NULL;
};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GIMAGE_H__
