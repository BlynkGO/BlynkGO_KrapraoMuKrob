#ifndef __GUTIL_H___
#define __GUTIL_H___

#include <Arduino.h>
#include "../utils/BlynkGO_Type.h"
#include "../utils/esp32_memory.h"
#include "../utils/TridentUnicode.h"
#include "GTimer.h"
#include "GLVGL.h"
#include "Point.h"

#ifndef MEM_CHECK
 #if defined(ESP32)
  #define MEM_CHECK       Serial.printf("[%s][%d] heap %d  psram %d\n", __func__,  __LINE__, ESP.getFreeHeap(), ESP.getFreePsram())
  #define STR_MEM_CHECK   StringX::printf("[%s][%d] heap %d  psram %d\n", __func__,  __LINE__, ESP.getFreeHeap(), ESP.getFreePsram())
 #else
  #define MEM_CHECK
  #define STR_MEM_CHECK
 #endif
#endif

#ifndef GWIDGET
#define GWIDGET     GWidget*widget
#endif

#ifndef GWIDGET_CB
#define GWIDGET_CB  [](GWIDGET)
#endif

#ifndef GWIDGET_EVENT_CB
#define GWIDGET_EVENT_CB  [](GWIDGET, event_t event)
#endif

#ifndef EVENT_CB
#define EVENT_CB  [](lv_event_t *ev)
#endif

#ifndef GWIDGET_DATA
#define GWIDGET_DATA(T) ((T*)widget->user_data())
#endif

#ifndef GWIDGET_CAST
#define GWIDGET_CAST(T) ((T*)widget)
#endif

#ifndef TFT_COLOR
#define TFT_COLOR   lv_color_u16      // แปลงจาก color_u16 --> lv_color_t
#endif

#ifndef COLOR16
#define COLOR16     lv_color_to_u16   // แปลงจาก lv_color_t --> color_u16
#endif

// inline lv_color16_t lv_color16_make(uint8_t r, uint8_t g, uint8_t b){
//   lv_color16_t color16;
//   color16.red   = (r >> 3); /*8 - 5  = 3*/
//   color16.green = (g >> 2); /*8 - 6  = 2*/
//   color16.blue  = (b >> 3); /*8 - 5  = 3*/
//   return color16;
// }

// inline uint16_t lv_color_to16(lv_color_t color) {
//   return (uint16_t) lv_color16_make(color.red, color.green, color.blue);
// }


inline lv_color_t lv_color16_to_color(lv_color16_t color16)
{
  lv_color_t color32;

#if LV_COLOR_DEPTH == 16
    /**
     * The floating point math for conversion is:
     *  valueto = valuefrom * ( (2^bitsto - 1) / (float)(2^bitsfrom - 1) )
     * The faster integer math for conversion is:
     *  valueto = ( valuefrom * multiplier + adder ) >> divisor
     *   multiplier = FLOOR( ( (2^bitsto - 1) << divisor ) / (float)(2^bitsfrom - 1) )
     *
     * Find the first divisor where ( adder >> divisor ) <= 0
     *
     * 5-bit to 8-bit: ( 31 * multiplier + adder ) >> divisor = 255
     * divisor  multiplier  adder  min (0)  max (31)
     *       0           8      7        7       255
     *       1          16     14        7       255
     *       2          32     28        7       255
     *       3          65     25        3       255
     *       4         131     19        1       255
     *       5         263      7        0       255
     *
     * 6-bit to 8-bit: 255 = ( 63 * multiplier + adder ) >> divisor
     * divisor  multiplier  adder  min (0)  max (63)
     *       0           4      3        3       255
     *       1           8      6        3       255
     *       2          16     12        3       255
     *       3          32     24        3       255
     *       4          64     48        3       255
     *       5         129     33        1       255
     *       6         259      3        0       255
     */

    color32.red   = (((color16.red  ) * 263 + 7) >> 5);
    color32.green = (((color16.green) * 259 + 3) >> 6);
    color32.blue  = (((color16.blue ) * 263 + 7) >> 5);
#endif //LV_COLOR_DEPTH == 16
  return  color32;
}

inline lv_color_t lv_color_u16_to_color(uint16_t color_u16){
  return lv_color16_to_color(*(lv_color16_t*)&color_u16);
}

inline lv_color_t lv_color_u16(uint16_t color_u16){
  return lv_color_u16_to_color(color_u16);
}

inline uint16_t TFT_COLOR_RGB(uint8_t r, uint8_t g, uint8_t b) {
  return (uint16_t) lv_color_to_u16(lv_color_make(r,g,b)); 
}

inline uint16_t TFT_COLOR_HEX(uint32_t c){
  return (uint16_t) lv_color_to_u16(lv_color_hex(c));
}

inline uint8_t TFT_COLOR_BRIGHTNESS(uint16_t color) {
  return lv_color_brightness(lv_color16_to_color(*(lv_color16_t*)&color));
}


inline uint16_t TFT_COLOR_MIX(uint16_t color1, uint16_t color2, uint8_t  id255) {// id255 : 0..255
  return lv_color_to_u16(lv_color_mix(lv_color_u16_to_color(color1), lv_color_u16_to_color(color2), id255));
}

/**
 * Convert a HSV color to color_t (16bit color)
 * @param h hue [0..359]
 * @param s saturation [0..100]
 * @param v value [0..100]
 * @return the given RGB color in RGB (with LV_COLOR_DEPTH depth)
 */
inline uint16_t TFT_COLOR_HSV(uint16_t h, uint8_t s, uint8_t v) {
  return  lv_color_to_u16(lv_color_hsv_to_rgb(h,s,v));
}

inline color_hsv_t TFT_COLOR_TO_HSV(uint16_t color) {
  return lv_color_to_hsv(lv_color16_to_color(*(lv_color16_t*)&color));
}

inline uint16_t TFT_COLOR_HSV_MIX( color_t color1, color_t color2, uint8_t id255 )  {  // id255 : 0..255
  color_hsv_t hsv[2] = {  TFT_COLOR_TO_HSV( color1 ),  TFT_COLOR_TO_HSV( color2 ) };
  id255 = constrain(id255, 0, 255);
  return TFT_COLOR_HSV( map( id255, 0, 255, hsv[0].h, hsv[1].h), 
                        map( id255, 0, 255, hsv[0].s, hsv[1].s),
                        map( id255, 0, 255, hsv[0].v, hsv[1].v) );
}

//https://vuetifyjs.com/en/styles/colors/#material-colors
inline uint16_t TFT_PALETTE(palette_t palette_color) {
  return lv_color_to_u16( lv_palette_main((lv_palette_t) palette_color) );
}

inline uint16_t TFT_PALETTE_DARKEN(palette_t palette_color,uint8_t level) {
  return lv_color_to_u16( lv_palette_darken((lv_palette_t) palette_color, level)) ;
}

inline uint16_t TFT_PALETTE_LIGHTEN(palette_t palette_color,uint8_t level) {
  return lv_color_to_u16( lv_palette_lighten((lv_palette_t) palette_color, level) );
}

inline area_t * area_set( area_t * area,  int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
  lv_area_set( area, x1, y1, x2, y2 );
  return area;
}

inline area_t * area_set( area_t & area,  int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
  lv_area_set( &area, x1, y1, x2, y2 );
  return &area;
}

inline area_t * area_move( area_t * area, int32_t ofs_x, int32_t ofs_y ){
  lv_area_move( area, ofs_x, ofs_y);
  return area;
}

inline area_t * area_align(const area_t * base, area_t * to_align, align_t Align, int32_t ofs_x=0, int32_t ofs_y=0) {
  lv_align_t _align_type = (lv_align_t) Align;
  switch(Align){
    case ALIGN_TOP_LEFT:    _align_type =LV_ALIGN_TOP_LEFT;      break;
    case ALIGN_TOP_MID:     _align_type =LV_ALIGN_TOP_MID;       break;
    case ALIGN_TOP_RIGHT:   _align_type =LV_ALIGN_TOP_RIGHT;     break;
    case ALIGN_BOTTOM_LEFT: _align_type =LV_ALIGN_BOTTOM_LEFT;   break;
    case ALIGN_BOTTOM_MID:  _align_type =LV_ALIGN_BOTTOM_MID;    break;
    case ALIGN_BOTTOM_RIGHT:_align_type =LV_ALIGN_BOTTOM_RIGHT;  break;
    case ALIGN_LEFT_TOP:    _align_type =LV_ALIGN_TOP_LEFT;      break;
    case ALIGN_LEFT_MID:    _align_type =LV_ALIGN_LEFT_MID;      break;
    case ALIGN_LEFT_BOTTOM: _align_type =LV_ALIGN_BOTTOM_LEFT;   break;
    case ALIGN_RIGHT_TOP:   _align_type =LV_ALIGN_TOP_RIGHT;     break;
    case ALIGN_RIGHT_MID:   _align_type =LV_ALIGN_RIGHT_MID;     break;
    case ALIGN_RIGHT_BOTTOM:_align_type =LV_ALIGN_BOTTOM_RIGHT;  break;

    case ALIGN_TOP:         _align_type =LV_ALIGN_TOP_MID;       break;
    case ALIGN_BOTTOM:      _align_type =LV_ALIGN_BOTTOM_MID;    break;
    case ALIGN_LEFT:        _align_type =LV_ALIGN_LEFT_MID;      break;
    case ALIGN_RIGHT:       _align_type =LV_ALIGN_RIGHT_MID;     break;

    case ALIGN_IN_TOP:      _align_type =LV_ALIGN_RIGHT_MID;     break;
    case ALIGN_OUT_TOP:     _align_type =LV_ALIGN_OUT_TOP_MID;   break;
    case ALIGN_IN_BOTTOM:   _align_type =LV_ALIGN_BOTTOM_MID;    break;
    case ALIGN_OUT_BOTTOM:  _align_type =LV_ALIGN_OUT_BOTTOM_MID;break;
    case ALIGN_IN_LEFT:     _align_type =LV_ALIGN_LEFT_MID;      break;
    case ALIGN_OUT_LEFT:    _align_type =LV_ALIGN_OUT_LEFT_MID;  break;
    case ALIGN_IN_RIGHT:    _align_type =LV_ALIGN_RIGHT_MID;     break;
    case ALIGN_OUT_RIGHT:   _align_type =LV_ALIGN_OUT_RIGHT_MID; break;

    case ALIGN_IN_TOP_LEFT:     _align_type = LV_ALIGN_TOP_LEFT;     break;
    case ALIGN_IN_TOP_MID:      _align_type = LV_ALIGN_TOP_MID;      break;
    case ALIGN_IN_TOP_RIGHT:    _align_type = LV_ALIGN_TOP_RIGHT;    break;
    case ALIGN_IN_BOTTOM_LEFT:  _align_type = LV_ALIGN_BOTTOM_LEFT;  break;
    case ALIGN_IN_BOTTOM_MID:   _align_type = LV_ALIGN_BOTTOM_MID;   break;
    case ALIGN_IN_BOTTOM_RIGHT: _align_type = LV_ALIGN_BOTTOM_RIGHT; break;
    case ALIGN_IN_LEFT_TOP:     _align_type = LV_ALIGN_TOP_LEFT;     break;
    case ALIGN_IN_LEFT_MID:     _align_type = LV_ALIGN_LEFT_MID;     break;
    case ALIGN_IN_LEFT_BOTTOM:  _align_type = LV_ALIGN_BOTTOM_LEFT;  break;
    case ALIGN_IN_RIGHT_TOP:    _align_type = LV_ALIGN_TOP_RIGHT;    break;
    case ALIGN_IN_RIGHT_MID:    _align_type = LV_ALIGN_RIGHT_MID;    break;
    case ALIGN_IN_RIGHT_BOTTOM: _align_type = LV_ALIGN_BOTTOM_RIGHT; break;
  }
  
  lv_area_align( base, to_align, _align_type, ofs_x, ofs_y);

  return to_align;
}

inline area_t * area_align(const area_t & base, area_t & to_align, align_t Align, int32_t ofs_x=0, int32_t ofs_y=0) {
  return area_align( &base, &to_align, Align, ofs_x, ofs_y);
}

inline bool area_is_point_on(const area_t *a_p, const point_t *p_p, int32_t radius=0){
  return lv_area_is_point_on(a_p, p_p, radius);
}

inline bool area_is_point_on(const area_t &a, const point_t &p, int32_t radius=0){
  return area_is_point_on(&a, &p, radius);
}

inline bool area_is_point_on(const area_t *a_p, const Point *p_p, int32_t radius=0){
  point_t p = {p_p->x, p_p->y };
  return area_is_point_on(a_p, &p, radius);
}

inline bool area_is_point_on(const area_t &a, const Point &p, int32_t radius=0){
  return area_is_point_on(&a, &p, radius);
}

inline void text_get_area(area_t * text_area, const char * text, const font_t * font, int32_t letter_space=0,
                      int32_t line_space=0, int32_t max_width=COORD_MAX)
{
  lv_point_t text_sz;
  lv_text_get_size(&text_sz, text, font, letter_space, line_space, max_width, LV_TEXT_FLAG_NONE);
  if(text_area!=NULL) {
    text_area->x1 = 0;
    text_area->y1 = 0;
    text_area->x2 = text_sz.x;
    text_area->y2 = text_sz.y;
  }
}

inline void text_get_area(area_t * text_area, const draw_label_dsc_t * label_dsc)
{
  lv_point_t text_sz;
  lv_text_get_size(&text_sz, label_dsc->text, label_dsc->font, label_dsc->letter_space, label_dsc->line_space, LV_COORD_MAX, label_dsc->flag);
  if(text_area!=NULL) {
    text_area->x1 = 0;
    text_area->y1 = 0;
    text_area->x2 = text_sz.x;
    text_area->y2 = text_sz.y;
  }
}

inline point_t text_get_size(const char* text, const font_t* font, int32_t letter_space=0, int32_t line_space=0, text_flag_t text_flag=0){
  lv_point_t text_sz;
  lv_text_get_size( &text_sz, text, font, letter_space, line_space, LV_COORD_MAX, (lv_text_flag_t) text_flag);
  return text_sz;
}

inline void image_get_area(area_t * image_area, const void * src){
  lv_image_header_t image_header;
  lv_image_decoder_get_info(src, &image_header);
  if( image_area != NULL){
    image_area->x1 = 0;
    image_area->y1 = 0;
    image_area->x2 = image_header.w - 1;
    image_area->y2 = image_header.h - 1;
  }
}

#define PCT(x)      lv_pct(x)
#define PCT2PX(x,b) lv_pct_to_px(x,b)
#define PCT_W(x)    PCT2PX(PCT(x),HOR_RES)
#define PCT_H(x)    PCT2PX(PCT(x),VER_RES)


#ifndef GLYPH_THRESHOLD
#define GLYPH_THRESHOLD    128
#endif 

inline String font_get_glyph(const font_t& font, uint32_t unicode_letter, uint32_t *box_w=NULL, uint32_t *box_h = NULL) {
  lv_font_glyph_dsc_t g_dsc;
  if (!lv_font_get_glyph_dsc(&font, &g_dsc, unicode_letter, 0)) {
    Serial.println("[Glyph] not found.");
    return "";
  }

  uint32_t _box_w = g_dsc.box_w;
  uint32_t _box_h = g_dsc.box_h;

  if(box_w !=NULL) *box_w = _box_w;
  if(box_h !=NULL) *box_h = _box_h;

  uint8_t glyph_bitmap[_box_w * _box_w]; // Temporary buffer for glyph bitmap

  lv_draw_buf_t draw_buf;
  draw_buf.data = glyph_bitmap;
  const void* ret = lv_font_get_glyph_bitmap(&g_dsc, &draw_buf);
  if (!ret) {
    Serial.println("[Glyph] Failed to retrieve glyph bitmap.");
    return "";
  }

  // Process each row of the bitmap
  String glyph_representation = "";
  for (uint32_t y = 0; y < _box_h; y++) {
    for (uint32_t x = 0; x < _box_w; x++) {
      uint32_t pixel_id      = (y * _box_w + x);
      uint8_t  pixel_opacity = glyph_bitmap[pixel_id];
      glyph_representation += (pixel_opacity >= GLYPH_THRESHOLD ? "." : " ");
    }
    glyph_representation += "\n"; // Newline after each row
  }
  return glyph_representation;
}

inline String font_get_glyph(const font_t& font, const char* utf8_char, uint32_t *box_w=NULL, uint32_t *box_h = NULL)
{
  return font_get_glyph(font, UNICODE(utf8_char), box_w, box_h);
}

#define COLOR_FORMAT_BPP(cf) (       \
  (cf) == COLOR_FORMAT_I1 ? 1 :        \
  (cf) == COLOR_FORMAT_A1 ? 1 :        \
  (cf) == COLOR_FORMAT_I2 ? 2 :        \
  (cf) == COLOR_FORMAT_A2 ? 2 :        \
  (cf) == COLOR_FORMAT_I4 ? 4 :        \
  (cf) == COLOR_FORMAT_A4 ? 4 :        \
  (cf) == COLOR_FORMAT_L8 ? 8 :        \
  (cf) == COLOR_FORMAT_A8 ? 8 :        \
  (cf) == COLOR_FORMAT_I8 ? 8 :        \
  (cf) == COLOR_FORMAT_AL88 ? 16 :     \
  (cf) == COLOR_FORMAT_RGB565 ? 16 :   \
  (cf) == COLOR_FORMAT_RGB565A8 ? 16 : \
  (cf) == COLOR_FORMAT_ARGB8565 ? 24 : \
  (cf) == COLOR_FORMAT_RGB888 ? 24 :   \
  (cf) == COLOR_FORMAT_ARGB8888 ? 32 : \
  (cf) == COLOR_FORMAT_XRGB8888 ? 32 : \
  0                                    \
)

namespace GUTIL {
  void draw_rect(layer_t * layer, const draw_rect_dsc_t * rect_dsc, const area_t * coords);
  void draw_rect(layer_t * layer, const draw_rect_dsc_t * rect_dsc, int32_t w, int32_t h, align_t Align, int32_t ofs_x=0, int32_t ofs_y=0);

  void draw_label(layer_t * layer, const draw_label_dsc_t * label_dsc, const area_t * coords);
  void draw_label(layer_t * layer, const draw_label_dsc_t * label_dsc, align_t Align, int32_t ofs_x=0, int32_t ofs_y=0);
  void draw_label(layer_t * layer, const char * label_text, const font_t* font, color_t label_color,  align_t Align, int32_t ofs_x=0, int32_t ofs_y=0);

  void draw_image(layer_t * layer, const draw_image_dsc_t * image_dsc, const area_t * coords);
  void draw_image(layer_t * layer, const draw_image_dsc_t * image_dsc, align_t Align, int32_t ofs_x=0, int32_t ofs_y=0);
  void draw_image(layer_t * layer, const img_t * image_src, align_t Align, int32_t ofs_x=0, int32_t ofs_y=0);
  void draw_image(layer_t * layer, const img_t * image_src, float angle, align_t Align, int32_t ofs_x=0, int32_t ofs_y=0);
  void draw_image(layer_t * layer, const img_t * image_src, point_t pivot, float angle, align_t Align, int32_t ofs_x=0, int32_t ofs_y=0);

  void draw_line(layer_t * layer, const draw_line_dsc_t * line_dsc);
  void draw_triangle(layer_t * layer, const draw_triangle_dsc_t * triangle_dsc);
  void draw_arc(layer_t * layer, const draw_arc_dsc_t * arc_dsc);
  void draw_mask_rect(layer_t * layer, const draw_mask_rect_dsc_t * mask_rect_dsc);
}

using namespace GUTIL;



#endif //__GUTIL_H___