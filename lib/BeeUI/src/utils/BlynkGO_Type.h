/*
 *********************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ BlynkGO_Type.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
 *   สร้างโดย TridentTD
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
 *********************************************************************
 */

#ifndef __BLYNKGO_TYPE_H__
#define __BLYNKGO_TYPE_H__

#include "./lvgl/lvgl.h"

#if defined(PYCPARSER) || defined(__CC_ARM)
#define FORMAT_ATTRIBUTE(fmtstr, vararg)
#elif defined(__GNUC__) && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 4) || __GNUC__ > 4)
#define FORMAT_ATTRIBUTE(fmtstr, vararg) __attribute__((format(gnu_printf, fmtstr, vararg)))
#elif (defined(__clang__) || defined(__GNUC__) || defined(__GNUG__))
#define FORMAT_ATTRIBUTE(fmtstr, vararg) __attribute__((format(printf, fmtstr, vararg)))
#else
#define FORMAT_ATTRIBUTE(fmtstr, vararg)
#endif


// typedef lv_display_t    display_t;
// typedef lv_indev_t      indev_t;
#define indev_t             lv_indev_t

typedef lv_font_t           font_t;
typedef lv_image_dsc_t      img_t;
typedef lv_image_header_t   image_header_t;
typedef lv_style_t          style_t;
typedef lv_anim_t           anim_t;

typedef uint16_t        color_t;
// #define color_t         uint16_t
typedef lv_color_hsv_t  color_hsv_t;
// typedef lv_color_format_t color_format_t;
typedef lv_color32_t    color32_t;
typedef lv_draw_buf_t   draw_buf_t;
typedef lv_layer_t      layer_t;

#define draw_layer_create         lv_draw_layer_create
#define render_layer              lv_draw_layer    

typedef lv_draw_task_t            draw_task_t;

typedef lv_draw_dsc_base_t        draw_base_dsc_t;
typedef lv_draw_rect_dsc_t        draw_rect_dsc_t;
typedef lv_draw_fill_dsc_t        draw_fill_dsc_t;
typedef lv_draw_border_dsc_t      draw_border_dsc_t;
typedef lv_draw_box_shadow_dsc_t  draw_box_shadow_dsc_t;
typedef lv_draw_label_dsc_t       draw_label_dsc_t;
typedef lv_draw_image_dsc_t       draw_image_dsc_t;
typedef lv_draw_arc_dsc_t         draw_arc_dsc_t;
typedef lv_draw_triangle_dsc_t    draw_triangle_dsc_t;
typedef lv_draw_mask_rect_dsc_t   draw_mask_rect_dsc_t;
typedef lv_draw_line_dsc_t        draw_line_dsc_t;

#define image_decoder_get_info    lv_image_decoder_get_info

#define draw_rect_dsc_init        lv_draw_rect_dsc_init
#define draw_fill_dsc_init        lv_draw_fill_dsc_init
#define draw_border_dsc_init      lv_draw_border_dsc_init
#define draw_box_shadow_dsc_init  lv_draw_box_shadow_dsc_init
#define draw_label_dsc_init       lv_draw_label_dsc_init
#define draw_image_dsc_init       lv_draw_image_dsc_init
#define draw_arc_dsc_init         lv_draw_arc_dsc_init
#define draw_triangle_dsc_init    lv_draw_triangle_dsc_init
#define draw_mask_rect_dsc_init   lv_draw_mask_rect_dsc_init
#define draw_line_dsc_init        lv_draw_line_dsc_init

// #define area_align                lv_area_align
#define area_copy                 lv_area_copy
#define area_get_height           lv_area_get_height
#define area_get_width            lv_area_get_width
#define area_increase             lv_area_increase

// #define draw_rect                 lv_draw_rect
// #define draw_label                lv_draw_label
// #define draw_image                lv_draw_image
// #define draw_line                 lv_draw_line
// #define draw_mask_rect            lv_draw_mask_rect
// #define draw_triangle             lv_draw_triangle
// #define draw_layer                lv_draw_layer
// #define draw_arc                  lv_draw_arc

#define DRAW_PART                 widget->draw_part()
#define DRAW_LAYER                widget->draw_layer()
#define DRAW_AREA                 &widget->draw_area()
#define DRAW_TYPE                 widget->draw_type()

#define COORD_MAX                 LV_COORD_MAX
#define COORD_MIN                 LV_COORD_MIN

#define hit_test_info_t           lv_hit_test_info_t

typedef lv_point_t          point_t;
typedef lv_point_precise_t  point_precise_t;

#define mem_monitor_t             lv_mem_monitor_t
#define mem_monitor               lv_mem_monitor

enum {
  /** No flags */
  POINT_TRANSFORM_FLAG_NONE = 0x00,

  /** Consider the transformation properties of the parents too */
  POINT_TRANSFORM_FLAG_RECURSIVE = 0x01,

  /** Execute the inverse of the transformation (-angle and 1/zoom) */
  POINT_TRANSFORM_FLAG_INVERSE = 0x02,

  /** Both inverse and recursive*/
  POINT_TRANSFORM_FLAG_INVERSE_RECURSIVE = 0x03,
};
typedef uint8_t point_transform_flag_t;

#if LV_USE_VECTOR_GRAPHIC
typedef lv_fpoint_t         fpoint_t;
#endif


typedef lv_obj_t        obj_t;
typedef lv_disp_t       disp_t;

// typedef lv_grad_dir_t   grad_dir_t;
typedef lv_grad_dsc_t   grad_dsc_t;
// typedef lv_align_t      align_t;
// typedef uint8_t         text_align_t;
// typedef text_align_t    label_align_t;
// typedef uint8_t         text_decor_t;

#define span_t          lv_span_t

#define group_t         lv_group_t 
#define obj_class_t     lv_obj_class_t

#define display_t                 lv_display_t
#define color_filter_dsc_t        lv_color_filter_dsc_t
#define montserrat_14             lv_font_montserrat_14
#define HOR_RES                   LV_HOR_RES
#define VER_RES                   LV_VER_RES

#if LV_USE_FLOAT
typedef float value_precise_t;
#else
typedef int32_t value_precise_t;
#endif

#define _anim_path_cb_t             lv_anim_path_cb_t
#define anim_path_linear            lv_anim_path_linear 
#define anim_path_ease_in           lv_anim_path_ease_in
#define anim_path_ease_out          lv_anim_path_ease_out
#define anim_path_ease_in_out       lv_anim_path_ease_in_out
#define anim_path_overshoot         lv_anim_path_overshoot
#define anim_path_bounce            lv_anim_path_bounce
#define anim_path_step              lv_anim_path_step
#define anim_path_custom_bezier3    lv_anim_path_custom_bezier3

#define anim_timeline_t             lv_anim_timeline_t
#define anim_exec_xcb_t             lv_anim_exec_xcb_t
#define anim_custom_exec_cb_t       lv_anim_custom_exec_cb_t

#define ANIMIMG_CLASS                   (&lv_animimg_class)
#define ARC_CLASS                       (&lv_arc_class)
#define BAR_CLASS                       (&lv_bar_class)
#define BUTTON_CLASS                    (&lv_button_class)
#define BUTTONMATRIX_CLASS              (&lv_buttonmatrix_class)
#define CALENDAR_HEADER_ARROW_CLASS     (&lv_calendar_header_arrow_class)
#define CALENDAR_HEADER_DROPDOWN_CLASS  (&lv_calendar_header_dropdown_class)
#define CALENDAR_CLASS                  (&lv_calendar_class)
#define CANVAS_CLASS                    (&lv_canvas_class)
#define CHART_CLASS                     (&lv_chart_class)
#define CHECKBOX_CLASS                  (&lv_checkbox_class)
#define DROPDOWN_CLASS                  (&lv_dropdown_class)
#define DROPDOWNLIST_CLASS              (&lv_dropdownlist_class)
#define IMAGE_CLASS                     (&lv_image_class)
#define IMAGEBUTTON_CLASS               (&lv_imagebutton_class)
#define KEYBOARD_CLASS                  (&lv_keyboard_class)
#define KNOB_CLASS                      (&lv_knob_class)
#define LABEL_CLASS                     (&lv_label_class)
#define LED_CLASS                       (&lv_led_class)
#define LINE_CLASS                      (&lv_line_class)
#define LIST_CLASS                      (&lv_list_class)
#define LIST_BUTTON_CLASS               (&lv_list_button_class)
#define LIST_TEXT_CLASS                 (&lv_list_text_class)
#define LOTTIE_CLASS                    (&lv_lottie_class)
#define MENU_CLASS                      (&lv_menu_class)
#define MSGBOX_CLASS                    (&lv_msgbox_class)
#define MSGBOX_HEADER_CLASS             (&lv_msgbox_header_class)
#define MSGBOX_CONTENT_CLASS            (&lv_msgbox_content_class)
#define MSGBOX_FOOTER_CLASS             (&lv_msgbox_footer_class)
#define MSGBOX_FOOTER_BUTTON_CLASS      (&lv_msgbox_footer_button_class)
#define MSGBOX_HEADER_BUTTON_CLASS      (&lv_msgbox_header_button_class)
#define MSGBOX_BACKDROP_CLASS           (&lv_msgbox_backdrop_class)
#define OBJ_CLASS                       (&lv_obj_class)
#define RECT_CLASS                      (&lv_obj_class)
#define ROLLER_CLASS                    (&lv_roller_class)
#define ROLLER_LABEL_CLASS              (&lv_roller_label_class)
#define SCALE_CLASS                     (&lv_scale_class)
#define SLIDER_CLASS                    (&lv_slider_class)
#define SPANGROUP_CLASS                 (&lv_spangroup_class)
#define SPINBOX_CLASS                   (&lv_spinbox_class)
#define SPINNER_CLASS                   (&lv_spinner_class)
#define SWITCH_CLASS                    (&lv_switch_class)
#define TABLE_CLASS                     (&lv_table_class)
#define TABVIEW_CLASS                   (&lv_tabview_class)
#define TEMPL_CLASS                     (&lv_templ_class)
#define TEXTAREA_CLASS                  (&lv_textarea_class)
#define TILEVIEW_CLASS                  (&lv_tileview_class)
#define WIN_CLASS                       (&lv_win_class)


typedef enum {
  ANIM_PATH_LINEAR,         // ปกติ ค่าเพิ่มแบบ liner, 
  ANIM_PATH_EASE_IN,        // ค่า จากค่อยๆช้า->เร็ว,      เช่น ลูกบอล กลิ้งลงจากทางชัน, ลูกบอลกระเด้ง ที่สม่ำเสมอไปเรื่อยๆ
  ANIM_PATH_EASE_OUT,       // ค่า จากเร็ว->ช้าลง, 
  ANIM_PATH_EASE_IN_OUT,    // ค่า จากค่อยๆช้า->เร็ว->ช้า,  เช่น ลูกตุ้ม Pendulum
  ANIM_PATH_OVERSHOOT,      
  ANIM_PATH_BOUNCE,         // ค่าเพิ่มแบบเด้งสะท้อน คือ เด้งสะท้อนแรงจนสุดท้ายค่าเด้งสะท้อนค่อยๆลดลงๆจนถึงค่าเป้าหมาย, 
  ANIM_PATH_STEP,
  ANIM_PATH_CUSTOM_BEZIER3,
} anim_path_type_t;

#define RADIUS_CIRCLE       LV_RADIUS_CIRCLE
#define SIZE_CONTENT        LV_SIZE_CONTENT
#define CONTENT_SIZE        LV_SIZE_CONTENT
#define GRID_CONTENT        LV_GRID_CONTENT

typedef enum {
  SPAN_OVERFLOW_CLIP,
  SPAN_OVERFLOW_ELLIPSIS,
  SPAN_OVERFLOW_LAST,  /**< Fence member*/
} span_overflow_t;


typedef enum {
  SPAN_MODE_FIXED,     /**< fixed the obj size */
  SPAN_MODE_EXPAND,    /**< Expand the object size to the text size */
  SPAN_MODE_BREAK,     /**< Keep width, break the too long lines and expand height */
  SPAN_MODE_LAST       /**< Fence member */
} span_mode_t;


enum {
  DRAW_TASK_TYPE_NONE = 0,
  DRAW_TASK_TYPE_FILL,
  DRAW_TASK_TYPE_BORDER,
  DRAW_TASK_TYPE_BOX_SHADOW,
  DRAW_TASK_TYPE_LABEL,
  DRAW_TASK_TYPE_IMAGE,
  DRAW_TASK_TYPE_LAYER,
  DRAW_TASK_TYPE_LINE,
  DRAW_TASK_TYPE_ARC,
  DRAW_TASK_TYPE_TRIANGLE,
  DRAW_TASK_TYPE_MASK_RECTANGLE,
  DRAW_TASK_TYPE_MASK_BITMAP,
  DRAW_TASK_TYPE_VECTOR,

  DRAW_TYPE_FILL          = DRAW_TASK_TYPE_FILL,
  DRAW_TYPE_BORDER        = DRAW_TASK_TYPE_BORDER,
  DRAW_TYPE_BOX_SHADOW    = DRAW_TASK_TYPE_BOX_SHADOW,
  DRAW_TYPE_LABEL         = DRAW_TASK_TYPE_LABEL,
  DRAW_TYPE_IMAGE         = DRAW_TASK_TYPE_IMAGE,
  DRAW_TYPE_LAYER         = DRAW_TASK_TYPE_LAYER,
  DRAW_TYPE_LINE          = DRAW_TASK_TYPE_LINE,
  DRAW_TYPE_ARC           = DRAW_TASK_TYPE_ARC,
  DRAW_TYPE_TRIANGLE      = DRAW_TASK_TYPE_TRIANGLE,
  DRAW_TYPE_MASK_RECTANGLE= DRAW_TASK_TYPE_MASK_RECTANGLE,
  DRAW_TYPE_MASK_BITMAP   = DRAW_TASK_TYPE_MASK_BITMAP,
  DRAW_TYPE_VECTOR        = DRAW_TASK_TYPE_VECTOR,
  DRAW_TYPE_NONE          = DRAW_TASK_TYPE_NONE,
};
typedef uint8_t  draw_task_type_t;


enum {
  OBJ_TREE_WALK_NEXT,
  OBJ_TREE_WALK_SKIP_CHILDREN,
  OBJ_TREE_WALK_END,
};
typedef uint8_t obj_tree_walk_res_t;

typedef obj_tree_walk_res_t (*obj_tree_walk_cb_t)(obj_t *, void *);

/**
 * Possible states of a widget.
 * OR-ed values are possible
 */
enum gstate_t{
    GSTATE_DEFAULT     =  0x0000,
    GSTATE_OFF         =  GSTATE_DEFAULT,  // BlynkGO
    GSTATE_CHECKED     =  0x0001,
    GSTATE_ON          =  GSTATE_CHECKED,  // BlynkGO
    GSTATE_FOCUSED     =  0x0002,
    GSTATE_FOCUS_KEY   =  0x0004,
    GSTATE_EDITED      =  0x0008,
    GSTATE_HOVERED     =  0x0010,
    GSTATE_PRESSED     =  0x0020,
    GSTATE_SCROLLED    =  0x0040,
    GSTATE_DISABLED    =  0x0080,
    GSTATE_USER_1      =  0x1000,
    GSTATE_USER_2      =  0x2000,
    GSTATE_USER_3      =  0x4000,
    GSTATE_USER_4      =  0x8000,
    GSTATE_CTRL        =  GSTATE_USER_1,
    GSTATE_CTRL_PRESSED=  GSTATE_USER_2,    

    GSTATE_ANY = 0xFFFF,    /**< Special value can be used in some functions to target all states*/

    G_DEFAULT          =  GSTATE_DEFAULT, 
    G_OFF              =  GSTATE_OFF,  // BlynkGO
    G_CHECKED          =  GSTATE_CHECKED,
    G_ON               =  GSTATE_ON,  // BlynkGO
    G_FOCUSED          =  GSTATE_FOCUSED,
    G_FOCUS_KEY        =  GSTATE_FOCUS_KEY,
    G_EDITED           =  GSTATE_EDITED,
    G_HOVERED          =  GSTATE_HOVERED,
    G_PRESSED          =  GSTATE_PRESSED,
    G_SCROLLED         =  GSTATE_SCROLLED,
    G_DISABLED         =  GSTATE_DISABLED,
    G_USER_1           =  GSTATE_USER_1,
    G_USER_2           =  GSTATE_USER_2,
    G_USER_3           =  GSTATE_USER_3,
    G_USER_4           =  GSTATE_USER_4,
    G_ANY              =  GSTATE_ANY,

    //------------------------
    GPART_MAIN         = 0x000000,   /**< A background like rectangle*/
    GPART_SCROLLBAR    = 0x010000,   /**< The scrollbar(s)*/
    GPART_INDICATOR    = 0x020000,   /**< Indicator, e.g. for slider, bar, switch, or the tick box of the checkbox*/
    GPART_KNOB         = 0x030000,   /**< Like handle to grab to adjust the value*/
    GPART_SELECTED     = 0x040000,   /**< Indicate the currently selected option or section*/
    GPART_ITEMS        = 0x050000,   /**< Used if the widget has multiple similar elements (e.g. table cells)*/
    GPART_CURSOR       = 0x060000,   /**< Mark a specific place e.g. for text area's cursor or on a chart*/
    GPART_CUSTOM_FIRST = 0x080000,    /**< Extension point for custom widgets*/
    GPART_TEXTAREA_PLACEHOLDER = GPART_CUSTOM_FIRST,

    GPART_ANY          = 0x0F0000,    /**< Special value can be used in some functions to target all parts*/

    GPART_CELL         =  GPART_ITEMS,

    DRAW_PART_MAIN             =  GPART_MAIN,
    DRAW_PART_SCROLLBAR        =  GPART_SCROLLBAR,
    DRAW_PART_INDICATOR        =  GPART_INDICATOR,
    DRAW_PART_KNOB             =  GPART_KNOB,
    DRAW_PART_SELECTED         =  GPART_SELECTED,
    DRAW_PART_ITEMS            =  GPART_ITEMS,
    DRAW_PART_CELL             =  GPART_CELL,
    DRAW_PART_CURSOR           =  GPART_CURSOR,
    DRAW_PART_CURSOR_FIRST     =  GPART_CUSTOM_FIRST,
};
#define gpart_t               gstate_t
#define style_selector_t      gstate_t



/**
 * On/Off features controlling the object's behavior.
 * OR-ed values are possible
 *
 * Note: update obj flags corresponding properties below
 * whenever add/remove flags or change bit definition of flags.
 */
typedef enum {
    FLAG_HIDDEN          = (1L << 0),  /**< Make the object hidden. (Like it wasn't there at all)*/
    FLAG_CLICKABLE       = (1L << 1),  /**< Make the object clickable by the input devices*/
    FLAG_CLICK_FOCUSABLE = (1L << 2),  /**< Add focused state to the object when clicked*/
    FLAG_CHECKABLE       = (1L << 3),  /**< Toggle checked state when the object is clicked*/
    FLAG_SCROLLABLE      = (1L << 4),  /**< Make the object scrollable*/
    FLAG_SCROLL_ELASTIC  = (1L << 5),  /**< Allow scrolling inside but with slower speed*/
    FLAG_SCROLL_MOMENTUM = (1L << 6),  /**< Make the object scroll further when "thrown"*/
    FLAG_SCROLL_ONE      = (1L << 7),  /**< Allow scrolling only one snappable children*/
    FLAG_SCROLL_CHAIN_HOR = (1L << 8), /**< Allow propagating the horizontal scroll to a parent*/
    FLAG_SCROLL_CHAIN_VER = (1L << 9), /**< Allow propagating the vertical scroll to a parent*/
    FLAG_SCROLL_CHAIN     = (FLAG_SCROLL_CHAIN_HOR | FLAG_SCROLL_CHAIN_VER),
    FLAG_SCROLL_ON_FOCUS = (1L << 10),  /**< Automatically scroll object to make it visible when focused*/
    FLAG_SCROLL_WITH_ARROW  = (1L << 11), /**< Allow scrolling the focused object with arrow keys*/
    FLAG_SNAPPABLE       = (1L << 12), /**< If scroll snap is enabled on the parent it can snap to this object*/
    FLAG_PRESS_LOCK      = (1L << 13), /**< Keep the object pressed even if the press slid from the object*/
    FLAG_EVENT_BUBBLE    = (1L << 14), /**< Propagate the events to the parent too*/
    FLAG_GESTURE_BUBBLE  = (1L << 15), /**< Propagate the gestures to the parent*/
    FLAG_ADV_HITTEST     = (1L << 16), /**< Allow performing more accurate hit (click) test. E.g. consider rounded corners.*/
    FLAG_IGNORE_LAYOUT   = (1L << 17), /**< Make the object not positioned by the layouts*/
    FLAG_FLOATING        = (1L << 18), /**< Do not scroll the object when the parent scrolls and ignore layout*/
    FLAG_SEND_DRAW_TASK_EVENTS = (1L << 19), /**< Send `LV_EVENT_DRAW_TASK_ADDED` events*/
    FLAG_OVERFLOW_VISIBLE = (1L << 20),/**< Do not clip the children to the parent's ext draw size*/
#if LV_USE_FLEX
    FLAG_FLEX_IN_NEW_TRACK = (1L << 21),     /**< Start a new flex track on this item*/
#endif

    FLAG_LAYOUT_1        = (1L << 23), /**< Custom flag, free to use by layouts*/
    FLAG_LAYOUT_2        = (1L << 24), /**< Custom flag, free to use by layouts*/

    FLAG_WIDGET_1        = (1L << 25), /**< Custom flag, free to use by widget*/
    FLAG_WIDGET_2        = (1L << 26), /**< Custom flag, free to use by widget*/
    FLAG_USER_1          = (1L << 27), /**< Custom flag, free to use by user*/
    FLAG_USER_2          = (1L << 28), /**< Custom flag, free to use by user*/
    FLAG_USER_3          = (1L << 29), /**< Custom flag, free to use by user*/
    FLAG_USER_4          = (1L << 30), /**< Custom flag, free to use by user*/
} flag_t;

typedef enum {
  GRID_ALIGN_START,
  GRID_ALIGN_CENTER,
  GRID_ALIGN_END,
  GRID_ALIGN_STRETCH,
  GRID_ALIGN_SPACE_EVENLY,
  GRID_ALIGN_SPACE_AROUND,
  GRID_ALIGN_SPACE_BETWEEN,
} grid_align_t;

typedef struct {
  int32_t col;
  int32_t row;
} grid_pos_t;

/**
 * The direction of the gradient.
 */
typedef enum {
  GRAD_DIR_NONE,       /**< No gradient (the `grad_color` property is ignored)*/
  GRAD_DIR_VER,        /**< Simple vertical (top to bottom) gradient*/
  GRAD_DIR_HOR,        /**< Simple horizontal (left to right) gradient*/
  GRAD_DIR_LINEAR,     /**< Linear gradient defined by start and end points. Can be at any angle.*/
  GRAD_DIR_RADIAL,     /**< Radial gradient defined by start and end circles*/
  GRAD_DIR_CONICAL,    /**< Conical gradient defined by center point, start and end angles*/
} grad_dir_t;


/** Alignments*/
typedef enum  {
  ALIGN_DEFAULT = 0,
  ALIGN_TOP_LEFT,
  ALIGN_TOP_MID,
  ALIGN_TOP_RIGHT,
  ALIGN_BOTTOM_LEFT,
  ALIGN_BOTTOM_MID,
  ALIGN_BOTTOM_RIGHT,
  ALIGN_LEFT_MID,
  ALIGN_RIGHT_MID,
  ALIGN_CENTER,

  ALIGN_OUT_TOP_LEFT,
  ALIGN_OUT_TOP_MID,
  ALIGN_OUT_TOP_RIGHT,
  ALIGN_OUT_BOTTOM_LEFT,
  ALIGN_OUT_BOTTOM_MID,
  ALIGN_OUT_BOTTOM_RIGHT,
  ALIGN_OUT_LEFT_TOP,
  ALIGN_OUT_LEFT_MID,
  ALIGN_OUT_LEFT_BOTTOM,
  ALIGN_OUT_RIGHT_TOP,
  ALIGN_OUT_RIGHT_MID,
  ALIGN_OUT_RIGHT_BOTTOM,
  //-----------------------------------
  ALIGN_IN_TOP,       // = ALIGN_TOP_MID,
  ALIGN_OUT_TOP,      // = ALIGN_OUT_TOP_MID,
  ALIGN_IN_BOTTOM,    // = ALIGN_BOTTOM_MID,
  ALIGN_OUT_BOTTOM,   // = ALIGN_OUT_BOTTOM_MID,
  ALIGN_LEFT_TOP,     // = ALIGN_OUT_LEFT_TOP,
  ALIGN_LEFT_BOTTOM,  // = ALIGN_OUT_LEFT_BOTTOM,
  ALIGN_IN_LEFT,      // = ALIGN_LEFT_MID,
  ALIGN_OUT_LEFT,     // = ALIGN_OUT_LEFT_MID,
  ALIGN_RIGHT_TOP,    // = ALIGN_OUT_RIGHT_TOP,
  ALIGN_RIGHT_BOTTOM, // = ALIGN_OUT_RIGHT_BOTTOM,
  ALIGN_IN_RIGHT,     // = ALIGN_RIGHT_MID,
  ALIGN_OUT_RIGHT,    // = ALIGN_OUT_RIGHT_MID,
  ALIGN_TOP,          // = ALIGN_TOP_MID   /ALIGN_OUT_TOP_MID
  ALIGN_BOTTOM,       // = ALIGN_BOTTOM_MID/ALIGN_OUT_BOTTOM_MID,
  ALIGN_LEFT,         // = ALIGN_LEFT_MID  /ALIGN_OUT_LEFT_MID,
  ALIGN_RIGHT,        // = ALIGN_RIGHT_MID /ALIGN_OUT_RIGHT_MID,
  //-----------------------------------
  ALIGN_IN_TOP_LEFT,
  ALIGN_IN_TOP_MID,
  ALIGN_IN_TOP_RIGHT,
  ALIGN_IN_BOTTOM_LEFT,
  ALIGN_IN_BOTTOM_MID,
  ALIGN_IN_BOTTOM_RIGHT,
  ALIGN_IN_LEFT_TOP,
  ALIGN_IN_LEFT_MID,
  ALIGN_IN_LEFT_BOTTOM,
  ALIGN_IN_RIGHT_TOP,
  ALIGN_IN_RIGHT_MID,
  ALIGN_IN_RIGHT_BOTTOM,
} align_t;

/** Label align policy*/
typedef enum {
  TEXT_ALIGN_AUTO, /**< Align text auto*/
  TEXT_ALIGN_LEFT, /**< Align text to left*/
  TEXT_ALIGN_CENTER, /**< Align text to center*/
  TEXT_ALIGN_RIGHT, /**< Align text to right*/

  LABEL_ALIGN_AUTO   = TEXT_ALIGN_AUTO, /**< Align text auto*/
  LABEL_ALIGN_LEFT   = TEXT_ALIGN_LEFT, /**< Align text to left*/
  LABEL_ALIGN_CENTER = TEXT_ALIGN_CENTER, /**< Align text to center*/
  LABEL_ALIGN_RIGHT  = TEXT_ALIGN_RIGHT, /**< Align text to right*/
} text_align_t;

#define label_align_t     lv_text_align_t

/**
 * Some options to apply decorations on texts.
 * 'OR'ed values can be used.
 */
typedef enum {
  TEXT_DECOR_NONE          = 0x00,
  TEXT_DECOR_UNDERLINE     = 0x01,
  TEXT_DECOR_STRIKETHROUGH = 0x02,
} text_decor_t;



enum {
  TEXT_FLAG_NONE    = 0x00,
  TEXT_FLAG_EXPAND  = 0x01, /**< Ignore max-width to avoid automatic word wrapping*/
  TEXT_FLAG_FIT     = 0x02, /**< Max-width is already equal to the longest line. (Used to skip some calculation)*/
  TEXT_FLAG_BREAK_ALL = 0x04, /**< To prevent overflow, insert breaks between any two characters.
                                      Otherwise breaks are inserted at word boundaries, as configured via LV_TXT_BREAK_CHARS
                                      or according to LV_TXT_LINE_BREAK_LONG_LEN, LV_TXT_LINE_BREAK_LONG_PRE_MIN_LEN,
                                      and LV_TXT_LINE_BREAK_LONG_POST_MIN_LEN.*/
};
typedef uint8_t text_flag_t;

/** Long mode behaviors. Used in 'lv_label_ext_t'*/
typedef enum {
  LABEL_LONG_WRAP,             /**< Keep the object width, wrap lines longer than object width and expand the object height*/
  LABEL_LONG_DOT,              /**< Keep the size and write dots at the end if the text is too long*/
  LABEL_LONG_SCROLL,           /**< Keep the size and roll the text back and forth*/
  LABEL_LONG_SCROLL_CIRCULAR,  /**< Keep the size and roll the text circularly*/
  LABEL_LONG_CLIP,             /**< Keep the size and clip the text out of it*/
} long_mode_t;

typedef enum {
  TABLE_CELL_CTRL_MERGE_RIGHT = 1 << 0,
  TABLE_CELL_CTRL_TEXT_CROP   = 1 << 1,
  TABLE_CELL_CTRL_CUSTOM_1    = 1 << 4,
  TABLE_CELL_CTRL_CUSTOM_2    = 1 << 5,
  TABLE_CELL_CTRL_CUSTOM_3    = 1 << 6,
  TABLE_CELL_CTRL_CUSTOM_4    = 1 << 7,
} table_cell_ctrl_t;

enum {
  FIT_NONE,  /**< Do not change the size automatically*/
  FIT_TIGHT, /**< Shrink wrap around the children */
  FIT_FLOOD, /**< Align the size to the parent's edge*/
  FIT_FILL,  /**< Align the size to the parent's edge first but if there is an object out of it then get larger */
  _FIT_NUM
};
typedef uint8_t fit_t;

#define FIT_CHILD     FIT_TIGHT
#define FIT_PARENT    FIT_FLOOD
#define FIT_MAX       FIT_FILL

enum {
  LAYOUT_NONE = LV_LAYOUT_NONE,
  LAYOUT_OFF = LV_LAYOUT_NONE, /**< No layout */
  LAYOUT_FLEX = LV_LAYOUT_FLEX,
  LAYOUT_GRID_CELL = LV_LAYOUT_GRID,

  LAYOUT_CENTER, /**< Center objects */
  LAYOUT_LEFT,   /**< Left objects */
  LAYOUT_RIGHT,  /**< Right objects */
  LAYOUT_COL_L,  /**< Column left align*/
  LAYOUT_COL_L_REVERSE,
  LAYOUT_COL_M,  /**< Column middle align*/
  LAYOUT_COL_M_REVERSE,
  LAYOUT_COL = LAYOUT_COL_M,
  LAYOUT_COL_REVERSE = LAYOUT_COL_M_REVERSE,
  LAYOUT_COL_R,  /**< Column right align*/
  LAYOUT_COL_R_REVERSE,
  LAYOUT_ROW_T,  /**< Row top align*/
  LAYOUT_ROW_T_REVERSE,
  LAYOUT_ROW_M,  /**< Row middle align*/
  LAYOUT_ROW_M_REVERSE,
  LAYOUT_ROW = LAYOUT_ROW_M,
  LAYOUT_ROW_REVERSE = LAYOUT_ROW_M_REVERSE,
  LAYOUT_ROW_B,  /**< Row bottom align*/
  LAYOUT_ROW_B_REVERSE,
  LAYOUT_PRETTY_T, /**< Put as many object as possible in row and begin a new row ; top align */
  LAYOUT_PRETTY_M, /**< Put as many object as possible in row and begin a new row ; mid align */
  LAYOUT_PRETTY = LAYOUT_PRETTY_M, /**< Put as many object as possible in row and begin a new row*/
  LAYOUT_PRETTY_ROW = LAYOUT_PRETTY,
  LAYOUT_PRETTY_B, /**< Put as many object as possible in row and begin a new row ; bottom align */
  LAYOUT_PRETTY_REVERSE_T,
  LAYOUT_PRETTY_REVERSE_M,
  LAYOUT_PRETTY_REVERSE = LAYOUT_PRETTY_REVERSE_M,
  LAYOUT_PRETTY_ROW_REVERSE = LAYOUT_PRETTY_REVERSE,
  LAYOUT_PRETTY_REVERSE_B,
  LAYOUT_PRETTY_COL,
  LAYOUT_PRETTY_COL_REVERSE,
  LAYOUT_GRID_T,   /**< Align same-sized object into a grid ; top align */
  LAYOUT_GRID_M,   /**< Align same-sized object into a grid ; mid align */
  LAYOUT_GRID = LAYOUT_GRID_M,
  LAYOUT_GRID_ROW = LAYOUT_GRID,
  LAYOUT_GRID_B,   /**< Align same-sized object into a grid ; bottom align */
  LAYOUT_GRID_REVERSE_T,
  LAYOUT_GRID_REVERSE_M,
  LAYOUT_GRID_REVERSE = LAYOUT_GRID_REVERSE_M,
  LAYOUT_GRID_ROW_REVERSE = LAYOUT_GRID_REVERSE,
  LAYOUT_GRID_REVERSE_B,
  LAYOUT_GRID_COL,
  LAYOUT_GRID_COL_REVERSE,
  LAYOUT_LAST,
};
typedef uint8_t layout_t;

enum {
  GLAYOUT_NONE = 0,
  GLAYOUT_FLEX,
  GLAYOUT_GRID,
  _GLAYOUT_LAST
};
typedef uint32_t glayout_t;

#define GRID_TEMPLATE_LAST    LV_GRID_TEMPLATE_LAST
#define GRID_FR               LV_GRID_FR

enum {
  FLEX_ALIGN_START,
  FLEX_ALIGN_END,
  FLEX_ALIGN_CENTER,  
  FLEX_ALIGN_SPACE_EVENLY,
  FLEX_ALIGN_SPACE_AROUND,
  FLEX_ALIGN_SPACE_BETWEEN,
  LAYOUT_ALIGN_START = FLEX_ALIGN_START,
  LAYOUT_ALIGN_END = FLEX_ALIGN_END,
  LAYOUT_ALIGN_CENTER = FLEX_ALIGN_CENTER,  
  LAYOUT_ALIGN_SPACE_EVENLY = FLEX_ALIGN_SPACE_EVENLY,
  LAYOUT_ALIGN_SPACE_AROUND = FLEX_ALIGN_SPACE_AROUND,
  LAYOUT_ALIGN_SPACE_BETWEEN = FLEX_ALIGN_SPACE_BETWEEN,
  CONTENT_ALIGN_START = FLEX_ALIGN_START,
  CONTENT_ALIGN_END = FLEX_ALIGN_END,
  CONTENT_ALIGN_CENTER = FLEX_ALIGN_CENTER,  
} ;
typedef uint8_t flex_align_t;
typedef uint8_t layout_align_t;

enum {
  FLEX_FLOW_ROW                 = 0x00,
  FLEX_FLOW_COLUMN              = _LV_FLEX_COLUMN,
  FLEX_FLOW_ROW_WRAP            = FLEX_FLOW_ROW | _LV_FLEX_WRAP,
  FLEX_FLOW_ROW_REVERSE         = FLEX_FLOW_ROW | _LV_FLEX_REVERSE,
  FLEX_FLOW_ROW_WRAP_REVERSE    = FLEX_FLOW_ROW | _LV_FLEX_WRAP | _LV_FLEX_REVERSE,
  FLEX_FLOW_COLUMN_WRAP         = FLEX_FLOW_COLUMN | _LV_FLEX_WRAP,
  FLEX_FLOW_COLUMN_REVERSE      = FLEX_FLOW_COLUMN | _LV_FLEX_REVERSE,
  FLEX_FLOW_COLUMN_WRAP_REVERSE = FLEX_FLOW_COLUMN | _LV_FLEX_WRAP | _LV_FLEX_REVERSE,
};
typedef uint8_t  flex_flow_t;

enum {
  STYLE_PROP_INV               = 0,

  /*Group 0*/
  STYLE_WIDTH                  = 1,
  STYLE_HEIGHT                 = 2,
  STYLE_LENGTH                 = 3,

  STYLE_MIN_WIDTH              = 4,
  STYLE_MAX_WIDTH              = 5,
  STYLE_MIN_HEIGHT             = 6,
  STYLE_MAX_HEIGHT             = 7,

  STYLE_X                      = 8,
  STYLE_Y                      = 9,
  STYLE_ALIGN                  = 10,

  STYLE_RADIUS                 = 12,

  /*Group 1*/
  STYLE_PAD_TOP                = 16,
  STYLE_PAD_BOTTOM             = 17,
  STYLE_PAD_LEFT               = 18,
  STYLE_PAD_RIGHT              = 19,

  STYLE_PAD_ROW                = 20,
  STYLE_PAD_COLUMN             = 21,
  STYLE_LAYOUT                 = 22,

  STYLE_MARGIN_TOP             = 24,
  STYLE_MARGIN_BOTTOM          = 25,
  STYLE_MARGIN_LEFT            = 26,
  STYLE_MARGIN_RIGHT           = 27,

  /*Group 2*/
  STYLE_BG_COLOR               = 28,
  STYLE_BG_OPA                 = 29,

  STYLE_BG_GRAD_DIR            = 32,
  STYLE_BG_MAIN_STOP           = 33,
  STYLE_BG_GRAD_STOP           = 34,
  STYLE_BG_GRAD_COLOR          = 35,

  STYLE_BG_MAIN_OPA            = 36,
  STYLE_BG_GRAD_OPA            = 37,
  STYLE_BG_GRAD                = 38,
  STYLE_BASE_DIR               = 39,

  STYLE_BG_IMAGE_SRC             = 40,
  STYLE_BG_IMAGE_OPA             = 41,
  STYLE_BG_IMAGE_RECOLOR         = 42,
  STYLE_BG_IMAGE_RECOLOR_OPA     = 43,

  STYLE_BG_IMAGE_TILED           = 44,
  STYLE_CLIP_CORNER            = 45,

  /*Group 3*/
  STYLE_BORDER_WIDTH           = 48,
  STYLE_BORDER_COLOR           = 49,
  STYLE_BORDER_OPA             = 50,

  STYLE_BORDER_SIDE            = 52,
  STYLE_BORDER_POST            = 53,

  STYLE_OUTLINE_WIDTH          = 56,
  STYLE_OUTLINE_COLOR          = 57,
  STYLE_OUTLINE_OPA            = 58,
  STYLE_OUTLINE_PAD            = 59,

  /*Group 4*/
  STYLE_SHADOW_WIDTH           = 60,
  STYLE_SHADOW_COLOR           = 61,
  STYLE_SHADOW_OPA             = 62,

  STYLE_SHADOW_OFFSET_X        = 64,
  STYLE_SHADOW_OFFSET_Y        = 65,
  STYLE_SHADOW_SPREAD          = 66,

  STYLE_IMAGE_OPA                = 68,
  STYLE_IMAGE_RECOLOR            = 69,
  STYLE_IMAGE_RECOLOR_OPA        = 70,

  STYLE_LINE_WIDTH             = 72,
  STYLE_LINE_DASH_WIDTH        = 73,
  STYLE_LINE_DASH_GAP          = 74,
  STYLE_LINE_ROUNDED           = 75,
  STYLE_LINE_COLOR             = 76,
  STYLE_LINE_OPA               = 77,

  /*Group 5*/
  STYLE_ARC_WIDTH              = 80,
  STYLE_ARC_ROUNDED            = 81,
  STYLE_ARC_COLOR              = 82,
  STYLE_ARC_OPA                = 83,
  STYLE_ARC_IMAGE_SRC            = 84,

  STYLE_TEXT_COLOR             = 88,
  STYLE_TEXT_OPA               = 89,
  STYLE_TEXT_FONT              = 90,

  STYLE_TEXT_LETTER_SPACE      = 91,
  STYLE_TEXT_LINE_SPACE        = 92,
  STYLE_TEXT_DECOR             = 93,
  STYLE_TEXT_ALIGN             = 94,

  STYLE_OPA                    = 95,
  STYLE_OPA_LAYERED            = 96,
  STYLE_COLOR_FILTER_DSC       = 97,
  STYLE_COLOR_FILTER_OPA       = 98,
  STYLE_ANIM                   = 99,
  STYLE_ANIM_DURATION          = 100,
  STYLE_TRANSITION             = 102,
  STYLE_BLEND_MODE             = 103,
  STYLE_TRANSFORM_WIDTH        = 104,
  STYLE_TRANSFORM_HEIGHT       = 105,
  STYLE_TRANSLATE_X            = 106,
  STYLE_TRANSLATE_Y            = 107,
  STYLE_TRANSFORM_SCALE_X      = 108,
  STYLE_TRANSFORM_SCALE_Y      = 109,
  STYLE_TRANSFORM_ROTATION     = 110,
  STYLE_TRANSFORM_PIVOT_X      = 111,
  STYLE_TRANSFORM_PIVOT_Y      = 112,
  STYLE_TRANSFORM_SKEW_X       = 113,
  STYLE_TRANSFORM_SKEW_Y       = 114,

#if LV_USE_FLEX
  STYLE_FLEX_FLOW              = 115,
  STYLE_FLEX_MAIN_PLACE        = 116,
  STYLE_FLEX_CROSS_PLACE       = 117,
  STYLE_FLEX_TRACK_PLACE       = 118,
  STYLE_FLEX_GROW              = 119,
#endif

#if LV_USE_GRID
  STYLE_GRID_COLUMN_ALIGN      = 120,
  STYLE_GRID_ROW_ALIGN         = 121,
  STYLE_GRID_ROW_DSC_ARRAY     = 122,
  STYLE_GRID_COLUMN_DSC_ARRAY  = 123,
  STYLE_GRID_CELL_COLUMN_POS   = 124,
  STYLE_GRID_CELL_COLUMN_SPAN  = 125,
  STYLE_GRID_CELL_X_ALIGN      = 126,
  STYLE_GRID_CELL_ROW_POS      = 127,
  STYLE_GRID_CELL_ROW_SPAN     = 128,
  STYLE_GRID_CELL_Y_ALIGN      = 129,
#endif

  _STYLE_LAST_BUILT_IN_PROP     = 130,

  _STYLE_NUM_BUILT_IN_PROPS     = _LV_STYLE_LAST_BUILT_IN_PROP + 1,

  STYLE_PROP_ANY                = 0xFF,
  _STYLE_PROP_CONST             = 0xFF /* magic value for const styles */
};
typedef uint8_t style_prop_t;


#define style_transition_t        lv_style_transition_dsc_t
#define style_transition_dsc_t    lv_style_transition_dsc_t
#define style_value_t             lv_style_value_t
#define style_const_prop_t        lv_style_const_prop_t

enum {
  STYLE_RES_NOT_FOUND,
  STYLE_RES_FOUND,
};
typedef uint8_t style_res_t;

enum {
  CLOCKWISE,
  ANTICLOCKWISE,
};

typedef uint8_t     rotate_direction_t;


enum {
  BUTTON_STATE_RELEASED,/**< BUTTON_PUSH ขณะไม่มีการสัมผัส , BUTTON_SWITCH ขณะ OFF ขณะไม่มีการสัมผัส */
  BUTTON_STATE_PRESSED, /**< BUTTON_PUSH ขณะมีการสัมผัส , BUTTON_SWITCH ขณะ OFF ขณะมีการสัมผัส */
  BUTTON_STATE_DISABLED,/**< BUTTON ขณะไม่ให้ทำงาน */
  BUTTON_STATE_CHECKED_RELEASED, /**< BUTTON_SWITCH ขณะ ON ขณะไม่มีการสัมผัส */
  BUTTON_STATE_CHECKED_PRESSED, /**< BUTTON_SWITCH ขณะ ON ขณะไม่มีการสัมผัส */
  BUTTON_STATE_CHECKED_DISABLED, 
  _BUTTON_STATE_NUM,
  
  RELEASED = BUTTON_STATE_RELEASED,                 /**< BUTTON_PUSH ขณะไม่มีการสัมผัส , BUTTON_SWITCH ขณะ OFF ขณะไม่มีการสัมผัส */
  PRESSED = BUTTON_STATE_PRESSED,                   /**< BUTTON_PUSH ขณะมีการสัมผัส , BUTTON_SWITCH ขณะ OFF ขณะมีการสัมผัส */
  INACTIVE=BUTTON_STATE_DISABLED,                   /**< BUTTON ขณะไม่ให้ทำงาน */
  TOGGLE_RELEASED =BUTTON_STATE_CHECKED_RELEASED,   /**< BUTTON_SWITCH ขณะ ON ขณะไม่มีการสัมผัส */
  TOGGLE_PRESSED = BUTTON_STATE_CHECKED_PRESSED,    /**< BUTTON_SWITCH ขณะ ON ขณะมีการสัมผัส */
};
typedef uint8_t     button_state_t;

enum {
  BUTTON_PUSH,
  BUTTON_SWITCH,
};
typedef uint8_t     button_type_t;

enum {
  BUTTON_MODE_NORMAL,
  BUTTON_MODE_TOGGLE,
  BUTTON_MODE_INACTIVE,
};
typedef uint8_t button_mode_t;

enum {
  IMAGEBUTTON_STATE_RELEASED,
  IMAGEBUTTON_STATE_PRESSED,
  IMAGEBUTTON_STATE_DISABLED,
  IMAGEBUTTON_STATE_CHECKED_RELEASED,
  IMAGEBUTTON_STATE_CHECKED_PRESSED,
  IMAGEBUTTON_STATE_CHECKED_DISABLED,
  _IMAGEBUTTON_STATE_NUM,
};
typedef uint8_t  imagebutton_state_t;

enum {
  GAUGE_TYPE_ARC,
  GAUGE_TYPE_FULL,
};
typedef uint8_t gauge_type_t;
typedef uint8_t GGauge_type_t;


/**
 * Possible options for blending opaque drawings
 */
typedef enum {
  BLEND_MODE_NORMAL,     /**< Simply mix according to the opacity value*/
  BLEND_MODE_ADDITIVE,   /**< Add the respective color channels*/
  BLEND_MODE_SUBTRACTIVE,/**< Subtract the foreground from the background*/
  BLEND_MODE_MULTIPLY,   /**< Multiply the foreground and background*/
} blend_mode_t;

/** Roller mode. */
typedef enum {
  ROLLER_MODE_NORMAL,   /**< Normal mode (roller ends at the end of the options). */
  ROLLER_MODE_INFINITE, /**< Infinite mode (roller can be scrolled forever). */
} roller_mode_t;


/**
 * Image size mode, when image size and object size is different
 */
typedef enum {
  IMAGE_ALIGN_DEFAULT = 0,
  IMAGE_ALIGN_TOP_LEFT,
  IMAGE_ALIGN_TOP_MID,
  IMAGE_ALIGN_TOP_RIGHT,
  IMAGE_ALIGN_BOTTOM_LEFT,
  IMAGE_ALIGN_BOTTOM_MID,
  IMAGE_ALIGN_BOTTOM_RIGHT,
  IMAGE_ALIGN_LEFT_MID,
  IMAGE_ALIGN_RIGHT_MID,
  IMAGE_ALIGN_CENTER,
  IMAGE_ALIGN_AUTO_TRANSFORM,
  IMAGE_ALIGN_STRETCH,
  IMAGE_ALIGN_TILE,
} image_align_t;

// enum {
//     EVENT_ALL = LV_EVENT_ALL,

//     /** Input device events*/
//     EVENT_PRESSED = LV_EVENT_PRESSED,             /**< The object has been pressed*/
//     EVENT_PRESSING = LV_EVENT_PRESSING,            /**< The object is being pressed (called continuously while pressing)*/
//     EVENT_PRESS_LOST = LV_EVENT_PRESS_LOST,          /**< The object is still being pressed but slid cursor/finger off of the object */
//     EVENT_SHORT_CLICKED = LV_EVENT_SHORT_CLICKED,       /**< The object was pressed for a short period of time, then released it. Not called if scrolled.*/
//     EVENT_SINGLE_CLICKED = LV_EVENT_SINGLE_CLICKED,      /**< Called for the first short click within a small distance and short time*/
//     EVENT_DOUBLE_CLICKED = LV_EVENT_DOUBLE_CLICKED,      /**< Called for the second short click within small distance and short time*/
//     EVENT_TRIPLE_CLICKED = LV_EVENT_TRIPLE_CLICKED,      /**< Called for the third short click within small distance and short time*/
//     EVENT_LONG_PRESSED = LV_EVENT_LONG_PRESSED,        /**< Object has been pressed for at least `long_press_time`.  Not called if scrolled.*/
//     EVENT_LONG_PRESSED_REPEAT = LV_EVENT_LONG_PRESSED_REPEAT, /**< Called after `long_press_time` in every `long_press_repeat_time` ms.  Not called if scrolled.*/
//     EVENT_CLICKED = LV_EVENT_CLICKED,             /**< Called on release if not scrolled (regardless to long press)*/
//     EVENT_RELEASED = LV_EVENT_RELEASED,            /**< Called in every cases when the object has been released*/
//     EVENT_SCROLL_BEGIN = LV_EVENT_SCROLL_BEGIN,        /**< Scrolling begins. The event parameter is a pointer to the animation of the scroll. Can be modified*/
//     EVENT_SCROLL_THROW_BEGIN = LV_EVENT_SCROLL_THROW_BEGIN,
//     EVENT_SCROLL_END = LV_EVENT_SCROLL_END,          /**< Scrolling ends*/
//     EVENT_SCROLL = LV_EVENT_SCROLL,              /**< Scrolling*/
//     EVENT_GESTURE = LV_EVENT_GESTURE,             /**< A gesture is detected. Get the gesture with `lv_indev_get_gesture_dir(lv_indev_active());` */
//     EVENT_KEY = LV_EVENT_KEY,                 /**< A key is sent to the object. Get the key with `lv_indev_get_key(lv_indev_active());`*/
//     EVENT_ROTARY = LV_EVENT_ROTARY,    /**< An encoder or wheel was rotated. Get the rotation count with `lv_event_get_rotary_diff(e);`*/  // v9.1.0
//     EVENT_FOCUSED = LV_EVENT_FOCUSED,             /**< The object is focused*/
//     EVENT_DEFOCUSED = LV_EVENT_DEFOCUSED,           /**< The object is defocused*/
//     EVENT_LEAVE = LV_EVENT_LEAVE,               /**< The object is defocused but still selected*/
//     EVENT_HIT_TEST = LV_EVENT_HIT_TEST,            /**< Perform advanced hit-testing*/
//     EVENT_INDEV_RESET = LV_EVENT_INDEV_RESET,         /**< Indev has been reset*/
//     EVENT_HOVER_OVER = LV_EVENT_HOVER_OVER,          /**< Indev hover over object*/
//     EVENT_HOVER_LEAVE = LV_EVENT_HOVER_LEAVE,         /**< Indev hover leave object*/

//     /** Drawing events*/
//     EVENT_COVER_CHECK = LV_EVENT_COVER_CHECK,        /**< Check if the object fully covers an area. The event parameter is `lv_cover_check_info_t *`.*/
//     EVENT_REFR_EXT_DRAW_SIZE = LV_EVENT_REFR_EXT_DRAW_SIZE, /**< Get the required extra draw area around the object (e.g. for shadow). The event parameter is `int32_t *` to store the size.*/
//     EVENT_DRAW_MAIN_BEGIN = LV_EVENT_DRAW_MAIN_BEGIN,    /**< Starting the main drawing phase*/
//     EVENT_DRAW_MAIN = LV_EVENT_DRAW_MAIN,          /**< Perform the main drawing*/
//     EVENT_DRAW_MAIN_END = LV_EVENT_DRAW_MAIN_END,      /**< Finishing the main drawing phase*/
//     EVENT_DRAW_POST_BEGIN = LV_EVENT_DRAW_POST_BEGIN,    /**< Starting the post draw phase (when all children are drawn)*/
//     EVENT_DRAW_POST = LV_EVENT_DRAW_POST,          /**< Perform the post draw phase (when all children are drawn)*/
//     EVENT_DRAW_POST_END = LV_EVENT_DRAW_POST_END,      /**< Finishing the post draw phase (when all children are drawn)*/
//     EVENT_DRAW_TASK_ADDED = LV_EVENT_DRAW_TASK_ADDED,      /**< Adding a draw task */
//     EVENT_DRAW_TASK = EVENT_DRAW_TASK_ADDED,   // BlynkGO

//     /** Special events*/
//     EVENT_VALUE_CHANGED = LV_EVENT_VALUE_CHANGED,       /**< The object's value has changed (i.e. slider moved)*/
//     EVENT_INSERT = LV_EVENT_INSERT,              /**< A text is inserted to the object. The event data is `char *` being inserted.*/
//     EVENT_REFRESH = LV_EVENT_REFRESH,             /**< Notify the object to refresh something on it (for the user)*/
//     EVENT_READY = LV_EVENT_READY,               /**< A process has finished*/
//     EVENT_CANCEL = LV_EVENT_CANCEL,              /**< A process has been cancelled */

//     /** Other events*/
//     EVENT_CREATE = LV_EVENT_CREATE,              /**< Object is being created*/
//     EVENT_DELETE = LV_EVENT_DELETE,              /**< Object is being deleted*/
//     EVENT_CHILD_CHANGED = LV_EVENT_CHILD_CHANGED,       /**< Child was removed, added, or its size, position were changed */
//     EVENT_CHILD_CREATED = LV_EVENT_CHILD_CREATED,       /**< Child was created, always bubbles up to all parents*/
//     EVENT_CHILD_DELETED = LV_EVENT_CHILD_DELETED,       /**< Child was deleted, always bubbles up to all parents*/
//     EVENT_SCREEN_UNLOAD_START = LV_EVENT_SCREEN_UNLOAD_START, /**< A screen unload started, fired immediately when scr_load is called*/
//     EVENT_SCREEN_LOAD_START = LV_EVENT_SCREEN_LOAD_START,   /**< A screen load started, fired when the screen change delay is expired*/
//     EVENT_SCREEN_LOADED = LV_EVENT_SCREEN_LOADED,       /**< A screen was loaded*/
//     EVENT_SCREEN_UNLOADED = LV_EVENT_SCREEN_UNLOADED,     /**< A screen was unloaded*/
//     EVENT_SIZE_CHANGED = LV_EVENT_SIZE_CHANGED,        /**< Object coordinates/size have changed*/
//     EVENT_STYLE_CHANGED = LV_EVENT_STYLE_CHANGED,       /**< Object's style has changed*/
//     EVENT_LAYOUT_CHANGED = LV_EVENT_LAYOUT_CHANGED,      /**< The children position has changed due to a layout recalculation*/
//     EVENT_GET_SELF_SIZE = LV_EVENT_GET_SELF_SIZE,       /**< Get the internal size of a widget*/

//     /** Events of optional LVGL components*/
//     EVENT_INVALIDATE_AREA = LV_EVENT_INVALIDATE_AREA,
//     EVENT_RESOLUTION_CHANGED = LV_EVENT_RESOLUTION_CHANGED,
//     EVENT_COLOR_FORMAT_CHANGED = LV_EVENT_COLOR_FORMAT_CHANGED,
//     EVENT_REFR_REQUEST = LV_EVENT_REFR_REQUEST,
//     EVENT_REFR_START = LV_EVENT_REFR_START,
//     EVENT_REFR_READY = LV_EVENT_REFR_READY,
//     EVENT_RENDER_START = LV_EVENT_RENDER_START,
//     EVENT_RENDER_READY = LV_EVENT_RENDER_READY,
//     EVENT_FLUSH_START = LV_EVENT_FLUSH_START,
//     EVENT_FLUSH_FINISH = LV_EVENT_FLUSH_FINISH,
//     EVENT_FLUSH_WAIT_START = LV_EVENT_FLUSH_WAIT_START,    // v9.1.0
//     EVENT_FLUSH_WAIT_FINISH = LV_EVENT_FLUSH_WAIT_FINISH,   // v9.1.0

//     EVENT_VSYNC = LV_EVENT_VSYNC,

//     _EVENT_LAST = _LV_EVENT_LAST,                 /** Number of default events*/

//     EVENT_PREPROCESS = 0x8000,   /** This is a flag that can be set with an event so it's processed
//                                       before the class default event processing */
//     EVENT_MARKED_DELETING = LV_EVENT_MARKED_DELETING, 
// };

/** event สำหรับ v9.3.0 */
enum {
    EVENT_ALL = LV_EVENT_ALL,

    /** Input device events*/
    EVENT_PRESSED = LV_EVENT_PRESSED,                         /**< Widget has been pressed */
    EVENT_PRESSING = LV_EVENT_PRESSING,                       /**< Widget is being pressed (sent continuously while pressing)*/
    EVENT_PRESS_LOST = LV_EVENT_PRESS_LOST,                   /**< Widget is still being pressed but slid cursor/finger off Widget */
    EVENT_SHORT_CLICKED = LV_EVENT_SHORT_CLICKED,             /**< Widget was pressed for a short period of time, then released. Not sent if scrolled. */
    EVENT_SINGLE_CLICKED = LV_EVENT_SINGLE_CLICKED,           /**< Sent for first short click within a small distance and short time */
    EVENT_DOUBLE_CLICKED = LV_EVENT_DOUBLE_CLICKED,           /**< Sent for second short click within small distance and short time */
    EVENT_TRIPLE_CLICKED = LV_EVENT_TRIPLE_CLICKED,           /**< Sent for third short click within small distance and short time */
    EVENT_LONG_PRESSED = LV_EVENT_LONG_PRESSED,               /**< Object has been pressed for at least `long_press_time`.  Not sent if scrolled. */
    EVENT_LONG_PRESSED_REPEAT = LV_EVENT_LONG_PRESSED_REPEAT, /**< Sent after `long_press_time` in every `long_press_repeat_time` ms.  Not sent if scrolled. */
    EVENT_CLICKED = LV_EVENT_CLICKED,                         /**< Sent on release if not scrolled (regardless to long press)*/
    EVENT_RELEASED = LV_EVENT_RELEASED,                       /**< Sent in every cases when Widget has been released */
    EVENT_SCROLL_BEGIN = LV_EVENT_SCROLL_BEGIN,               /**< Scrolling begins. The event parameter is a pointer to the animation of the scroll. Can be modified */
    EVENT_SCROLL_THROW_BEGIN = LV_EVENT_SCROLL_THROW_BEGIN,
    EVENT_SCROLL_END = LV_EVENT_SCROLL_END,                   /**< Scrolling ends */
    EVENT_SCROLL = LV_EVENT_SCROLL,                           /**< Scrolling */
    EVENT_GESTURE = LV_EVENT_GESTURE,                         /**< A gesture is detected. Get gesture with `lv_indev_get_gesture_dir(lv_indev_active());` */
    EVENT_KEY = LV_EVENT_KEY,                                 /**< A key is sent to Widget. Get key with `lv_indev_get_key(lv_indev_active());`*/
    EVENT_ROTARY = LV_EVENT_ROTARY,                           /**< An encoder or wheel was rotated. Get rotation count with `lv_event_get_rotary_diff(e);`*/
    EVENT_FOCUSED = LV_EVENT_FOCUSED,                         /**< Widget received focus */
    EVENT_DEFOCUSED = LV_EVENT_DEFOCUSED,                     /**< Widget's focus has been lost */
    EVENT_LEAVE = LV_EVENT_LEAVE,                             /**< Widget's focus has been lost but is still selected */
    EVENT_HIT_TEST = LV_EVENT_HIT_TEST,                       /**< Perform advanced hit-testing */
    EVENT_INDEV_RESET = LV_EVENT_INDEV_RESET,                 /**< Indev has been reset */
    EVENT_HOVER_OVER = LV_EVENT_HOVER_OVER,                   /**< Indev hover over object */
    EVENT_HOVER_LEAVE = LV_EVENT_HOVER_LEAVE,                 /**< Indev hover leave object */

    /** Drawing events */
    EVENT_COVER_CHECK = LV_EVENT_COVER_CHECK,                 /**< Check if Widget fully covers an area. The event parameter is `lv_cover_check_info_t *`. */
    EVENT_REFR_EXT_DRAW_SIZE = LV_EVENT_REFR_EXT_DRAW_SIZE,   /**< Get required extra draw area around Widget (e.g. for shadow). The event parameter is `int32_t *` to store the size. */
    EVENT_DRAW_MAIN_BEGIN = LV_EVENT_DRAW_MAIN_BEGIN,         /**< Starting the main drawing phase */
    EVENT_DRAW_MAIN = LV_EVENT_DRAW_MAIN,                     /**< Perform the main drawing */
    EVENT_DRAW_MAIN_END = LV_EVENT_DRAW_MAIN_END,             /**< Finishing the main drawing phase */
    EVENT_DRAW_POST_BEGIN = LV_EVENT_DRAW_POST_BEGIN,         /**< Starting the post draw phase (when all children are drawn)*/
    EVENT_DRAW_POST = LV_EVENT_DRAW_POST,                     /**< Perform the post draw phase (when all children are drawn)*/
    EVENT_DRAW_POST_END = LV_EVENT_DRAW_POST_END,             /**< Finishing the post draw phase (when all children are drawn)*/
    EVENT_DRAW_TASK_ADDED = LV_EVENT_DRAW_TASK_ADDED,         /**< Adding a draw task. The `LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS` flag needs to be set */

    // BlynkGO
    EVENT_DRAW_TASK = EVENT_DRAW_TASK_ADDED,                  /**< Adding a draw task. The `LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS` flag needs to be set */

    /** Special events */
    EVENT_VALUE_CHANGED = LV_EVENT_VALUE_CHANGED,             /**< Widget's value has changed (i.e. slider moved)*/
    EVENT_INSERT = LV_EVENT_INSERT,                           /**< Text has been inserted into Widget. The event data is `char *` being inserted. */
    EVENT_REFRESH = LV_EVENT_REFRESH,                         /**< Notify Widget to refresh something on it (for user)*/
    EVENT_READY = LV_EVENT_READY,                             /**< A process has finished */
    EVENT_CANCEL = LV_EVENT_CANCEL,                           /**< A process has been cancelled */

    /** Other events */
    EVENT_CREATE = LV_EVENT_CREATE,                           /**< Object is being created */
    EVENT_DELETE = LV_EVENT_DELETE,                           /**< Object is being deleted */
    EVENT_CHILD_CHANGED = LV_EVENT_CHILD_CHANGED,             /**< Child was removed, added, or its size, position were changed */
    EVENT_CHILD_CREATED = LV_EVENT_CHILD_CREATED,             /**< Child was created, always bubbles up to all parents */
    EVENT_CHILD_DELETED = LV_EVENT_CHILD_DELETED,             /**< Child was deleted, always bubbles up to all parents */
    EVENT_SCREEN_UNLOAD_START = LV_EVENT_SCREEN_UNLOAD_START, /**< A screen unload started, fired immediately when scr_load is called */
    EVENT_SCREEN_LOAD_START = LV_EVENT_SCREEN_LOAD_START,     /**< A screen load started, fired when the screen change delay is expired */
    EVENT_SCREEN_LOADED = LV_EVENT_SCREEN_LOADED,             /**< A screen was loaded */
    EVENT_SCREEN_UNLOADED = LV_EVENT_SCREEN_UNLOADED,         /**< A screen was unloaded */
    EVENT_SIZE_CHANGED = LV_EVENT_SIZE_CHANGED,               /**< Object coordinates/size have changed */
    EVENT_STYLE_CHANGED = LV_EVENT_STYLE_CHANGED,             /**< Object's style has changed */
    EVENT_LAYOUT_CHANGED = LV_EVENT_LAYOUT_CHANGED,           /**< A child's position position has changed due to a layout recalculation */
    EVENT_GET_SELF_SIZE = LV_EVENT_GET_SELF_SIZE,             /**< Get internal size of a widget */

    /** Events of optional LVGL components */
    EVENT_INVALIDATE_AREA = LV_EVENT_INVALIDATE_AREA,         /**< An area is invalidated (marked for redraw). `lv_event_get_param(e)`
                                                               * returns a pointer to an `lv_area_t` object with the coordinates of the
                                                               * area to be invalidated.  The area can be freely modified if needed to
                                                               * adapt it a special requirement of the display. Usually needed with
                                                               * monochrome displays to invalidate `N x 8` rows or columns in one pass. */
    EVENT_RESOLUTION_CHANGED = LV_EVENT_RESOLUTION_CHANGED,   /**< Sent when the resolution changes due to `lv_display_set_resolution()` or `lv_display_set_rotation()`. */
    EVENT_COLOR_FORMAT_CHANGED = LV_EVENT_COLOR_FORMAT_CHANGED,/**< Sent as a result of any call to `lv_display_set_color_format()`. */
    EVENT_REFR_REQUEST = LV_EVENT_REFR_REQUEST,               /**< Sent when something happened that requires redraw. */
    EVENT_REFR_START = LV_EVENT_REFR_START,                   /**< Sent before a refreshing cycle starts. Sent even if there is nothing to redraw. */
    EVENT_REFR_READY = LV_EVENT_REFR_READY,                   /**< Sent when refreshing has been completed (after rendering and calling flush callback). Sent even if no redraw happened. */
    EVENT_RENDER_START = LV_EVENT_RENDER_START,               /**< Sent just before rendering begins. */
    EVENT_RENDER_READY = LV_EVENT_RENDER_READY,               /**< Sent after rendering has been completed (before calling flush callback) */
    EVENT_FLUSH_START = LV_EVENT_FLUSH_START,                 /**< Sent before flush callback is called. */
    EVENT_FLUSH_FINISH = LV_EVENT_FLUSH_FINISH,               /**< Sent after flush callback call has returned. */
    EVENT_FLUSH_WAIT_START = LV_EVENT_FLUSH_WAIT_START,       /**< Sent before flush wait callback is called. */
    EVENT_FLUSH_WAIT_FINISH = LV_EVENT_FLUSH_WAIT_FINISH,     /**< Sent after flush wait callback call has returned. */

    EVENT_VSYNC = LV_EVENT_VSYNC,
    EVENT_VSYNC_REQUEST = LV_EVENT_VSYNC_REQUEST,
#ifdef _WIN32
    EVENT_RIGHT_CLICKED = LV_EVENT_RIGHT_CLICKED,             // BlynkGO
#endif
    EVENT_LAST = LV_EVENT_LAST,                               /** Number of default events */

    EVENT_PREPROCESS = LV_EVENT_PREPROCESS,                   /** This is a flag that can be set with an event so it's processed
                                                                before the class default event processing */
    EVENT_MARKED_DELETING = LV_EVENT_MARKED_DELETING,
};
typedef uint16_t    event_t;

#define event_dsc_t     lv_event_dsc_t
#define hit_test_info_t lv_hit_test_info_t
#define cover_res_t     lv_cover_res_t

enum {
    TFT_PALETTE_RED,
    TFT_PALETTE_PINK,
    TFT_PALETTE_PURPLE,
    TFT_PALETTE_DEEP_PURPLE,
    TFT_PALETTE_INDIGO,
    TFT_PALETTE_BLUE,
    TFT_PALETTE_LIGHT_BLUE,
    TFT_PALETTE_CYAN,
    TFT_PALETTE_TEAL,
    TFT_PALETTE_GREEN,
    TFT_PALETTE_LIGHT_GREEN,
    TFT_PALETTE_LIME,
    TFT_PALETTE_YELLOW,
    TFT_PALETTE_AMBER,
    TFT_PALETTE_ORANGE,
    TFT_PALETTE_DEEP_ORANGE,
    TFT_PALETTE_BROWN,
    TFT_PALETTE_BLUE_GREY,
    TFT_PALETTE_BLUE_GRAY = TFT_PALETTE_BLUE_GREY,
    TFT_PALETTE_GREY,
    TFT_PALETTE_GRAY = TFT_PALETTE_GREY,
    TFT_PALETTE_LAST,
    TFT_PALETTE_NONE = 0xff,
};
typedef uint8_t   palette_t;

enum {
  WIDGET_TYPE_NONE  = 0,
  WIDGET_TYPE_GRECT,
  WIDGET_TYPE_GANIMIMAGE,
  WIDGET_TYPE_GAPP,
  WIDGET_TYPE_GARC,
  WIDGET_TYPE_GBAR,
  WIDGET_TYPE_GBUTTON,
  WIDGET_TYPE_GBUTTONMATRIX,
  WIDGET_TYPE_GCALENDAR,
  WIDGET_TYPE_GCANVAS,
  WIDGET_TYPE_GCHART,
  WIDGET_TYPE_GCHARTRANGEBAR,
  WIDGET_TYPE_GCHECKBOX,
  WIDGET_TYPE_GCIRCLE,
  WIDGET_TYPE_GCONTAINER,
  WIDGET_TYPE_GDROPDOWNLIST,
  WIDGET_TYPE_GGAUGE,
  WIDGET_TYPE_GGAUGERAINBOW,
  WIDGET_TYPE_GICON,
  WIDGET_TYPE_GIMAGE,
  WIDGET_TYPE_GIMAGEBUTTON,
  WIDGET_TYPE_GKEYBOARD,
  WIDGET_TYPE_GKEYUNLOCKER,
  WIDGET_TYPE_GLABEL,
  WIDGET_TYPE_GLED,
  WIDGET_TYPE_GLINE,
  WIDGET_TYPE_GLIST,
  WIDGET_TYPE_GLOTTIE,
  WIDGET_TYPE_GMASK,
  WIDGET_TYPE_GMENU,
  WIDGET_TYPE_GMESSAGEBOX,
  WIDGET_TYPE_GMULTISCREEN,
  WIDGET_TYPE_GPAGE,
  WIDGET_TYPE_GPARAGRAPH,
  WIDGET_TYPE_GPASSCODELOCK,
  WIDGET_TYPE_GQRCODE,
  WIDGET_TYPE_GROLLER,
  WIDGET_TYPE_GSLIDER,
  WIDGET_TYPE_GSPINBOX,
  WIDGET_TYPE_GSPINNER,
  WIDGET_TYPE_GSTEP,
  WIDGET_TYPE_GSWITCH,
  WIDGET_TYPE_GTABLE,
  WIDGET_TYPE_GTABVIEW,
  WIDGET_TYPE_GTILEVIEW,
  WIDGET_TYPE_GTILE,
  WIDGET_TYPE_GTEXTAREA,
  WIDGET_TYPE_GTEXTAREA_INPUTPAD,
  WIDGET_TYPE_GWIFIMANAGER,
  WIDGET_TYPE_GWIFISETTING,

  WIDGET_TYPE_USER1,
  WIDGET_TYPE_USER2,
  WIDGET_TYPE_USER3,
  WIDGET_TYPE_USER4,
  WIDGET_TYPE_USER5,
  WIDGET_TYPE_USER6,
  WIDGET_TYPE_USER7,
  WIDGET_TYPE_USER8,
  WIDGET_TYPE_USER9,
  WIDGET_TYPE_USER10,
  WIDGET_TYPE_MAX,
};
typedef uint8_t   widget_type_t;

enum  {
    OPA_TRANSP = 0,
    OPA_0      = 0,
    OPA_10     = 25,
    OPA_20     = 51,
    OPA_30     = 76,
    OPA_40     = 102,
    OPA_50     = 127,
    OPA_60     = 153,
    OPA_70     = 178,
    OPA_80     = 204,
    OPA_90     = 229,
    OPA_100    = 255,
    OPA_COVER  = 255,
};
typedef uint8_t opa_t;

enum  {
    GSTYLE_PROP_INV               = 0,

    /*Group 0*/
    GSTYLE_WIDTH                  = 1,
    GSTYLE_HEIGHT                 = 2,
    GSTYLE_LENGTH                 = 3,

    GSTYLE_MIN_WIDTH              = 4,
    GSTYLE_MAX_WIDTH              = 5,
    GSTYLE_MIN_HEIGHT             = 6,
    GSTYLE_MAX_HEIGHT             = 7,

    GSTYLE_X                      = 8,
    GSTYLE_Y                      = 9,
    GSTYLE_ALIGN                  = 10,

    GSTYLE_RADIUS                 = 12,

    /*Group 1*/
    GSTYLE_PAD_TOP                = 16,
    GSTYLE_PAD_BOTTOM             = 17,
    GSTYLE_PAD_LEFT               = 18,
    GSTYLE_PAD_RIGHT              = 19,

    GSTYLE_PAD_ROW                = 20,
    GSTYLE_PAD_COLUMN             = 21,
    GSTYLE_LAYOUT                 = 22,

    GSTYLE_MARGIN_TOP             = 24,
    GSTYLE_MARGIN_BOTTOM          = 25,
    GSTYLE_MARGIN_LEFT            = 26,
    GSTYLE_MARGIN_RIGHT           = 27,

    /*Group 2*/
    GSTYLE_BG_COLOR               = 28,
    GSTYLE_BG_OPA                 = 29,

    GSTYLE_BG_GRAD_DIR            = 32,
    GSTYLE_BG_MAIN_STOP           = 33,
    GSTYLE_BG_GRAD_STOP           = 34,
    GSTYLE_BG_GRAD_COLOR          = 35,

    GSTYLE_BG_MAIN_OPA            = 36,
    GSTYLE_BG_GRAD_OPA            = 37,
    GSTYLE_BG_GRAD                = 38,
    GSTYLE_BASE_DIR               = 39,

    GSTYLE_BG_IMAGE_SRC             = 40,
    GSTYLE_BG_IMAGE_OPA             = 41,
    GSTYLE_BG_IMAGE_RECOLOR         = 42,
    GSTYLE_BG_IMAGE_RECOLOR_OPA     = 43,

    GSTYLE_BG_IMAGE_TILED           = 44,
    GSTYLE_CLIP_CORNER            = 45,

    /*Group 3*/
    GSTYLE_BORDER_WIDTH           = 48,
    GSTYLE_BORDER_COLOR           = 49,
    GSTYLE_BORDER_OPA             = 50,

    GSTYLE_BORDER_SIDE            = 52,
    GSTYLE_BORDER_POST            = 53,

    GSTYLE_OUTLINE_WIDTH          = 56,
    GSTYLE_OUTLINE                = GSTYLE_OUTLINE_WIDTH,
    GSTYLE_OUTLINE_COLOR          = 57,
    GSTYLE_OUTLINE_OPA            = 58,
    GSTYLE_OUTLINE_PAD            = 59,

    /*Group 4*/
    GSTYLE_SHADOW_WIDTH           = 60,
    GSTYLE_SHADOW_COLOR           = 61,
    GSTYLE_SHADOW_OPA             = 62,

    GSTYLE_SHADOW_OFFSET_X        = 64,
    GSTYLE_SHADOW_OFFSET_Y        = 65,
    GSTYLE_SHADOW_SPREAD          = 66,

    GSTYLE_IMAGE_OPA                = 68,
    GSTYLE_IMAGE_RECOLOR            = 69,
    GSTYLE_IMAGE_RECOLOR_OPA        = 70,

    GSTYLE_LINE_WIDTH             = 72,
    GSTYLE_LINE_DASH_WIDTH        = 73,
    GSTYLE_LINE_DASH_GAP          = 74,
    GSTYLE_LINE_ROUNDED           = 75,
    GSTYLE_LINE_COLOR             = 76,
    GSTYLE_LINE_OPA               = 77,

    /*Group 5*/
    GSTYLE_ARC_WIDTH              = 80,
    GSTYLE_ARC_ROUNDED            = 81,
    GSTYLE_ARC_COLOR              = 82,
    GSTYLE_ARC_OPA                = 83,
    GSTYLE_ARC_IMAGE_SRC            = 84,

    GSTYLE_TEXT_COLOR             = 88,
    GSTYLE_TEXT_OPA               = 89,
    GSTYLE_TEXT_FONT              = 90,

    GSTYLE_TEXT_LETTER_SPACE      = 91,
    GSTYLE_TEXT_LINE_SPACE        = 92,
    GSTYLE_TEXT_DECOR             = 93,
    GSTYLE_TEXT_ALIGN             = 94,

    GSTYLE_OPA                    = 95,
    GSTYLE_OPA_LAYERED            = 96,
    GSTYLE_COLOR_FILTER_DSC       = 97,
    GSTYLE_COLOR_FILTER_OPA       = 98,
    GSTYLE_ANIM                   = 99,
    GSTYLE_ANIM_DURATION          = 100,
    GSTYLE_TRANSITION             = 102,
    GSTYLE_BLEND_MODE             = 103,
    GSTYLE_TRANSFORM_WIDTH        = 104,
    GSTYLE_TRANSFORM_HEIGHT       = 105,
    GSTYLE_TRANSLATE_X            = 106,
    GSTYLE_TRANSLATE_Y            = 107,
    GSTYLE_TRANSFORM_SCALE_X      = 108,
    GSTYLE_TRANSFORM_SCALE_Y      = 109,
    GSTYLE_TRANSFORM_ROTATION     = 110,
    GSTYLE_TRANSFORM_PIVOT_X      = 111,
    GSTYLE_TRANSFORM_PIVOT_Y      = 112,
    GSTYLE_TRANSFORM_SKEW_X       = 113,
    GSTYLE_TRANSFORM_SKEW_Y       = 114,
    GSTYLE_BITMAP_MASK_SRC        = 115,
    GSTYLE_ROTARY_SENSITIVITY     = 116,

#if LV_USE_FLEX
    GSTYLE_FLEX_FLOW              = 125,
    GSTYLE_FLEX_MAIN_PLACE        = 126,
    GSTYLE_FLEX_CROSS_PLACE       = 127,
    GSTYLE_FLEX_TRACK_PLACE       = 128,
    GSTYLE_FLEX_GROW              = 129,
#endif

#if LV_USE_GRID
    GSTYLE_GRID_COLUMN_ALIGN      = 130,
    GSTYLE_GRID_ROW_ALIGN         = 131,
    GSTYLE_GRID_ROW_DSC_ARRAY     = 132,
    GSTYLE_GRID_COLUMN_DSC_ARRAY  = 133,
    GSTYLE_GRID_CELL_COLUMN_POS   = 134,
    GSTYLE_GRID_CELL_COLUMN_SPAN  = 135,
    GSTYLE_GRID_CELL_X_ALIGN      = 136,
    GSTYLE_GRID_CELL_ROW_POS      = 137,
    GSTYLE_GRID_CELL_ROW_SPAN     = 138,
    GSTYLE_GRID_CELL_Y_ALIGN      = 139,
#endif

    _GSTYLE_LAST_BUILT_IN_PROP     = 140,

    _GSTYLE_NUM_BUILT_IN_PROPS     = _GSTYLE_LAST_BUILT_IN_PROP + 1,

    GSTYLE_PROP_ANY                = 0xFF,
    _GSTYLE_PROP_CONST             = 0xFF /* magic value for const styles */
};
typedef uint8_t style_prop_t;

#define style_value_t     lv_style_value_t

typedef enum {
  COLOR_FORMAT_UNKNOWN           = 0,

  COLOR_FORMAT_RAW               = 0x01,
  COLOR_FORMAT_RAW_ALPHA         = 0x02,

    /*<=1 byte (+alpha) formats*/
  COLOR_FORMAT_L8                = 0x06,
  COLOR_FORMAT_MASK              = COLOR_FORMAT_L8,
  COLOR_FORMAT_PRINTER           = COLOR_FORMAT_L8,
  COLOR_FORMAT_I1                = 0x07,
  COLOR_FORMAT_I2                = 0x08,
  COLOR_FORMAT_I4                = 0x09,
  COLOR_FORMAT_I8                = 0x0A,
  COLOR_FORMAT_A8                = 0x0E,

    /*2 byte (+alpha) formats*/
  COLOR_FORMAT_RGB565            = 0x12,
  COLOR_FORMAT_ARGB8565          = 0x13,   /**< Not supported by sw renderer yet. */
  COLOR_FORMAT_RGB565A8          = 0x14,   /**< Color array followed by Alpha array*/
  COLOR_FORMAT_AL88              = 0x15,   /**< L8 with alpha >*/

    /*3 byte (+alpha) formats*/
  COLOR_FORMAT_RGB888            = 0x0F,
  COLOR_FORMAT_ARGB8888          = 0x10,
  COLOR_FORMAT_XRGB8888          = 0x11,

    /*Formats not supported by software renderer but kept here so GPU can use it*/
  COLOR_FORMAT_A1                = 0x0B,
  COLOR_FORMAT_A2                = 0x0C,
  COLOR_FORMAT_A4                = 0x0D,

    /* reference to https://wiki.videolan.org/YUV/ */
    /*YUV planar formats*/
  COLOR_FORMAT_YUV_START         = 0x20,
  COLOR_FORMAT_I420              = LV_COLOR_FORMAT_YUV_START,  /*YUV420 planar(3 plane)*/
  COLOR_FORMAT_I422              = 0x21,  /*YUV422 planar(3 plane)*/
  COLOR_FORMAT_I444              = 0x22,  /*YUV444 planar(3 plane)*/
  COLOR_FORMAT_I400              = 0x23,  /*YUV400 no chroma channel*/
  COLOR_FORMAT_NV21              = 0x24,  /*YUV420 planar(2 plane), UV plane in 'V, U, V, U'*/
  COLOR_FORMAT_NV12              = 0x25,  /*YUV420 planar(2 plane), UV plane in 'U, V, U, V'*/

    /*YUV packed formats*/
  COLOR_FORMAT_YUY2              = 0x26,  /*YUV422 packed like 'Y U Y V'*/
  COLOR_FORMAT_UYVY              = 0x27,  /*YUV422 packed like 'U Y V Y'*/

  COLOR_FORMAT_YUV_END           = LV_COLOR_FORMAT_UYVY,

    /*Color formats in which LVGL can render*/
#if LV_COLOR_DEPTH == 1
  COLOR_FORMAT_NATIVE            = LV_COLOR_FORMAT_I1,
  COLOR_FORMAT_NATIVE_WITH_ALPHA = LV_COLOR_FORMAT_I1,
#elif LV_COLOR_DEPTH == 8
  COLOR_FORMAT_NATIVE            = LV_COLOR_FORMAT_L8,
  COLOR_FORMAT_NATIVE_WITH_ALPHA = LV_COLOR_FORMAT_AL88,
#elif LV_COLOR_DEPTH == 16
  COLOR_FORMAT_NATIVE            = LV_COLOR_FORMAT_RGB565,
  COLOR_FORMAT_NATIVE_WITH_ALPHA = LV_COLOR_FORMAT_RGB565A8,
#elif LV_COLOR_DEPTH == 24
  COLOR_FORMAT_NATIVE            = LV_COLOR_FORMAT_RGB888,
  COLOR_FORMAT_NATIVE_WITH_ALPHA = LV_COLOR_FORMAT_ARGB8888,
#elif LV_COLOR_DEPTH == 32
  COLOR_FORMAT_NATIVE            = LV_COLOR_FORMAT_XRGB8888,
  COLOR_FORMAT_NATIVE_WITH_ALPHA = LV_COLOR_FORMAT_ARGB8888,
#else
#error "LV_COLOR_DEPTH should be 1, 8, 16, 24 or 32"
#endif

} color_format_t;

#define COLOR_FORMAT_GET_SIZE   LV_COLOR_FORMAT_GET_SIZE
#define COLOR_FORMAT_GET_BPP    LV_COLOR_FORMAT_GET_BPP

// #define color_format_t        lv_color_format_t
#define IMAGE_HEADER_MAGIC    LV_IMAGE_HEADER_MAGIC


/**
 * Define a static draw buffer with the given width, height, and color format.
 * Stride alignment is set to LV_DRAW_BUF_STRIDE_ALIGN.
 *
 * For platform that needs special buffer alignment, call LV_DRAW_BUF_INIT_STATIC.
 */
#define DRAW_BUF_DEFINE_STATIC(name, _w, _h, _cf)   LV_DRAW_BUF_DEFINE_STATIC(name, _w, _h, _cf)
#define DRAW_BUF_INIT_STATIC(name)                  LV_DRAW_BUF_INIT_STATIC(name)


// #define DRAW_BUF_DEFINE       LV_DRAW_BUF_DEFINE  
#define vector_dsc_t          lv_vector_dsc_t
#define vector_path_t         lv_vector_path_t
#define vector_dsc_create     lv_vector_dsc_create
#define vector_path_create    lv_vector_path_create

typedef enum {
  VECTOR_PATH_QUALITY_MEDIUM = 0, /* default*/
  VECTOR_PATH_QUALITY_HIGH,
  VECTOR_PATH_QUALITY_LOW,
} vector_path_quality_t;

typedef enum {
  VECTOR_GRADIENT_SPREAD_PAD = 0,
  VECTOR_GRADIENT_SPREAD_REPEAT,
  VECTOR_GRADIENT_SPREAD_REFLECT,
} vector_gradient_spread_t;

typedef lv_gradient_stop_t  gradient_stop_t;

enum {
  /**
   * For RGB map of the image data, mark if it's pre-multiplied with alpha.
   * For indexed image, this bit indicated palette data is pre-multiplied with alpha.
   */
  IMAGE_FLAGS_PREMULTIPLIED    = 0x0001,
  /**
   * The image data is compressed, so decoder needs to decode image firstly.
   * If this flag is set, the whole image will be decompressed upon decode, and
   * `get_area_cb` won't be necessary.
   */
  IMAGE_FLAGS_COMPRESSED       = 0x0008,

  /*Below flags are applicable only for draw buffer header.*/

  /**
   * The image is allocated from heap, thus should be freed after use.
   */
  IMAGE_FLAGS_ALLOCATED        = 0x0010,

  /**
   * If the image data is malloced and can be processed in place.
   * In image decoder post processing, this flag means we modify it in-place.
   */
  IMAGE_FLAGS_MODIFIABLE       = 0x0020,

  /**
   * Flags reserved for user, lvgl won't use these bits.
   */
  IMAGE_FLAGS_USER1            = 0x0100,
  IMAGE_FLAGS_USER2            = 0x0200,
  IMAGE_FLAGS_USER3            = 0x0400,
  IMAGE_FLAGS_USER4            = 0x0800,
  IMAGE_FLAGS_USER5            = 0x1000,
  IMAGE_FLAGS_USER6            = 0x2000,
  IMAGE_FLAGS_USER7            = 0x4000,
  IMAGE_FLAGS_USER8            = 0x8000,
};
typedef uint8_t  image_flags_t;

enum {
  BAR_MODE_NORMAL,
  BAR_MODE_SYMMETRICAL,
  BAR_MODE_RANGE
};
typedef uint8_t bar_mode_t;

typedef enum {
  BAR_ORIENTATION_AUTO,
  BAR_ORIENTATION_HORIZONTAL,
  BAR_ORIENTATION_VERTICAL
} bar_orientation_t;

typedef enum {
  SWITCH_ORIENTATION_AUTO,
  SWITCH_ORIENTATION_HORIZONTAL,
  SWITCH_ORIENTATION_VERTICAL
} switch_orientation_t;


typedef lv_calendar_date_t calendar_date_t;

enum {
  SLIDER_MODE_NORMAL      = BAR_MODE_NORMAL,
  SLIDER_MODE_SYMMETRICAL = BAR_MODE_SYMMETRICAL,
  SLIDER_MODE_RANGE       = BAR_MODE_RANGE
};
typedef uint8_t slider_mode_t;

/**
 * Selects on which sides border should be drawn
 * 'OR'ed values can be used.
 */
typedef enum {
  BORDER_SIDE_NONE     = 0x00,
  BORDER_SIDE_BOTTOM   = 0x01,
  BORDER_SIDE_TOP      = 0x02,
  BORDER_SIDE_LEFT     = 0x04,
  BORDER_SIDE_RIGHT    = 0x08,
  BORDER_SIDE_FULL     = 0x0F,
  BORDER_SIDE_INTERNAL = 0x10, /**< FOR matrix-like objects (e.g. Button matrix)*/
} border_side_t;
#define border_t    lv_border_side_t

typedef enum {
  BASE_DIR_LTR      = 0x00,
  BASE_DIR_RTL      = 0x01,
  BASE_DIR_AUTO     = 0x02,

  BASE_DIR_NEUTRAL  = 0x20,
  BASE_DIR_WEAK     = 0x21,
} base_dir_t;

typedef lv_area_t area_t;

/** Type to store button control bits (disabled, hidden etc.)
 * The first 3 bits are used to store the width*/
typedef enum {
  _BUTTONMATRIX_WIDTH             = 0x000F, /**< Reserved to store the size units*/
  BUTTONMATRIX_CTRL_HIDDEN        = 0x0010, /**< Button hidden*/
  BUTTONMATRIX_CTRL_NO_REPEAT     = 0x0020, /**< Do not repeat press this button.*/
  BUTTONMATRIX_CTRL_DISABLED      = 0x0040, /**< Disable this button.*/
  BUTTONMATRIX_CTRL_CHECKABLE     = 0x0080, /**< The button can be toggled.*/
  BUTTONMATRIX_CTRL_CHECKED       = 0x0100, /**< Button is currently toggled (e.g. checked).*/
  BUTTONMATRIX_CTRL_CLICK_TRIG    = 0x0200, /**< 1: Send LV_EVENT_VALUE_CHANGE on CLICK, 0: Send LV_EVENT_VALUE_CHANGE on PRESS*/
  BUTTONMATRIX_CTRL_POPOVER       = 0x0400, /**< Show a popover when pressing this key*/
  BUTTONMATRIX_CTRL_RESERVED_1    = 0x0800, /**< Reserved for later use*/
  BUTTONMATRIX_CTRL_RESERVED_2    = 0x1000, /**< Reserved for later use*/
  BUTTONMATRIX_CTRL_RESERVED_3    = 0x2000, /**< Reserved for later use*/
  BUTTONMATRIX_CTRL_CUSTOM_1      = 0x4000, /**< Custom free to use flag*/
  BUTTONMATRIX_CTRL_CUSTOM_2      = 0x8000, /**< Custom free to use flag*/

  _KEYBOARD_WIDTH                 = 0x000F, /**< Reserved to store the size units*/
  KEYBOARD_CTRL_HIDDEN            = 0x0010, /**< Button hidden*/
  KEYBOARD_CTRL_NO_REPEAT         = 0x0020, /**< Do not repeat press this button.*/
  KEYBOARD_CTRL_DISABLED          = 0x0040, /**< Disable this button.*/
  KEYBOARD_CTRL_CHECKABLE         = 0x0080, /**< The button can be toggled.*/
  KEYBOARD_CTRL_CHECKED           = 0x0100, /**< Button is currently toggled (e.g. checked).*/
  KEYBOARD_CTRL_CLICK_TRIG        = 0x0200, /**< 1: Send LV_EVENT_VALUE_CHANGE on CLICK, 0: Send LV_EVENT_VALUE_CHANGE on PRESS*/
  KEYBOARD_CTRL_POPOVER           = 0x0400, /**< Show a popover when pressing this key*/
  KEYBOARD_CTRL_RESERVED_1        = 0x0800, /**< Reserved for later use*/
  KEYBOARD_CTRL_RESERVED_2        = 0x1000, /**< Reserved for later use*/
  KEYBOARD_CTRL_RESERVED_3        = 0x2000, /**< Reserved for later use*/
  KEYBOARD_CTRL_CUSTOM_1          = 0x4000, /**< Custom free to use flag*/
  KEYBOARD_CTRL_CUSTOM_2          = 0x8000, /**< Custom free to use flag*/
} buttonmatrix_ctrl_t;
typedef uint32_t keyboard_ctrl_t;

typedef enum {
  KEYBOARD_MODE_TEXT_LOWER,
  KEYBOARD_MODE_TEXT_UPPER,
  KEYBOARD_MODE_SPECIAL,
  KEYBOARD_MODE_NUMBER,
  KEYBOARD_MODE_USER_1,
  KEYBOARD_MODE_USER_2,
  KEYBOARD_MODE_USER_3,
  KEYBOARD_MODE_USER_4,
  
  KEYBOARD_MODE_TH_FULL,
  KEYBOARD_MODE_TH_FULL_SHIFT,
  KEYBOARD_MODE_TH_MINI_0,
  KEYBOARD_MODE_TH                 = KEYBOARD_MODE_TH_MINI_0,
  KEYBOARD_MODE_TH_MINI_ALPHABET   = KEYBOARD_MODE_TH_MINI_0,
  KEYBOARD_MODE_TH_MINI_1,
  KEYBOARD_MODE_TH_MINI_2,
  KEYBOARD_MODE_TH_MINI_3,
  KEYBOARD_MODE_TH_MINI_4,
  KEYBOARD_MODE_TH_MINI_5,
  KEYBOARD_MODE_TH_MINI_SARA       = KEYBOARD_MODE_TH_MINI_5,
  KEYBOARD_MODE_TH_MINI_6,
  KEYBOARD_MODE_TH_MINI_7,
  KEYBOARD_MODE_TH_MINI_8,
  KEYBOARD_MODE_TH_MINI_VANNAYUK   = KEYBOARD_MODE_TH_MINI_8,
  KEYBOARD_MODE_TH_MINI_9,
  KEYBOARD_MODE_TH_MINI_NUMPAD     = KEYBOARD_MODE_TH_MINI_9,
  KEYBOARD_MODE_TH_MINI_10,
  KEYBOARD_MODE_TH_MINI_11,
  KEYBOARD_MODE_TH_MINI_12,

  KEYBOARD_MODE_EN_FULL,
  KEYBOARD_MODE_EN_FULL_SHIFT,
  KEYBOARD_MODE_EN_FULL_NUMPAD,
  KEYBOARD_MODE_EN_MINI_0,
  KEYBOARD_MODE_EN                 = KEYBOARD_MODE_EN_MINI_0,
  KEYBOARD_MODE_EN_MINI_LOWER      = KEYBOARD_MODE_EN_MINI_0,
  KEYBOARD_MODE_EN_MINI_1,
  KEYBOARD_MODE_EN_MINI_2,
  KEYBOARD_MODE_EN_MINI_3,
  KEYBOARD_MODE_EN_MINI_UPPER      = KEYBOARD_MODE_EN_MINI_3,
  KEYBOARD_MODE_EN_MINI_4,
  KEYBOARD_MODE_EN_MINI_5,
  KEYBOARD_MODE_EN_MINI_6,
  KEYBOARD_MODE_NUMPAD             = KEYBOARD_MODE_EN_MINI_6,
  KEYBOARD_MODE_EN_MINI_NUMPAD     = KEYBOARD_MODE_EN_MINI_6,
  KEYBOARD_MODE_EN_MINI_7,
  KEYBOARD_MODE_EN_MINI_8,
  KEYBOARD_MODE_EN_MINI_9,
} keyboard_mode_t;


enum {
  CHART_TYPE_NONE,     /**< Don't draw the series*/
  CHART_TYPE_LINE,     /**< Connect the points with lines*/
  CHART_TYPE_BAR,      /**< Draw columns*/
  CHART_TYPE_SCATTER,  /**< Draw points and lines in 2D (x,y coordinates)*/
  CHART_TYPE_POINT = 4, 
};
typedef uint8_t chart_type_t;

/**
 * Enumeration of the axis'
 */
typedef enum {
  CHART_AXIS_PRIMARY_Y     = 0x00,
  CHART_AXIS_SECONDARY_Y   = 0x01,
  CHART_AXIS_PRIMARY_X     = 0x02,
  CHART_AXIS_SECONDARY_X   = 0x04,
  CHART_AXIS_LAST
} chart_axis_t;

/**
 * Chart update mode for `lv_chart_set_next`
 */
typedef enum {
  CHART_UPDATE_MODE_SHIFT,     /**< Shift old data to the left and add the new one the right*/
  CHART_UPDATE_MODE_CIRCULAR,  /**< Add the new data in a circular way*/
} chart_update_mode_t;

#define chart_series_t  lv_chart_series_t
#define chart_cursor_t  lv_chart_cursor_t
#define chart_rangebar_series_t lv_chart_rangebar_series_t
#define chart_rangebar_cursor_t lv_chart_rangebar_cursor_t

// typedef enum {
//   DIR_NONE     = 0x00,
//   DIR_LEFT     = (1 << 0),
//   DIR_RIGHT    = (1 << 1),
//   DIR_TOP      = (1 << 2),
//   DIR_BOTTOM   = (1 << 3),
//   DIR_HOR      = DIR_LEFT | DIR_RIGHT,
//   DIR_VER      = DIR_TOP | DIR_BOTTOM,
//   DIR_ALL      = DIR_HOR | DIR_VER,
// } dir_t;

enum {
  DIR_NONE     = 0x00,
  DIR_LEFT     = (1 << 0),
  DIR_RIGHT    = (1 << 1),
  DIR_TOP      = (1 << 2),
  DIR_BOTTOM   = (1 << 3),
  DIR_HOR      = DIR_LEFT | DIR_RIGHT,
  DIR_VER      = DIR_TOP | DIR_BOTTOM,
  DIR_ALL      = DIR_HOR | DIR_VER,
};
typedef uint8_t dir_t;


/** Scrollbar modes: shows when should the scrollbars be visible*/
typedef enum {
  SCROLLBAR_MODE_OFF,      /**< Never show scrollbars*/
  SCROLLBAR_MODE_ON,       /**< Always show scrollbars*/
  SCROLLBAR_MODE_ACTIVE,   /**< Show scroll bars when object is being scrolled*/
  SCROLLBAR_MODE_AUTO,     /**< Show scroll bars when the content is large enough to be scrolled*/

  SCROLLBAR_OFF = SCROLLBAR_MODE_OFF,         /**< Never show scrollbars*/
  SCROLLBAR_ON = SCROLLBAR_MODE_ON,           /**< Always show scrollbars*/
  SCROLLBAR_ACTIVE = SCROLLBAR_MODE_ACTIVE,   /**< Show scroll bars when object is being scrolled*/
  SCROLLBAR_AUTO = SCROLLBAR_MODE_AUTO,       /**< Show scroll bars when the content is large enough to be scrolled*/
} scrollbar_mode_t;


/** Scroll span align options. Tells where to align the snappable children when scroll stops.*/
typedef enum {
  SCROLL_SNAP_NONE,    /**< Do not align, leave where it is*/
  SCROLL_SNAP_START,   /**< Align to the left/top*/
  SCROLL_SNAP_END,     /**< Align to the right/bottom*/
  SCROLL_SNAP_CENTER   /**< Align to the center*/
} scroll_snap_t;

/** Can be used to indicate if animations are enabled or disabled in a case*/
enum {
  ANIM_OFF,
  ANIM_ON,
};
typedef uint8_t anim_enable_t;

enum  {
  GRESULT_INVALID = 0, /*Typically indicates that the object is deleted (become invalid) in the action
                      function or an operation was failed*/
  GRESULT_OK,      /*The object is valid (no deleted) after the action*/
};
typedef uint8_t gresult_t;


/**
 * Scale mode
 */
typedef enum {
  SCALE_MODE_HORIZONTAL_TOP    = 0x00U,
  SCALE_MODE_HORIZONTAL_BOTTOM = 0x01U,
  SCALE_MODE_VERTICAL_LEFT     = 0x02U,
  SCALE_MODE_VERTICAL_RIGHT    = 0x04U,
  SCALE_MODE_ROUND_INNER       = 0x08U,
  SCALE_MODE_ROUND_OUTER      = 0x10U,
  SCALE_MODE_LAST,

  SCALE_MODE_HOR_TOP        = SCALE_MODE_HORIZONTAL_TOP,
  SCALE_MODE_HOR_BOTTOM     = SCALE_MODE_HORIZONTAL_BOTTOM,
  SCALE_MODE_VER_LEFT       = SCALE_MODE_VERTICAL_LEFT,
  SCALE_MODE_VER_RIGHT      = SCALE_MODE_VERTICAL_RIGHT,

  SCALE_MODE_TOP            = SCALE_MODE_HORIZONTAL_TOP,
  SCALE_MODE_BOTTOM         = SCALE_MODE_HORIZONTAL_BOTTOM,
  SCALE_MODE_LEFT           = SCALE_MODE_VERTICAL_LEFT,
  SCALE_MODE_RIGHT          = SCALE_MODE_VERTICAL_RIGHT,

  SCALE_MODE_ROUND          = SCALE_MODE_ROUND_INNER,
} scale_mode_t;

#define scale_section_t lv_scale_section_t


typedef enum {
  MENU_HEADER_TOP_FIXED,   /**< Header is positioned at the top */
  MENU_HEADER_TOP_UNFIXED, /**< Header is positioned at the top and can be scrolled out of view*/
  MENU_HEADER_BOTTOM_FIXED /**< Header is positioned at the bottom */
} menu_mode_header_t;

typedef enum {
  MENU_ROOT_BACK_BUTTON_DISABLED,
  MENU_ROOT_BACK_BUTTON_ENABLED
} menu_mode_root_back_button_t;


#define ANIM_REPEAT_INFINITE      LV_ANIM_REPEAT_INFINITE
#define ANIM_PLAYTIME_INFINITE    LV_ANIM_PLAYTIME_INFINITE

#define TFT_BLACK           0x0000      /*   0,   0,   0 */
#define TFT_NAVY            0x000F      /*   0,   0, 128 */
#define TFT_DARKGREEN       0x03E0      /*   0, 128,   0 */
#define TFT_DARKCYAN        0x03EF      /*   0, 128, 128 */
#define TFT_MAROON          0x7800      /* 128,   0,   0 */
#define TFT_PURPLE          0x780F      /* 128,   0, 128 */
#define TFT_OLIVE           0x7BE0      /* 128, 128,   0 */
#define TFT_LIGHTGRAY       0xC618      /* 192, 192, 192 */
#define TFT_DARKGRAY        0x7BEF      /* 128, 128, 128 */ //0xBDD7      // 
#define TFT_BLUE            0x001F      /*   0,   0, 255 */
#define TFT_SKYBLUE         0x867D      /* RGB(135, 206, 235) */
#define TFT_BLUE_LVGL       0x54BB
#define TFT_GREEN           0x07E0      /*   0, 255,   0 */
#define TFT_LIGHTGREEN      0x77F3      /* 113, 253, 115 */
#define TFT_CYAN            0x07FF      /*   0, 255, 255 */
#define TFT_RED             0xF800      /* 255,   0,   0 */
#define TFT_MAGENTA         0xF81F      /* 255,   0, 255 */
#define TFT_YELLOW          0xFFE0      /* 255, 255,   0 */
#define TFT_LIGHTYELLOW     0xFF93      /* 255, 241, 165 */
#define TFT_WHITE           0xFFFF      /* 255, 255, 255 */
// #define TFT_ORANGE          0xF9E0      /* 250,  62,   0 */   // 0xFAE2 /* 255,  94,  19 */   0xFDA0 /* 255, 180,   0 */
#define TFT_ORANGE          0xFBE0
#define TFT_GREENYELLOW     0xB7E0      /* 180, 255,   0 */
#define TFT_PINK            0xFC9F
#define TFT_SADDLEBROWN     0x8A22      /* #8B4513 RGB(139, 69, 19) */
#define TFT_BROWN           0x9A60      /* 150,  75,   0 */

#define TFT_GREENBLYNK      0x2631
#define TFT_REDBLYNK        0xD20B
#define TFT_YELLOWBLYNK     0xF483
#define TFT_BLUEBLYNK       0x529F  //0x061F
#define TFT_VIOLETBLYNK     0x5BD9

#define TFT_DARKGREENBLYNK  0x00c2
#define TFT_DARKREDBLYNK    0x1841
#define TFT_DARKYELLOWBLYNK 0x2080
#define TFT_DARKBLUEBLYNK   0x0844
#define TFT_DARKVIOLETBLYNK 0x0883

#define TFT_GRAY            0x8410
#define TFT_DIMGRAY         0x6B4D
#define TFT_GRAYBLYNK       0x2106
#define TFT_DARKGRAYBLYNK   0x10C3
#define TFT_DARKGRAYBLYNK2  0x1082
#define TFT_SILVER          0xC618

#define TFT_VIOLET          0x6013
#define TFT_DARKVIOLET      0x2004
#define TFT_PIGBLOOD        0x7804
#define TFT_DARKPIGBLOOD    0x2802
#define TFT_DARKYELLOW      0x2940
#define TFT_DARKRED         0x2800
#define TFT_REDGARNET       0x7802  //91A8 //71A6
#define TFT_EMERALD         0x564F  // 0x2B86
#define TFT_BROWN           0x9A60  /* 150,  75,   0 */

#define TFT_OLDROSE         0xFC10
#define TFT_PINK1           0xFC18
#define TFT_OLDGREEN        0x958B
#define TFT_TRANSPARENT     0x07E0



// #define SYMBOL_AUDIO           "\xef\x80\x81"   // \uf001
// #define SYMBOL_VIDEO           "\xef\x80\x88"   // \uf008
// #define SYMBOL_LIST            "\xef\x80\x8b"   // \uf00b
// #define SYMBOL_OK              "\xef\x80\x8c"   // \uf00c
// #define SYMBOL_CLOSE           "\xef\x80\x8d"   // \uf00d
// #define SYMBOL_POWER           "\xef\x80\x91"   // \uf011
// #define SYMBOL_SETTINGS        "\xef\x80\x93"   // \uf013
// #define SYMBOL_TRASH           "\xef\x8B\xAD"   // \uf2ed   old "\xef\x80\x94"   // \uf014
// #define SYMBOL_HOME            "\xef\x80\x95"   // \uf015
// #define SYMBOL_DOWNLOAD        "\xef\x80\x99"   // \uf019

// #define SYMBOL_DRIVE           "\xef\x80\x9c"   // \uf01c
// #define SYMBOL_REFRESH         "\xef\x80\xa1"   // \uf021
// #define SYMBOL_MUTE            "\xef\x80\xa6"   // \uf026
// #define SYMBOL_VOLUME_MID      "\xef\x80\xa7"   // \uf027
// #define SYMBOL_VOLUME_MAX      "\xef\x80\xa8"   // \uf028
// #define SYMBOL_IMAGE           "\xef\x80\xbe"   // \uf03e
// #define SYMBOL_EDIT            "\xef\x81\x80"   // \uf040
// #define SYMBOL_PREV            "\xef\x81\x88"   // \uf048
// #define SYMBOL_PLAY            "\xef\x81\x8b"   // \uf04b
// #define SYMBOL_PAUSE           "\xef\x81\x8c"   // \uf04c
// #define SYMBOL_STOP            "\xef\x81\x8d"   // \uf04d
// #define SYMBOL_NEXT            "\xef\x81\x91"   // \uf051
// #define SYMBOL_EJECT           "\xef\x81\x92"   // \uf052
// #define SYMBOL_LEFT            "\xef\x81\x93"   // \uf053
// #define SYMBOL_RIGHT           "\xef\x81\x94"   // \uf054
// #define SYMBOL_ARROW_LEFT      "\xef\x81\xa0"   // \uf060
// #define SYMBOL_ARROW_RIGHT     "\xef\x81\xa1"   // \uf061
// #define SYMBOL_ARROW_UP        "\xef\x81\xa2"   // \uf062
// #define SYMBOL_ARROW_DOWN      "\xef\x81\xa3"   // \uf063
// #define SYMBOL_PLUS            "\xef\x81\xa7"   // \uf067
// #define SYMBOL_MINUS           "\xef\x81\xa8"   // \uf068

// #define SYMBOL_WARNING         "\xef\x81\xb1"   // \uf071
// #define SYMBOL_SHUFFLE         "\xef\x81\xb4"   // \uf074
// #define SYMBOL_UP              "\xef\x81\xb7"   // \uf077
// #define SYMBOL_DOWN            "\xef\x81\xb8"   // \uf078
// #define SYMBOL_LOOP            "\xef\x81\xb9"   // \uf079
// #define SYMBOL_DIRECTORY       "\xef\x81\xbb"   // \uf07b
// #define SYMBOL_UPLOAD          "\xef\x82\x93"   // \uf093
// #define SYMBOL_CALL            "\xef\x82\x95"   // \uf095
// #define SYMBOL_CUT             "\xef\x83\x84"   // \uf0c4
// #define SYMBOL_COPY            "\xef\x83\x85"   // \uf0c5
// #define SYMBOL_SAVE            "\xef\x83\x87"   // \uf0c7
// #define SYMBOL_CHARGE          "\xef\x83\xa7"   // \uf0e7
// #define SYMBOL_BELL            "\xef\x83\xb3"   // \uf0f3
// #define SYMBOL_KEYBOARD        "\xef\x84\x9c"   // \uf11c
// #define SYMBOL_GPS             "\xef\x84\xa4"   // \uf124
// #define SYMBOL_FILE            "\xef\x85\x9b"   // \uf15b
// #define SYMBOL_ARROW_LONG_LEFT "\xef\x85\xb7"   // \uf177
// #define SYMBOL_WIFI            "\xef\x87\xab"   // \uf1eb
// #define SYMBOL_BATTERY_FULL    "\xef\x89\x80"   // \uf240
// #define SYMBOL_BATTERY_3       "\xef\x89\x81"   // \uf241
// #define SYMBOL_BATTERY_2       "\xef\x89\x82"   // \uf242
// #define SYMBOL_BATTERY_1       "\xef\x89\x83"   // \uf243
// #define SYMBOL_BATTERY_EMPTY   "\xef\x89\x84"   // \uf244
// #define SYMBOL_BLUETOOTH       "\xef\x8a\x93"   // \uf293
// #define SYMBOL_THERMO_4        "\xef\x8b\x87"   // \uf2c7
// #define SYMBOL_THERMO_3        "\xef\x8b\x88"   // \uf2c8
// #define SYMBOL_THERMO_2        "\xef\x8b\x89"   // \uf2c9
// #define SYMBOL_THERMO_1        "\xef\x8b\x8a"   // \uf2ca
// #define SYMBOL_THERMO_0        "\xef\x8b\x8b"   // \uf2cb
// #define SYMBOL_THERMO          SYMBOL_THERMO_4 
// #define SYMBOL_HUMID           "\xEF\x81\x83"   // \uf043
// #define SYMBOL_SHOWER          "\xef\x8b\x8c"   // \uf2cc
// #define SYMBOL_BATHROOM        "\xef\x8b\x8d"   // \uf2cd
// #define SYMBOL_WIFI_1          "\xef\x8b\xa1"   // \uf2e1
// #define SYMBOL_WIFI_2          "\xef\x8b\xa2"   // \uf2e2
// #define SYMBOL_WIFI_3          "\xef\x8b\xa3"   // \uf2e3
// #define SYMBOL_WIFI_4          "\xef\x8b\xa4"   // \uf2e4
// #define SYMBOL_WIFI_NO_CON_1   "\xef\x8b\xa5"   // \uf2e5
// #define SYMBOL_WIFI_NO_CON_2   "\xef\x8b\xa6"   // \uf2e6
// #define SYMBOL_ENTER           "\xef\x8b\xa7"   // \uf2e7     "\xef\x8b\xa1"
// #define SYMBOL_SD_CARD         "\xef\x9F\x82"   /*63426, 0xF7C2*/
// #define SYMBOL_NEW_LINE        SYMBOL_ENTER    //"\xef\xA2\xA2"   /*63650, 0xF8A2*/
// #define SYMBOL_DUMMY           "\xEF\xA3\xBF"   // \uf8ff
// #define SYMBOL_OPTION          "\xef\x85\x82"   // \uf142
// #define SYMBOL_ALARM           "\xef\x8b\xa8"   // \uf2e8
// #define SYMBOL_EYE_OPEN        "\xef\x81\xae"   // \uf06e
// #define SYMBOL_EYE_CLOSE       "\xef\x81\xb0"   // \uf070
// #define SYMBOL_DEGREE          "°"
// #define SYMBOL_MICRO           "µ"
// #define SYMBOL_UMBRELLA        "\xef\x83\xa9"   // \uf0e9
// #define SYMBOL_WALKING         "\xef\x8b\xa9"   // \uf2e9
// #define SYMBOL_BACKSPACE       "\xef\x8b\xaa"   // \uf2ea

#define SYMBOL_AUDIO           "\xEF\x80\x81" /*61441, 0xF001*/
#define SYMBOL_VIDEO           "\xEF\x80\x88" /*61448, 0xF008*/
#define SYMBOL_LIST            "\xEF\x80\x8B" /*61451, 0xF00B*/
#define SYMBOL_OK              "\xEF\x80\x8C" /*61452, 0xF00C*/
#define SYMBOL_CLOSE           "\xEF\x80\x8D" /*61453, 0xF00D*/
#define SYMBOL_POWER           "\xEF\x80\x91" /*61457, 0xF011*/
#define SYMBOL_SETTINGS        "\xEF\x80\x93" /*61459, 0xF013*/
#define SYMBOL_HOME            "\xEF\x80\x95" /*61461, 0xF015*/
#define SYMBOL_DOWNLOAD        "\xEF\x80\x99" /*61465, 0xF019*/
#define SYMBOL_DRIVE           "\xEF\x80\x9C" /*61468, 0xF01C*/
#define SYMBOL_REFRESH         "\xEF\x80\xA1" /*61473, 0xF021*/
#define SYMBOL_MUTE            "\xEF\x80\xA6" /*61478, 0xF026*/
#define SYMBOL_VOLUME_MID      "\xEF\x80\xA7" /*61479, 0xF027*/
#define SYMBOL_VOLUME_MAX      "\xEF\x80\xA8" /*61480, 0xF028*/
#define SYMBOL_IMAGE           "\xEF\x80\xBE" /*61502, 0xF03E*/
#define SYMBOL_TINT            "\xEF\x81\x83" /*61507, 0xF043*/
#define SYMBOL_PREV            "\xEF\x81\x88" /*61512, 0xF048*/
#define SYMBOL_PLAY            "\xEF\x81\x8B" /*61515, 0xF04B*/
#define SYMBOL_PAUSE           "\xEF\x81\x8C" /*61516, 0xF04C*/
#define SYMBOL_STOP            "\xEF\x81\x8D" /*61517, 0xF04D*/
#define SYMBOL_NEXT            "\xEF\x81\x91" /*61521, 0xF051*/
#define SYMBOL_EJECT           "\xEF\x81\x92" /*61522, 0xF052*/
#define SYMBOL_LEFT            "\xEF\x81\x93" /*61523, 0xF053*/
#define SYMBOL_RIGHT           "\xEF\x81\x94" /*61524, 0xF054*/
#define SYMBOL_PLUS            "\xEF\x81\xA7" /*61543, 0xF067*/
#define SYMBOL_MINUS           "\xEF\x81\xA8" /*61544, 0xF068*/
#define SYMBOL_EYE_OPEN        "\xEF\x81\xAE" /*61550, 0xF06E*/
#define SYMBOL_EYE_CLOSE       "\xEF\x81\xB0" /*61552, 0xF070*/
#define SYMBOL_WARNING         "\xEF\x81\xB1" /*61553, 0xF071*/
#define SYMBOL_SHUFFLE         "\xEF\x81\xB4" /*61556, 0xF074*/
#define SYMBOL_UP              "\xEF\x81\xB7" /*61559, 0xF077*/
#define SYMBOL_DOWN            "\xEF\x81\xB8" /*61560, 0xF078*/
#define SYMBOL_LOOP            "\xEF\x81\xB9" /*61561, 0xF079*/
#define SYMBOL_DIRECTORY       "\xEF\x81\xBB" /*61563, 0xF07B*/
#define SYMBOL_UPLOAD          "\xEF\x82\x93" /*61587, 0xF093*/
#define SYMBOL_CALL            "\xEF\x82\x95" /*61589, 0xF095*/
#define SYMBOL_CUT             "\xEF\x83\x84" /*61636, 0xF0C4*/
#define SYMBOL_COPY            "\xEF\x83\x85" /*61637, 0xF0C5*/
#define SYMBOL_SAVE            "\xEF\x83\x87" /*61639, 0xF0C7*/
#define SYMBOL_BARS            "\xEF\x83\x89" /*61641, 0xF0C9*/
#define SYMBOL_ENVELOPE        "\xEF\x83\xA0" /*61664, 0xF0E0*/
#define SYMBOL_CHARGE          "\xEF\x83\xA7" /*61671, 0xF0E7*/
#define SYMBOL_PASTE           "\xEF\x83\xAA" /*61674, 0xF0EA*/
#define SYMBOL_BELL            "\xEF\x83\xB3" /*61683, 0xF0F3*/
#define SYMBOL_KEYBOARD        "\xEF\x84\x9C" /*61724, 0xF11C*/
#define SYMBOL_GPS             "\xEF\x84\xA4" /*61732, 0xF124*/
#define SYMBOL_FILE            "\xEF\x85\x9B" /*61787, 0xF158*/
#define SYMBOL_WIFI            "\xEF\x87\xAB" /*61931, 0xF1EB*/
#define SYMBOL_BATTERY_FULL    "\xEF\x89\x80" /*62016, 0xF240*/
#define SYMBOL_BATTERY_3       "\xEF\x89\x81" /*62017, 0xF241*/
#define SYMBOL_BATTERY_2       "\xEF\x89\x82" /*62018, 0xF242*/
#define SYMBOL_BATTERY_1       "\xEF\x89\x83" /*62019, 0xF243*/
#define SYMBOL_BATTERY_EMPTY   "\xEF\x89\x84" /*62020, 0xF244*/
#define SYMBOL_USB             "\xEF\x8a\x87" /*62087, 0xF287*/
#define SYMBOL_BLUETOOTH       "\xEF\x8a\x93" /*62099, 0xF293*/
#define SYMBOL_TRASH           "\xEF\x8B\xAD" /*62189, 0xF2ED*/
#define SYMBOL_EDIT            "\xEF\x8C\x84" /*62212, 0xF304*/
#define SYMBOL_BACKSPACE       "\xEF\x95\x9A" /*62810, 0xF55A*/
#define SYMBOL_SD_CARD         "\xEF\x9F\x82" /*63426, 0xF7C2*/
#define SYMBOL_NEW_LINE        "\xEF\xA2\xA2" /*63650, 0xF8A2*/
#define SYMBOL_DUMMY           "\xEF\xA3\xBF" /** Invalid symbol at (U+F8FF). If written before a string then `lv_img` will show it as a label*/

#define SYMBOL_THERMO_4        "\xef\x8b\x87"   // \uf2c7
#define SYMBOL_THERMO_3        "\xef\x8b\x88"   // \uf2c8
#define SYMBOL_THERMO_2        "\xef\x8b\x89"   // \uf2c9
#define SYMBOL_THERMO_1        "\xef\x8b\x8a"   // \uf2ca
#define SYMBOL_THERMO_0        "\xef\x8b\x8b"   // \uf2cb
#define SYMBOL_THERMO          SYMBOL_THERMO_4 
#define SYMBOL_HUMID           "\xEF\x81\x83"   // \uf043
#define SYMBOL_SHOWER          "\xef\x8b\x8c"   // \uf2cc
#define SYMBOL_BATHROOM        "\xef\x8b\x8d"   // \uf2cd
#define SYMBOL_WIFI_1          "\xef\x8b\xa1"   // \uf2e1
#define SYMBOL_WIFI_2          "\xef\x8b\xa2"   // \uf2e2
#define SYMBOL_WIFI_3          "\xef\x8b\xa3"   // \uf2e3
#define SYMBOL_WIFI_4          "\xef\x8b\xa4"   // \uf2e4
#define SYMBOL_WIFI_NO_CON_1   "\xef\x8b\xa5"   // \uf2e5
#define SYMBOL_WIFI_NO_CON_2   "\xef\x8b\xa6"   // \uf2e6
#define SYMBOL_ENTER           "\xef\x8b\xa7"   // \uf2e7     "\xef\x8b\xa1"
#define SYMBOL_OPTION          "\xef\x85\x82"   // \uf142
#define SYMBOL_ALARM           "\xef\x8b\xa8"   // \uf2e8
#define SYMBOL_DEGREE          "°"
#define SYMBOL_MICRO           "µ"
#define SYMBOL_UMBRELLA        "\xef\x83\xa9"   // \uf0e9
#define SYMBOL_WALKING         "\xef\x8b\xa9"   // \uf2e9
#define SYMBOL_BACKSPACE       "\xef\x8b\xaa"   // \uf2ea


#define SYMBOL_ARROW_LEFT      "\xef\x81\xa0"   // \uf060
#define SYMBOL_ARROW_RIGHT     "\xef\x81\xa1"   // \uf061
#define SYMBOL_ARROW_UP        "\xef\x81\xa2"   // \uf062
#define SYMBOL_ARROW_DOWN      "\xef\x81\xa3"   // \uf063

#define SYMBOL_SHIFT           "\xEF\x8B\xBA"   /*62202, 0xF2FA*/
#define SYMBOL_SHIFT_UP        "\xEF\x8B\xBB"   /*62203, 0xF2FB*/


#ifndef FONT_DECLARE
#define FONT_DECLARE          LV_FONT_DECLARE
#endif

#ifndef IMG_DECLARE
#define IMG_DECLARE           LV_IMG_DECLARE
#define IMAGE_DECLARE         LV_IMG_DECLARE
#endif

#endif //__BLYNKGO_TYPE_H__
