/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GObject.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GOBJECT_H__
#define __GOBJECT_H__


#include <Arduino.h>
#include "GUtils.h"
#include "GLVGL.h"
#include "GStyle.h"
#include "Point.h"
#include "../utils/BlynkGO_Type.h"
#if defined ESP32
#include "../utils/TridentTD_ESP32NVS/TridentTD_ESP32NVS.h"  // ESP32 NVS
#endif

#if LV_USE_SDL
extern lv_indev_t * mouse;
extern lv_indev_t * mousewheel;
extern lv_indev_t * pc_keyboard;
#endif

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------


class   GObject;
extern  GObject   GScreen;

#ifndef GWidget
#define GWidget   GObject
#endif

#ifndef GRect
#define GRect     GObject
#endif

typedef std::vector<int32_t> v_grid_dsc;
#define GRID_COL    v_grid_dsc
#define GRID_ROW    v_grid_dsc

#define FLAG_TOP    FLAG_USER_4


typedef void (*event_cb_t)      (GWidget* widget, event_t event);
typedef void (*event_handler_t) (GWidget* parent);
void main_event_cb(lv_event_t * event);

#if LV_USE_SDL
extern lv_group_t * empty_group;
extern lv_group_t * pc_keyboard_group;
#endif

// point_t touch_pt();   //absolute touch point

class GObject  {
  public:
    GObject(GWidget& parent=GScreen)                        : _par(&parent) {}
    GObject(GWidget* parent)                                : _par( parent) {}
    virtual ~GObject();             /* virtual = ทำลาย ของ derived แล้วค่อย มาทำลายตัว หลัก */

    virtual void    create();
    inline  void    create(GWidget& parent)                 { this->_par = &parent; this->create();               }
    inline  void    create(GWidget* parent)                 { this->_par =  parent; this->create();               }

    virtual void    del();          /* ลบแบบปกติสำหรับ GWidget ใดๆที่สร้างแบบปกติ ไม่ได้สร้างด้วย new ; virtual = ไป del() ของ derived แทน ถ้ามี  */
    // bool            isCreated()                             { return this->_created;        }
    bool            isCreated();
    void            setObject(obj_t * obj);
    inline void     link(obj_t* obj)                        { this->setObject(obj);         }
    inline void     link(GWidget& widget)                   { this->setObject(widget.obj);  }

    bool            sameWith(GWidget &base);
    bool            sameWith(GWidget *base);
    bool            operator ==(GWidget &base);
    bool            operator ==(GWidget *base);
    bool            operator !=(GWidget &base);
    void            operator =(obj_t *obj);

    inline void     user_data(void* user_data)              { this->_user_data = user_data; }
    inline void*    user_data()                             { return this->_user_data;      }
 
  
   /* --------- Parent & Child API ------- */
    void            parent(GWidget* parent);
    void            parent(GWidget& parent);
    void            parent(obj_t* parent);
    inline GWidget* parent()                                { return this->_par;            }

    uint32_t        child_num();
    GWidget*        child(uint32_t child_id);      // child_id : 0 ถึง น้อยกว่า child_num()
    int32_t         child_id(GWidget*widget);      // ติดลบแสดงว่าไม่ได้เป็น child ของ layer นี้

    void            toForeground();
    void            toBackground();
    void            layer_id(int32_t layer_id);    // layer_id : 0 ถึง น้อยกว่า child_num() ถ้า -1 นับย้อนกลับ
    int32_t         layer_id();
    
    void            align(align_t align, int32_t x_ofs=0, int32_t y_ofs=0);
    void            align(GWidget* widget, align_t align, int32_t x_ofs=0, int32_t y_ofs=0);    
    inline void     align(GWidget& widget, align_t align, int32_t x_ofs=0, int32_t y_ofs=0)           { this->align(&widget, align, x_ofs, y_ofs);  }
    inline void     align_center( int32_t x_ofs=0, int32_t y_ofs=0)                                   { this->align(ALIGN_CENTER, x_ofs, y_ofs);    }
    void            realign();


    inline void     position(int32_t x, int32_t y)          { this->_align(ALIGN_TOP_LEFT); this->pos(x,y);     }
    inline void     position(Point p)                       { this->position(p.x,p.y);                          }     // ตำแหน่ง (x,y) ของวิตเจ็ต นับจาก (0,0) ของ parent
    inline Point    position()                              { return Point(this->get_x(), this->get_y());       }     // ตำแหน่ง (x,y) ของวิตเจ็ต นับจาก (0,0) ของ parent

    inline void     posX(int32_t x)                         { this->set_x(x);                                   }
    inline void     posY(int32_t y)                         { this->set_y(y);                                   }
    inline int32_t  posX()                                  { return this->get_x();                             }
    inline int32_t  posY()                                  { return this->get_y();                             }
    inline void     update_position()                       { this->position(this->get_x(), this->get_y());     }

    inline int32_t  leftX()                                 { return this->get_x();                             }
    inline int32_t  rightX()                                { return this->get_x2();                            }
    inline int32_t  topY()                                  { return this->get_y();                             }
    inline int32_t  bottomY()                               { return this->get_y2();                            }
    inline int32_t  centerX()                               { return (this->leftX() + this->rightX())/2;        }
    inline int32_t  centerY()                               { return (this->topY()  + this->bottomY())/2;       }

    inline Point    top_left()                              { return Point(this->leftX(), this->topY());        }
    inline Point    top_right()                             { return Point(this->rightX(), this->topY());       }
    inline Point    bottom_left()                           { return Point(this->leftX(), this->bottomY());     }
    inline Point    bottom_right()                          { return Point(this->rightX(), this->bottomY());    }

    inline void     center(Point p)                         { this->position(p - this->centerpoint());          }   // set center of the widget relative to parent
    inline void     center(int32_t x, int32_t y)            { this->center(Point(x,y));                         }   // set center of the widget relative to parent

    /* center of the widget  relative to parent (จุดศก.ของ widget อยู่พิกัดไหนเทียบจาก parent) */
    inline Point    center()                                { return this->top_left() + this->centerpoint();    }   

    /* centerpoint inner of the widget (จุดศก.ของ widget ภายใน วิตเจ็ตนั้นๆ เทียบจากจุดบนซ้ายของ widget นั้น )*/
    inline Point    centerpoint()                           { return Point(this->width()/2, this->height()/2);  } 

    void layout(layout_t layout);
    inline layout_t layout()                                { return this->_layout;                             }
    
    inline void layout(layout_t layout, int32_t padding) {
      GObject::layout(layout); this->padding(padding);
    }

    inline void layout(layout_t layout, int32_t p_top, int32_t p_bottom, int32_t p_left, int32_t p_right) {
      GObject::layout(layout); this->padding(p_top,p_bottom,p_left,p_right);
    }

    inline void layout(layout_t layout, int32_t p_top, int32_t p_bottom, int32_t p_left, int32_t p_right, int32_t p_inner) {
      GObject::layout(layout); this->padding(p_top,p_bottom,p_left,p_right, p_inner);      
    }

    inline void layout(layout_t layout, int32_t p_top, int32_t p_bottom, int32_t p_left, int32_t p_right, int32_t p_row, int32_t p_column) {
      GObject::layout(layout); this->padding(p_top,p_bottom,p_left,p_right, p_row,p_column);       
    }

    inline int32_t GRID_column_width(uint32_t col_id)             { return (_u_col_dsc != NULL && !_u_col_dsc->empty() &&  col_id >= 0 && col_id < _u_col_dsc->size())? (*_u_col_dsc)[col_id] : -1 ;}
    inline int32_t GRID_row_height(uint32_t row_id)               { return (_u_row_dsc != NULL && !_u_row_dsc->empty() &&  row_id >= 0 && row_id < _u_row_dsc->size())? (*_u_row_dsc)[row_id] : -1 ;}

    void GRID_CELL(GRID_COL col_dsc, GRID_ROW row_dsc);
    inline void GRID_CELL(GRID_COL col_dsc, GRID_ROW row_dsc, grid_align_t column_align, grid_align_t row_align){
      this->GRID_CELL(col_dsc, row_dsc);
      this->grid_align(column_align, row_align);
    }

    inline void scrollbar(scrollbar_mode_t mode, bool scroll_hor =false , bool scroll_ver = true ){ 
      GObject::scrollbar_mode(mode); GObject::scroll_dir( (dir_t) ((int)(scroll_ver? DIR_VER : DIR_NONE ) | (int)(scroll_hor? DIR_HOR : DIR_NONE )));
    }

    inline dir_t gesture_dir()                                    { return lv_indev_get_gesture_dir(lv_indev_active());   }
    
    /**
     * Delete all children of an object.
     * Also remove the objects from their group and remove all animations (if any).
     * Send `EVENT_DELETED` to deleted objects.
     */
    void clean();

    /**
     * Delete an object after some delay
     * @param delay_ms  time to wait before delete in milliseconds
     */
    void delete_delayed(uint32_t delay_ms);

    /**
     * A function to be easily used in animation ready callback to delete an object when the animation is ready
     * @param a         pointer to the animation
     */
    void delete_anim_completed_cb(anim_t * a);

    /**
     * Helper function for asynchronously deleting objects.
     * Useful for cases where you can't delete an object directly in an `EVENT_DELETE` handler (i.e. parent).
     * @see async_call
     */
    void delete_async(obj_t * obj);


    /**
     * Swap the positions of two objects.
     * When used in listboxes, it can be used to sort the listbox items.
     * @param widget1  pointer to the first GWidget
     * @param widget2  pointer to the second GWidget
     */
    void swap(GWidget*widget1, GWidget*widget2);

    /**
     * moves the object to the given index in its parent.
     * When used in listboxes, it can be used to sort the listbox items.
     * @param index  new index in parent. -1 to count from the back
     * @note to move to the background: move_to_index(0)
     * @note to move forward (up): move_to_index(get_index(obj) - 1)
     */
    void move_to_index(int32_t index);

    /**
     * Get the screen of an object
     * @param obj       pointer to an object
     * @return          pointer to the object's screen
     */
    obj_t * get_screen();

    /**
     * Get the display of the object
     * @return          pointer to the object's display
     */
    display_t * get_display();

    /**
     * Get the child of an object by the child's index.
     * @param idx       the index of the child.
     *                  0: the oldest (firstly created) child
     *                  1: the second oldest
     *                  child count-1: the youngest
     *                  -1: the youngest
     *                  -2: the second youngest
     * @return          pointer to the child or NULL if the index was invalid
     */
    obj_t * get_child(int32_t idx);

    /**
     * Get the child of an object by the child's index. Consider the children only with a given type.
     * @param idx       the index of the child.
     *                  0: the oldest (firstly created) child
     *                  1: the second oldest
     *                  child count-1: the youngest
     *                  -1: the youngest
     *                  -2: the second youngest
     * @param class_p   the type of the children to check
     * @return          pointer to the child or NULL if the index was invalid
     */
    obj_t * get_child_by_type(int32_t idx, const obj_class_t * class_p);

    /**
     * Get the GChild of an object by the child's index. Consider the children's GWidget only with a given type.
     * @param idx       the index of the child.
     *                  0: the oldest (firstly created) child
     *                  1: the second oldest
     *                  child count-1: the youngest
     *                  -1: the youngest
     *                  -2: the second youngest
     * @param class_p   the type of the children to check
     * @return          pointer to the child or NULL if the index was invalid
     */
    GWidget * get_GChild_by_type(int32_t idx, const obj_class_t * class_p);
    GWidget * child_by_type(int32_t idx, const obj_class_t * class_p)       { return get_GChild_by_type(idx, class_p);    }

    /**
     * Return a sibling of an object
     * @param idx       0: `obj` itself
     *                  -1: the first older sibling
     *                  -2: the next older sibling
     *                  1: the first younger sibling
     *                  2: the next younger sibling
     *                  etc
     * @return          pointer to the requested sibling  or NULL if there is no such sibling
     */
    obj_t * get_sibling(int32_t idx);

    /**
     * Return a sibling of an object. Consider the siblings only with a given type.
     * @param idx       0: `obj` itself
     *                  -1: the first older sibling
     *                  -2: the next older sibling
     *                  1: the first younger sibling
     *                  2: the next younger sibling
     *                  etc
     * @param class_p   the type of the children to check
     * @return          pointer to the requested sibling  or NULL if there is no such sibling
     */
    obj_t * sibling_by_type(int32_t idx, const obj_class_t * class_p);

    /**
     * Get the number of children
     * @return          the number of children
     */
    uint32_t child_count();

    /**
     * Get the number of children having a given type.
     * @param class_p   the type of the children to check
     * @return          the number of children
     */

    uint32_t child_count_by_type(const obj_class_t * class_p);

    /**
     * Get the index of a child.
     * @return          the child index of the object.
     *                  E.g. 0: the oldest (firstly created child).
     *                  (-1 if child could not be found or no parent exists)
     */
    int32_t index();

    /**
     * Get the index of a child. Consider the children only with a given type.
     * @param class_p   the type of the children to check
     * @return          the child index of the object.
     *                  E.g. 0: the oldest (firstly created child with the given class).
     *                  (-1 if child could not be found or no parent exists)
     */
    int32_t index_by_type(const obj_class_t * class_p);

    /**
     * Iterate through all children of any object.
     * @param start_obj     start integrating from this object
     * @param cb            call this callback on the objects
     * @param user_data     pointer to any user related data (will be passed to `cb`)
     */
    static void tree_walk(obj_t * start_obj, obj_tree_walk_cb_t cb, void * user_data);

    /**
     * Iterate through all children of any object and print their ID.
     * @param start_obj     start integrating from this object
     */
    static void dump_tree(obj_t * start_ob);

    /**********************
     * Style Main PROTOTYPES
     **********************/
    void            addStyle(GStyle&gstyle, style_selector_t selector=GPART_MAIN);
    void            refreshStyle(style_selector_t selector=GPART_ANY, style_prop_t prop=GSTYLE_PROP_ANY);               
    void            removeStyle(GStyle &gstyle, style_selector_t style_selector=GPART_MAIN);
    void            removeStyle(style_selector_t style_selector);
    void            removeStyleAll();


    /**
     * Add a style to an object.
     * @param style     pointer to a style to add
     * @param selector  OR-ed value of parts and state to which the style should be added
     * @example         add_style(btn, &style_btn, 0); //Default button style
     * @example         add_style(btn, &btn_red, GSTATE_PRESSED); //Overwrite only some colors to red when pressed
     */
    void add_style(const style_t * style, style_selector_t selector=GPART_MAIN);

    /**
     * Replaces a style of an object, preserving the order of the style stack (local styles and transitions are ignored).
     * @param old_style     pointer to a style to replace.
     * @param new_style     pointer to a style to replace the old style with.
     * @param selector      OR-ed values of states and a part to replace only styles with matching selectors. LV_STATE_ANY and LV_PART_ANY can be used
     * @example replace_style(obj, &yellow_style, &blue_style, (gstate_t) GPART_ANY  | GSTATE_ANY); //Replace a specific style
     * @example replace_style(obj, &yellow_style, &blue_style, (gstate_t) GPART_MAIN | GSTATE_PRESSED); //Replace a specific style assigned to the main part when it is pressed
     */
    bool replace_style(const style_t * old_style, const style_t * new_style,
                              style_selector_t selector=GPART_MAIN);

    /**
     * Remove a style from an object.
     * @param style     pointer to a style to remove. Can be NULL to check only the selector
     * @param selector  OR-ed values of states and a part to remove only styles with matching selectors. GSTATE_ANY and GPART_ANY can be used
     * @example remove_style(obj, &style, (gstate_t) GPART_ANY | GSTATE_ANY); //Remove a specific style
     * @example remove_style(obj, NULL, (gstate_t) GPART_MAIN | GSTATE_ANY); //Remove all styles from the main part
     * @example remove_style(obj, NULL, (gstate_t) GPART_ANY | GSTATE_ANY); //Remove all styles
     */
    void remove_style(const style_t * style, style_selector_t selector=GPART_MAIN);

    /**
     * Remove all styles from an object
     */
    void remove_style_all();

    /**
     * Notify all object if a style is modified
     * @param style     pointer to a style. Only the objects with this style will be notified
     *                  (NULL to notify all objects)
     */
    void report_style_change(style_t * style);

    /**
     * Notify an object and its children about its style is modified.
     * @param part      the part whose style was changed. E.g. `LV_PART_ANY`, `LV_PART_MAIN`
     * @param prop      `LV_STYLE_PROP_ANY` or an `LV_STYLE_...` property.
     *                  It is used to optimize what needs to be refreshed.
     *                  `LV_STYLE_PROP_INV` to perform only a style cache update
     */
    void refresh_style(gpart_t part, style_prop_t prop);

    /**
     * Enable or disable automatic style refreshing when a new style is added/removed to/from an object
     * or any other style change happens.
     * @param en        true: enable refreshing; false: disable refreshing
     */
    void enable_style_refresh(bool en);

    /**
     * Get the value of a style property. The current state of the object will be considered.
     * Inherited properties will be inherited.
     * If a property is not set a default value will be returned.
     * @param part      a part from which the property should be get
     * @param prop      the property to get
     * @return          the value of the property.
     *                  Should be read from the correct field of the `lv_style_value_t` according to the type of the property.
     */
    style_value_t style_prop(gpart_t part, style_prop_t prop);

    /**
     * Check if an object has a specified style property for a given style selector.
     * @param selector  the style selector to be checked, defining the scope of the style to be examined.
     * @param prop      the property to be checked.
     * @return          true if the object has the specified selector and property, false otherwise.
     */
    bool has_style_prop(style_selector_t selector, style_prop_t prop);

    /**
     * Set local style property on an object's part and state.
     * @param prop      the property
     * @param value     value of the property. The correct element should be set according to the type of the property
     * @param selector  OR-ed value of parts and state for which the style should be set
     */
    void local_style_prop(style_prop_t prop, style_value_t value,
                                    style_selector_t selector=GPART_MAIN);

    style_res_t local_style_prop(style_prop_t prop, style_value_t * value,
                                              style_selector_t selector=GPART_MAIN);

    /**
     * Remove a local style property from a part of an object with a given state.
     * @param prop      a style property to remove.
     * @param selector  OR-ed value of parts and state for which the style should be removed
     * @return true     the property was found and removed; false: the property was not found
     */
    bool remove_local_style_prop(style_prop_t prop, style_selector_t selector=GPART_MAIN);


    /**
     * Fade in an an object and all its children.
     * @param time      time of fade
     * @param delay     delay to start the animation
     */
    void fade_in(uint32_t time, uint32_t delay);

    /**
     * Fade out an an object and all its children.
     * @param time      time of fade
     * @param delay     delay to start the animation
     */
    void fade_out(uint32_t time, uint32_t delay);

    static inline gstate_t get_selector_state(style_selector_t selector)
    {
        return (gstate_t)(selector & 0xFFFF);
    }

    inline gpart_t style_get_selector_part(style_selector_t selector)
    {
        return (gpart_t)(selector & 0xFF0000);
    }


    inline void pad_all(int32_t value, style_selector_t selector=GPART_MAIN)
    {
        pad_left(value, selector);
        pad_right(value, selector);
        pad_top(value, selector);
        pad_bottom(value, selector);
    }

    inline void pad(int32_t value, style_selector_t selector=GPART_MAIN)    { this->pad_all(value, selector); this->pad_gap(value, selector); }

    inline void pad_hor(int32_t value, style_selector_t selector=GPART_MAIN)
    {
        pad_left(value, selector);
        pad_right(value, selector);
    }

    inline void pad_ver(int32_t value, style_selector_t selector=GPART_MAIN)
    {
        pad_top(value, selector);
        pad_bottom(value, selector);
    }

    inline void margin_all(int32_t value, style_selector_t selector=GPART_MAIN)
    {
        margin_left(value, selector);
        margin_right(value, selector);
        margin_top(value, selector);
        margin_bottom(value, selector);
    }

    inline void margin_hor(int32_t value, style_selector_t selector=GPART_MAIN)
    {
        margin_left(value, selector);
        margin_right(value, selector);
    }

    inline void margin_ver(int32_t value, style_selector_t selector=GPART_MAIN)
    {
        margin_top(value, selector);
        margin_bottom(value, selector);
    }

    inline void pad_gap(int32_t value, style_selector_t selector=GPART_MAIN)
    {
        pad_row(value, selector);
        pad_column(value, selector);
    }

    inline void style_size(int32_t width, int32_t height, style_selector_t selector=GPART_MAIN)
    {
        style_width(width, selector);
        style_height(height, selector);
    }

    inline void size(int32_t width, int32_t height, style_selector_t selector)
    {
        style_size(width, height, selector);
    }


    inline void transform_scale(int32_t value, style_selector_t selector=GPART_MAIN)
    {
        transform_scale_x(value, selector);
        transform_scale_y(value, selector);
    }

    inline void style_scale(int32_t value, style_selector_t selector=GPART_MAIN)
    {
      static style_prop_t tr_prop[] = { GSTYLE_TRANSFORM_PIVOT_X, GSTYLE_TRANSFORM_PIVOT_Y, GSTYLE_TRANSFORM_SCALE_X, GSTYLE_TRANSFORM_SCALE_Y, 0};
      static GTransition tr;
      tr.init(tr_prop, ANIM_PATH_LINEAR, 200);
      
      transition( tr );
      transform_pivot(centerpoint(), selector);
      transform_scale(value, selector);
    }

    inline void style_scale(int32_t value, Point pivot, style_selector_t selector=GPART_MAIN)
    {
      static style_prop_t tr_prop[] = { GSTYLE_TRANSFORM_PIVOT_X, GSTYLE_TRANSFORM_PIVOT_Y, GSTYLE_TRANSFORM_SCALE_X, GSTYLE_TRANSFORM_SCALE_Y, 0};
      static GTransition tr;
      tr.init(tr_prop, ANIM_PATH_LINEAR, 200);
      
      transition( tr );
      transform_pivot(pivot, selector);
      transform_scale(value, selector);
    }

    inline int32_t space_left(gpart_t part=GPART_MAIN)
    {
        int32_t padding = this->pad_left(part);
        int32_t border_width = this->border_width(part);
        border_side_t border_side = this->border_side(part);
        return (border_side & BORDER_SIDE_LEFT) ? padding + border_width : padding;
    }

    inline int32_t space_right(gpart_t part=GPART_MAIN)
    {
        int32_t padding = this->pad_right(part);
        int32_t border_width = this->border_width(part);
        lv_border_side_t border_side = (lv_border_side_t) this->border_side(part);
        return (border_side & BORDER_SIDE_RIGHT) ? padding + border_width : padding;
    }

    inline int32_t space_top(gpart_t part=GPART_MAIN)
    {
        int32_t padding = this->pad_top(part);
        int32_t border_width = this->border_width(part);
        lv_border_side_t border_side = (lv_border_side_t) this->border_side(part);
        return (border_side & BORDER_SIDE_TOP) ? padding + border_width : padding;
    }

    inline int32_t space_bottom(gpart_t part=GPART_MAIN)
    {
        int32_t padding = this->pad_bottom(part);
        int32_t border_width = this->border_width(part);
        lv_border_side_t border_side = (lv_border_side_t) this->border_side(part);
        return (border_side & BORDER_SIDE_BOTTOM) ? padding + border_width : padding;
    }

    text_align_t calculate_style_text_align(gpart_t part, const char * txt);

    inline int32_t transform_scale_x_safe(gpart_t part=GPART_MAIN)
    {
        int16_t zoom = transform_scale_x(part);
        return zoom != 0 ? zoom : 1;
    }

    inline int32_t transform_scale_y_safe( gpart_t part=GPART_MAIN)
    {
        int16_t zoom = transform_scale_y(part);
        return zoom != 0 ? zoom : 1;
    }

    /**
     * Get the `opa` style property from all parents and multiply and `>> 8` them.
     * @param obj       the object whose opacity should be get
     * @param part      the part whose opacity should be get. Non-MAIN parts will consider the `opa` of the MAIN part too
     * @return          the final opacity considering the parents' opacity too
     */
    opa_t opa_recursive(gpart_t part=GPART_MAIN);

    //-----------------------------------------
    // Style All APIs
    //-----------------------------------------
    inline int32_t  style_width(gpart_t part=GPART_MAIN)                                  { return (int32_t) (style_prop(part, GSTYLE_WIDTH).num);                  }
    inline int32_t  style_min_width(gpart_t part=GPART_MAIN)                              { return (int32_t) (style_prop(part, GSTYLE_MIN_WIDTH).num);              }
    inline int32_t  style_max_width(gpart_t part=GPART_MAIN)                              { return (int32_t) (style_prop(part, GSTYLE_MAX_WIDTH).num);              }

    inline int32_t  min_width(gpart_t part=GPART_MAIN)                                    { return this->style_min_width(part);         }
    inline int32_t  max_width(gpart_t part=GPART_MAIN)                                    { return this->style_max_width(part);         }

    inline int32_t  style_height(gpart_t part=GPART_MAIN)                                 { return (int32_t) (style_prop(part, GSTYLE_HEIGHT).num);                 }
    inline int32_t  style_min_height(gpart_t part=GPART_MAIN)                             { return (int32_t) (style_prop(part, GSTYLE_MIN_HEIGHT).num);             }
    inline int32_t  style_max_height(gpart_t part=GPART_MAIN)                             { return (int32_t) (style_prop(part, GSTYLE_MAX_HEIGHT).num);             }

    inline int32_t  min_height(gpart_t part=GPART_MAIN)                                    { return this->style_min_height(part);       }
    inline int32_t  max_height(gpart_t part=GPART_MAIN)                                    { return this->style_max_height(part);       }


    inline int32_t  style_length(gpart_t part=GPART_MAIN)                                 { return (int32_t) (style_prop(part, GSTYLE_LENGTH).num);                 }
    inline int32_t  style_x(gpart_t part=GPART_MAIN)                                      { return (int32_t) (style_prop(part, GSTYLE_X).num);                      }
    inline int32_t  style_y(gpart_t part=GPART_MAIN)                                      { return (int32_t) (style_prop(part, GSTYLE_Y).num);                      }

    inline align_t  style_align(gpart_t part=GPART_MAIN)                                  { return (align_t) (style_prop(part, GSTYLE_ALIGN).num);                  }

    inline int32_t  transform_width(gpart_t part=GPART_MAIN)                              { return (int32_t) (style_prop(part, GSTYLE_TRANSFORM_WIDTH).num);        }
    inline int32_t  transform_height(gpart_t part=GPART_MAIN)                             { return (int32_t) (style_prop(part, GSTYLE_TRANSFORM_HEIGHT).num);       }
    inline int32_t  translate_x(gpart_t part=GPART_MAIN)                                  { return (int32_t) (style_prop(part, GSTYLE_TRANSLATE_X).num);            }
    inline int32_t  translate_y(gpart_t part=GPART_MAIN)                                  { return (int32_t) (style_prop(part, GSTYLE_TRANSLATE_Y).num);            }
    inline int32_t  transform_scale_x(gpart_t part=GPART_MAIN)                            { return (int32_t) (style_prop(part, GSTYLE_TRANSFORM_SCALE_X).num);      }
    inline int32_t  transform_scale_y(gpart_t part=GPART_MAIN)                            { return (int32_t) (style_prop(part, GSTYLE_TRANSFORM_SCALE_Y).num);      }
    inline int32_t  transform_rotation(gpart_t part=GPART_MAIN)                           { return (int32_t) (style_prop(part, GSTYLE_TRANSFORM_ROTATION).num);     }
    inline int32_t  transform_pivot_x(gpart_t part=GPART_MAIN)                            { return (int32_t) (style_prop(part, GSTYLE_TRANSFORM_PIVOT_X).num);      }
    inline int32_t  transform_pivot_y(gpart_t part=GPART_MAIN)                            { return (int32_t) (style_prop(part, GSTYLE_TRANSFORM_PIVOT_Y).num);      }

    inline int32_t  transform_skew_x(gpart_t part=GPART_MAIN)                             { return (int32_t) (style_prop(part, GSTYLE_TRANSFORM_SKEW_X).num);       }
    inline int32_t  transform_skew_y(gpart_t part=GPART_MAIN)                             { return (int32_t) (style_prop(part, GSTYLE_TRANSFORM_SKEW_Y).num);       }


    inline int32_t  pad_top(gpart_t part=GPART_MAIN)                                      { return (int32_t) (style_prop(part, GSTYLE_PAD_TOP).num);                }
    inline int32_t  pad_bottom(gpart_t part=GPART_MAIN)                                   { return (int32_t) (style_prop(part, GSTYLE_PAD_BOTTOM).num);             }
    inline int32_t  pad_left(gpart_t part=GPART_MAIN)                                     { return (int32_t) (style_prop(part, GSTYLE_PAD_LEFT).num);               }
    inline int32_t  pad_right(gpart_t part=GPART_MAIN)                                    { return (int32_t) (style_prop(part, GSTYLE_PAD_RIGHT).num);              }
    inline int32_t  pad_row(gpart_t part=GPART_MAIN)                                      { return (int32_t) (style_prop(part, GSTYLE_PAD_ROW).num);                }
    inline int32_t  pad_column(gpart_t part=GPART_MAIN)                                   { return (int32_t) (style_prop(part, GSTYLE_PAD_COLUMN).num);             }

    inline int32_t  pad(gpart_t part=GPART_MAIN)                                          { return min(min(min(this->pad_top(part) , this->pad_bottom(part)),this->pad_left(part)), this->pad_right(part));  }
    inline int32_t  pad_inner(gpart_t part=GPART_MAIN)                                    { return min(this->pad_row(part) , this->pad_column(part));               }
    inline int32_t  pad_ver(gpart_t part=GPART_MAIN)                                      { return min(this->pad_top(part) , this->pad_bottom(part));  }
    inline int32_t  pad_hor(gpart_t part=GPART_MAIN)                                      { return min(this->pad_left(part) , this->pad_right(part));  }

    inline int32_t  padding_top(gpart_t part=GPART_MAIN)                                  { return this->pad_top(part);                 }
    inline int32_t  padding_bottom(gpart_t part=GPART_MAIN)                               { return this->pad_bottom(part);              }
    inline int32_t  padding_left(gpart_t part=GPART_MAIN)                                 { return this->pad_left(part);                }
    inline int32_t  padding_right(gpart_t part=GPART_MAIN)                                { return this->pad_right(part);               }
    inline int32_t  padding_row(gpart_t part=GPART_MAIN)                                  { return this->pad_row(part);                 }
    inline int32_t  padding_column(gpart_t part=GPART_MAIN)                               { return this->pad_column(part);              }

    inline int32_t  padding(gpart_t part=GPART_MAIN)                                      { return this->pad(part);                     }
    inline int32_t  padding_inner(gpart_t part=GPART_MAIN)                                { return this->pad_inner(part);               }
    inline int32_t  padding_ver(gpart_t part=GPART_MAIN)                                  { return this->pad_ver(part);                 }
    inline int32_t  padding_hor(gpart_t part=GPART_MAIN)                                  { return this->pad_hor(part);                 }


    inline int32_t  margin_top(gpart_t part=GPART_MAIN)                                   { return (int32_t) (style_prop(part, GSTYLE_MARGIN_TOP).num);             }
    inline int32_t  margin_bottom(gpart_t part=GPART_MAIN)                                { return (int32_t) (style_prop(part, GSTYLE_MARGIN_BOTTOM).num);          }
    inline int32_t  margin_left(gpart_t part=GPART_MAIN)                                  { return (int32_t) (style_prop(part, GSTYLE_MARGIN_LEFT).num);            }
    inline int32_t  margin_right(gpart_t part=GPART_MAIN)                                 { return (int32_t) (style_prop(part, GSTYLE_MARGIN_RIGHT).num);           }

    inline color_t  bg_color(gpart_t part=GPART_MAIN)                                     { return lv_color_to_u16(style_prop(part, GSTYLE_BG_COLOR).color);        }
    inline color_t  bg_color_filtered(gpart_t part=GPART_MAIN)                            { return lv_color_to_u16(lv_obj_style_apply_color_filter(obj, part, style_prop(part, GSTYLE_BG_COLOR)).color);       }

    inline color_t  color(gpart_t part=GPART_MAIN)                                        { return bg_color(part);    }

    inline opa_t    bg_opa(gpart_t part=GPART_MAIN)                                       { return (opa_t) (style_prop(part, GSTYLE_BG_OPA).num);                   }
    inline color_t  bg_grad_color(gpart_t part=GPART_MAIN)                                { return lv_color_to_u16(style_prop(part, GSTYLE_BG_GRAD_COLOR).color);   }
    inline color_t  bg_grad_color_filtered(gpart_t part=GPART_MAIN)                       { return lv_color_to_u16(lv_obj_style_apply_color_filter(obj, part, style_prop(part, GSTYLE_BG_GRAD_COLOR)).color);  }
    inline grad_dir_t bg_grad_dir(gpart_t part=GPART_MAIN)                                { return (grad_dir_t) (style_prop(part, GSTYLE_BG_GRAD_DIR).num);         }

    inline int32_t  bg_main_stop(gpart_t part=GPART_MAIN)                                 { return (int32_t) (style_prop(part, GSTYLE_BG_MAIN_STOP).num);           }
    inline int32_t  bg_grad_stop(gpart_t part=GPART_MAIN)                                 { return (int32_t) (style_prop(part, GSTYLE_BG_GRAD_STOP).num);           }

    inline opa_t    bg_main_opa(gpart_t part=GPART_MAIN)                                  { return (opa_t) (style_prop(part, GSTYLE_BG_MAIN_OPA).num);              }
    inline opa_t    bg_grad_opa(gpart_t part=GPART_MAIN)                                  { return (opa_t) (style_prop(part, GSTYLE_BG_GRAD_OPA).num);              }
    inline const grad_dsc_t * bg_grad(gpart_t part=GPART_MAIN)                            { return (const grad_dsc_t *) (style_prop(part, GSTYLE_BG_GRAD).ptr);     }

    inline const void * bg_image_src(gpart_t part=GPART_MAIN)                             { return (const void *) (style_prop(part, GSTYLE_BG_IMAGE_SRC).ptr);      }
    inline const void * image(gpart_t part=GPART_MAIN)                                    { return (const void *) this->bg_image_src(part);                         }
    inline opa_t    bg_image_opa(gpart_t part=GPART_MAIN)                                 { return (opa_t) (style_prop(part, GSTYLE_BG_IMAGE_OPA).num);             }
    inline color_t  bg_image_recolor(gpart_t part=GPART_MAIN)                             { return lv_color_to_u16(style_prop(part, GSTYLE_BG_IMAGE_RECOLOR).color);}
    inline color_t  bg_image_recolor_filtered(gpart_t part=GPART_MAIN)                    { return lv_color_to_u16(lv_obj_style_apply_color_filter(obj, part, style_prop(part, GSTYLE_BG_IMAGE_RECOLOR)).color);}
    inline opa_t    bg_image_recolor_opa(gpart_t part=GPART_MAIN)                         { return (opa_t) (style_prop(part, GSTYLE_BG_IMAGE_RECOLOR_OPA).num);     }
    inline bool     bg_image_tiled(gpart_t part=GPART_MAIN)                               { return (bool)  (style_prop(part, GSTYLE_BG_MAIN_STOP).num);             }

    inline color_t  border_color(gpart_t part=GPART_MAIN)                                 { return lv_color_to_u16(style_prop(part, GSTYLE_BORDER_COLOR).color);    }
    inline color_t  border_color_filtered(gpart_t part=GPART_MAIN)                        { return lv_color_to_u16(lv_obj_style_apply_color_filter(obj, part, style_prop(part, GSTYLE_BORDER_COLOR)).color); }


    inline opa_t    border_opa(gpart_t part=GPART_MAIN)                                   { return (opa_t) (style_prop(part, GSTYLE_BORDER_OPA).num);               }
    inline int32_t  border_width(gpart_t part=GPART_MAIN)                                 { return (int32_t) (style_prop(part, GSTYLE_BORDER_WIDTH).num);           }
    inline int32_t  border(gpart_t part=GPART_MAIN)                                       { return this->border_width();  }
    inline border_side_t border_side(gpart_t part=GPART_MAIN)                             { return (border_side_t) (style_prop(part, GSTYLE_BORDER_SIDE).num);      }
    inline bool     border_post(gpart_t part=GPART_MAIN)                                  { return (bool)  (style_prop(part, GSTYLE_BORDER_POST).num);              }

    inline int32_t  outline_width(gpart_t part=GPART_MAIN)                                { return (int32_t) (style_prop(part, GSTYLE_OUTLINE_WIDTH).num);          }
    inline color_t  outline_color(gpart_t part=GPART_MAIN)                                { return lv_color_to_u16(style_prop(part, GSTYLE_OUTLINE_COLOR).color);   }
    inline color_t  outline_color_filtered(gpart_t part=GPART_MAIN)                       { return lv_color_to_u16(lv_obj_style_apply_color_filter(obj, part, style_prop(part, GSTYLE_OUTLINE_COLOR)).color);}
    inline opa_t    outline_opa(gpart_t part=GPART_MAIN)                                  { return (opa_t) (style_prop(part, GSTYLE_OUTLINE_OPA).num);              }
    inline int32_t  outline_pad(gpart_t part=GPART_MAIN)                                  { return (int32_t) (style_prop(part, GSTYLE_OUTLINE_PAD).num);            }

    inline int32_t  shadow_width(gpart_t part=GPART_MAIN)                                 { return (int32_t) (style_prop(part, GSTYLE_SHADOW_WIDTH).num);           }
    inline int32_t  shadow(gpart_t part=GPART_MAIN)                                       { return this->shadow_width(part);                                        }
    inline int32_t  shadow_offset_x(gpart_t part=GPART_MAIN)                              { return (int32_t) (style_prop(part, GSTYLE_SHADOW_OFFSET_X).num);        }
    inline int32_t  shadow_offset_y(gpart_t part=GPART_MAIN)                              { return (int32_t) (style_prop(part, GSTYLE_SHADOW_OFFSET_Y).num);        }
    inline Point    shadow_offset(gpart_t part=GPART_MAIN)                                { return Point(shadow_offset_x(part), shadow_offset_y(part));             }
    inline int32_t  shadow_spread(gpart_t part=GPART_MAIN)                                { return (int32_t) (style_prop(part, GSTYLE_SHADOW_SPREAD).num);          }
    inline color_t  shadow_color(gpart_t part=GPART_MAIN)                                 { return lv_color_to_u16(style_prop(part, GSTYLE_SHADOW_COLOR).color);    }
    inline color_t  shadow_color_filtered(gpart_t part=GPART_MAIN)                        { return lv_color_to_u16(lv_obj_style_apply_color_filter(obj, part, style_prop(part, GSTYLE_SHADOW_COLOR)).color); }
    inline opa_t    shadow_opa(gpart_t part=GPART_MAIN)                                   { return (opa_t) (style_prop(part, GSTYLE_SHADOW_OPA).num);               }

    inline opa_t    image_opa(gpart_t part=GPART_MAIN)                                    { return (opa_t) (style_prop(part, GSTYLE_IMAGE_OPA).num);                }
    inline color_t  image_recolor(gpart_t part=GPART_MAIN)                                { return lv_color_to_u16(style_prop(part, GSTYLE_IMAGE_RECOLOR).color);   }
    inline color_t  image_recolor_filtered(gpart_t part=GPART_MAIN)                       { return lv_color_to_u16(lv_obj_style_apply_color_filter(obj, part, style_prop(part, GSTYLE_IMAGE_RECOLOR)).color);}
    inline opa_t    image_recolor_opa(gpart_t part=GPART_MAIN)                            { return (opa_t) (style_prop(part, GSTYLE_IMAGE_RECOLOR_OPA).num);        }

    inline int32_t  line_width(gpart_t part=GPART_MAIN)                                   { return (int32_t) (style_prop(part, GSTYLE_LINE_WIDTH).num);             }
    inline int32_t  line_dash_width(gpart_t part=GPART_MAIN)                              { return (int32_t) (style_prop(part, GSTYLE_LINE_DASH_WIDTH).num);        }
    inline int32_t  line_dash_gap(gpart_t part=GPART_MAIN)                                { return (int32_t) (style_prop(part, GSTYLE_LINE_DASH_GAP).num);          }
    inline bool     line_rounded(gpart_t part=GPART_MAIN)                                 { return (bool)  (style_prop(part, GSTYLE_LINE_ROUNDED).num);             }
    inline color_t  line_color(gpart_t part=GPART_MAIN)                                   { return lv_color_to_u16(style_prop(part, GSTYLE_LINE_COLOR).color);      }
    inline color_t  line_color_filtered(gpart_t part=GPART_MAIN)                          { return lv_color_to_u16(lv_obj_style_apply_color_filter(obj, part, style_prop(part, GSTYLE_LINE_COLOR)).color);   }
    inline opa_t    line_opa(gpart_t part=GPART_MAIN)                                     { return (opa_t) (style_prop(part, GSTYLE_LINE_OPA).num);                 }

    inline int32_t  arc_width(gpart_t part=GPART_MAIN)                                    { return (int32_t) (style_prop(part, GSTYLE_ARC_WIDTH).num);              }
    inline bool     arc_rounded(gpart_t part=GPART_MAIN)                                  { return (bool)  (style_prop(part, GSTYLE_ARC_ROUNDED).num);              }
    inline color_t  arc_color(gpart_t part=GPART_MAIN)                                    { return lv_color_to_u16(style_prop(part, GSTYLE_ARC_COLOR).color);       }
    inline color_t  arc_color_filtered(gpart_t part=GPART_MAIN)                           { return lv_color_to_u16(lv_obj_style_apply_color_filter(obj, part, style_prop(part, GSTYLE_ARC_COLOR)).color);    }
    inline opa_t    arc_opa(gpart_t part=GPART_MAIN)                                      { return (opa_t) (style_prop(part, GSTYLE_ARC_OPA).num);                  }
    inline const void * arc_image_src(gpart_t part=GPART_MAIN)                            { return (const void *) (style_prop(part, GSTYLE_ARC_IMAGE_SRC).ptr);     }

    inline color_t  text_color(gpart_t part=GPART_MAIN)                                   { return lv_color_to_u16(style_prop(part, GSTYLE_TEXT_COLOR).color);      }
    inline color_t  font_color(gpart_t part=GPART_MAIN)                                   { return this->text_color(part);    }
    inline color_t  text_color_filtered(gpart_t part=GPART_MAIN)                          { return lv_color_to_u16(lv_obj_style_apply_color_filter(obj, part, style_prop(part, GSTYLE_TEXT_COLOR)).color);   }
    inline color_t  font_color_filtered(gpart_t part=GPART_MAIN)                          { return this->text_color_filtered(part);  }
    inline opa_t    text_opa(gpart_t part=GPART_MAIN)                                     { return (opa_t) (style_prop(part, GSTYLE_TEXT_OPA).num);                 }
    inline const font_t * text_font(gpart_t part=GPART_MAIN)                              { return (const font_t *) (style_prop(part, GSTYLE_TEXT_FONT).ptr);       }
    inline const font_t * font(gpart_t part=GPART_MAIN)                                   { return this->text_font(part);    }
    inline int32_t font_height(gpart_t part=GPART_MAIN)                                   { return this->font(part)->line_height;       }
    inline int32_t font_base_line(gpart_t part=GPART_MAIN)                                { return this->font(part)->base_line;         }

    inline int32_t  text_letter_space(gpart_t part=GPART_MAIN)                            { return (int32_t) (style_prop(part, GSTYLE_TEXT_LETTER_SPACE).num);      }
    inline int32_t  text_line_space(gpart_t part=GPART_MAIN)                              { return (int32_t) (style_prop(part, GSTYLE_TEXT_LINE_SPACE).num);        }
    inline text_decor_t text_decor(gpart_t part=GPART_MAIN)                               { return (text_decor_t) (style_prop(part, GSTYLE_TEXT_DECOR).num);        }
    inline text_align_t text_align(gpart_t part=GPART_MAIN)                               { return (text_align_t) (style_prop(part, GSTYLE_TEXT_ALIGN).num);        }

    inline int32_t  radius(gpart_t part=GPART_MAIN)                                       { return (int32_t) (style_prop(part, GSTYLE_RADIUS).num);                 }
    inline bool     clip_corner(gpart_t part=GPART_MAIN)                                  { return (bool)  (style_prop(part, GSTYLE_CLIP_CORNER).num);              }

    inline int32_t  corner_radius(gpart_t part=GPART_MAIN)                                { return this->radius(part);      }
    inline bool     corner_mask(gpart_t part=GPART_MAIN)                                  { return this->clip_corner(part); }

    inline opa_t    opa(gpart_t part=GPART_MAIN)                                          { return (opa_t) (style_prop(part, GSTYLE_OPA).num);                      }
    inline opa_t    opa_layered(gpart_t part=GPART_MAIN)                                  { return (opa_t) (style_prop(part, GSTYLE_OPA_LAYERED).num);              }


    inline const color_filter_dsc_t * color_filter_dsc(gpart_t part=GPART_MAIN)           { return (const color_filter_dsc_t *) (style_prop(part, GSTYLE_COLOR_FILTER_DSC).ptr);    }
    inline opa_t color_filter_opa(gpart_t part=GPART_MAIN)                                { return (opa_t) (style_prop(part, GSTYLE_COLOR_FILTER_OPA).num);         }
    inline const anim_t * style_anim(gpart_t part=GPART_MAIN)                             { return (const anim_t *) (style_prop(part, GSTYLE_ANIM).ptr);            }

    inline uint32_t anim_duration(gpart_t part=GPART_MAIN)                                { return (uint32_t) (style_prop(part, GSTYLE_ANIM_DURATION).num);         }
    inline uint32_t anim_speed(gpart_t part=GPART_MAIN)                                   { return this->anim_duration(part);   }


    inline const style_transition_dsc_t * transition(gpart_t part=GPART_MAIN)             { return (const style_transition_dsc_t *) (style_prop(part, GSTYLE_TRANSITION).ptr);      }
    inline blend_mode_t blend_mode(gpart_t part=GPART_MAIN)                               { return (blend_mode_t) (style_prop(part, GSTYLE_BLEND_MODE).num);        }
    inline uint16_t style_layout(gpart_t part=GPART_MAIN)                                 { return (uint16_t) (style_prop(part, GSTYLE_LAYOUT).num);                }
    inline base_dir_t base_dir(gpart_t part=GPART_MAIN)                                   { return (base_dir_t) (style_prop(part, GSTYLE_BASE_DIR).num);            }

    inline const img_t* bitmap_mask_src(gpart_t part=GPART_MAIN)                          { return (const img_t*) (style_prop(part, GSTYLE_BITMAP_MASK_SRC).ptr);   }
    inline const img_t* mask(gpart_t part=GPART_MAIN)                                     { return this->bitmap_mask_src(part);  }
    inline uint32_t rotary_sensitivity(gpart_t part=GPART_MAIN)                           { return (uint32_t) (style_prop(part, GSTYLE_ROTARY_SENSITIVITY).num);    }


    #if LV_USE_FLEX

    inline flex_flow_t  flex_flow(gpart_t part=GPART_MAIN)                                { return (flex_flow_t) (style_prop(part, GSTYLE_FLEX_FLOW).num);          }
    inline flex_align_t flex_main_place(gpart_t part=GPART_MAIN)                          { return (flex_align_t) (style_prop(part, GSTYLE_FLEX_MAIN_PLACE).num);   }
    inline flex_align_t flex_cross_place(gpart_t part=GPART_MAIN)                         { return (flex_align_t) (style_prop(part, GSTYLE_FLEX_CROSS_PLACE).num);  }
    inline flex_align_t flex_track_place(gpart_t part=GPART_MAIN)                         { return (flex_align_t) (style_prop(part, GSTYLE_FLEX_TRACK_PLACE).num);  }
    inline uint8_t      flex_grow(gpart_t part=GPART_MAIN)                                { return (uint8_t) (style_prop(part, GSTYLE_FLEX_GROW).num);              }

    #endif /*LV_USE_FLEX*/

    #if LV_USE_GRID

    inline const int32_t* grid_column_dsc(gpart_t part=GPART_MAIN)                        { return (const int32_t *) (style_prop(part, GSTYLE_GRID_COLUMN_DSC_ARRAY).ptr);  }
    inline const int32_t* grid_row_dsc(gpart_t part=GPART_MAIN)                           { return (const int32_t *) (style_prop(part, GSTYLE_GRID_ROW_DSC_ARRAY).ptr);     }
    inline grid_align_t   grid_column_align(gpart_t part=GPART_MAIN)                      { return (grid_align_t) (style_prop(part, GSTYLE_GRID_COLUMN_ALIGN).num);         }
    inline grid_align_t   grid_row_align(gpart_t part=GPART_MAIN)                         { return (grid_align_t) (style_prop(part, GSTYLE_GRID_ROW_ALIGN).num);            }
    inline int32_t        grid_cell_column_pos(gpart_t part=GPART_MAIN)                   { return (int32_t) (style_prop(part, GSTYLE_GRID_CELL_COLUMN_POS).num);           }
    inline int32_t        grid_cell_row_pos(gpart_t part=GPART_MAIN)                      { return (int32_t) (style_prop(part, GSTYLE_GRID_CELL_ROW_POS).num);              }
    inline grid_align_t   grid_cell_x_align(gpart_t part=GPART_MAIN)                      { return (grid_align_t) (style_prop(part, GSTYLE_GRID_CELL_X_ALIGN).num);         }
    inline grid_align_t   grid_cell_y_align(gpart_t part=GPART_MAIN)                      { return (grid_align_t) (style_prop(part, GSTYLE_GRID_CELL_Y_ALIGN).num);         }
    inline int32_t        grid_cell_column_span(gpart_t part=GPART_MAIN)                  { return (int32_t) (style_prop(part, GSTYLE_GRID_CELL_COLUMN_SPAN).num);          }
    inline int32_t        grid_cell_row_span(gpart_t part=GPART_MAIN)                     { return (int32_t) (style_prop(part, GSTYLE_GRID_CELL_ROW_SPAN).num);             }
        
    #endif /*LV_USE_GRID*/

    void style_width(int32_t value, style_selector_t selector=GPART_MAIN);
    void style_min_width(int32_t value, style_selector_t selector=GPART_MAIN);
    void style_max_width(int32_t value, style_selector_t selector=GPART_MAIN);

    void min_width(int32_t value, style_selector_t selector=GPART_MAIN)                   { this->style_min_width(value, selector);                     }
    void max_width(int32_t value, style_selector_t selector=GPART_MAIN)                   { this->style_max_width(value, selector);                     }

    void style_height(int32_t value, style_selector_t selector=GPART_MAIN);
    void style_min_height(int32_t value, style_selector_t selector=GPART_MAIN);
    void style_max_height(int32_t value, style_selector_t selector=GPART_MAIN);

    void min_height(int32_t value, style_selector_t selector=GPART_MAIN)                  { this->style_min_height(value, selector);                    }
    void max_height(int32_t value, style_selector_t selector=GPART_MAIN)                  { this->style_max_height(value, selector);                    }

    void min_size(int32_t w, int32_t h, style_selector_t selector=GPART_MAIN)             { this->min_width(w, selector); this->min_height(h,selector); }
    void max_size(int32_t w, int32_t h, style_selector_t selector=GPART_MAIN)             { this->max_width(w, selector); this->max_height(h,selector); }

    void style_length(int32_t value, style_selector_t selector=GPART_MAIN);
    void style_x(int32_t value, style_selector_t selector=GPART_MAIN);
    void style_y(int32_t value, style_selector_t selector=GPART_MAIN);
    void style_align(align_t value, style_selector_t selector=GPART_MAIN);
    void transform_width(int32_t value, style_selector_t selector=GPART_MAIN);
    void transform_height(int32_t value, style_selector_t selector=GPART_MAIN);
    void translate_x(int32_t value, style_selector_t selector=GPART_MAIN);
    void translate_y(int32_t value, style_selector_t selector=GPART_MAIN);
    void transform_scale_x(int32_t value, style_selector_t selector=GPART_MAIN);
    void transform_scale_y(int32_t value, style_selector_t selector=GPART_MAIN);
    void transform_rotation(int32_t value, style_selector_t selector=GPART_MAIN);
    void transform_pivot_x(int32_t value, style_selector_t selector=GPART_MAIN);
    void transform_pivot_y(int32_t value, style_selector_t selector=GPART_MAIN);
    void transform_skew_x(int32_t value, style_selector_t selector=GPART_MAIN);
    void transform_skew_y(int32_t value, style_selector_t selector=GPART_MAIN);

    inline void   translate(int32_t x, int32_t y , style_selector_t selector=GPART_MAIN)          { this->translate_x(x, selector); this->translate_y(y, selector);                                   }
    inline void   transform_size(int32_t w, int32_t h , style_selector_t selector=GPART_MAIN)     { this->transform_width(w, selector); this->transform_height(h, selector);                          }
    inline void   transform_scale(int32_t scale_x, int32_t scale_y , style_selector_t selector=GPART_MAIN)  { this->transform_scale_x(scale_x, selector); this->transform_scale_x(scale_y, selector); }
    inline void   transform_pivot(int32_t pivot_x, int32_t pivot_y, style_selector_t selector=GPART_MAIN)   { this->transform_pivot_x(pivot_x, selector); this->transform_pivot_y(pivot_y, selector); }
    inline void   transform_pivot(Point pivot, style_selector_t selector=GPART_MAIN)              { this->transform_pivot(pivot.x, pivot.y, selector);                                                }
    inline void   transform_skew(int32_t skew_x, int32_t skew_y, style_selector_t selector=GPART_MAIN) { this->transform_skew_x(skew_x, selector); this->transform_skew_y(skew_y, selector);          }
    inline void   transform_skew(Point skew, style_selector_t selector=GPART_MAIN)                { this->transform_skew(skew.x, skew.y, selector);                                                   }

    inline void   rotation(float angle , style_selector_t selector=GPART_MAIN)                    { this->transform_rotation( (int) round(angle*10), selector);                                       }
    inline float  rotation(style_selector_t selector=GPART_MAIN)                                  { int32_t v =this->transform_rotation( selector); return v/10.0; }
    inline void   pivot(int32_t pivot_x, int32_t pivot_y, style_selector_t selector=GPART_MAIN)   { this->transform_pivot(pivot_x, pivot_y, selector);                                                }
    inline void   pivot(Point pivot, style_selector_t selector=GPART_MAIN)                        { this->transform_pivot(pivot, selector);                                                           }


    inline void   remove_color(style_selector_t selector=GPART_MAIN)                              { this->remove_local_style_prop(GSTYLE_BG_COLOR, selector);     this->remove_local_style_prop(GSTYLE_BG_GRAD_COLOR, selector);  }
    inline void   remove_border(style_selector_t selector=GPART_MAIN)                             { this->remove_local_style_prop(GSTYLE_BORDER_WIDTH, selector); this->remove_local_style_prop(GSTYLE_BORDER_COLOR,  selector);  }
    inline void   remove_text_font(style_selector_t selector=GPART_MAIN)                          { this->remove_local_style_prop(GSTYLE_TEXT_FONT, selector);            }
    inline void   remove_text_color(style_selector_t selector=GPART_MAIN)                         { this->remove_local_style_prop(GSTYLE_TEXT_COLOR, selector);           }
    inline void   remove_image_recolor(style_selector_t selector=GPART_MAIN)                      { this->remove_local_style_prop(GSTYLE_IMAGE_RECOLOR, selector);        }
    inline void   remove_image_recolor_opa(style_selector_t selector=GPART_MAIN)                  { this->remove_local_style_prop(GSTYLE_IMAGE_RECOLOR_OPA, selector);    }     


    void pad_top(int32_t value, style_selector_t selector=GPART_MAIN);
    void pad_bottom(int32_t value, style_selector_t selector=GPART_MAIN);
    void pad_left(int32_t value, style_selector_t selector=GPART_MAIN);
    void pad_right(int32_t value, style_selector_t selector=GPART_MAIN);
    void pad_row(int32_t value, style_selector_t selector=GPART_MAIN);
    void pad_column(int32_t value, style_selector_t selector=GPART_MAIN);
    inline void pad_inner(int32_t value, style_selector_t selector=GPART_MAIN)                    { this->pad_row(value,selector); this->pad_column(value,selector); }

    inline void padding_top(int32_t value, style_selector_t selector=GPART_MAIN)                  { this->pad_top(value,selector);    }
    inline void padding_bottom(int32_t value, style_selector_t selector=GPART_MAIN)               { this->pad_bottom(value,selector); }
    inline void padding_left(int32_t value, style_selector_t selector=GPART_MAIN)                 { this->pad_left(value,selector);   }
    inline void padding_right(int32_t value, style_selector_t selector=GPART_MAIN)                { this->pad_right(value,selector);  }
    inline void padding_row(int32_t value, style_selector_t selector=GPART_MAIN)                  { this->pad_row(value,selector);    }
    inline void padding_column(int32_t value, style_selector_t selector=GPART_MAIN)               { this->pad_column(value,selector); }
    inline void padding_inner(int32_t value, style_selector_t selector=GPART_MAIN)                { this->pad_inner(value,selector);  }

    inline void padding(int32_t pad_top, int32_t pad_bottom, int32_t pad_left, int32_t pad_right, style_selector_t selector=GPART_MAIN)
    {
      this->pad_top   (pad_top    , selector);
      this->pad_bottom(pad_bottom , selector);
      this->pad_left  (pad_left   , selector);
      this->pad_right (pad_right  , selector);
    }

    inline void padding(int32_t pad_top, int32_t pad_bottom, int32_t pad_left, int32_t pad_right, int32_t pad_inner, style_selector_t selector=GPART_MAIN)
    {
      this->pad_top   (pad_top    , selector);
      this->pad_bottom(pad_bottom , selector);
      this->pad_left  (pad_left   , selector);
      this->pad_right (pad_right  , selector);
      this->pad_row   (pad_inner  , selector);
      this->pad_column(pad_inner  , selector);
    }

    inline void padding(int32_t pad_top, int32_t pad_bottom, int32_t pad_left, int32_t pad_right, int32_t pad_row, int32_t pad_column, style_selector_t selector=GPART_MAIN)
    {
      this->pad_top   (pad_top    , selector);
      this->pad_bottom(pad_bottom , selector);
      this->pad_left  (pad_left   , selector);
      this->pad_right (pad_right  , selector);
      this->pad_row   (pad_row    , selector);
      this->pad_column(pad_column , selector);
    }


    inline void padding(int32_t value, style_selector_t selector=GPART_MAIN)                      { this->pad_all(value, selector);  this->pad_gap(value, selector);   }
    inline void padding_ver(int32_t value, style_selector_t selector=GPART_MAIN)                  { this->pad_ver(value, selector);       }
    inline void padding_hor(int32_t value, style_selector_t selector=GPART_MAIN)                  { this->pad_hor(value, selector);       }

    void margin_top(int32_t value, style_selector_t selector=GPART_MAIN);
    void margin_bottom(int32_t value, style_selector_t selector=GPART_MAIN);
    void margin_left(int32_t value, style_selector_t selector=GPART_MAIN);
    void margin_right(int32_t value, style_selector_t selector=GPART_MAIN);

    inline void margin(int32_t margin_top, int32_t margin_bottom, int32_t margin_left, int32_t margin_right, style_selector_t selector=GPART_MAIN)
    {
      this->margin_top   (margin_top    , selector);
      this->margin_bottom(margin_bottom , selector);
      this->margin_left  (margin_left   , selector);
      this->margin_right (margin_right  , selector);
    }

    void bg_color(color_t value, style_selector_t selector=GPART_MAIN);
    void bg_opa(opa_t value, style_selector_t selector=GPART_MAIN);
    inline void bg_color(color_t value, opa_t opa, style_selector_t selector=GPART_MAIN)            { this->bg_color(value, selector); this->bg_opa(opa, selector); }

    void bg_grad_color(color_t value, style_selector_t selector=GPART_MAIN);
    void bg_grad_dir(grad_dir_t value, style_selector_t selector=GPART_MAIN);
    void bg_main_stop(int32_t value, style_selector_t selector=GPART_MAIN);
    void bg_grad_stop(int32_t value, style_selector_t selector=GPART_MAIN);
    void bg_main_opa(opa_t value, style_selector_t selector=GPART_MAIN);
    void bg_grad_opa(opa_t value, style_selector_t selector=GPART_MAIN);
    void bg_grad(const lv_grad_dsc_t * value, style_selector_t selector=GPART_MAIN);

    inline void color(color_t value, style_selector_t selector=GPART_MAIN)                          { this->bg_color(value, selector);      }
    inline void color(color_t main_color, color_t grad_color, style_selector_t selector=GPART_MAIN) { this->bg_color(main_color, selector); this->bg_grad_color(grad_color, selector); if( this->bg_grad_dir(selector) == GRAD_DIR_NONE) this->bg_grad_dir(GRAD_DIR_VER, selector);   }
    inline void color(color_t main_color, color_t grad_color, grad_dir_t grad_dir, style_selector_t selector=GPART_MAIN) { this->bg_color(main_color, selector); this->bg_grad_color(grad_color, selector); this->bg_grad_dir(grad_dir, selector);                                    }
    inline void grad_color(color_t value, style_selector_t selector=GPART_MAIN)                     { this->bg_grad_color(value, selector); if( this->bg_grad_dir(selector) == GRAD_DIR_NONE) this->bg_grad_dir(GRAD_DIR_VER, selector);                                              }
    inline void grad_dir(grad_dir_t value, style_selector_t selector=GPART_MAIN)                    { this->bg_grad_dir(value, selector);   }
    inline void color_stop(int32_t value, style_selector_t selector=GPART_MAIN)                     { this->bg_main_stop(value, selector);  }
    inline void grad_stop(int32_t value, style_selector_t selector=GPART_MAIN)                      { this->bg_grad_stop(value, selector);  }

    void bg_image_src(const void * value, style_selector_t selector=GPART_MAIN);
    void bg_image_opa(opa_t value, style_selector_t selector=GPART_MAIN);
    void bg_image_recolor(color_t value, style_selector_t selector=GPART_MAIN);
    void bg_image_recolor_opa(opa_t value, style_selector_t selector=GPART_MAIN);
    void bg_image_tiled(bool value, style_selector_t selector=GPART_MAIN);

    inline void image(const void * value, style_selector_t selector=GPART_MAIN)                   { this->bg_image_src(value, selector);                                                   }
    inline void image(const img_t* value, style_selector_t selector=GPART_MAIN)                   { this->bg_image_src((const void *)value, selector);                                     }
    inline void image(const img_t& value, style_selector_t selector=GPART_MAIN)                   { this->bg_image_src((const void *)&value, selector);                                    }
    inline void image(const void * value, opa_t opa, style_selector_t selector=GPART_MAIN)        { this->bg_image_src(value, selector);   this->bg_image_opa(opa, selector);              }
    inline void image(const img_t* value, opa_t opa, style_selector_t selector=GPART_MAIN)        { this->bg_image_src((const void *)value, selector);  this->bg_image_opa(opa, selector); }
    inline void image(const img_t& value, opa_t opa, style_selector_t selector=GPART_MAIN)        { this->bg_image_src((const void *)&value, selector); this->bg_image_opa(opa, selector); }
    // inline void image_opa(opa_t value, style_selector_t selector=GPART_MAIN)                      { this->bg_image_opa(value, selector);                                                }
    // inline void image_color(color_t value, style_selector_t selector=GPART_MAIN)                  { this->bg_image_recolor(value, selector);                                            }
    // inline void image_color(color_t value, opa_t opa, style_selector_t selector=GPART_MAIN)       { this->bg_image_recolor(value, selector); this->bg_image_recolor_opa(opa, selector); }
    // inline void image_color_opa(opa_t value, style_selector_t selector=GPART_MAIN)                { this->bg_image_recolor_opa(value, selector);                                        }
    inline void image_tiled(bool value, style_selector_t selector=GPART_MAIN)                     { this->bg_image_tiled(value, selector);                                              }

    void border_color(color_t value, style_selector_t selector=GPART_MAIN);
    void border_opa(opa_t value, style_selector_t selector=GPART_MAIN);
    void border_width(int32_t value, style_selector_t selector=GPART_MAIN);
    inline void border(int32_t value, style_selector_t selector=GPART_MAIN)                                                     { this->border_width(value, selector);  }
    inline void border(int32_t value, color_t color, style_selector_t selector=GPART_MAIN)                                      { this->border_width(value, selector); this->border_color(color, selector); }
    inline void border(int32_t value, color_t color, opa_t opa, style_selector_t selector=GPART_MAIN)                           { this->border_width(value, selector); this->border_color(color, selector); this->border_opa(opa, selector);  }
    void border_side(border_side_t value, style_selector_t selector=GPART_MAIN);
    void border_post(bool value, style_selector_t selector=GPART_MAIN);
    void outline_width(int32_t value, style_selector_t selector=GPART_MAIN);
    void outline_color(color_t value, style_selector_t selector=GPART_MAIN);
    void outline_opa(opa_t value, style_selector_t selector=GPART_MAIN);
    void outline_pad(int32_t value, style_selector_t selector=GPART_MAIN);
    void shadow_width(int32_t value, style_selector_t selector=GPART_MAIN);
    inline void shadow(int32_t value, style_selector_t selector=GPART_MAIN)                                                     { this->shadow_width(value, selector);  }
    inline void shadow(int32_t value, color_t color, style_selector_t selector=GPART_MAIN)                                      { this->shadow_width(value, selector); this->shadow_color(color,selector); }
    inline void shadow(int32_t shadow_width, int32_t shadow_spread, color_t color, style_selector_t selector=GPART_MAIN)        { this->shadow_width(shadow_width, selector); this->shadow_spread(shadow_spread, selector);  this->shadow_color(color,selector); }
    void shadow_offset_x(int32_t value, style_selector_t selector=GPART_MAIN);
    void shadow_offset_y(int32_t value, style_selector_t selector=GPART_MAIN);
    inline void shadow_offset(int32_t x_ofs, int32_t y_ofs, style_selector_t selector=GPART_MAIN)                               { this->shadow_offset_x(x_ofs, selector); this->shadow_offset_y(y_ofs, selector);   }
    void shadow_spread(int32_t value, style_selector_t selector=GPART_MAIN);
    void shadow_color(color_t value, style_selector_t selector=GPART_MAIN);
    void shadow_opa(opa_t value, style_selector_t selector=GPART_MAIN);

    void image_opa(opa_t value, style_selector_t selector=GPART_MAIN);
    void image_recolor(color_t value, style_selector_t selector=GPART_MAIN);
    void image_recolor_opa(opa_t value, style_selector_t selector=GPART_MAIN);

    void line_width(int32_t value, style_selector_t selector=GPART_MAIN);
    void line_dash_width(int32_t value, style_selector_t selector=GPART_MAIN);
    void line_dash_gap(int32_t value, style_selector_t selector=GPART_MAIN);
    void line_rounded(bool value, style_selector_t selector=GPART_MAIN);
    void line_color(color_t value, style_selector_t selector=GPART_MAIN);
    void line_opa(opa_t value, style_selector_t selector=GPART_MAIN);
    void arc_width(int32_t value, style_selector_t selector=GPART_MAIN);
    void arc_rounded(bool value, style_selector_t selector=GPART_MAIN);
    void arc_color(color_t value, style_selector_t selector=GPART_MAIN);
    void arc_opa(opa_t value, style_selector_t selector=GPART_MAIN);
    void arc_image_src(const void * value, style_selector_t selector=GPART_MAIN);
    void text_color(color_t value, style_selector_t selector=GPART_MAIN);
    void text_opa(opa_t value, style_selector_t selector=GPART_MAIN);
    void text_font(const font_t * value, style_selector_t selector=GPART_MAIN);
    inline void font(const font_t *value, style_selector_t selector=GPART_MAIN)                 { this->text_font(value, selector);         }
    inline void font(const font_t &value, style_selector_t selector=GPART_MAIN)                 { this->text_font(&value, selector);        }
    inline void font(const font_t *value, color_t color, style_selector_t selector=GPART_MAIN)  { this->text_font(value, selector);  this->text_color(color, selector);   }
    inline void font(const font_t &value, color_t color, style_selector_t selector=GPART_MAIN)  { this->text_font(&value, selector); this->text_color(color, selector);   }
    inline void font_color(color_t value, style_selector_t selector=GPART_MAIN)                 { this->text_color(value, selector);        }
    void text_letter_space(int32_t value, style_selector_t selector=GPART_MAIN);
    void text_line_space(int32_t value, style_selector_t selector=GPART_MAIN);
    void text_decor(text_decor_t value, style_selector_t selector=GPART_MAIN);
    inline void letter_space(int32_t value, style_selector_t selector=GPART_MAIN)               { this->text_letter_space(value, selector); }
    inline void line_space(int32_t value, style_selector_t selector=GPART_MAIN)                 { this->text_line_space(value,selector);    }
    inline void decor(text_decor_t value, style_selector_t selector=GPART_MAIN)                 { this->text_decor(value,selector);         }

    void text_align(text_align_t value, style_selector_t selector=GPART_MAIN);
    void radius(int32_t value, style_selector_t selector=GPART_MAIN);
    void clip_corner(bool value, style_selector_t selector=GPART_MAIN);

    inline void corner_radius(int32_t value, style_selector_t selector=GPART_MAIN)              { this->radius(value, selector);        }
    inline void corner_mask  (int32_t value, style_selector_t selector=GPART_MAIN)              { this->clip_corner(value, selector);   }
    inline void rounded(bool enable, style_selector_t selector=GPART_MAIN)                      { this->radius((enable)? RADIUS_CIRCLE:0, selector);        }

    void opa(opa_t value, style_selector_t selector=GPART_MAIN);
    void opa_layered(opa_t value, style_selector_t selector=GPART_MAIN);
    void color_filter_dsc(const color_filter_dsc_t * value, lv_style_selector_t selector=GPART_MAIN);
    void color_filter_opa(opa_t value, style_selector_t selector=GPART_MAIN);
    void anim(const anim_t * value, style_selector_t selector=GPART_MAIN);
    void anim_duration(uint32_t value, style_selector_t selector=GPART_MAIN);

    inline void anim_speed(uint32_t value, style_selector_t selector=GPART_MAIN)                { this->anim_duration(value, selector); }

    void transition(const style_transition_dsc_t * value, style_selector_t selector=GPART_MAIN);
    void transition(GTransition &transition, style_selector_t selector=GPART_MAIN);
    void blend_mode(blend_mode_t value, style_selector_t selector=GPART_MAIN);
    void style_layout(uint16_t value, style_selector_t selector=GPART_MAIN);
    void base_dir(base_dir_t value, style_selector_t selector=GPART_MAIN);

    void bitmap_mask_src(const void  *value, style_selector_t selector=GPART_MAIN);
    inline void mask(const void   *value, style_selector_t selector=GPART_MAIN)                 { this->bitmap_mask_src(value, selector);   }
    inline void mask(const img_t  *value, style_selector_t selector=GPART_MAIN)                 { this->bitmap_mask_src(value, selector);   }
    inline void mask(const img_t  &value, style_selector_t selector=GPART_MAIN)                 { this->bitmap_mask_src(&value, selector);  }
    void rotary_sensitivity( uint32_t value, style_selector_t selector=GPART_MAIN);

    /***************************/
    //  Layout : FLEX & GRID
    /***************************/

    #if LV_USE_FLEX

    inline void FLEX(flex_flow_t flex_flow, flex_align_t flex_main_place,flex_align_t flex_cross_place,flex_align_t flex_track_place, style_selector_t selector=GPART_MAIN)
    {
      this->layout(LAYOUT_FLEX);
      this->flex_flow(flex_flow, selector);
      this->flex_align(flex_main_place, flex_cross_place, flex_track_place, selector);
    }

    void style_flex_flow(flex_flow_t value, style_selector_t selector=GPART_MAIN);
    void style_flex_main_place(flex_align_t value, style_selector_t selector=GPART_MAIN);
    void style_flex_cross_place(flex_align_t value, style_selector_t selector=GPART_MAIN);
    void style_flex_track_place(flex_align_t value, style_selector_t selector=GPART_MAIN);
    void style_flex_grow(uint8_t value, style_selector_t selector=GPART_MAIN);

    inline void style_flex_align(flex_align_t flex_main_place,flex_align_t flex_cross_place,flex_align_t flex_track_place, style_selector_t selector=GPART_MAIN)
    {
      this->style_flex_main_place(flex_main_place , selector);
      this->style_flex_cross_place(flex_cross_place, selector);
      this->style_flex_track_place(flex_track_place, selector);
    }

    inline void flex_flow(uint8_t value, style_selector_t selector=GPART_MAIN)            { this->style_flex_flow(value, selector); }
    inline void flex_main_place(uint8_t value, style_selector_t selector=GPART_MAIN)      { this->style_flex_main_place(value, selector); }
    inline void flex_cross_place(uint8_t value, style_selector_t selector=GPART_MAIN)     { this->style_flex_cross_place(value, selector); }
    inline void flex_track_place(uint8_t value, style_selector_t selector=GPART_MAIN)     { this->style_flex_track_place(value, selector); }
    inline void flex_grow(uint8_t value, style_selector_t selector=GPART_MAIN)            { this->style_flex_grow(value, selector); }
    inline void flex_align(flex_align_t flex_main_place,flex_align_t flex_cross_place,flex_align_t flex_track_place, style_selector_t selector=GPART_MAIN)
    {
      this->style_flex_align(flex_main_place, flex_cross_place, flex_track_place, selector);
    }

    #endif /*LV_USE_FLEX*/

    #if LV_USE_GRID

    void grid_column_dsc_array(const int32_t * value, style_selector_t selector=GPART_MAIN);
    void grid_column_align(grid_align_t value, style_selector_t selector=GPART_MAIN);
    void grid_row_dsc_array(const int32_t * value, style_selector_t selector=GPART_MAIN);
    void grid_row_align(grid_align_t value, style_selector_t selector=GPART_MAIN);
    void grid_cell_column_pos(int32_t value, style_selector_t selector=GPART_MAIN);
    void grid_cell_x_align(grid_align_t value, style_selector_t selector=GPART_MAIN);
    void grid_cell_column_span(int32_t value, style_selector_t selector=GPART_MAIN);
    void grid_cell_row_pos(int32_t value, style_selector_t selector=GPART_MAIN);
    void grid_cell_y_align(grid_align_t value, style_selector_t selector=GPART_MAIN);
    void grid_cell_row_span(int32_t value, style_selector_t selector=GPART_MAIN);

    void grid_cell( int32_t col, int32_t row, style_selector_t selector=GPART_MAIN);
    void grid_cell_align(  grid_align_t cell_x_align, grid_align_t cell_y_align, style_selector_t selector=GPART_MAIN);
    void grid_cell_span( int32_t col_span, int32_t row_span, style_selector_t selector=GPART_MAIN);

    inline void grid_cell( int32_t col, int32_t row, grid_align_t cell_x_align, grid_align_t cell_y_align, style_selector_t selector=GPART_MAIN){
      this->grid_cell( col, row, selector);
      this->grid_cell_align( cell_x_align, cell_y_align, selector);
    }

    inline void grid_cell( int32_t col, int32_t row, grid_align_t cell_x_align, grid_align_t cell_y_align, int32_t offset_x, int32_t offset_y=0, style_selector_t selector=GPART_MAIN){
      this->grid_cell( col, row, selector);
      this->grid_cell_align( cell_x_align, cell_y_align, selector);
      this->translate(offset_x, offset_y, selector);
    }

    inline void grid_cell( int32_t col, int32_t row, int32_t col_span, int32_t row_span, style_selector_t selector=GPART_MAIN){
      this->grid_cell( col, row, selector);
      this->grid_cell_span( col_span, row_span, selector);
    }

    inline void grid_cell( int32_t col, int32_t row, int32_t col_span, int32_t row_span, grid_align_t cell_x_align, grid_align_t cell_y_align, int32_t offset_x, int32_t offset_y=0, style_selector_t selector=GPART_MAIN){
      this->grid_cell( col, row, selector);
      this->grid_cell_span( col_span, row_span, selector);
      this->grid_cell_align( cell_x_align, cell_y_align, selector);
      this->translate(offset_x, offset_y, selector);
    }

    inline void grid_cell_align( grid_align_t cell_x_align, grid_align_t cell_y_align, int32_t offset_x, int32_t offset_y=0, style_selector_t selector=GPART_MAIN){
      this->grid_cell_align(cell_x_align, cell_y_align, selector);
      this->translate(offset_x, offset_y, selector);
    }

    inline void cell_design(int32_t radius=8, color_t bg_color=TFT_COLOR_HEX(0x192221)){
      this->bg_color(bg_color);
      this->radius(radius);
    }

    #endif /*LV_USE_GRID*/

    /**
     * Set how the item should flow
     * @param flow an element of `flex_flow_t`.
     */
    void layout_flex_flow(flex_flow_t flow);

    /**
     * Set how to place (where to align) the items and tracks
     * @param main_place where to place the items on main axis (in their track). Any value of `flex_align_t`.
     * @param cross_place where to place the item in their track on the cross axis. `FLEX_ALIGN_START/END/CENTER`
     * @param track_cross_place where to place the tracks in the cross direction. Any value of `flex_align_t`.
     */
    void layout_flex_align(flex_align_t main_place, flex_align_t cross_place, flex_align_t track_cross_place);

    inline void flex_align(flex_align_t flex_align, gstate_t selector=GPART_MAIN )          { this->flex_align(flex_align, flex_align, flex_align, selector); }
    inline void content_align(flex_align_t flex_align, gstate_t selector=GPART_MAIN)        { this->flex_main_place(flex_align, selector);                    }

    /**
     * Sets the width or height (on main axis) to grow the object in order fill the free space
     * @param grow a value to set how much free space to take proportionally to other growing items.
     */
    void layout_flex_grow(uint8_t grow);

    void grid_dsc_array(const int32_t col_dsc[], const int32_t row_dsc[]);

    void grid_align(grid_align_t column_align, grid_align_t row_align);

    /**
     * Set the cell of an object. The object's parent needs to have grid layout, else nothing will happen
     * @param column_align the vertical alignment in the cell. `LV_GRID_START/END/CENTER/STRETCH`
     * @param col_pos column ID
     * @param col_span number of columns to take (>= 1)
     * @param row_align the horizontal alignment in the cell. `LV_GRID_START/END/CENTER/STRETCH`
     * @param row_pos row ID
     * @param row_span number of rows to take (>= 1)
     */
    // void grid_cell( grid_align_t column_align, int32_t col_pos, int32_t col_span,
    //                        grid_align_t row_align   , int32_t row_pos, int32_t row_span);
    void grid_cell( int32_t col_pos, int32_t row_pos, int32_t col_span, int32_t row_span, grid_align_t column_align, grid_align_t row_align );


    // void grid_cell(int32_t col_pos, int32_t row_pos);
    inline void grid_cell(grid_pos_t grid_pos)                    { this->grid_cell(grid_pos.col, grid_pos.row); }
    grid_pos_t grid_cell();

#if LV_USE_SNAPSHOT    
    draw_buf_t * capture(color_format_t cf=COLOR_FORMAT_ARGB8888);
    bool capture(String file_name);   // SD://filename.bmp/.jpg/.png  , SPIFFS:://filename.bmp/.jpg/.png  
#endif 

    /*=====================
    * Setter functions
    *====================*/

    /**
     * Set one or more flags
     * @param f     R-ed values from `flag_t` to set.
     */
    void add_flag(flag_t f);

    inline void addFlag(flag_t f)               { this->add_flag(f);  }

    /**
     * Remove one or more flags
     * @param f     OR-ed values from `flag_t` to set.
     */
    void remove_flag(flag_t f);

    inline void removeFlag(flag_t f)            { this->remove_flag(f); }
    inline void clearFlag(flag_t f)            { this->remove_flag(f); }

    /**
     * Set add or remove one or more flags.
     * @param f     OR-ed values from `flag_t` to update.
     * @param v     true: add the flags; false: remove the flags
     */
    void update_flag(flag_t f, bool v);

    /**
     * Add one or more gstates to the object. The other gstate bits will remain unchanged.
     * If specified in the styles, transition animation will be started from the previous gstate to the current.
     * @param state     the gstates to add. E.g `GSTATE_PRESSED | GSTATE_FOCUSED`
     */
    void add_gstate(gstate_t state);

    /**
     * Remove one or more gstates to the object. The other gstate bits will remain unchanged.
     * If specified in the styles, transition animation will be started from the previous gstate to the current.
     * @param state     the gstates to add. E.g `STATE_PRESSED | STATE_FOCUSED`
     */
    void remove_gstate(gstate_t state);

    /**
     * Add or remove one or more gstates to the object. The other state bits will remain unchanged.
     * @param state     the gstates to add. E.g `STATE_PRESSED | STATE_FOCUSED`
     * @param v         true: add the gstates; false: remove the gstates
     */
    void set_gstate(gstate_t state, bool v);

    inline void setState(gstate_t state, bool v)    { this->set_gstate(state, v);   }

    inline void hidden(bool enable)             { (enable)? this->addFlag(FLAG_HIDDEN)            : this->clearFlag(FLAG_HIDDEN);             }
    inline bool hidden()                        { return this->hasFlag(FLAG_HIDDEN);                                                          }
    inline void show(bool enable)               { this->hidden(!enable);                                                                      }
    inline bool show()                          { return !this->hidden();                                                                     }
    inline void visible(bool enable)            { this->show(enable);                                                                         }
    inline bool visible()                       { return this->show();                                                                        }
    inline void clickable(bool enable)          { (enable)? this->addFlag(FLAG_CLICKABLE)         : this->clearFlag(FLAG_CLICKABLE);          }
    inline bool clickable()                     { return this->hasFlag(FLAG_CLICKABLE);                                                       }
    inline void focusable(bool enable)          { (enable)? this->addFlag(FLAG_CLICK_FOCUSABLE)   : this->clearFlag(FLAG_CLICK_FOCUSABLE);    }
    inline bool focusable()                     { return this->hasFlag(FLAG_CLICK_FOCUSABLE);                                                 }
    inline void checkable(bool enable)          { (enable)? this->addFlag(FLAG_CHECKABLE)         : this->clearFlag(FLAG_CHECKABLE);          }
    inline bool checkable()                     { return this->hasFlag(FLAG_CHECKABLE);                                                       }
    inline void scrollable(bool enable)         { (enable)? this->addFlag(FLAG_SCROLLABLE)        : this->clearFlag(FLAG_SCROLLABLE);         }
    inline bool scrollable()                    { return this->hasFlag(FLAG_SCROLLABLE);                                                      }
    inline void scroll_elastic(bool enable)     { (enable)? this->addFlag(FLAG_SCROLL_ELASTIC)    : this->clearFlag(FLAG_SCROLL_ELASTIC);     }
    inline bool scroll_elastic()                { return this->hasFlag(FLAG_SCROLL_ELASTIC);                                                  }
    inline void scroll_momentum(bool enable)    { (enable)? this->addFlag(FLAG_SCROLL_MOMENTUM)   : this->clearFlag(FLAG_SCROLL_MOMENTUM);    }
    inline bool scroll_momentum()               { return this->hasFlag(FLAG_SCROLL_MOMENTUM);                                                 }
    inline void scroll_one(bool enable)         { (enable)? this->addFlag(FLAG_SCROLL_ONE)        : this->clearFlag(FLAG_SCROLL_ONE);         }
    inline bool scroll_one()                    { return this->hasFlag(FLAG_SCROLL_ONE);                                                      }
    inline void scroll_chain_hor(bool enable)   { (enable)? this->addFlag(FLAG_SCROLL_CHAIN_HOR)  : this->clearFlag(FLAG_SCROLL_CHAIN_HOR);   }
    inline bool scroll_chain_hor()              { return this->hasFlag(FLAG_SCROLL_CHAIN_HOR);                                                }
    inline void scroll_chain_ver(bool enable)   { (enable)? this->addFlag(FLAG_SCROLL_CHAIN_VER)  : this->clearFlag(FLAG_SCROLL_CHAIN_VER);   }
    inline bool scroll_chain_ver()              { return this->hasFlag(FLAG_SCROLL_CHAIN_VER);                                                }
    inline void scroll_chain(bool enable)       { (enable)? this->addFlag(FLAG_SCROLL_CHAIN)      : this->clearFlag(FLAG_SCROLL_CHAIN);       }
    inline bool scroll_chain()                  { return this->hasFlag(FLAG_SCROLL_CHAIN);                                                    }
    inline void scroll_on_focus(bool enable)    { (enable)? this->addFlag(FLAG_SCROLL_ON_FOCUS)   : this->clearFlag(FLAG_SCROLL_ON_FOCUS);    }
    inline bool scroll_on_focus()               { return this->hasFlag(FLAG_SCROLL_ON_FOCUS);                                                 }
    inline void scroll_with_arrow(bool enable)  { (enable)? this->addFlag(FLAG_SCROLL_WITH_ARROW) : this->clearFlag(FLAG_SCROLL_WITH_ARROW);  }
    inline bool scroll_with_arrow()             { return this->hasFlag(FLAG_SCROLL_WITH_ARROW);                                               }
    inline void snappable(bool enable)          { (enable)? this->addFlag(FLAG_SNAPPABLE)         : this->clearFlag(FLAG_SNAPPABLE);          }
    inline bool snappable()                     { return this->hasFlag(FLAG_SNAPPABLE);                                                       }
    inline void press_lock(bool enable)         { (enable)? this->addFlag(FLAG_PRESS_LOCK)        : this->clearFlag(FLAG_PRESS_LOCK);         }
    inline bool press_lock()                    { return this->hasFlag(FLAG_PRESS_LOCK);                                                      }
    inline void event_bubble(bool enable)       { (enable)? this->addFlag(FLAG_EVENT_BUBBLE)      : this->clearFlag(FLAG_EVENT_BUBBLE);       }
    inline bool event_bubble()                  { return this->hasFlag(FLAG_EVENT_BUBBLE);                                                    }
    inline void gesture_bubble(bool enable)     { (enable)? this->addFlag(FLAG_GESTURE_BUBBLE)    : this->clearFlag(FLAG_GESTURE_BUBBLE);     }
    inline bool gesture_bubble()                { return this->hasFlag(FLAG_GESTURE_BUBBLE);                                                  }
    inline void adv_hittest(bool enable)        { (enable)? this->addFlag(FLAG_ADV_HITTEST)       : this->clearFlag(FLAG_ADV_HITTEST);        }
    inline bool adv_hittest()                   { return this->hasFlag(FLAG_ADV_HITTEST);                                                     }
    inline void ignore_layout(bool enable)      { (enable)? this->addFlag(FLAG_IGNORE_LAYOUT)     : this->clearFlag(FLAG_IGNORE_LAYOUT);      }
    inline bool ignore_layout()                 { return this->hasFlag(FLAG_IGNORE_LAYOUT);                                                   }
    inline void floating(bool enable)           { (enable)? this->addFlag(FLAG_FLOATING)          : this->clearFlag(FLAG_FLOATING);           }
    inline bool floating()                      { return this->hasFlag(FLAG_FLOATING);                                                        }
    inline void overflow_visible(bool enable)   { (enable)? this->addFlag(FLAG_OVERFLOW_VISIBLE)  : this->clearFlag(FLAG_OVERFLOW_VISIBLE);   }
    inline bool overflow_visible()              { return this->hasFlag(FLAG_OVERFLOW_VISIBLE);                                                }
    inline void flex_in_new_track(bool enable)  { (enable)? this->addFlag(FLAG_FLEX_IN_NEW_TRACK) : this->clearFlag(FLAG_FLEX_IN_NEW_TRACK);  }
    inline bool flex_in_new_track()             { return this->hasFlag(FLAG_FLEX_IN_NEW_TRACK);                                               }
    inline void flex_new_line(bool enable)      { this->flex_in_new_track(enable);    }
    inline bool flex_new_line()                 { return this->flex_in_new_track();   }
    inline void flag_layout1(bool enable)       { (enable)? this->addFlag(FLAG_LAYOUT_1)          : this->clearFlag(FLAG_LAYOUT_1);           }
    inline bool flag_layout1()                  { return this->hasFlag(FLAG_LAYOUT_1);                                                        }
    inline void flag_layout2(bool enable)       { (enable)? this->addFlag(FLAG_LAYOUT_2)          : this->clearFlag(FLAG_LAYOUT_2);           }
    inline bool flag_layout2()                  { return this->hasFlag(FLAG_LAYOUT_2);                                                        }
    inline void flag_widget1(bool enable)       { (enable)? this->addFlag(FLAG_WIDGET_1)          : this->clearFlag(FLAG_WIDGET_1);           }
    inline bool flag_widget1()                  { return this->hasFlag(FLAG_WIDGET_1);                                                        }
    inline void flag_widget2(bool enable)       { (enable)? this->addFlag(FLAG_WIDGET_2)          : this->clearFlag(FLAG_WIDGET_2);           }
    inline bool flag_widget2()                  { return this->hasFlag(FLAG_WIDGET_2);                                                        }
    inline void top(bool enable)                { (enable)? this->addFlag(FLAG_TOP)               : this->clearFlag(FLAG_TOP);                }
    inline bool top()                           { return this->hasFlag(FLAG_TOP);                                                             }

    inline void checked(bool en)                { this->setState(GSTATE_CHECKED, en);     }
    inline bool checked()                       { return this->hasState(GSTATE_CHECKED);  }
    inline void disabled(bool en)               { this->setState(GSTATE_DISABLED, en);    }
    inline bool disabled()                      { return this->hasState(GSTATE_DISABLED); }
    inline bool pressed(bool en)                { this->setState(GSTATE_PRESSED, en);     }
    inline bool pressed()                       { return this->hasState(GSTATE_PRESSED);  }
    inline bool isPressed()                     { return this->pressed();                 }
    inline void inactive(bool en)               { this->disabled(en);                     }
    inline bool inactive()                      { return this->disabled();                }
    inline void active(bool en)                 { this->inactive(!en);                    }
    inline bool active()                        { return !this->inactive();               }
    inline void event_parent(bool en)           { this->event_bubble(en);                 }
    inline bool event_parent()                  { return this->event_bubble();            }

    inline bool isON()                          { return this->checked();                 }
    inline bool isOFF()                         { return !this->isON();                   }

    /*=======================
    * Getter functions
    *======================*/

    /**
     * Check if a given flag or all the given flags are set on an object.
     * @param f     the flag(s) to check (OR-ed values can be used)
     * @return      true: all flags are set; false: not all flags are set
     */
    bool has_flag(flag_t f);

    inline bool hasFlag(flag_t f)               { return this->has_flag(f);               }

    /**
     * Check if a given flag or any of the flags are set on an object.
     * @param f     the flag(s) to check (OR-ed values can be used)
     * @return      true: at lest one flag flag is set; false: none of the flags are set
     */
    bool has_flag_any(flag_t f);

    /**
     * Get the state of an object
     * @return      the gstate (OR-ed values from `gstate_t`)
     */
    gstate_t get_gstate();

    inline gstate_t getState()                  { return get_gstate();                      }
    

    /**
     * Check if the object is in a given gstate or not.
     * @param state     a state or combination of gstates to check
     * @return          true: `obj` is in `gstate`; false: `obj` is not in `gstate`
     */
    bool has_gstate(gstate_t state);

    inline bool hasState(gstate_t state)        { return this->has_gstate(state);           }

    /**
     * Get the group of the object
     * @return      the pointer to group of the object
     */
    group_t * get_group();

    // /**
    //  * Get the user_data field of the object
    //  * @return      the pointer to the user_data of the object
    //  */
    // static inline void * lv_obj_get_user_data(lv_obj_t * obj)
    // {
    //     return obj->user_data;
    // }

    /*=======================
    * Other functions
    *======================*/

    /**
     * Allocate special data for an object if not allocated yet.
     * @param obj   pointer to an object
     */
    void allocate_spec_attr();

    /**
     * Check the type of obj.
     * @param class_p   a class to check (e.g. `lv_slider_class`)
     * @return          true: `class_p` is the `obj` class.
     */
    bool check_type(const obj_class_t * class_p);

    /**
     * Check if any object has a given class (type).
     * It checks the ancestor classes too.
     * @param class_p   a class to check (e.g. `slider_class`)
     * @return          true: `obj` has the given class
     */
    bool has_class(const obj_class_t * class_p);

    /**
     * Get the class (type) of the object
     * @return      the class (type) of the object
     */
    const obj_class_t * get_class();

    inline String class_name()                                { return String(this->get_class()->name); }

    /**
     * Check if any object is still "alive".
     * @return          true: valid
     */
    bool is_valid();



    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Set the position of an object relative to the set alignment.
     * @param x         new x coordinate
     * @param y         new y coordinate
     * @note            With default alignment it's the distance from the top left corner
     * @note            E.g. ALIGN_CENTER alignment it's the offset from the center of the parent
     * @note            The position is interpreted on the content area of the parent
     * @note            The values can be set in pixel or in percentage of parent size with `PCT(v)`
     */
    void pos(int32_t x, int32_t y);

    inline void pos(Point p)                        { this->pos(p.x,p.y); }

    /**
     * Set the x coordinate of an object
     * @param x         new x coordinate
     * @note            With default alignment it's the distance from the top left corner
     * @note            E.g. LV_ALIGN_CENTER alignment it's the offset from the center of the parent
     * @note            The position is interpreted on the content area of the parent
     * @note            The values can be set in pixel or in percentage of parent size with `PCT(v)`
     */
    void set_x(int32_t x);


    /**
     * Set the y coordinate of an object
     * @param y         new y coordinate
     * @note            With default alignment it's the distance from the top left corner
     * @note            E.g. LV_ALIGN_CENTER alignment it's the offset from the center of the parent
     * @note            The position is interpreted on the content area of the parent
     * @note            The values can be set in pixel or in percentage of parent size with `lv_pct(v)`
     */
    void set_y(int32_t y);



    /**
     * Set the size of an object.
     * @param w         the new width
     * @param h         the new height
     * @note            possible values are:
     *                  pixel               simple set the size accordingly
     *                  SIZE_CONTENT        set the size to involve all children in the given direction
     *                  PCT(x)              to set size in percentage of the parent's content area size (the size without paddings).
     *                                      x should be in [0..1000]% range
     */
    void size(int32_t w, int32_t h);

    inline void size(GWidget* widget)         { if(widget == NULL) return; if(!widget->isCreated()) widget->create();  this->size(widget->width(), widget->height());  }
    inline void size(GWidget& widget)         { this->size(&widget);                      }
    inline void size(const img_t& img)        { this->size(img.header.w, img.header.h);   }
    inline void size(const img_t* img)        { this->size(img->header.w, img->header.h); }
    inline void size(Point sz)                { this->size(sz.x, sz.y);                   }
    // inline void size(int32_t sz)              { this->size(sz,sz);                        }

    Point size();

    /**
     * Recalculate the size of the object
     * @return          true: the size has been changed
     */
    bool refr_size();

    /**
     * Set the width of an object
     * @param w         the new width
     * @note            possible values are:
     *                  pixel               simple set the size accordingly
     *                  SIZE_CONTENT        set the size to involve all children in the given direction
     *                  PCT(x)              to set size in percentage of the parent's content area size (the size without paddings).
     *                                      x should be in [0..1000]% range
     */
    void width(int32_t w);

    inline void width(GWidget* widget)          { if(widget == NULL) return; if(!widget->isCreated()) widget->create();  this->width(widget->width());  }
    void        width(GWidget& widget)          { this->width(&widget);         }
    inline void width(const img_t& img)         { this->width(img.header.w);    }
    inline void width(const img_t* img)         { this->width(img->header.w);   }

    /**
     * Set the height of an object
     * @param h         the new height
     * @note            possible values are:
     *                  pixel               simple set the size accordingly
     *                  SIZE_CONTENT        set the size to involve all children in the given direction
     *                  PCT(x)              to set size in percentage of the parent's content area size (the size without paddings).
     *                                      x should be in [0..1000]% range
     */
    void height(int32_t h);

    inline void height(GWidget* widget)         { if(widget == NULL) return; if(!widget->isCreated()) widget->create();  this->height(widget->height());  }
    void        height(GWidget& widget)         { this->height(&widget);        }
    inline void height(const img_t& img)        { this->height(img.header.h);   }
    inline void height(const img_t* img)        { this->height(img->header.h);  }


    /**
     * Set the width reduced by the left and right padding and the border width.
     * @param w         the width without paddings in pixels
     */
    void content_width(int32_t w);

    inline void width_fit(int32_t w)          { this->content_width(w); }

    /**
     * Set the height reduced by the top and bottom padding and the border width.
     * @param h         the height without paddings in pixels
     */
    void content_height(int32_t h);

    inline void height_fit(int32_t w)          { this->content_height(w); }

    inline void content_size(int32_t w, int32_t h)      { this->content_width(w); this->content_height(h);  }

    /**
     * Set a layout for an object
     * @param layout    pointer to a layout descriptor to set
     */
    void set_layout(glayout_t layout);

    /**
     * Test whether the and object is positioned by a layout or not
     * @return true:    positioned by a layout; false: not positioned by a layout
     */
    bool is_layout_positioned();

    /**
     * Mark the object (whose children needs to be updated) for layout update.
     */
    void mark_layout_as_dirty();

    /**
     * Update the layout of an object (whose children needs to be updated).
     */
    void update_layout();

    /**
     * Change the alignment of an object.
     * @param align     type of alignment (see 'align_t' enum) `ALIGN_OUT_...` can't be used.
     */
    void _align(align_t align);

    /**
     * Change the alignment of an object and set new coordinates.
     * Equivalent to:
     * lv_obj_set_align(obj, align);
     * lv_obj_set_pos(obj, x_ofs, y_ofs);
     * @param align     type of alignment (see 'align_t' enum) `ALIGN_OUT_...` can't be used.
     * @param x_ofs     x coordinate offset after alignment
     * @param y_ofs     y coordinate offset after alignment
     */
    void _align(align_t align, int32_t x_ofs, int32_t y_ofs);


    /**
     * Align an object to an other object.
     * @param base      pointer to an other object (if NULL `obj`s parent is used). 'obj' will be aligned to it.
     * @param align     type of alignment (see 'align_t' enum)
     * @param x_ofs     x coordinate offset after alignment
     * @param y_ofs     y coordinate offset after alignment
     * @note            if the position or size of `base` changes `obj` needs to be aligned manually again
     */
    void _align_to(const obj_t * base, align_t align, int32_t x_ofs, int32_t y_ofs);


    /**
     * Copy the coordinates of an object to an area
     * @param coords    pointer to an area to store the coordinates
     */
    void get_coords(area_t * coords);

    /**
     * Get the x coordinate of object.
     * @return          distance of `obj` from the left side of its parent plus the parent's left padding
     * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
     *                  call `update_layout()`.
     * @note            Zero return value means the object is on the left padding of the parent, and not on the left edge.
     * @note            Scrolling of the parent doesn't change the returned value.
     * @note            The returned value is always the distance from the parent even if `obj` is positioned by a layout.
     */
    int32_t get_x();



    /**
     * Get the x2 coordinate of object.
     * @return          distance of `obj` from the right side of its parent plus the parent's right padding
     * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
     *                  call `update_layout()`.
     * @note            Zero return value means the object is on the right padding of the parent, and not on the right edge.
     * @note            Scrolling of the parent doesn't change the returned value.
     * @note            The returned value is always the distance from the parent even if `obj` is positioned by a layout.
     */
    int32_t get_x2();


    /**
     * Get the y coordinate of object.
     * @return          distance of `obj` from the top side of its parent plus the parent's top padding
     * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
     *                  call `update_layout()`.
     * @note            Zero return value means the object is on the top padding of the parent, and not on the top edge.
     * @note            Scrolling of the parent doesn't change the returned value.
     * @note            The returned value is always the distance from the parent even if `obj` is positioned by a layout.
     */
    int32_t get_y();


    /**
     * Get the y2 coordinate of object.
     * @return          distance of `obj` from the bottom side of its parent plus the parent's bottom padding
     * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
     *                  call `update_layout()`.
     * @note            Zero return value means the object is on the bottom padding of the parent, and not on the bottom edge.
     * @note            Scrolling of the parent doesn't change the returned value.
     * @note            The returned value is always the distance from the parent even if `obj` is positioned by a layout.
     */
    int32_t get_y2();



    /**
     * Get the actually set x coordinate of object, i.e. the offset form the set alignment
     * @return          the set x coordinate
     */
    int32_t get_x_aligned();

    /**
     * Get the actually set y coordinate of object, i.e. the offset form the set alignment
     * @return          the set y coordinate
     */
    int32_t get_y_aligned();

    /**
     * Get the width of an object
     * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
     *                  call `update_layout()`.
     * @return          the width in pixels
     */
    int32_t width();

    int32_t raw_width();

    /**
     * Get the height of an object
     * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
     *                  call `update_layout()`.
     * @return          the height in pixels
     */
    int32_t height();

    int32_t raw_height();

    /**
     * Get the width reduced by the left and right padding and the border width.
     * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
     *                  call `lv_obj_update_layout(obj)`.
     * @return          the width which still fits into its parent without causing overflow (making the parent scrollable)
     */
    int32_t content_width();

    inline int32_t width_fit()            { return this->content_width(); }

    /**
     * Get the height reduced by the top and bottom padding and the border width.
     * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
     *                  call `lv_obj_update_layout(obj)`.
     * @return          the height which still fits into the parent without causing overflow (making the parent scrollable)
     */
    int32_t content_height();

    inline int32_t height_fit()            { return this->content_height(); }


    /**
     * Get the area reduced by the paddings and the border width.
     * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
     *                  call `update_layout()`.
     * @param area      the area which still fits into the parent without causing overflow (making the parent scrollable)
     */
    void content_coords(area_t * area);

    /**
     * Get the width occupied by the "parts" of the widget. E.g. the width of all columns of a table.
     * @return          the width of the virtually drawn content
     * @note            This size independent from the real size of the widget.
     *                  It just tells how large the internal ("virtual") content is.
     */
    int32_t self_width();

    /**
     * Get the height occupied by the "parts" of the widget. E.g. the height of all rows of a table.
     * @return          the width of the virtually drawn content
     * @note            This size independent from the real size of the widget.
     *                  It just tells how large the internal ("virtual") content is.
     */
    int32_t self_height();

    /**
     * Handle if the size of the internal ("virtual") content of an object has changed.
     * @return          false: nothing happened; true: refresh happened
     */
    bool refresh_self_size();

    void refr_pos();

    void move_to(int32_t x, int32_t y);

    void move_children_by(int32_t x_diff, int32_t y_diff, bool ignore_floating);


#if defined V9_0_0
    /**
     * Transform a point using the angle and zoom style properties of an object
     * @param p             a point to transform, the result will be written back here too
     * @param recursive     consider the transformation properties of the parents too
     * @param inv           do the inverse of the transformation (-angle and 1/zoom)
     */
    void transform_point(point_t * p, bool recursive, bool inv);

    /**
     * Transform an area using the angle and zoom style properties of an object
     * @param area          an area to transform, the result will be written back here too
     * @param recursive     consider the transformation properties of the parents too
     * @param inv           do the inverse of the transformation (-angle and 1/zoom)
     */
    void transformed_area(area_t * area, bool recursive, bool inv);
#elif defined V_9_1_0

    /**
     * Transform a point using the angle and zoom style properties of an object
     * @param p             a point to transform, the result will be written back here too
     * @param flags         OR-ed valued of :cpp:enum:`lv_obj_point_transform_flag_t`
     */
    void transform_point(point_t * p, point_transform_flag_t flags);

    /**
     * Transform an array of points using the angle and zoom style properties of an object
     * @param points        the array of points to transform, the result will be written back here too
     * @param count         number of points in the array
     * @param flags         OR-ed valued of :cpp:enum:`lv_obj_point_transform_flag_t`
     */
    void transform_point_array(point_t points[], size_t count,
                                    point_transform_flag_t flags);

    /**
     * Transform an area using the angle and zoom style properties of an object
     * @param area          an area to transform, the result will be written back here too
     * @param flags         OR-ed valued of :cpp:enum:`lv_obj_point_transform_flag_t`
     */
    void transformed_area(area_t * area, point_transform_flag_t flags);
#endif // V9_0_0

    /**
     * Mark an area of an object as invalid.
     * The area will be truncated to the object's area and marked for redraw.
     * @param           area the area to redraw
     */
    void invalidate_area(const area_t * area);

    /**
     * Mark the object as invalid to redrawn its area
     */
    void invalidate();

    /**
     * Tell whether an area of an object is visible (even partially) now or not
     * @param area      the are to check. The visible part of the area will be written back here.
     * @return true     visible; false not visible (hidden, out of parent, on other screen, etc)
     */
    bool area_is_visible(area_t * area);

    /**
     * Tell whether an object is visible (even partially) now or not
     * @return      true: visible; false not visible (hidden, out of parent, on other screen, etc)
     */
    bool is_visible();

    /**
     * Set the size of an extended clickable area
     * @param size      extended clickable area in all 4 directions [px]
     */
    void set_ext_click_area(int32_t size);

    /**
     * Get the an area where to object can be clicked.
     * It's the object's normal area plus the extended click area.
     * @param area      store the result area here
     */
    void get_click_area(area_t * area);

    /**
     * Hit-test an object given a particular point in screen space.
     * @param point     screen-space point (absolute coordinate)
     * @return          true: if the object is considered under the point
     */
    bool hit_test(const point_t * point);

    /**
     * Clamp a width between min and max width. If the min/max width is in percentage value use the ref_width
     * @param width         width to clamp
     * @param min_width     the minimal width
     * @param max_width     the maximal width
     * @param ref_width     the reference width used when min/max width is in percentage
     * @return              the clamped width
     */
    int32_t clamp_width(int32_t width, int32_t min_width, int32_t max_width, int32_t ref_width);

    /**
     * Clamp a height between min and max height. If the min/max height is in percentage value use the ref_height
     * @param height         height to clamp
     * @param min_height     the minimal height
     * @param max_height     the maximal height
     * @param ref_height     the reference height used when min/max height is in percentage
     * @return              the clamped height
     */
    int32_t clamp_height(int32_t height, int32_t min_height, int32_t max_height, int32_t ref_height);

    /* --------- SCROLL API ------- */


    /*=====================
    * Setter functions
    *====================*/

    /**
     * Set how the scrollbars should behave.
     * @param mode      SCROLL_MODE_ON/OFF/AUTO/ACTIVE
     */
    void scrollbar_mode( scrollbar_mode_t mode);

    /**
     * Set the object in which directions can be scrolled
     * @param dir       the allow scroll directions. An element or OR-ed values of `dir_t`
     */
    void scroll_dir(dir_t dir);

    /**
     * Set where to snap the children when scrolling ends horizontally
     * @param align     the snap align to set from `scroll_snap_t`
     */
    void scroll_snap_x(scroll_snap_t align);

    /**
     * Set where to snap the children when scrolling ends vertically
     * @param align     the snap align to set from `scroll_snap_t`
     */
    void scroll_snap_y(scroll_snap_t align);

    /*=====================
    * Getter functions
    *====================*/

    /**
     * Get the current scroll mode (when to hide the scrollbars)
     * @param obj       pointer to an object
     * @return          the current scroll mode from `lv_scrollbar_mode_t`
     */
    scrollbar_mode_t scrollbar_mode();

    /**
     * Get the object in which directions can be scrolled
     * @param dir       the allow scroll directions. An element or OR-ed values of `dir_t`
     */
    dir_t scroll_dir();

    /**
     * Get where to snap the children when scrolling ends horizontally
     * @return          the current snap align from `scroll_snap_t`
     */
    scroll_snap_t scroll_snap_x();

    /**
     * Get where to snap the children when scrolling ends vertically
     * @return          the current snap align from `scroll_snap_t`
     */
    scroll_snap_t scroll_snap_y();

    /**
     * Get current X scroll position.
     * @return          the current scroll position from the left edge.
     *                  If the object is not scrolled return 0
     *                  If scrolled return > 0
     *                  If scrolled in (elastic scroll) return < 0
     */
    int32_t scroll_x();

    /**
     * Get current Y scroll position.
     * @return          the current scroll position from the top edge.
     *                  If the object is not scrolled return 0
     *                  If scrolled return > 0
     *                  If scrolled inside return < 0
     */
    int32_t scroll_y();

    /**
     * Return the height of the area above the object.
     * That is the number of pixels the object can be scrolled down.
     * Normally positive but can be negative when scrolled inside.
     * @return          the scrollable area above the object in pixels
     */
    int32_t scroll_top();

    /**
     * Return the height of the area below the object.
     * That is the number of pixels the object can be scrolled down.
     * Normally positive but can be negative when scrolled inside.
     * @return          the scrollable area below the object in pixels
     */
    int32_t scroll_bottom();

    /**
     * Return the width of the area on the left the object.
     * That is the number of pixels the object can be scrolled down.
     * Normally positive but can be negative when scrolled inside.
     * @return          the scrollable area on the left the object in pixels
     */
    int32_t scroll_left();

    /**
     * Return the width of the area on the right the object.
     * That is the number of pixels the object can be scrolled down.
     * Normally positive but can be negative when scrolled inside.
     * @return          the scrollable area on the right the object in pixels
     */
    int32_t scroll_right();

    /**
     * Get the X and Y coordinates where the scrolling will end for this object if a scrolling animation is in progress.
     * If no scrolling animation, give the current `x` or `y` scroll position.
     * @param end       pointer to store the result
     */
    void scroll_end(point_t * end);

    /*=====================
    * Other functions
    *====================*/

    /**
     * Scroll by a given amount of pixels
     * @param x         pixels to scroll horizontally
     * @param y         pixels to scroll vertically
     * @param anim_en   ANIM_ON: scroll with animation; ANIM_OFF: scroll immediately
     * @note            > 0 value means scroll right/bottom (show the more content on the right/bottom)
     * @note            e.g. dy = -20 means scroll down 20 px
     */
    void scroll_by(int32_t x, int32_t y, anim_enable_t anim_en=false);

    /**
     * Scroll by a given amount of pixels.
     * `dx` and `dy` will be limited internally to allow scrolling only on the content area.
     * @param dx        pixels to scroll horizontally
     * @param dy        pixels to scroll vertically
     * @param anim_en   ANIM_ON: scroll with animation; ANIM_OFF: scroll immediately
     * @note            e.g. dy = -20 means scroll down 20 px
     */
    void scroll_by_bounded(int32_t dx, int32_t dy, anim_enable_t anim_en=false);

    /**
     * Scroll to a given coordinate on an object.
     * `x` and `y` will be limited internally to allow scrolling only on the content area.
     * @param x         pixels to scroll horizontally
     * @param y         pixels to scroll vertically
     * @param anim_en   ANIM_ON: scroll with animation; ANIM_OFF: scroll immediately
     */
    void scroll_to(int32_t x, int32_t y, anim_enable_t anim_en=false);

    /**
     * Scroll to a given X coordinate on an object.
     * `x` will be limited internally to allow scrolling only on the content area.
     * @param x         pixels to scroll horizontally
     * @param anim_en   ANIM_ON: scroll with animation; ANIM_OFF: scroll immediately
     */
    void scroll_to_x(int32_t x, anim_enable_t anim_en=false);

    /**
     * Scroll to a given Y coordinate on an object
     * `y` will be limited internally to allow scrolling only on the content area.
     * @param y         pixels to scroll vertically
     * @param anim_en   ANIM_ON: scroll with animation; ANIM_OFF: scroll immediately
     */
    void scroll_to_y(int32_t y, anim_enable_t anim_en=false);

    /**
     * Scroll to an object until it becomes visible on its parent
     * @param anim_en   ANIM_ON: scroll with animation; ANIM_OFF: scroll immediately
     */
    void scroll_to_view(anim_enable_t anim_en);

    /**
     * Scroll to an object until it becomes visible on its parent.
     * Do the same on the parent's parent, and so on.
     * Therefore the object will be scrolled into view even it has nested scrollable parents
     * @param anim_en   ANIM_ON: scroll with animation; ANIM_OFF: scroll immediately
     */
    void scroll_to_view_recursive(anim_enable_t anim_en);

    // /**
    //  * Low level function to scroll by given x and y coordinates.
    //  * `LV_EVENT_SCROLL` is sent.
    //  * @param x         pixels to scroll horizontally
    //  * @param y         pixels to scroll vertically
    //  * @return          `LV_RESULT_INVALID`: to object was deleted in `LV_EVENT_SCROLL`;
    //  *                  `LV_RESULT_OK`: if the object is still valid
    //  */
    // gresult_t _scroll_by_raw(int32_t x, int32_t y);

    /**
     * Tell whether an object is being scrolled or not at this moment
     * @return      true: `obj` is being scrolled
     */
    bool is_scrolling();

    /**
     * Check the children of `obj` and scroll `obj` to fulfill the scroll_snap settings
     * @param anim_en   ANIM_ON/OFF
     */
    void update_snap(anim_enable_t anim_en);

    /**
     * Get the area of the scrollbars
     * @param hor   pointer to store the area of the horizontal scrollbar
     * @param ver   pointer to store the area of the vertical  scrollbar
     */
    void scrollbar_area(area_t * hor, area_t * ver);

    /**
     * Invalidate the area of the scrollbars
     */
    void scrollbar_invalidate();

    /**
     * Checks if the content is scrolled "in" and adjusts it to a normal position.
     * @param anim_en   ANIM_ON/OFF
     */
    void readjust_scroll(anim_enable_t anim_en);


    // ------------------------------------------------------
    /* คำสั่งปรับแต่ง design ให้ scrollbar */
    inline void scrollbar_pad_top(int32_t value)            { GObject::pad_top(value, (gstate_t)(GPART_SCROLLBAR));     }
    inline void scrollbar_pad_bottom(int32_t value)         { GObject::pad_bottom(value, (gstate_t)(GPART_SCROLLBAR));  }
    inline void scrollbar_pad_left(int32_t value)           { GObject::pad_left (value, (gstate_t)(GPART_SCROLLBAR));   }
    inline void scrollbar_pad_right(int32_t value)          { GObject::pad_right (value, (gstate_t)(GPART_SCROLLBAR));  }
    inline void scrollbar_pad(int32_t value)                { GObject::pad_all(value, (gstate_t)(GPART_SCROLLBAR));     }

    /* --------- EVENT API ------- */
    event_handler_t  fn_onclicked = NULL;
#if LV_VERSION_CHECK(9, 3, 0)
    event_handler_t  fn_ondoubleclicked = NULL;
#endif
    event_handler_t  fn_onpressed = NULL;
    event_handler_t  fn_onpressing = NULL;
    event_handler_t  fn_onpresslost = NULL;
    event_handler_t  fn_onreleased = NULL;
    event_handler_t  fn_onlongpressed = NULL;
    event_handler_t  fn_onlongpressed_repeat = NULL;
    event_handler_t  fn_onvaluechanged = NULL;
    event_handler_t  fn_ondelete  = NULL;
    event_handler_t  fn_ongesture = NULL;
    event_handler_t  fn_ondrawmain = NULL;
    event_handler_t  fn_ondrawmain_begin = NULL;
    event_handler_t  fn_ondrawmain_end = NULL;
    event_handler_t  fn_ondrawtask = NULL;
    event_handler_t  fn_onfocused = NULL;
    event_handler_t  fn_ondefocused = NULL;
    event_handler_t  fn_onsizechanged = NULL;
    event_handler_t  fn_onstylechanged = NULL;
    event_cb_t       _event_cb    = NULL;

    inline void event_cb(event_cb_t event_cb, void* user_data=NULL)   { if(!this->isCreated()) this->create();  this->_event_cb = event_cb;  this->user_data(user_data);  }
    inline event_cb_t  event_cb()                       { return _event_cb; }

    inline void onClicked(event_handler_t fn)           { if(!this->isCreated()) this->create();  fn_onclicked = fn;            }
#if LV_VERSION_CHECK(9, 3, 0)
    inline void onDoubleClicked(event_handler_t fn)     { if(!this->isCreated()) this->create();  fn_ondoubleclicked = fn;      }
#endif
    inline void onPressed(event_handler_t fn)           { if(!this->isCreated()) this->create();  fn_onpressed = fn;            }
    inline void onPressing(event_handler_t fn)          { if(!this->isCreated()) this->create();  fn_onpressing = fn;           }
    inline void onReleased(event_handler_t fn)          { if(!this->isCreated()) this->create();  fn_onreleased = fn;           }
    inline void onPressLost(event_handler_t fn)         { if(!this->isCreated()) this->create();  fn_onpresslost = fn;          }
    inline void onLongPressed(event_handler_t fn)       { if(!this->isCreated()) this->create();  fn_onlongpressed = fn;        }
    inline void onLongPressedRepeat(event_handler_t fn) { if(!this->isCreated()) this->create();  fn_onlongpressed_repeat = fn; }
    inline void onDelete(event_handler_t fn)            { if(!this->isCreated()) this->create();  fn_ondelete = fn;             }
    inline void onGesture(event_handler_t fn)           { if(!this->isCreated()) this->create();  fn_ongesture = fn;            }
    inline void onDrawMain(event_handler_t fn)          { if(!this->isCreated()) this->create();  fn_ondrawmain = fn;           }
    inline void onDrawMainBegin(event_handler_t fn)     { if(!this->isCreated()) this->create();  fn_ondrawmain_begin = fn;     }
    inline void onDrawMainEnd(event_handler_t fn)       { if(!this->isCreated()) this->create();  fn_ondrawmain_end = fn;       }
    inline void onDrawTask(event_handler_t fn)          { if(!this->isCreated()) this->create();  fn_ondrawtask = fn;           }
    inline void onFocused(event_handler_t fn)           { if(!this->isCreated()) this->create();  fn_onfocused = fn;            }
    inline void onDefocused(event_handler_t fn)         { if(!this->isCreated()) this->create();  fn_ondefocused = fn;          }
    inline void onSizeChanged(event_handler_t fn)       { if(!this->isCreated()) this->create();  fn_onsizechanged = fn;        }
    inline void onStyleChanged(event_handler_t fn)      { if(!this->isCreated()) this->create();  fn_onstylechanged = fn;       }
    inline void onValueChanged(event_handler_t fn)      { if(!this->isCreated()) this->create();  fn_onvaluechanged = fn;  /*this->event_send(EVENT_VALUE_CHANGED);*/ }

    inline void onClicked(event_handler_t fn, void*user_data)           { if(!this->isCreated()) this->create();  fn_onclicked = fn; this->user_data(user_data);            }
#if LV_VERSION_CHECK(9, 3, 0)
    inline void onDoubleClicked(event_handler_t fn, void*user_data)     { if(!this->isCreated()) this->create();  fn_ondoubleclicked = fn;  this->user_data(user_data);     }
#endif
    inline void onPressed(event_handler_t fn, void*user_data)           { if(!this->isCreated()) this->create();  fn_onpressed = fn;  this->user_data(user_data);           }
    inline void onPressing(event_handler_t fn, void*user_data)          { if(!this->isCreated()) this->create();  fn_onpressing = fn;  this->user_data(user_data);          }
    inline void onReleased(event_handler_t fn, void*user_data)          { if(!this->isCreated()) this->create();  fn_onreleased = fn;   this->user_data(user_data);         }
    inline void onLongPressed(event_handler_t fn, void*user_data)       { if(!this->isCreated()) this->create();  fn_onlongpressed = fn;  this->user_data(user_data);       }
    inline void onLongPressedRepeat(event_handler_t fn, void*user_data) { if(!this->isCreated()) this->create();  fn_onlongpressed_repeat = fn; this->user_data(user_data); }
    inline void onDelete(event_handler_t fn, void*user_data)            { if(!this->isCreated()) this->create();  fn_ondelete = fn;   this->user_data(user_data);           }
    inline void onGesture(event_handler_t fn, void*user_data)           { if(!this->isCreated()) this->create();  fn_ongesture = fn;   this->user_data(user_data);          }
    inline void onDrawMain(event_handler_t fn, void*user_data)          { if(!this->isCreated()) this->create();  fn_ondrawmain = fn;  this->user_data(user_data);          }
    inline void onDrawMainBegin(event_handler_t fn, void*user_data)     { if(!this->isCreated()) this->create();  fn_ondrawmain_begin = fn;  this->user_data(user_data);    }
    inline void onDrawMainEnd(event_handler_t fn, void*user_data)       { if(!this->isCreated()) this->create();  fn_ondrawmain_end = fn;  this->user_data(user_data);      }
    inline void onDrawTask(event_handler_t fn, void*user_data)          { if(!this->isCreated()) this->create();  fn_ondrawtask = fn; this->user_data(user_data);           }
    inline void onFocused(event_handler_t fn, void*user_data)           { if(!this->isCreated()) this->create();  fn_onfocused = fn;  this->user_data(user_data);           }
    inline void onDefocused(event_handler_t fn, void*user_data)         { if(!this->isCreated()) this->create();  fn_ondefocused = fn;   this->user_data(user_data);        }
    inline void onSizeChanged(event_handler_t fn, void*user_data)       { if(!this->isCreated()) this->create();  fn_onsizechanged = fn;  this->user_data(user_data);       }
    inline void onStyleChanged(event_handler_t fn, void*user_data)      { if(!this->isCreated()) this->create();  fn_onstylechanged = fn;  this->user_data(user_data);      }
    inline void onValueChanged(event_handler_t fn, void*user_data)      { if(!this->isCreated()) this->create();  fn_onvaluechanged = fn;  this->user_data(user_data); /*this->event_send(EVENT_VALUE_CHANGED);*/ }

    bool        event_send(event_t event, void * event_data=NULL);
    inline bool send_event(event_t event, void * event_data=NULL);
    void *      event_data();

    GWidget* event_target();
    GWidget* event_current_target();

    inline void hookDrawTask(bool en)                   { this->addFlag(FLAG_SEND_DRAW_TASK_EVENTS);          }
    inline bool hookDrawTask()                          { return this->hasFlag(FLAG_SEND_DRAW_TASK_EVENTS);   }

    draw_task_t*        draw_task();
    Point               event_old_size();
    layer_t*            draw_layer(lv_event_t* e=NULL);
    area_t&             draw_area();
    inline area_t       inner_area()                    { area_t area = { 0, 0, this->width()-1, this->height()-1}; return area; }
    gpart_t             draw_part();
    draw_task_type_t    draw_type();
    uint32_t            draw_id1();
    uint32_t            draw_id2();

    draw_base_dsc_t*    draw_base_dsc();
    draw_rect_dsc_t*    draw_rect_dsc();
    draw_line_dsc_t*    draw_line_dsc();
    draw_fill_dsc_t*    draw_fill_dsc();
    draw_border_dsc_t*  draw_border_dsc();
    draw_label_dsc_t*   draw_label_dsc();
    draw_image_dsc_t*   draw_image_dsc();
    draw_arc_dsc_t*     draw_arc_dsc();
    draw_box_shadow_dsc_t* draw_box_shadow_dsc();
    draw_triangle_dsc_t*draw_triangle_dsc();

    void init_draw_rect_dsc(gpart_t part, draw_rect_dsc_t& rect_dsc);
    void init_draw_label_dsc(gpart_t part, draw_label_dsc_t& label_dsc);
    void init_draw_image_dsc(gpart_t part, draw_image_dsc_t& image_dsc);
    void init_draw_line_dsc(gpart_t part, draw_line_dsc_t& line_dsc);
    void init_draw_arc_dsc(gpart_t part, draw_arc_dsc_t& arc_dsc);

    void softdrawRect(draw_rect_dsc_t & draw_rect_dsc, area_t *area);
    void softdrawLabel(draw_label_dsc_t& draw_label_dsc, area_t *area);
    void softdrawImage(draw_image_dsc_t& draw_image_dsc, area_t *area);
    void softdrawArc(draw_arc_dsc_t& draw_arc_dsc);
    void softdrawTriangle(draw_triangle_dsc_t& draw_tri_dsc);
    void softdrawLine(draw_line_dsc_t& draw_line_dsc);

    inline area_t softdraw_make_area(int32_t w, int32_t h, align_t align, int32_t ofs_x=0, int32_t ofs_y=0) {
      area_t area = { 0, 0, w-1, h-1};
      area_align(this->draw_area(), area, align, ofs_x, ofs_y);
      return area;
    }

    inline void softdrawRect(draw_rect_dsc_t & draw_rect_dsc, area_t &area) {
      this->softdrawRect( draw_rect_dsc, &area);
    }

    inline area_t softdrawRect( int32_t w, int32_t h, color_t color, int32_t radius, int32_t border_width, color_t border_color, opa_t opa=OPA_COVER, align_t align=ALIGN_CENTER, int32_t ofs_x=0, int32_t ofs_y=0)
    {
      lv_draw_rect_dsc_t rect_dsc;
      lv_draw_rect_dsc_init(&rect_dsc);
      lv_obj_init_draw_rect_dsc(this->obj, LV_PART_MAIN, &rect_dsc);

      rect_dsc.bg_color = TFT_COLOR(color);
      rect_dsc.bg_opa = opa;
      rect_dsc.radius = radius;
      rect_dsc.border_width = border_width;
      rect_dsc.border_color = TFT_COLOR(border_color);
      
      area_t rect_area = { 0, 0, w-1, h-1};
      area_align(this->draw_area(), rect_area, align, ofs_x, ofs_y);
      lv_draw_rect(this->draw_layer(), &rect_dsc, &rect_area);

      return rect_area;
    }

    inline area_t softdrawRect( int32_t w, int32_t h, color_t color, int32_t radius, align_t align=ALIGN_CENTER, int32_t ofs_x=0, int32_t ofs_y=0)
    {
      return this->softdrawRect(w, h, color, radius, 0, TFT_BLACK, OPA_COVER, align, ofs_x, ofs_y);
    }

    inline area_t softdrawRect( int32_t w, int32_t h, color_t color, align_t align=ALIGN_CENTER, int32_t ofs_x=0, int32_t ofs_y=0)
    {
      return this->softdrawRect(w, h, color, 0, 0, TFT_BLACK, OPA_COVER, align, ofs_x, ofs_y);
    }

    inline void softdrawLabel(draw_label_dsc_t& draw_label_dsc, area_t &area) {
      this->softdrawLabel( draw_label_dsc, &area);
    }

    inline void softdrawLabel(String text, const font_t& font= prasanmit_35, color_t color=TFT_WHITE, align_t align=ALIGN_CENTER, int32_t ofs_x=0, int32_t ofs_y=0)
    {
      lv_draw_label_dsc_t label_dsc;
      lv_draw_label_dsc_init(&label_dsc);
      lv_obj_init_draw_label_dsc(this->obj, LV_PART_MAIN, &label_dsc);

      label_dsc.text = text.c_str();
      label_dsc.text_length = text.length();
      label_dsc.font = &font;
      label_dsc.color = TFT_COLOR(color);

      area_t text_area;
      text_get_area(&text_area, &label_dsc);
      area_align(&this->draw_area(), &text_area, align, ofs_x, ofs_y);
      this->softdrawLabel( label_dsc, text_area);
    }

    inline void softdrawLabel(String text, align_t align, int32_t ofs_x=0, int32_t ofs_y=0)
    {
      this->softdrawLabel(text, prasanmit_35, TFT_WHITE, align, ofs_x, ofs_y);
    }

    inline void softdrawLabel(String text, color_t color, align_t align, int32_t ofs_x=0, int32_t ofs_y=0)
    {
      this->softdrawLabel(text, prasanmit_35, color, align, ofs_x, ofs_y);
    }

    inline void softdrawImage(draw_image_dsc_t& draw_image_dsc, area_t &area) {
      this->softdrawImage( draw_image_dsc, &area);
    }

    inline void softdrawImage(draw_image_dsc_t& draw_image_dsc, align_t align=ALIGN_CENTER, int32_t ofs_x=0, int32_t ofs_y=0) {
      const img_t *image_src = (const img_t *) draw_image_dsc.src;

      area_t img_area = {0,0, image_src->header.w-1, image_src->header.h-1};
      lv_point_t size_scaled;
      size_scaled.x = image_src->header.w * draw_image_dsc.scale_x / LV_SCALE_NONE; 
      size_scaled.y = image_src->header.h * draw_image_dsc.scale_y / LV_SCALE_NONE;

      area_align(&this->draw_area(), &img_area, ALIGN_TOP_LEFT, 0, 0);
      switch(align){
        case ALIGN_TOP_LEFT:
          /* OK */
          break;
        case ALIGN_TOP:
          area_move(&img_area,  this->width()/2, 0);
          area_move(&img_area, -size_scaled.x/2, 0);
          break;
        case ALIGN_TOP_RIGHT:
          area_move(&img_area,  this->width(), 0);
          area_move(&img_area, -size_scaled.x, 0);
          break;
        case ALIGN_LEFT:
          area_move(&img_area,  0,  this->height()/2);
          area_move(&img_area,  0, -size_scaled.y/2);
          break;
        case ALIGN_CENTER:
          area_move(&img_area,  this->width()/2,  this->height()/2);
          area_move(&img_area, -size_scaled.x/2, -size_scaled.y/2);
          break;
        case ALIGN_RIGHT:
          area_move(&img_area,  this->width(),  this->height()/2);
          area_move(&img_area, -size_scaled.x, -size_scaled.y/2);
          break;
        case ALIGN_BOTTOM_LEFT:
          area_move(&img_area,  0,  this->height());
          area_move(&img_area,  0, -size_scaled.y);
          break;
        case ALIGN_BOTTOM:
          area_move(&img_area,  this->width()/2,  this->height());
          area_move(&img_area,  -size_scaled.x/2, -size_scaled.y);
          break;
        case ALIGN_BOTTOM_RIGHT:
          area_move(&img_area,  this->width(),  this->height());
          area_move(&img_area,  -size_scaled.x, -size_scaled.y);
          break;
      }
      area_move(&img_area, ofs_x, ofs_y);
      lv_draw_image( this->draw_layer(), &draw_image_dsc, &img_area );
    }

    inline void softdrawImage(const img_t* image_src, int32_t scale /* 512 double size, 128 half size.*/, align_t align=ALIGN_CENTER, int32_t ofs_x=0, int32_t ofs_y=0)
    {
      lv_draw_image_dsc_t img_dsc;
      lv_draw_image_dsc_init(&img_dsc);
      lv_obj_init_draw_image_dsc(this->obj, LV_PART_MAIN, &img_dsc);

      img_dsc.src = image_src;
      img_dsc.scale_x = scale;
      img_dsc.scale_y = scale;
      img_dsc.pivot.x = 0;
      img_dsc.pivot.y = 0;

      area_t img_area = {0,0, image_src->header.w-1, image_src->header.h-1};

      lv_point_t size_scaled;
      size_scaled.x = image_src->header.w * scale / LV_SCALE_NONE; 
      size_scaled.y = image_src->header.h * scale / LV_SCALE_NONE;

      area_align(&this->draw_area(), &img_area, ALIGN_TOP_LEFT, 0, 0);
      switch(align){
        case ALIGN_TOP_LEFT:
          /* OK */
          break;
        case ALIGN_TOP:
          area_move(&img_area,  this->width()/2, 0);
          area_move(&img_area, -size_scaled.x/2, 0);
          break;
        case ALIGN_TOP_RIGHT:
          area_move(&img_area,  this->width(), 0);
          area_move(&img_area, -size_scaled.x, 0);
          break;
        case ALIGN_LEFT:
          area_move(&img_area,  0,  this->height()/2);
          area_move(&img_area,  0, -size_scaled.y/2);
          break;
        case ALIGN_CENTER:
          area_move(&img_area,  this->width()/2,  this->height()/2);
          area_move(&img_area, -size_scaled.x/2, -size_scaled.y/2);
          break;
        case ALIGN_RIGHT:
          area_move(&img_area,  this->width(),  this->height()/2);
          area_move(&img_area, -size_scaled.x, -size_scaled.y/2);
          break;
        case ALIGN_BOTTOM_LEFT:
          area_move(&img_area,  0,  this->height());
          area_move(&img_area,  0, -size_scaled.y);
          break;
        case ALIGN_BOTTOM:
          area_move(&img_area,  this->width()/2,  this->height());
          area_move(&img_area,  -size_scaled.x/2, -size_scaled.y);
          break;
        case ALIGN_BOTTOM_RIGHT:
          area_move(&img_area,  this->width(),  this->height());
          area_move(&img_area,  -size_scaled.x, -size_scaled.y);
          break;
      }
      area_move(&img_area, ofs_x, ofs_y);
      lv_draw_image( this->draw_layer(), &img_dsc, &img_area );
    }

    inline void softdrawImage(const img_t* image_src, align_t align=ALIGN_CENTER, int32_t ofs_x=0, int32_t ofs_y=0)
    {
      this->softdrawImage( image_src, 256, align, ofs_x, ofs_y);
    }

    inline void softdrawImage(const img_t& image_src, int32_t scale /* 512 double size, 128 half size.*/, align_t align=ALIGN_CENTER, int32_t ofs_x=0, int32_t ofs_y=0)
    {
      this->softdrawImage( &image_src, scale, align, ofs_x, ofs_y);
    }

    inline void softdrawImage(const img_t& image_src, align_t align=ALIGN_CENTER, int32_t ofs_x=0, int32_t ofs_y=0)
    {
      this->softdrawImage( &image_src, 256, align, ofs_x, ofs_y);
    }

    inline void softdrawImage(const img_t* image_src, int32_t scale /* 512 double size, 128 half size.*/, float angle /*0.0 - 360.0*/, align_t align=ALIGN_CENTER, int32_t ofs_x=0, int32_t ofs_y=0)
    {
      lv_draw_image_dsc_t img_dsc;
      lv_draw_image_dsc_init(&img_dsc);
      lv_obj_init_draw_image_dsc(this->obj, LV_PART_MAIN, &img_dsc);

      img_dsc.src = image_src;
      img_dsc.scale_x = scale;
      img_dsc.scale_y = scale;
      img_dsc.pivot.x = image_src->header.w/2;
      img_dsc.pivot.y = image_src->header.h/2;
      img_dsc.rotation = (int32_t)(angle*10);

      area_t img_area = {0,0, image_src->header.w-1, image_src->header.h-1};

      lv_point_t size_scaled;
      size_scaled.x = image_src->header.w * scale / LV_SCALE_NONE; 
      size_scaled.y = image_src->header.h * scale / LV_SCALE_NONE;

      area_align(&this->draw_area(), &img_area, ALIGN_TOP_LEFT, 0, 0);
      switch(align){
        case ALIGN_TOP_LEFT:
          /* OK */
          break;
        case ALIGN_TOP:
          area_move(&img_area,  this->width()/2, 0);
          area_move(&img_area, -size_scaled.x/2, 0);
          break;
        case ALIGN_TOP_RIGHT:
          area_move(&img_area,  this->width(), 0);
          area_move(&img_area, -size_scaled.x, 0);
          break;
        case ALIGN_LEFT:
          area_move(&img_area,  0,  this->height()/2);
          area_move(&img_area,  0, -size_scaled.y/2);
          break;
        case ALIGN_CENTER:
          area_move(&img_area,  this->width()/2,  this->height()/2);
          area_move(&img_area, -size_scaled.x/2, -size_scaled.y/2);
          break;
        case ALIGN_RIGHT:
          area_move(&img_area,  this->width(),  this->height()/2);
          area_move(&img_area, -size_scaled.x, -size_scaled.y/2);
          break;
        case ALIGN_BOTTOM_LEFT:
          area_move(&img_area,  0,  this->height());
          area_move(&img_area,  0, -size_scaled.y);
          break;
        case ALIGN_BOTTOM:
          area_move(&img_area,  this->width()/2,  this->height());
          area_move(&img_area,  -size_scaled.x/2, -size_scaled.y);
          break;
        case ALIGN_BOTTOM_RIGHT:
          area_move(&img_area,  this->width(),  this->height());
          area_move(&img_area,  -size_scaled.x, -size_scaled.y);
          break;
      }
      area_move(&img_area, ofs_x, ofs_y);
      lv_draw_image( this->draw_layer(), &img_dsc, &img_area );
    }

    inline void softdrawImage(const img_t& image_src, int32_t scale /* 512 double size, 128 half size.*/, float angle, align_t align=ALIGN_CENTER, int32_t ofs_x=0, int32_t ofs_y=0)
    {
      this->softdrawImage(&image_src, scale, angle, align, ofs_x, ofs_y);
    }

    inline void softdrawImage(const img_t* image_src, int32_t scale /* 512 double size, 128 half size.*/, Point c){
      this->softdrawImage(image_src, scale, ALIGN_TOP_LEFT, c.x - (image_src->header.w * scale/256)/2, c.y - (image_src->header.h*scale/256)/2);
    }

    inline void softdrawImage(const img_t& image_src, int32_t scale /* 512 double size, 128 half size.*/, Point c){
      this->softdrawImage(&image_src, scale, c);
    }

    inline void softdrawLine(Point p1, Point p2, int32_t line_width=1, int32_t dash_width=-1, int32_t dash_gap=-1, color_t color=TFT_WHITE, opa_t opa=OPA_COVER, bool round_start=false, bool round_end=false){
      lv_draw_line_dsc_t line_dsc;
      lv_draw_line_dsc_init(&line_dsc);
      lv_obj_init_draw_line_dsc(this->obj, LV_PART_MAIN, &line_dsc);
      line_dsc.width = line_width;
      line_dsc.color = TFT_COLOR(color);
      line_dsc.opa   = opa;
      line_dsc.p1.x  = this->coords()->x1 + p1.x;
      line_dsc.p1.y  = this->coords()->y1 + p1.y;
      line_dsc.p2.x  = this->coords()->x1 + p2.x;
      line_dsc.p2.y  = this->coords()->y1 + p2.y;
      if(dash_width > 0) {
        line_dsc.dash_width = dash_width;
        line_dsc.dash_gap = dash_gap;
      }
      line_dsc.round_start = round_start;
      line_dsc.round_end   = round_end;
      lv_draw_line(this->draw_layer(), &line_dsc);
    }

    inline void softdrawLine(Point p1, Point p2, int32_t line_width, color_t color=TFT_WHITE, opa_t opa=OPA_COVER, bool round_start=false, bool round_end=false){
      this->softdrawLine(p1, p2, line_width, -1, -1, color, opa, round_start, round_end);
    }

    hit_test_info_t*    hit_test_info();

    inline int32_t event_target_id()                    { return this->child_id(this->event_target());  }
    inline widget_type_t widget_type()                  { return this->_widget_type;                    }


    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Send an event to the object
     * @param event_code    the type of the event from `event_t`
     * @param param         arbitrary data depending on the widget type and the event. (Usually `NULL`)
     * @return RESULT_OK: `obj` was not deleted in the event; RESULT_INVALID: `obj` was deleted in the event_code
     */
    gresult_t _send_event(event_t event_code, void * param=NULL);

    /**
     * Used by the widgets internally to call the ancestor widget types's event handler
     * @param class_p   pointer to the class of the widget (NOT the ancestor class)
     * @param e         pointer to the event descriptor
     * @return          RESULT_OK: the target object was not deleted in the event; RESULT_INVALID: it was deleted in the event_code
     */
    gresult_t event_base(const obj_class_t * class_p, lv_event_t * e);

    /**
     * Get the current target of the event. It's the object which event handler being called.
     * If the event is not bubbled it's the same as "original" target.
     * @param e     pointer to the event descriptor
     * @return      the target of the event_code
     */
    obj_t * event_get_current_target_obj(lv_event_t * e);

    /**
     * Get the object originally targeted by the event. It's the same even if the event is bubbled.
     * @param e     pointer to the event descriptor
     * @return      pointer to the original target of the event_code
     */
    obj_t * event_get_target_obj(lv_event_t * e);

    /**
     * Add an event handler function for an object.
     * Used by the user to react on event which happens with the object.
     * An object can have multiple event handler. They will be called in the same order as they were added.
     * @param filter    an event code (e.g. `LV_EVENT_CLICKED`) on which the event should be called. `EVENT_ALL` can be used to receive all the events.
     * @param event_cb  the new event function
     * @param           user_data custom data data will be available in `event_cb`
     */
    void add_event_cb(lv_event_cb_t event_cb, event_t filter=EVENT_ALL, void * user_data=NULL);

    uint32_t event_count();

    event_dsc_t * event_dsc(uint32_t index);

    bool remove_event(uint32_t index);

    bool remove_event_cb(lv_event_cb_t event_cb);

    /**
     * Remove an event_cb with user_data
     * @param event_cb      the event_cb of the event to remove
     * @param user_data     user_data
     * @return              the count of the event removed
     */
    uint32_t remove_event_cb_with_user_data(lv_event_cb_t event_cb, void * user_data);

    /**
     * Get the input device passed as parameter to indev related events.
     * @param e     pointer to an event
     * @return      the indev that triggered the event or NULL if called on a not indev related event
     */
    indev_t * event_get_indev(lv_event_t * e);

    /**
     * Get the draw context which should be the first parameter of the draw functions.
     * Namely: `LV_EVENT_DRAW_MAIN/POST`, `LV_EVENT_DRAW_MAIN/POST_BEGIN`, `LV_EVENT_DRAW_MAIN/POST_END`
     * @param e     pointer to an event
     * @return      pointer to a draw context or NULL if called on an unrelated event
     */
    layer_t * event_get_layer(lv_event_t * e);

    /**
     * Get the old area of the object before its size was changed. Can be used in `LV_EVENT_SIZE_CHANGED`
     * @param e     pointer to an event
     * @return      the old absolute area of the object or NULL if called on an unrelated event
     */
    const area_t * event_get_old_size(lv_event_t * e);

    /**
     * Get the key passed as parameter to an event. Can be used in `LV_EVENT_KEY`
     * @param e     pointer to an event
     * @return      the triggering key or NULL if called on an unrelated event
     */
    uint32_t event_get_key(lv_event_t * e);

    /**
     * Get the animation descriptor of a scrolling. Can be used in `LV_EVENT_SCROLL_BEGIN`
     * @param e     pointer to an event
     * @return      the animation that will scroll the object. (can be modified as required)
     */
    anim_t * event_get_scroll_anim(lv_event_t * e);

    /**
     * Set the new extra draw size. Can be used in `EVENT_REFR_EXT_DRAW_SIZE`
     * @param e     pointer to an event
     * @param size  The new extra draw size
     */
    void event_set_ext_draw_size(lv_event_t * e, int32_t size);

    /**
     * Get a pointer to an `lv_point_t` variable in which the self size should be saved (width in `point->x` and height `point->y`).
     * Can be used in `LV_EVENT_GET_SELF_SIZE`
     * @param e     pointer to an event
     * @return      pointer to `lv_point_t` or NULL if called on an unrelated event
     */
    point_t * event_get_self_size_info(lv_event_t * e);

    /**
     * Get a pointer to an `lv_hit_test_info_t` variable in which the hit test result should be saved. Can be used in `LV_EVENT_HIT_TEST`
     * @param e     pointer to an event
     * @return      pointer to `lv_hit_test_info_t` or NULL if called on an unrelated event
     */
    hit_test_info_t * event_get_hit_test_info(lv_event_t * e);

    /**
     * Get a pointer to an area which should be examined whether the object fully covers it or not.
     * Can be used in `LV_EVENT_HIT_TEST`
     * @param e     pointer to an event
     * @return      an area with absolute coordinates to check
     */
    const area_t * event_get_cover_area(lv_event_t * e);

    /**
     * Set the result of cover checking. Can be used in `LV_EVENT_COVER_CHECK`
     * @param e     pointer to an event
     * @param res   an element of ::lv_cover_check_info_t
     */
    void event_set_cover_res(lv_event_t * e, cover_res_t res);

    /**
     * Get the draw task which was just added.
     * Can be used in `LV_EVENT_DRAW_TASK_ADDED event`
     * @param e     pointer to an event
     * @return      the added draw task
     */
    draw_task_t * event_get_draw_task(lv_event_t * e);


    GWidget* gwidget();
    area_t*  coords();

    /**
     * Get the touch point on the widget.
     * 
     * @param absolute  true = relative to screen, false = relative to widget (default)
     * @return          The touch position as a Point.
     */
    Point touch_point(bool absolute=false);

    Point vect_point();
    inline void  drag_n_drop(bool en)               { this->_drag_n_drop = en;    }
    inline bool  drag_n_drop()                      { return this->_drag_n_drop;  }
    inline bool  draging()                          { return this->_draging;      }

    obj_t   *obj = NULL;
    GWidget *_par= NULL;
    bool    _created=false;


    GWidget *_widget_align_to = NULL;
    align_t _align_type= ALIGN_CENTER;
    int32_t _align_offset_x=0, _align_offset_y=0;
    int32_t _ext_draw_size=0;
    
    inline lv_event_t*  cur_event()                  { return _cur_event; }
    inline event_t      cur_event_code()             { return lv_event_get_code(_cur_event);         }
    inline void*        cur_event_param()            { return lv_event_get_param(this->cur_event()); }
    inline layer_t*     event_draw_layer()           { return lv_event_get_layer(this->cur_event()); } 

    lv_event_t *_cur_event;
    bool    _draging=false;
  protected:
    layout_t _layout = LAYOUT_NONE;
    std::unique_ptr<v_grid_dsc> _u_col_dsc;
    std::unique_ptr<v_grid_dsc> _u_row_dsc;

    widget_type_t _widget_type = WIDGET_TYPE_GRECT;
    int32_t _w= -1, _h= -1;
  private:
    void*   _user_data = NULL;
    bool    _drag_n_drop = false;
};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GOBJECT_H__
