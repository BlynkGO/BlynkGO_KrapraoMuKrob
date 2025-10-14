/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GChart.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GCHART_H__
#define __GCHART_H__


#include "GObject.h"

#define CHART_POINT_NONE     (INT32_MAX)

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

typedef String (*gchart_popup_format_cb_t)(chart_series_t* series, uint32_t id, int32_t y);

class GChart : public GObject {
  public:
    GChart(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GChart(GWidget* parent)                                  : GObject(parent)  {}
    GChart(uint32_t point_count, GWidget& parent=GScreen)    : GObject(&parent), _point_count(point_count) {}
    GChart(uint32_t point_count, uint8_t hdiv, uint8_t vdiv, GWidget& parent=GScreen)
       : GObject(&parent), _point_count(point_count), _hdiv(hdiv), _vdiv(vdiv) {}

    virtual ~GChart();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }


    /**
     * Set a new type for a chart
     * @param type      new type of the chart (from 'chart_type_t' enum)
     */
    void chart_type(chart_type_t type);  // CHART_TYPE_NONE, CHART_TYPE_LINE, CHART_TYPE_BAR, CHART_TYPE_SCATTER | CHART_TYPE_POINT

    void type(chart_type_t type)                            { this->chart_type(type);         }

    /**
     * Set the number of points on a data line on a chart
     * @param cnt       new number of points on the data lines
     */
    void point_count(uint32_t cnt);

    /**
     * Set the minimal and maximal y values on an axis
     * @param axis      `CHART_AXIS_PRIMARY_Y` or `CHART_AXIS_SECONDARY_Y`
     * @param min       minimum value of the y axis
     * @param max       maximum value of the y axis
     */
    void range(chart_axis_t axis, int32_t min, int32_t max);

    inline void range(int32_t vmin, int32_t vmax)       {  this->range(CHART_AXIS_PRIMARY_Y, vmin, vmax);   }

    /**
     * Set update mode of the chart object. Affects
     * @param update_mode      the update mode
     */
    void update_mode(chart_update_mode_t update_mode);  // CHART_UPDATE_MODE_SHIFT, CHART_UPDATE_MODE_CIRCULAR

    /**
     * Set the number of horizontal and vertical division lines
     * @param hdiv      number of horizontal division lines
     * @param vdiv      number of vertical division lines
     */
    void div_line_count(uint8_t hdiv, uint8_t vdiv);

    /**
     * Get the type of a chart
     * @return          type of the chart (from 'chart_type_t' enum)
     */
    chart_type_t chart_type(); // CHART_TYPE_NONE, CHART_TYPE_LINE, CHART_TYPE_BAR, CHART_TYPE_SCATTER

    inline chart_type_t type()                                { return this->_chart_type;   }

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
    uint32_t x_start_point(chart_series_t * ser);

    /**
     * Get the position of a point to the chart.
     * @param ser       pointer to series
     * @param id        the index.
     * @param p_out     store the result position here
     */
    void point_pos_by_id(chart_series_t * ser, uint32_t id, lv_point_t * p_out);

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
     * @param axis      the y axis to which the series should be attached (::CHART_AXIS_PRIMARY_Y or ::CHART_AXIS_SECONDARY_Y)
     * @return          pointer to the allocated data series or NULL on failure
     */
    chart_series_t * add_series(color_t color, chart_axis_t axis= CHART_AXIS_PRIMARY_Y);

    inline chart_series_t * createSerie(color_t color, chart_axis_t axis= CHART_AXIS_PRIMARY_Y)   { return this->add_series(color, axis);  }

    /**
     * Deallocate and remove a data series from a chart
     * @param obj       pointer to a chart object
     * @param series    pointer to a data series on 'chart'
     */
    void remove_series(chart_series_t * series);

    /**
     * Hide/Unhide a single series of a chart.
     * @param series    pointer to a series object
     * @param hide      true: hide the series
     */
    void hide_series(chart_series_t * series, bool hide);

    inline void show_series(chart_series_t * series, bool hide)     { this->hide_series(series, !hide); }

    /**
     * Change the color of a series
     * @param series    pointer to a series object
     * @param color     the new color of the series
     */
    void series_color(chart_series_t * series, color_t color);

    inline color_t series_color(chart_series_t *series) {
      this->create();
      return (series != NULL)? lv_color_to_u16(series->color) : TFT_BLACK;
    }

    /**
     * Set the index of the x-axis start point in the data array.
     * This point will be considers the first (left) point and the other points will be drawn after it.
     * @param ser       pointer to a data series on 'chart'
     * @param id        the index of the x point in the data array
     */
    void x_start_point(chart_series_t * ser, uint32_t id);

    /**
     * Get the next series.
     * @param ser      the previous series or NULL to get the first
     * @return          the next series or NULL if there is no more.
     */
    chart_series_t * series_next(const chart_series_t * ser=NULL);

    inline chart_series_t * series_first()                            { return this->series_next(NULL);    }

    /*=====================
    * Cursor
    *====================*/

    /**
     * Add a cursor with a given color
     * @param obj       pointer to chart object
     * @param color     color of the cursor
     * @param dir       direction of the cursor. `DIR_RIGHT/LEFT/TOP/DOWN/HOR/VER/ALL`. OR-ed values are possible
     * @return          pointer to the created cursor
     */
    chart_cursor_t  * add_cursor(color_t color, dir_t dir);

    /**
     * Set the coordinate of the cursor with respect to the paddings
     * @param cursor    pointer to the cursor
     * @param pos       the new coordinate of cursor relative to the chart
     */
    void cursor_pos(chart_cursor_t * cursor, lv_point_t * pos);

    /**
     * Stick the cursor to a point
     * @param cursor    pointer to the cursor
     * @param ser       pointer to a series
     * @param point_id  the point's index or `LV_CHART_POINT_NONE` to not assign to any points.
     */
    void cursor_point(chart_cursor_t * cursor, chart_series_t * ser,
                                  uint32_t point_id);

    /**
     * Get the coordinate of the cursor with respect to the paddings
     * @param cursor    pointer to cursor
     * @return          coordinate of the cursor as lv_point_t
     */
    lv_point_t cursor_point(chart_cursor_t * cursor);

    /*=====================
    * Set/Get value(s)
    *====================*/

    /**
     * Initialize all data points of a series with a value
     * @param ser       pointer to a data series on 'chart'
     * @param value     the new value for all points. `CHART_POINT_NONE` can be used to hide the points.
     */
    void all_value(chart_series_t * ser, int32_t value);

    /**
     * Set the next point's Y value according to the update mode policy.
     * @param ser       pointer to a data series on 'chart'
     * @param value     the new value of the next data
     */
    void next_value(chart_series_t * ser, int32_t value);

    inline void addPoint(chart_series_t * ser, int32_t value)       { this->next_value( ser, value);      }

    /**
     * Set the next point's X and Y value according to the update mode policy.
     * @param ser       pointer to a data series on 'chart'
     * @param x_value   the new X value of the next data
     * @param y_value   the new Y value of the next data
     */
    void next_value2(chart_series_t * ser, int32_t x_value, int32_t y_value);

    inline void addPoint(chart_series_t * ser, Point p)               { this->next_value2( ser, p.x, p.y);  }
    inline void addPoint(chart_series_t * ser, int32_t x, int32_t y)  { this->next_value2( ser, x, y);      }

    /**
     * Set an individual point's y value of a chart's series directly based on its index
     * @param ser     pointer to a data series on 'chart'
     * @param id      the index of the x point in the array
     * @param value   value to assign to array point
     */
    void series_value_by_id(chart_series_t * ser, uint32_t id, int32_t value);

    inline void value_by_id(chart_series_t * ser, uint32_t id, int32_t value)   { this->series_value_by_id(ser, id, value); }

    /**
     * Get an individual point's y value of a chart's series directly based on its index
     * @param ser     pointer to a data series on 'chart'
     * @param id      the index of the x point in the array
     * @param value   pointer to store the y value retrieved from the array point
     */
    void get_series_value_by_id(chart_series_t * ser, uint32_t id, int32_t * value);

    inline void get_value_by_id(chart_series_t * ser, uint32_t id, int32_t * value)
    {
      this->get_series_value_by_id(ser, id, value);
    }

    /**
     * Set an individual point's x and y value of a chart's series directly based on its index
     * Can be used only with `CHART_TYPE_SCATTER`.
     * @param ser       pointer to a data series on 'chart'
     * @param id        the index of the x point in the array
     * @param x_value   the new X value of the next data
     * @param y_value   the new Y value of the next data
     */
    void series_value_by_id2(chart_series_t * ser, uint32_t id, int32_t x_value,
                                  int32_t y_value);

    inline void value_by_id2(chart_series_t * ser, uint32_t id, int32_t x_value,
                                  int32_t y_value)
    {
      this->series_value_by_id2(ser, id, x_value, y_value);
    }

    /**
     * Set an external array for the y data points to use for the chart
     * NOTE: It is the users responsibility to make sure the `point_cnt` matches the external array size.
     * @param ser       pointer to a data series on 'chart'
     * @param array     external array of points for chart
     */
    void ext_y_array(chart_series_t * ser, int32_t array[]);

    /**
     * Set an external array for the x data points to use for the chart
     * NOTE: It is the users responsibility to make sure the `point_cnt` matches the external array size.
     * @param ser       pointer to a data series on 'chart'
     * @param array     external array of points for chart
     */
    void ext_x_array(chart_series_t * ser, int32_t array[]);

    /**
     * Get the array of y values of a series
     * @param ser   pointer to a data series on 'chart'
     * @return      the array of values with 'point_count' elements
     */
    int32_t * y_array(chart_series_t * ser);

    /**
     * Get the array of x values of a series
     * @param ser   pointer to a data series on 'chart'
     * @return      the array of values with 'point_count' elements
     */
    int32_t * x_array(chart_series_t * ser);

    /**
     * Get the index of the currently pressed point. It's the same for every series.
     * @param obj       pointer to a chart object
     * @return          the index of the point [0 .. point count] or CHART_POINT_NONE if no point is being pressed
     */
    uint32_t pressed_point();

    /**
     * Get the overall offset from the chart's side to the center of the first point.
     * In case of a bar chart it will be the center of the first column group
     * @return          the offset of the center
     */
    int32_t first_point_center_offset();


    void show_point(bool en);

    inline void touch_popup(bool en, gchart_popup_format_cb_t fn=NULL)        { this->_touch_popup = en; _fn_popup_format_cb = fn; }
    inline void draw_grad(bool en)                                            { this->_draw_grad = en; this->hookDrawTask(en);     }
    
    bool _draw_grad = false;
    bool _touch_popup = false;
    gchart_popup_format_cb_t _fn_popup_format_cb=NULL;

  private:
    chart_type_t _chart_type= CHART_TYPE_LINE | CHART_TYPE_POINT;
    uint32_t      _point_count = 0;
    uint8_t       _hdiv = 0;
    uint8_t       _vdiv = 0;

};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GCHART_H__
