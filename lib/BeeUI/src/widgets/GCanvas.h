/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GCanvas.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GCANVAS_H__
#define __GCANVAS_H__


#include "GObject.h"
#include "GLayer.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

#ifndef DRAW_BUF_DEFINE
#define DRAW_BUF_DEFINE(name, _w, _h, _cf) \
    static uint8_t buf_##name[_LV_DRAW_BUF_SIZE(_w, _h, _cf)]; \
    static draw_buf_t name; \
      name.header.magic = LV_IMAGE_HEADER_MAGIC; \
      name.header.cf    = (_cf); \
      name.header.flags = LV_IMAGE_FLAGS_MODIFIABLE; \
      name.header.w     = (_w); \
      name.header.h     = (_h); \
      name.header.stride = _LV_DRAW_BUF_STRIDE(_w, _cf); \
      name.header.reserved_2 = 0; \
      name.data_size = sizeof(buf_##name); \
      name.data = buf_##name; \
      name.unaligned_data = buf_##name; 
#endif

// --- error ------
// static uint8_t* buf_draw_buf = (uint8_t*) esp32_malloc(BlynkGO.width()*BlynkGO.height()*4);
// static draw_buf_t draw_buf = { 
//   .header = {
//               .magic      = IMAGE_HEADER_MAGIC,
//               .cf         = COLOR_FORMAT_ARGB8888,
//               .flags      = IMAGE_FLAGS_MODIFIABLE,
//               .w          = (BlynkGO.width()),
//               .h          = (BlynkGO.height()),
//               .stride     = 4,
//               .reserved_2 = 0,
//             },
//   .data_size = BlynkGO.width()*BlynkGO.height()*4,
//   .data = buf_draw_buf,
//   .unaligned_data = buf_draw_buf,
// };

class GCanvas : public GObject {
  public:
    GCanvas(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GCanvas(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GCanvas();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    inline  void  draw_buf(draw_buf_t& draw_buf)            { this->draw_buf(&draw_buf);      }

    /*=====================
    * Setter functions
    *====================*/

    /**
     * Set a buffer for the canvas.
     * Use `draw_buf` instead if you need to set a buffer with alignment requirement.
     * The required size is (COLOR_FORMAT_GET_SIZE(cf) * w) / 8 * h)
     * It can be allocated with `lv_malloc()` or
     * it can be statically allocated array (e.g. static lv_color_t buf[100*50]) or
     * it can be an address in RAM or external SRAM
     * @param canvas pointer to a canvas object
     * @param w width of the canvas
     * @param h height of the canvas
     * @param cf color format. `COLOR_FORMAT...`
     */
    void buffer(void * buf, int32_t w, int32_t h, color_format_t cf=COLOR_FORMAT_RGB565);

    /**
     * Set a draw buffer for the canvas. A draw buffer either can be allocated by `draw_buf_create()`
     * or defined statically by `DRAW_BUF_DEFINE`. When buffer start address and stride has alignment
     * requirement, it's recommended to use `draw_buf_create`.
     * @param draw_buf  pointer to a draw buffer
     */
    void draw_buf(draw_buf_t * draw_buf);

    /**
     * Set a pixel's color and opacity
     * @param x     X coordinate of the pixel
     * @param y     Y coordinate of the pixel
     * @param color the color
     * @param opa   the opacity
     * @note        The following color formats are supported
     *              LV_COLOR_FORMAT_I1/2/4/8, LV_COLOR_FORMAT_A8,
     *              LV_COLOR_FORMAT_RGB565, LV_COLOR_FORMAT_RGB888,
     *              LV_COLOR_FORMAT_XRGB8888, LV_COLOR_FORMAT_ARGB8888
     */
    void px(int32_t x, int32_t y, color_t color, opa_t opa);

    /**
     * Set the palette color of a canvas for index format. Valid only for `COLOR_FORMAT_I1/2/4/8`
     * @param id        the palette color to set:
     *                  - for `COLOR_FORMAT_I1`: 0..1
     *                  - for `COLOR_FORMAT_I2`: 0..3
     *                  - for `COLOR_FORMAT_I4`: 0..15
     *                  - for `COLOR_FORMAT_I8`: 0..255
     * @param c         the color to set
     */
    void palette(uint8_t id, color32_t c);

    /*=====================
    * Getter functions
    *====================*/

    /**
     * Return the pointer for the draw buffer.
     * It's recommended to use this function instead of the buffer form the
     * return value of image() as is can be aligned
     * @return          pointer to the draw buffer
     */
    draw_buf_t * draw_buf();

    /**
     * Get a pixel's color
     * @param x     X coordinate of the pixel
     * @param y     Y coordinate of the pixel
     * @return      color of the pixel
     */
    color_t px(int32_t x, int32_t y);

    /**
     * Get a pixel's opacity
     * @param x     X coordinate of the pixel
     * @param y     Y coordinate of the pixel
     * @return      color of the pixel
     */
    opa_t px_opa(int32_t x, int32_t y);

    /**
     * Get the image of the canvas as a pointer to an `img_t` variable.
     * @return          pointer to the image descriptor.
     */
    img_t * image();

    /**
     * Return the pointer for the buffer.
     * It's recommended to use this function instead of the buffer form the
     * return value of image() as is can be aligned
     * @return          pointer to the buffer
     */
    const void * buf();

    /*=====================
    * Other functions
    *====================*/

    /**
     * Copy a buffer to the canvas
     * @param canvas_area   the area of the canvas to copy
     * @param dest_buf      pointer to a buffer to store the copied data
     * @param dest_area     the area of the destination buffer to copy to. If omitted NULL, copy to the whole `dest_buf`
     */
    void copy_buf(const area_t * canvas_area, draw_buf_t * dest_buf,
                            const area_t * dest_area);

    /**
     * Fill the canvas with color
     * @param color     the background color
     * @param opa       the desired opacity
     */
    void fill_bg(color_t color, opa_t opa=OPA_COVER);

    // void fill_bg(lv_color_t color, lv_opa_t opa);

    /**
     * Initialize a layer to use generic draw functions (draw_rect/label/...) on the canvas.
     * Needs to be usd in pair with `finish_layer`.
     * @param layer     pointer to a layer variable to initialize
     */
    void init_layer(layer_t * layer);

    inline void init_layer(layer_t &layer)        { this->init_layer(&layer);         }

    inline void init_layer(GLayer &layer)         { this->init_layer(layer._p_layer); }

    /**
     * Wait until all the drawings are finished on layer.
     * Needs to be usd in pair with `init_layer`.
     * @param layer     pointer to a layer to finalize
     */
    void finish_layer(layer_t * layer);

    inline void finish_layer(layer_t &layer)      { this->finish_layer(&layer);  this->invalidate();  }
    
    inline void finish_layer(GLayer &layer)       { this->finish_layer( layer._p_layer);  this->invalidate(); }

  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GCANVAS_H__
