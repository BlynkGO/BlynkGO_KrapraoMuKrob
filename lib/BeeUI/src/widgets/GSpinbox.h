/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GSpinbox.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GSPINBOX_H__
#define __GSPINBOX_H__


#include "GObject.h"
#include "GTextArea.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GSpinbox : public GTextArea {
  public:
    GSpinbox(GWidget& parent=GScreen)                       : GTextArea(&parent) {}
    GSpinbox(GWidget* parent)                               : GTextArea(parent)  {}
    virtual ~GSpinbox();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    inline  int toInt()                                     { return this->value(); }

    /*=====================
    * Setter functions
    *====================*/

    /**
     * Set spinbox value
     * @param v     value to be set
     */
    void value(int32_t v);

    /**
     * Set spinbox rollover function
     * @param rollover  true or false to enable or disable (default)
     */
    void rollover(bool rollover);

    /**
     * Set spinbox digit format (digit count and decimal format)
     * @param digit_count   number of digit excluding the decimal separator and the sign
     * @param sep_pos       number of digit before the decimal point. If 0, decimal point is not
     * shown
     */
    void digit_format(uint32_t digit_count, uint32_t sep_pos);

    /**
     * Set spinbox step
     * @param step  steps on increment/decrement. Can be 1, 10, 100, 1000, etc the digit that will change.
     */
    void step(uint32_t step);

    /**
     * Set spinbox value range
     * @param range_min maximum value, inclusive
     * @param range_max minimum value, inclusive
     */
    void range(int32_t range_min, int32_t range_max);

    /**
     * Set cursor position to a specific digit for edition
     * @param pos   selected position in spinbox
     */
    void cursor_pos(uint32_t pos);

    /**
     * Set direction of digit step when clicking an encoder button while in editing mode
     * @param direction     the direction (LV_DIR_RIGHT or LV_DIR_LEFT)
     */
    void digit_step_direction(dir_t direction);

    /*=====================
    * Getter functions
    *====================*/

    /**
     * Get spinbox rollover function status
     */
    bool rollover();

    /**
     * Get the spinbox numeral value (user has to convert to float according to its digit format)
     * @return      value integer value of the spinbox
     */
    int32_t value();

    /**
     * Get the spinbox step value (user has to convert to float according to its digit format)
     * @return      value integer step value of the spinbox
     */
    int32_t step();

    /*=====================
    * Other functions
    *====================*/

    /**
     * Select next lower digit for edition by dividing the step by 10
     */
    void step_next();

    /**
     * Select next higher digit for edition by multiplying the step by 10
     */
    void step_prev();

    /**
     * Increment spinbox value by one step
     */
    void increment();

    /**
     * Decrement spinbox value by one step
     */
    void decrement();

  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GSPINBOX_H__
