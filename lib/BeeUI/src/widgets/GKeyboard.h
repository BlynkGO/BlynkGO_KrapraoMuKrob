/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GKeyboard.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GKEYBOARD_H__
#define __GKEYBOARD_H__


#include "GObject.h"
#include "GButtonMatrix.h"
#include "GTextArea.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GKeyboard : public GButtonMatrix {
  public:
    GKeyboard(GWidget& parent=GScreen)                      : GButtonMatrix(&parent) {}
    GKeyboard(GWidget* parent)                              : GButtonMatrix(parent)  {}
    virtual ~GKeyboard();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    /*=====================
    * Setter functions
    *====================*/

    /**
     * Assign a Text Area to the Keyboard. The pressed characters will be put there.
     * @param ta        pointer to a Text Area object to write there
     */
    void textarea(GTextArea &ta);

    void textarea(GTextArea *ta);

    /**
     * Set a new a mode (text or number map)
     * @param mode      the mode from 'keyboard_mode_t'
     */
    void keyboard_mode(keyboard_mode_t mode);

    inline void mode(keyboard_mode_t mode)            { this->keyboard_mode(mode);  }

    /**
     * Show the button title in a popover when pressed.
     * @param en        whether "popovers" mode is enabled
     */
    void popovers(bool en);

    /**
     * Set a new map for the keyboard
     * @param mode      keyboard map to alter 'lv_keyboard_mode_t'
     * @param map       pointer to a string array to describe the map.
     *                  See 'lv_buttonmatrix_set_map()' for more info.
     * @param ctrl_map  See 'lv_buttonmatrix_set_ctrl_map()' for more info.

    */
    void map(keyboard_mode_t mode,  const char * map[],
                                    const buttonmatrix_ctrl_t ctrl_map[]);

    /*=====================
    * Getter functions
    *====================*/

    /**
     * Assign a Text Area to the Keyboard. The pressed characters will be put there.
     * @return          pointer to the assigned Text Area object
     */
    GTextArea& textarea();

    /**
     * Set a new a mode (text or number map)
     * @return          the current mode from 'keyboard_mode_t'
     */
    keyboard_mode_t keyboard_mode();

    inline keyboard_mode_t mode()                       { return this->keyboard_mode(); }

    // /**
    //  * Tell whether "popovers" mode is enabled or not.
    //  * @return          true: "popovers" mode is enabled; false: disabled
    //  */
    // bool popovers();

    /**
     * Get the current map of a keyboard
     * @return          the current map
     */
    using GButtonMatrix::map;
    // inline const char ** map()                        {  return GButtonMatrix::map(); }

    /**
     * Get the index of the lastly "activated" button by the user (pressed, released, focused etc)
     * Useful in the `event_cb` to get the text of the button, check if hidden etc.
     * @return          index of the last released button (BUTTONMATRIX_BUTTON_NONE: if unset)
     */
    using GButtonMatrix::selected_button;
    // inline uint32_t lv_keyboard_get_selected_button(const lv_obj_t * obj)
    // {
    //     return lv_buttonmatrix_get_selected_button(obj);
    // }

    /**
     * Get the button's text
    //  * @param obj       pointer to button matrix object
     * @param btn_id    the index a button not counting new line characters.
     * @return          text of btn_index` button
     */
    using GButtonMatrix::button_text;
    // static inline const char * lv_keyboard_get_button_text(const lv_obj_t * obj, uint32_t btn_id)
    // {
    //     return lv_buttonmatrix_get_button_text(obj, btn_id);
    // }

    // EVENT API
    event_handler_t  fn_onready = NULL;
    inline void onReady(event_handler_t fn)           { if(!this->isCreated()) this->create();  fn_onready = fn;            }

  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GKEYBOARD_H__
