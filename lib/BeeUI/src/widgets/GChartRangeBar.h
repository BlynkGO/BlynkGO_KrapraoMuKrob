/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GChartRangeBar.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GCHART_RANGEBAR_H_
#define __GCHART_RANGEBAR_H_


#include "GObject.h"
#include "../widgets_extra/chart_rangebar/lv_chart_rangebar.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GChartRangeBar : public GObject {
  public:
    GChartRangeBar(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GChartRangeBar(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GChartRangeBar();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }


    /**
     * Set the number of points on a data line on a chart
     * @param cnt       new number of points on the data lines
     */
    void point_count(uint32_t cnt);

    /**
     * Set the minimal and maximal y values on an axis
     * @param axis      `CHART_RANGEBAR_AXIS_PRIMARY_Y` or `CHART_RANGEBAR_AXIS_SECONDARY_Y`
     * @param min       minimum value of the y axis
     * @param max       maximum value of the y axis
     */
    void range(chart_axis_t axis, int32_t min, int32_t max);

    inline void range(int32_t vmin, int32_t vmax)       {  this->range(CHART_AXIS_PRIMARY_Y, vmin, vmax);   }

    /**
     * Set update mode of the chart object. Affects
     * @param update_mode      the update mode
     */
    void update_mode(chart_update_mode_t update_mode);

    /**
     * Set the number of horizontal and vertical division lines
     * @param hdiv      number of horizontal division lines
     * @param vdiv      number of vertical division lines
     */
    void div_line_count(uint8_t hdiv, uint8_t vdiv);

    /**
     * Get the data point number per data line on chart
     * @return          point number on each data line
     */
    uint32_t point_count();

    /**
     * Get the current index of the x-axis start point in the data array
     * @param ser       pointer to a data series on 'chart'
     * @return          the index of the current x start point in the data array
     */
    uint32_t x_start_point(chart_rangebar_series_t * ser);

    /**
     * Get the position of a point to the chart.
     * @param ser       pointer to series
     * @param id        the index.
     * @param p_out_min store the result position of min here
     * @param p_out_max store the result position of max here
     */
    void point_pos_by_id(chart_rangebar_series_t * ser, uint32_t id, point_t * p_out_min, point_t * p_out_max);

    /**
     * Get the rangebar's column-width.
     */
    uint32_t column_width();

    inline uint32_t bar_width()           { return this->column_width();    }

    /**
     * Refresh a chart if its data line has changed
     */
    void refresh();

    /*======================
    * Series
    *=====================*/

    /**
     * Allocate and add a data series to the chart
     * @param color     color of the data series
     * @param axis      the y axis to which the series should be attached (::LV_CHART_RANGEBAR_AXIS_PRIMARY_Y or ::LV_CHART_RANGEBAR_AXIS_SECONDARY_Y)
     * @return          pointer to the allocated data series or NULL on failure
     */
    chart_rangebar_series_t * add_series(color_t color, chart_axis_t axis= CHART_AXIS_PRIMARY_Y);

    inline chart_rangebar_series_t * createSerie(color_t color, chart_axis_t axis= CHART_AXIS_PRIMARY_Y)   { return this->add_series(color, axis);  }

    /**
     * Deallocate and remove a data series from a chart
     * @param series    pointer to a data series on 'chart'
     */
    void remove_series(chart_rangebar_series_t * series);

    /**
     * Hide/Unhide a single series of a chart.
     * @param series    pointer to a series object
     * @param hide      true: hide the series
     */
    void hide_series(chart_rangebar_series_t * series, bool hide);

    inline void show_series(chart_rangebar_series_t * series, bool hide)     { this->hide_series(series, !hide); }

    /**
     * Change the color of a series
     * @param series    pointer to a series object
     * @param color     the new color of the series
     */
    void series_color(chart_rangebar_series_t * series, color_t color);

    /**
     * Get the color of a series
     * @param series    pointer to a series object
     * @return          the color of the series
     */
    color_t series_color(const chart_rangebar_series_t * series);

    /**
     * Set the index of the x-axis start point in the data array.
     * This point will be considers the first (left) point and the other points will be drawn after it.
     * @param ser       pointer to a data series on 'chart'
     * @param id        the index of the x point in the data array
     */
    void x_start_point(chart_rangebar_series_t * ser, uint32_t id);

    /**
     * Get the next series.
     * @param ser      the previous series or NULL to get the first
     * @return          the next series or NULL if there is no more.
     */
    chart_rangebar_series_t * series_next(const chart_rangebar_series_t * ser);

    inline chart_rangebar_series_t * series_first()                 { return this->series_next(NULL);    }

    /*=====================
    * Cursor
    *====================*/

    /**
     * Add a cursor with a given color
     * @param color     color of the cursor
     * @param dir       direction of the cursor. `DIR_RIGHT/LEFT/TOP/DOWN/HOR/VER/ALL`. OR-ed values are possible
     * @return          pointer to the created cursor
     */
    chart_rangebar_cursor_t  * add_cursor(color_t color, dir_t dir);

    /**
     * Set the coordinate of the cursor with respect to the paddings
     * @param cursor    pointer to the cursor
     * @param pos       the new coordinate of cursor relative to the chart
     */
    void cursor_pos(chart_rangebar_cursor_t * cursor, point_t * pos);

    /**
     * Stick the cursor to a point
     * @param cursor    pointer to the cursor
     * @param ser       pointer to a series
     * @param point_id  the point's index or `LV_CHART_RANGEBAR_POINT_NONE` to not assign to any points.
     */
    void cursor_point(chart_rangebar_cursor_t * cursor, chart_rangebar_series_t * ser,
                                  uint32_t point_id);

    /**
     * Get the coordinate of the cursor with respect to the paddings
     * @param cursor    pointer to cursor
     * @return          coordinate of the cursor as lv_point_t
     */
    point_t cursor_point(chart_rangebar_cursor_t * cursor);

    /*=====================
    * Set/Get value(s)
    *====================*/

    /**
     * Initialize all data points of a series with a value
     * @param ser       pointer to a data series on 'chart'
     * @param value     the new value for all points. `CHART_POINT_NONE` can be used to hide the points.
     */
    void all_value(chart_rangebar_series_t * ser, int32_t value_min, int32_t value_max);

    /**
     * Set the next point's Y value according to the update mode policy.
     * @param ser       pointer to a data series on 'chart'
     * @param value_min the new value min of the next data
     * @param value_max the new value max of the next data
     */
    void next_value(chart_rangebar_series_t * ser, int32_t value_min, int32_t value_max);

    inline void addBar(chart_rangebar_series_t * ser, int32_t value_min, int32_t value_max)       { this->next_value( ser, value_min, value_max);  }

    /**
     * Set an individual point's y value of a chart's series directly based on its index
     * @param ser     pointer to a data series on 'chart'
     * @param id      the index of the x point in the array
     * @param value_min   value_min to assign to array point
     * @param value_max   value_max to assign to array point
     */
    void value_by_id(chart_rangebar_series_t * ser, uint32_t id, int32_t value_min, int32_t value_max);

    /**
     * Get an individual point's y value of a chart's series directly based on its index
     * @param ser     pointer to a data series on 'chart'
     * @param id      the index of the x point in the array
     * @param value_min   [out] pointer to store the y_min value at the given index
     * @param value_max   [out] pointer to store the y_max value at the given index
     */
    void get_value_by_id(chart_rangebar_series_t * ser, uint32_t id, int32_t * value_min, int32_t * value_max);

    /**
     * Set an external array for the y data points to use for the chart
     * NOTE: It is the users responsibility to make sure the `point_cnt` matches the external array size.
     * @param ser       pointer to a data series on 'chart'
     * @param array     external array of points for chart
     */
    void ext_y_array(chart_rangebar_series_t * ser, int32_t array_min[], int32_t array_max[]);

    /**
     * Set an external array for the x data points to use for the chart
     * NOTE: It is the users responsibility to make sure the `point_cnt` matches the external array size.
     * @param ser       pointer to a data series on 'chart'
     * @param array     external array of points for chart
     */
    void ext_x_array(chart_rangebar_series_t * ser, int32_t array[]);

    /**
     * Get the array of y values of a series
     * @param ser   pointer to a data series on 'chart'
     * @return      the array of values min with 'point_count' elements
     */
    int32_t * y_array_min(chart_rangebar_series_t * ser);

    /**
     * Get the array of y values of a series
     * @param ser   pointer to a data series on 'chart'
     * @return      the array of values max with 'point_count' elements
     */
    int32_t * y_array_max(chart_rangebar_series_t * ser);

    /**
     * Get the array of x values of a series
     * @param ser   pointer to a data series on 'chart'
     * @return      the array of values with 'point_count' elements
     */
    int32_t * x_array(chart_rangebar_series_t * ser);

    /**
     * Get the index of the currently pressed point. It's the same for every series.
     * @return          the index of the point [0 .. point count] or CHART_POINT_NONE if no point is being pressed
     */
    uint32_t pressed_point(); 

    /**
     * Get the overall offset from the chart's side to the center of the first point.
     * In case of a bar chart it will be the center of the first column group
     * @return          the offset of the center
     */
    int32_t first_point_center_offset();

  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GCHART_RANGEBAR_H_
