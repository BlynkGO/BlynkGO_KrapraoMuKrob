/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GCalendar.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GCALENDAR_H__
#define __GCALENDAR_H__


#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GCalendar : public GObject {
  public:
    GCalendar(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GCalendar(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GCalendar();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    GStyle items;
    GStyle items_pressed;

    void title_font(const font_t &font);
    inline const font_t * title_font()                      { return GObject::text_font(GPART_INDICATOR);         }
    void title_color(color_t c);

    /*=====================
    * Setter functions
    *====================*/

    /**
     * Set the today's date
     * @param year      today's year
     * @param month     today's month [1..12]
     * @param day       today's day [1..31]
     */
    void today_date(uint32_t year, uint32_t month, uint32_t day);

    /**
     * Set the currently showed
     * @param year          today's year
     * @param month         today's month [1..12]
     */
    void showed_date(uint32_t year, uint32_t month);

    /**
     * Set the highlighted dates
     * @param highlighted   pointer to an `lv_calendar_date_t` array containing the dates.
     *                      Only the pointer will be saved so this variable can't be local which will be destroyed later.
     * @param date_num number of dates in the array
     */
    void highlighted_dates(calendar_date_t highlighted[], size_t date_num);

    /**
     * Set the name of the days
     * @param day_names     pointer to an array with the names.
     *                      E.g. `const char * days[7] = {"Sun", "Mon", ...}`
     *                      Only the pointer will be saved so this variable can't be local which will be destroyed later.
     */
    void day_names(const char ** day_names);

    /*=====================
    * Getter functions
    *====================*/

    /**
     * Get the button matrix object of the calendar.
     * It shows the dates and day names.
     * @return          pointer to a the button matrix
     */
    obj_t * get_btnmatrix();

    /**
     * Get the today's date
     * @return          return pointer to an `calendar_date_t` variable containing the date of today.
     */
    const calendar_date_t * today_date();

    /**
     * Get the currently showed
     * @return          pointer to an `lv_calendar_date_t` variable containing the date is being shown.
     */
    const calendar_date_t * showed_date();

    /**
     * Get the highlighted dates
     * @return          pointer to an `calendar_date_t` array containing the dates.
     */
    calendar_date_t * highlighted_dates();

    /**
     * Get the number of the highlighted dates
     * @return          number of highlighted days
     */
    size_t highlighted_dates_num();

    /**
     * Get the currently pressed day
     * @param date      store the pressed date here
     * @return          true: there is a valid pressed date
     *                  false: there is no pressed data
     */
    bool pressed_date(calendar_date_t * date);

    /**********************
     * Calendar Header แบบ Dropdown
     **********************/

    /**
     * Create a calendar header with drop-drowns to select the year and month
     * @return          the created header
     */
    obj_t * header_dropdown_create();

    /**
     * Sets a custom calendar year list
     * @param years_list    pointer to an const char array with the years list, see lv_dropdown set_options for more information.
     *                      E.g. `const char * years = "2023\n2022\n2021\n2020\n2019"
     *                      Only the pointer will be saved so this variable can't be local which will be destroyed later.
     */
    void header_dropdown_set_year_list(const char * years_list);

    /**********************
     * Calendar Header แบบ ลูกศรซ้ายขวา
     **********************/
    /**
     * Create a calendar header with drop-drowns to select the year and month
     * @return          the created header
     */
    obj_t * header_arrow_create();


  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GCALENDAR_H__
