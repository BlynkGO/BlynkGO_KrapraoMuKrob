/********************************************
 *
 * include พื้นฐานให้ใช้กับ .c และ .cpp ได้ได้วย
 *
 ********************************************/

#ifndef _GVLGL_H__
#define _GVLGL_H__


#ifdef __cplusplus
extern "C" {
#endif

#if !defined LV_USE_SDL
  #include "../config/blynkgo_config.h"
#endif

#include "../utils/esp32_utils.h"
#include "../utils/esp32_memory.h"
#include "../utils/BlynkGO_Type.h"

#include "../utils/lv_conf.h"
#include "../utils/lvgl/lvgl.h"

#include "../utils/lvgl/src/font/lv_font.h"
#include "../utils/lvgl/src/misc/lv_text.h"
#include "../utils/lvgl/src/draw/lv_draw.h"
#include "../utils/lvgl/src/misc/lv_ll.h"
#include "../utils/lvgl/src/misc/lv_area.h"  // point_t;
#include "../utils/lvgl/src/font/lv_symbol_def.h"
#include "../utils/lvgl/src/draw/lv_draw_mask.h"
#include "../utils/lvgl/src/draw/lv_draw_buf.h"
#include "../utils/lvgl/src/misc/lv_timer.h"
#include "../utils/lvgl/src/misc/lv_color.h"

#include "../utils/lvgl/src/core/lv_obj.h"

#include "../utils/lvgl/src/core/lv_obj_private.h"
#include "../utils/lvgl/src/core/lv_obj_class_private.h"
#include "../utils/lvgl/src/misc/lv_anim_private.h"
#include "../utils/lvgl/src/misc/lv_area_private.h"
#include "../utils/lvgl/src/misc/lv_bidi_private.h"
#include "../utils/lvgl/src/misc/lv_color_op_private.h"
#include "../utils/lvgl/src/misc/lv_event_private.h"
#include "../utils/lvgl/src/misc/lv_fs_private.h"
#include "../utils/lvgl/src/misc/lv_profiler_builtin_private.h"
#include "../utils/lvgl/src/misc/lv_rb_private.h"
#include "../utils/lvgl/src/misc/lv_style_private.h"
#include "../utils/lvgl/src/misc/lv_text_private.h"
#include "../utils/lvgl/src/misc/lv_timer_private.h"

#include "../utils/lvgl/src/draw/lv_draw_buf_private.h"
#include "../utils/lvgl/src/draw/lv_draw_image_private.h"
#include "../utils/lvgl/src/draw/lv_draw_label_private.h"
#include "../utils/lvgl/src/draw/lv_draw_mask_private.h"
#include "../utils/lvgl/src/draw/lv_draw_private.h"
#include "../utils/lvgl/src/draw/lv_draw_rect_private.h"
#include "../utils/lvgl/src/draw/lv_draw_triangle_private.h"
#include "../utils/lvgl/src/draw/lv_draw_vector_private.h"
#include "../utils/lvgl/src/draw/lv_image_decoder_private.h"

#include "../utils/lvgl/src/indev/lv_indev_private.h"

#include "../utils/lvgl/src/widgets/animimage/lv_animimage_private.h"
#include "../utils/lvgl/src/widgets/arc/lv_arc_private.h"
#include "../utils/lvgl/src/widgets/button/lv_button_private.h"
#include "../utils/lvgl/src/widgets/buttonmatrix/lv_buttonmatrix_private.h"
// #include "../utils/lvgl/src/widgets/calendar/lv_calendar_chinese_private.h"
#include "../utils/lvgl/src/widgets/calendar/lv_calendar_private.h"
#include "../utils/lvgl/src/widgets/canvas/lv_canvas_private.h"
#include "../utils/lvgl/src/widgets/chart/lv_chart_private.h"
#include "../utils/lvgl/src/widgets/checkbox/lv_checkbox_private.h"
#include "../utils/lvgl/src/widgets/dropdown/lv_dropdown_private.h"
#include "../utils/lvgl/src/widgets/image/lv_image_private.h"
#include "../utils/lvgl/src/widgets/imagebutton/lv_imagebutton_private.h"
#include "../utils/lvgl/src/widgets/keyboard/lv_keyboard_private.h"
#include "../utils/lvgl/src/widgets/label/lv_label_private.h"
#include "../utils/lvgl/src/widgets/led/lv_led_private.h"
#include "../utils/lvgl/src/widgets/line/lv_line_private.h"
// #include "../utils/lvgl/src/widgets/lottie/lv_lottie_private.h"
#include "../utils/lvgl/src/widgets/menu/lv_menu_private.h"
#include "../utils/lvgl/src/widgets/msgbox/lv_msgbox_private.h"
#include "../utils/lvgl/src/widgets/roller/lv_roller_private.h"
#include "../utils/lvgl/src/widgets/scale/lv_scale_private.h"
#include "../utils/lvgl/src/widgets/slider/lv_slider_private.h"
#include "../utils/lvgl/src/widgets/roller/lv_roller_private.h"
#include "../utils/lvgl/src/widgets/span/lv_span_private.h"
#include "../utils/lvgl/src/widgets/spinbox/lv_spinbox_private.h"
#include "../utils/lvgl/src/widgets/switch/lv_switch_private.h"
#include "../utils/lvgl/src/widgets/table/lv_table_private.h"
#include "../utils/lvgl/src/widgets/tabview/lv_tabview_private.h"
#include "../utils/lvgl/src/widgets/textarea/lv_textarea_private.h"
#include "../utils/lvgl/src/widgets/tileview/lv_tileview_private.h"
#include "../utils/lvgl/src/widgets/win/lv_win_private.h"

#include "../utils/lvgl/src/widgets/buttonmatrix/lv_buttonmatrix.h"
#include "../utils/lvgl/src/widgets/keyboard/lv_keyboard.h"
#include "../utils/lvgl/src/widgets/textarea/lv_textarea.h"
#include "../utils/lvgl/src/widgets/label/lv_label.h"


// #include "../objx/widgets_trident.h"

// #if BLYNKGO_USE_KBD
// #include "../kbd/lv_keyboard.h"
// #endif //BLYNKGO_USE_KBD

// #if BLYNKGO_USE_FS
// #include "../fs/lv_fs_esp32.h"
// #endif //BLYNKGO_USE_FS

// #include "qrcode/qrcodegen.h"

#include <pgmspace.h>

// #define LV_ATTRIBUTE_MEM_ALIGN PROGMEM

#ifdef __cplusplus
}
#endif

#endif //_GVLGL_H__
