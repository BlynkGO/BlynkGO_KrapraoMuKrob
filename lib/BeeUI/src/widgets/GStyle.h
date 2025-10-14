/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GStyle.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GSTYLE_H__
#define __GSTYLE_H__

#include <Arduino.h>
#include "GUtils.h"
#include "GLVGL.h"
#include <memory>
#include <cstdlib>
#include <cstddef>

#include "GTransition.h"
// #include "GAnimation.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GStyle {
  public:
    GStyle();
    // GStyle(style_t *style_copy);      // จะ alloc + copy ในตัว
    // GStyle(GStyle &GStyle_copy);      // จะ alloc + copy ในตัว
    ~GStyle();

    void        create(style_t* copy_style=NULL);
    inline bool isCreated()       {  return ((this->_raw_style != NULL ) || (this->_sh_raw_style.get() !=nullptr)); }  
    void        reset();

    GStyle &  operator=(style_t& style);


#if 0
    void        corner_radius(int32_t r);
    inline void corner_radius(int32_t r, bool corner_mask) {
      this->corner_radius(r);
      this->corner_mask(corner_mask);
    }

    inline void radius(int32_t r)                    { this->corner_radius(r); }
    inline void radius(int32_t r, bool corner_mask)  { this->corner_radius(r, corner_mask); }

    void        clip_corner(bool enable);
    inline void corner_mask(bool enable)              { this->clip_corner(enable); }

    inline void size(int32_t w, int32_t h)            { this->width(w); this->height(h); }
    void        width(int32_t w);
    void        min_width(int32_t w);
    void        max_width(int32_t w);
    void        height(int32_t h);
    void        min_height(int32_t h);
    void        max_height(int32_t h);
// #endif

    void        posX(int32_t x);
    void        posY(int32_t y);
    inline void position(int32_t x, int32_t y)        { this->posX(x); this->posY(y); }
    void        transform_width(int32_t w);
    void        transform_height(int32_t h);
    void        transform_zoom(int32_t zoom);
    void        transform_angle(int32_t angle);
    void        translate_x(int32_t x);
    void        translate_y(int32_t x);
    void        transform_pivot_x(int32_t pivot_x);
    void        transform_pivot_y(int32_t pivot_y);

// #if 0
    void        color(color_t color);
    void        color(color_t color, color_t grad_color, uint8_t frac_color=0, uint8_t frac_grad_color=255);
    color_t     color();
    void        grad_color(color_t color);
    color_t     grad_color();
    void        grad_dir(grad_dir_t type);
    grad_dir_t  grad_dir();
    void        opa( uint8_t opa);
    void        border(int32_t border_width);
    void        border(int32_t border_width, color_t color);
    void        border_color(color_t color);
    void        border_opa(uint8_t opa);
    void        border_side(border_side_t side);
    void        border_post(bool value);

    void        bg_image(const img_t& img);
    void        bg_image(const img_t* img);
    void        bg_image_opa(uint8_t opa);
    void        bg_image_tiled(bool enable );

    void        shadow(int32_t width);
    void        shadow(int32_t width, color_t color);
    void        shadow_offset(int32_t offset_x, int32_t offset_y);
    void        shadow_spread(int32_t shadow_spread);
    void        shadow_color(color_t color);

    void        padding_top(int32_t padding_top);
    void        padding_bottom(int32_t padding_bottom);
    void        padding_left(int32_t padding_left);
    void        padding_right(int32_t padding_right);
    void        padding_row(int32_t padding_row);
    void        padding_column(int32_t padding_column);

    void        line_width(int32_t line_width);
    void        line_color(color_t line_color);
    void        line_rounded(bool rounded);
    void        line_dash_width(int32_t dash_width);
    void        line_dash_gap(int32_t dash_gap);
    void        line_opa(uint8_t opa);

    void        text_font(const font_t * font);
    inline void text_font(const font_t  &font)                  {  this->text_font(&font);                          }
    inline void text_font(const font_t * font, color_t color)   {  this->text_font( font); this->text_color(color); }
    inline void text_font(const font_t  &font, color_t color)   {  this->text_font(&font, color);                   }
    
    inline void font(const font_t * font)                       {  this->text_font(font);                           }
    inline void font(const font_t  &font)                       {  this->text_font(font);                           }
    inline void font(const font_t * font, color_t color)        {  this->text_font(font); this->text_color(color);  }
    inline void font(const font_t  &font, color_t color)        {  this->text_font(font, color);                    }

    void        text_opa(uint8_t opa);
    void        text_color(color_t color);
    inline void font_color(color_t color)                       {  this->text_color(color);                         }
    void        text_letter_space(int32_t letter_space);
    void        text_line_space(int32_t line_space);
    // void        text_decor(text_decor_t value);
    // void        text_align(text_align_t text_align);

    void        outline_width(int32_t width);
    inline void outline(int32_t width)                          { this->outline_width(width);                             }
    inline void outline(int32_t width, color_t color)           { this->outline_width(width); this->outline_color(color); }
    void        outline_opa(uint8_t opa);
    void        outline_color(color_t color);

    void        anim_speed(int32_t value);
    inline void anim_duration(int32_t value)                   { this->anim_speed(value);                          }


    inline void padding_inner(int32_t padding_inner)    {  
      this->padding_row(padding_inner); 
      this->padding_column(padding_inner); 
    }

    inline void padding(int32_t padding_top, int32_t padding_bottom, int32_t padding_left, int32_t padding_right, int32_t padding_inner){
      this->padding_top(padding_top);
      this->padding_bottom(padding_bottom);
      this->padding_left(padding_left);
      this->padding_right(padding_right);
      this->padding_inner(padding_inner);
    }

    inline void padding(int32_t padding_top, int32_t padding_bottom, int32_t padding_left, int32_t padding_right, int32_t padding_row, int32_t padding_column){
      this->padding_top(padding_top);
      this->padding_bottom(padding_bottom);
      this->padding_left(padding_left);
      this->padding_right(padding_right);
      this->padding_row(padding_row); 
      this->padding_column(padding_column); 
    }

    inline void padding(int32_t padding) {
      this->padding(padding,padding,padding,padding,padding,padding);
    }

    void        flex_grow(uint8_t value);
    // void        flex_flow(flex_flow_t value);
    // void        flex_main_place(flex_align_t value);
    // void        flex_cross_place(flex_align_t value);
    // void        flex_track_place(flex_align_t value);
  #endif //0


    // GStyle& operator=(GStyle& gstyle_src);

    // // void    setProperty(style_prop_t style_prop, style_value_t value);
    // // bool    getProperty(style_prop_t style_prop, style_value_t * value);
    // // bool    removeProperty(style_prop_t style_prop);
    // bool    isEmptyProperty();

    // void    copyStyle(GStyle& style_src);
    // inline void copyStyle(GStyle* style_src)        { this->copyStyle(*style_src); }

    inline style_t* raw()           { return (this->_raw_style !=NULL)? _raw_style : this->_sh_raw_style.get();  }
    inline bool is_gradient()       { return this->_u_grad_dsc.get() !=nullptr; }  // unique_ptr check

    void transition(GTransition &transition);


    /**
     * Initialize a style
     * @note Do not call `init` on styles that already have some properties
     *       because this function won't free the used memory, just sets a default state for the style.
     *       In other words be sure to initialize styles only once!
     */
    void init();

    /**
     * Clear all properties from a style and free all allocated memories.
     */
    void _reset();

    /**
     * Check if a style is constant
     * @return          true: the style is constant
     */
    bool is_const();

    /**
     * Register a new style property for custom usage
     * @return a new property ID, or STYLE_PROP_INV if there are no more available.
     * @example
     * style_prop_t MY_PROP;
     * static inline void style.set_my_prop(color_t value) {
     * style_value_t v = {.color = value}; style.set_prop(MY_PROP, v); }
     *
     * ...
     * MY_PROP = style.register_prop();
     * ...
     * style.set_my_prop(TFT_PALETTE(TFT_PALETTE_RED));
     */
    static style_prop_t register_prop(uint8_t flag);

    /**
     * Get the number of custom properties that have been registered thus far.
     */
    static style_prop_t num_custom_props(void);

    /**
     * Remove a property from a style
     * @param prop  a style property ORed with a state.
     * @return true: the property was found and removed; false: the property wasn't found
     */
    bool remove_prop(style_prop_t prop);

    /**
     * Set the value of property in a style.
     * This function shouldn't be used directly by the user.
     * Instead use `style.set_<prop_name>()`. E.g. `style.bg_color()`
     * @param prop the ID of a property (e.g. `STYLE_BG_COLOR`)
     * @param value `style_value_t` variable in which a field is set according to the type of `prop`
     */
    void set_prop(style_prop_t prop, style_value_t value);

    /**
     * Get the value of a property
     * @param prop  the ID of a property
     * @param value pointer to a `style_value_t` variable to store the value
     * @return RESULT_INVALID: the property wasn't found in the style (`value` is unchanged)
     *         RESULT_OK: the property was fond, and `value` is set accordingly
     * @note For performance reasons there are no sanity check on `style`
     */
    style_res_t get_prop(style_prop_t prop, style_value_t * value);

    /**
     * Initialize a transition descriptor.
     * @param tr        pointer to a transition descriptor to initialize
     * @param props     an array with the properties to transition. The last element must be zero.
     * @param path_cb   an animation path (ease) callback. If `NULL` liner path will be used.
     * @param time      duration of the transition in [ms]
     * @param delay     delay before the transition in [ms]
     * @param user_data any custom data that will be saved in the transition animation and will be available when `path_cb` is called
     * @example
     * const static style_prop_t trans_props[] = { STYLE_BG_OPA, STYLE_BG_COLOR, 0 };
     *  static style_transition_t trans1;
     *  lv_style_transition_dsc_init(&trans1, trans_props, NULL, 300, 0, NULL);
     */
    static void transition_init(style_transition_t * tr, const style_prop_t props[],
                                      lv_anim_path_cb_t path_cb, uint32_t time, uint32_t delay=0, void * user_data=NULL);

     /**
     * Get the default value of a property
     * @param prop the ID of a property
     * @return the default value
     */
    static style_value_t prop_get_default(style_prop_t prop);

    /**
     * Get the value of a property
     * @param prop  the ID of a property
     * @param value pointer to a `lv_style_value_t` variable to store the value
     * @return LV_RESULT_INVALID: the property wasn't found in the style (`value` is unchanged)
     *         LV_RESULT_OK: the property was fond, and `value` is set accordingly
     * @note For performance reasons there are no sanity check on `style`
     * @note This function is the same as ::lv_style_get_prop but inlined. Use it only on performance critical places
     */
    style_res_t get_prop_inlined(style_prop_t prop, style_value_t * value);

    /**
     * Checks if a style is empty (has no properties)
     * @return true if the style is empty
     */
    bool is_empty();

    // // /**
    // //  * Tell the group of a property. If the a property from a group is set in a style the (1 << group) bit of style->has_group is set.
    // //  * It allows early skipping the style if the property is not exists in the style at all.
    // //  * @param prop a style property
    // //  * @return the group [0..30] 30 means all the custom properties with index > 120
    // //  */
    // // static inline uint32_t _lv_style_get_prop_group(lv_style_prop_t prop)
    // // {
    // //     uint32_t group = prop >> 2;
    // //     if(group > 30) group = 31;    /*The MSB marks all the custom properties*/
    // //     return group;

    // // }

    // // /**
    // //  * Get the flags of a built-in or custom property.
    // //  *
    // //  * @param prop a style property
    // //  * @return the flags of the property
    // //  */
    // // uint8_t _lv_style_prop_lookup_flags(lv_style_prop_t prop);

    // // #include "lv_style_gen.h"

    // inline void _size(int32_t width, int32_t height)             { lv_style_set_size(this->raw(), width, height);    }
    // inline void pad_all(int32_t value)                          { lv_style_set_pad_all(this->raw(), value);         }
    // inline void pad_hor(int32_t value)                          { lv_style_set_pad_hor(this->raw(), value);         }
    // inline void pad_ver(int32_t value)                          { lv_style_set_pad_ver(this->raw(), value);         }
    // inline void pad_gap(int32_t value)                          { lv_style_set_pad_gap(this->raw(), value);         }
    // inline void transform_scale(int32_t value)                  { lv_style_set_transform_scale(this->raw(), value); }
    // inline bool prop_has_flag(style_prop_t prop, uint8_t flag)  { return lv_style_prop_has_flag(prop, flag);        }


    void width(int32_t value);
    void min_width(int32_t value);
    void max_width(int32_t value);
    void height(int32_t value);
    void min_height(int32_t value);
    void max_height(int32_t value);
    void length(int32_t value);
    void x(int32_t value);
    void y(int32_t value);
    void align(align_t value);
    void transform_width(int32_t value);
    void transform_height(int32_t value);
    void translate_x(int32_t value);
    void translate_y(int32_t value);
    void transform_scale_x(int32_t value);
    void transform_scale_y(int32_t value);
    void transform_rotation(int32_t value);
    void transform_pivot_x(int32_t value);
    void transform_pivot_y(int32_t value);
    void transform_skew_x(int32_t value);
    void transform_skew_y(int32_t value);
    void pad_top(int32_t value);
    void pad_bottom(int32_t value);
    void pad_left(int32_t value);
    void pad_right(int32_t value);
    void pad_row(int32_t value);
    void pad_column(int32_t value);

    inline void padding(int32_t value) {
      pad_top(value); pad_bottom(value); pad_left(value); pad_right(value); pad_row(value); pad_column(value);
    }

    inline void padding(int32_t top, int32_t bottom, int32_t left, int32_t right ) {
      pad_top(top); pad_bottom(bottom); pad_left(left); pad_right(right);
    }

    inline void padding(int32_t top, int32_t bottom, int32_t left, int32_t right, int32_t inner ) {
      pad_top(top); pad_bottom(bottom); pad_left(left); pad_right(right); pad_row(inner); pad_column(inner);
    }

    inline void padding(int32_t top, int32_t bottom, int32_t left, int32_t right, int32_t row, int32_t column ) {
      pad_top(top); pad_bottom(bottom); pad_left(left); pad_right(right); pad_row(row); pad_column(column);
    }

    inline void pad(int32_t value) {
      padding(value);
    }

    inline void pad(int32_t top, int32_t bottom, int32_t left, int32_t right ) {
      padding(top, bottom, left, right);
    }

    inline void pad(int32_t top, int32_t bottom, int32_t left, int32_t right, int32_t inner ) {
      padding(top, bottom, left, right, inner);
    }

    inline void pad(int32_t top, int32_t bottom, int32_t left, int32_t right, int32_t row, int32_t column ) {
      padding(top, bottom, left, right, row, column);
    }

    inline void pad_ver(int32_t ver) {
      pad_top(ver); pad_bottom(ver); 
    }

    inline void pad_hor(int32_t hor) {
      pad_left(hor); pad_right(hor); 
    }

    void margin_top(int32_t value);
    void margin_bottom(int32_t value);
    void margin_left(int32_t value);
    void margin_right(int32_t value);

    inline void margin(int32_t value) {
      margin_top(value); margin_bottom(value); margin_left(value); margin_right(value);
    }

    inline void margin(int32_t top, int32_t bottom, int32_t left, int32_t right ) {
      margin_top(top); margin_bottom(bottom); margin_left(left); margin_right(right);
    }

    void bg_color(color_t value);
    void bg_opa(opa_t value);
    void bg_grad_color(color_t value);
    void bg_grad_dir(lv_grad_dir_t value);
    void bg_main_stop(int32_t value);
    void bg_grad_stop(int32_t value);
    void bg_main_opa(opa_t value);
    void bg_grad_opa(opa_t value);
    void bg_grad(const lv_grad_dsc_t * value);

    inline void color(color_t value)                              { this->bg_color(value);                        }
    inline void grad_color(color_t value)                         { this->bg_grad_color(value);                   }
    inline void grad_dir(grad_dir_t value)                        { this->bg_grad_dir((lv_grad_dir_t) value);     }
    inline void main_stop(int32_t value)                          { this->bg_main_stop(value);                    }
    inline void grad_stop(int32_t value)                          { this->bg_grad_stop(value);                    }
    inline void main_opa(opa_t value)                             { this->bg_main_opa(value);                     }
    inline void grad_opa(opa_t value)                             { this->bg_grad_opa(value);                     }
    inline void grad(const grad_dsc_t * value)                    { this->bg_grad(value);                         }

    void bg_image_src(const void * value);
    void bg_image_opa(opa_t value);
    void bg_image_recolor(color_t value);
    void bg_image_recolor_opa(opa_t value);
    void bg_image_tiled(bool value);
    void border_color(color_t value);
    void border_opa(opa_t value);
    void border_width(int32_t value);
    inline void border(int32_t value)                             { this->border_width(value);                              }
    inline void border(int32_t value, color_t color)              { this->border(value); this->border_color(color);         }
    void border_side(lv_border_side_t value);
    void border_post(bool value);
    void outline_width(int32_t value);
    inline void outline(int32_t value)                            { this->outline_width(value);                             }
    inline void outline(int32_t value, color_t color)             { this->outline(value); this->outline_color(color);       }
    void outline_color(color_t value);
    void outline_opa(opa_t value);
    void outline_pad(int32_t value);
    void shadow_width(int32_t value);
    inline void shadow(int32_t value)                             { this->shadow_width(value);                              }
    inline void shadow(int32_t value, color_t color)              { this->shadow(value); this->shadow_color(color);         }
    void shadow_offset_x(int32_t value);
    void shadow_offset_y(int32_t value);
    inline void shadow_offset(int32_t ofx, int32_t ofy)           { this->shadow_offset_x(ofx); this->shadow_offset_y(ofy); }
    void shadow_spread(int32_t value);
    void shadow_color(color_t value);
    void shadow_opa(opa_t value);
    void image_opa(opa_t value);
    void image_recolor(color_t value);
    void image_recolor_opa(opa_t value);
    void line_width(int32_t value);
    void line_dash_width(int32_t value);
    void line_dash_gap(int32_t value);
    void line_rounded(bool value);
    void line_color(color_t value);
    void line_opa(opa_t value);
    void arc_width(int32_t value);
    void arc_rounded(bool value);
    void arc_color(color_t value);
    void arc_opa(opa_t value);
    void arc_image_src(const void * value);
    void text_color(color_t value);
    void text_opa(opa_t value);
    void text_font(const font_t * value);
    void text_letter_space(int32_t value);
    void text_line_space(int32_t value);
    void text_decor(text_decor_t value);
    void text_align(text_align_t value);

    inline void text_font(const font_t& value)                { this->text_font(&value);                          }
    inline void text_font(const font_t& value, color_t color) { this->text_font(&value); this->text_color(color); }
    inline void font(const font_t &value)                     { this->text_font(&value);                          }
    inline void font(const font_t &value, color_t color)      { this->text_font(&value); this->text_color(color); }
    inline void font_color(color_t color)                     { this->text_color(color);                          }

    void radius(int32_t value);
    void clip_corner(bool value);
    void opa(opa_t value);
    void opa_layered(opa_t value);
    void color_filter_dsc(const lv_color_filter_dsc_t * value);
    void color_filter_opa(opa_t value);
    void anim(const lv_anim_t * value);
    void anim_duration(uint32_t value);
    void transition(const lv_style_transition_dsc_t * value);
    void blend_mode(lv_blend_mode_t value);
    void layout(uint16_t value);
    void base_dir(base_dir_t value);
    void bitmap_mask_src(const img_t * value);
    inline void mask(const img_t * value)                   { this->bitmap_mask_src(value);   }
    inline void mask(const img_t & value)                   { this->bitmap_mask_src(&value);  }
    void rotary_sensitivity(uint32_t value);

    #if LV_USE_FLEX
        void flex_flow(lv_flex_flow_t value);
        void flex_main_place(lv_flex_align_t value);
        void flex_cross_place(lv_flex_align_t value);
        void flex_track_place(lv_flex_align_t value);
        void flex_grow(uint8_t value);
    #endif /*LV_USE_FLEX*/

    #if LV_USE_GRID

        void grid_column_dsc_array(const int32_t * value);
        void grid_column_align(lv_grid_align_t value);
        void grid_row_dsc_array(const int32_t * value);
        void grid_row_align(lv_grid_align_t value);
        void grid_cell_column_pos(int32_t value);
        void grid_cell_x_align(lv_grid_align_t value);
        void grid_cell_column_span(int32_t value);
        void grid_cell_row_pos(int32_t value);
        void grid_cell_y_align(lv_grid_align_t value);
        void grid_cell_row_span(int32_t value);
    #endif /*LV_USE_GRID*/

    std::shared_ptr<style_t>        _sh_raw_style;
    style_t *_raw_style = NULL;
    std::unique_ptr<lv_grad_dsc_t>  _u_grad_dsc;
    // bool     _created = false;


  private:
    void     alloc_grad_dsc();    // จอง mem สำหรับ grad_dsc แล้วทำการเชื่อมเข้ากับ style

    // style_t  *copy_style = NULL;
    // GStyle   *copy_gstyle = NULL;
    bool     _link_style = false;

    lv_color_t  _bg_color = lv_color_white();
};


//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------


#endif //__GSTYLE_H__
