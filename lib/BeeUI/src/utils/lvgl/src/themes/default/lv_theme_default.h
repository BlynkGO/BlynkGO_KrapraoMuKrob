/**
 * @file lv_theme_default.h
 *
 */

#ifndef LV_THEME_DEFAULT_H
#define LV_THEME_DEFAULT_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lv_theme.h"

#if LV_USE_THEME_DEFAULT

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
// BlynkGO
typedef struct {
    lv_style_t scr;
    lv_style_t scrollbar;
    lv_style_t scrollbar_scrolled;
    lv_style_t card;
    lv_style_t btn;

    /*Utility*/
    lv_style_t bg_color_primary;
    lv_style_t bg_color_primary_muted;
    lv_style_t bg_color_secondary;
    lv_style_t bg_color_secondary_muted;
    lv_style_t bg_color_grey;
    lv_style_t bg_color_white;
    lv_style_t pressed;
    lv_style_t disabled;
    lv_style_t pad_zero;
    lv_style_t pad_tiny;
    lv_style_t pad_small;
    lv_style_t pad_normal;
    lv_style_t pad_gap;
    lv_style_t line_space_large;
    lv_style_t text_align_center;
    lv_style_t outline_primary;
    lv_style_t outline_secondary;
    lv_style_t circle;
    lv_style_t no_radius;
    lv_style_t clip_corner;
    lv_style_t rotary_scroll;
#if LV_THEME_DEFAULT_GROW
    lv_style_t grow;
#endif
    lv_style_t transition_delayed;
    lv_style_t transition_normal;
    lv_style_t anim;
    lv_style_t anim_fast;

    /*Parts*/
    lv_style_t knob;

#if LV_USE_ARC
    lv_style_t arc_indic;
    lv_style_t arc_indic_primary;
#endif

#if LV_USE_CHART
    lv_style_t chart_series, chart_indic, chart_bg;
#endif

#if LV_USE_DROPDOWN
    lv_style_t dropdown_list;
#endif

#if LV_USE_CHECKBOX
    lv_style_t cb_marker, cb_marker_checked;
#endif

#if LV_USE_SWITCH
    lv_style_t switch_knob;
#endif

#if LV_USE_LINE
    lv_style_t line;
#endif

#if LV_USE_TABLE
    lv_style_t table_cell;
#endif

#if LV_USE_TEXTAREA
    lv_style_t ta_cursor, ta_placeholder;
#endif

#if LV_USE_CALENDAR
    lv_style_t calendar_btnm_bg, calendar_btnm_day, calendar_header;
#endif

#if LV_USE_MENU
    lv_style_t menu_bg, menu_cont, menu_sidebar_cont, menu_main_cont, menu_page, menu_header_cont, menu_header_btn,
               menu_section, menu_pressed, menu_separator;
#endif

#if LV_USE_MSGBOX
    lv_style_t msgbox_backdrop_bg;
#endif

#if LV_USE_KEYBOARD
    lv_style_t keyboard_button_bg;
#endif

#if LV_USE_LIST
    lv_style_t list_bg, list_btn, list_item_grow;
#endif

#if LV_USE_TABVIEW
    lv_style_t tab_bg_focus, tab_btn;
#endif
#if LV_USE_LED
    lv_style_t led;
#endif

#if LV_USE_SCALE
    lv_style_t scale;
#endif
} default_theme_styles_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize the theme
 * @param disp pointer to display
 * @param color_primary the primary color of the theme
 * @param color_secondary the secondary color for the theme
 * @param dark
 * @param font pointer to a font to use.
 * @return a pointer to reference this theme later
 */
lv_theme_t * lv_theme_default_init(lv_display_t * disp, lv_color_t color_primary, lv_color_t color_secondary, bool dark,
                                   const lv_font_t * font);

/**
 * Get default theme
 * @return a pointer to default theme, or NULL if this is not initialized
 */
lv_theme_t * lv_theme_default_get(void);

/**
 * Check if default theme is initialized
 * @return true if default theme is initialized, false otherwise
 */
bool lv_theme_default_is_inited(void);

/**
 * Deinitialize the default theme
 */
void lv_theme_default_deinit(void);

// BlynkGO
const default_theme_styles_t* lv_theme_default_get_styles(void);

/**********************
 *      MACROS
 **********************/

#endif

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_THEME_DEFAULT_H*/
