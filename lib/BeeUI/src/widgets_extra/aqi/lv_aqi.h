#ifndef LV_AQI_H
#define LV_AQI_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"
#include "utils/lvgl/src/core/lv_obj.h"
#include "utils/lvgl/src/core/lv_obj_private.h"   /* ต้องมี ไม่งั้น error */
#include "utils/lvgl/src/widgets/label/lv_label.h"
#include "utils/lvgl/src/widgets/label/lv_label_private.h"
#include "TridentTD_AQI.h"

/*********************
 *      DEFINES
 *********************/



/**********************
 *      TYPEDEFS
 **********************/
enum {
  LV_AQI_TYPE_US,
  LV_AQI_TYPE_TH,
  LV_AQI_TYPE_CN,
  LV_AQI_TYPE_MAX,
};
typedef uint8_t lv_aqi_type_t;

enum {
  LV_AQI_DISPLAY_AQI,
  LV_AQI_DISPLAY_PM25,
  LV_AQI_DISPLAY_PM10,
  LV_AQI_DISPLAY_PM1,
  LV_AQI_DISPLAY_MAX,
};
typedef uint8_t lv_aqi_display_type_t;

typedef struct _lv_aqi_t {
  lv_obj_t obj;
  lv_obj_t * warning_lb;   /* สำหรับ แสดงข้อความแจ้งเตือน ทำเป็น widget label เนื่องจากให้มีการ ทำ text rolling */
  lv_aqi_display_type_t display_type;
  lv_aqi_type_t aqi_type;
  int8_t aqi_level_count;
  float aqi_val;
  float pm25_val;
  float pm10_val;
  float pm1_val;

  float prev_aqi;
  bool  reflesh_warning_text;
  int32_t arc_r;
  int32_t arc_thick;

} lv_aqi_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
lv_obj_t* lv_aqi_create(lv_obj_t*parent);

/*=====================
 * Setter functions
 *====================*/

void lv_aqi_set_aqi(lv_obj_t* aqi, float aqi_val);

void lv_aqi_set_pm25(lv_obj_t* aqi, float pm25_val);

// void lv_aqi_set_pm10(lv_obj_t* aqi, float pm10_val);

// void lv_aqi_set_pm1(lv_obj_t* aqi, float pm1_val);

// void lv_aqi_set_type(lv_obj_t* aqi, lv_aqi_type_t type); 

// void lv_aqi_set_warning_show(lv_obj_t* aqi, bool show);

/*=====================
 * Getter functions
 *====================*/
// lv_gauge_type_t lv_aqi_get_type(lv_obj_t* gauge);

// float lv_aqi_get_value(lv_obj_t* gauge);

// float lv_aqi_get_min_value(lv_obj_t* gauge);

// float lv_aqi_get_max_value(lv_obj_t* gauge);

// uint8_t lv_aqi_get_decimal(lv_obj_t* gauge);

// float lv_aqi_get_angle_offset(lv_obj_t* gauge);

// float lv_aqi_get_angle_total(lv_obj_t* gauge);

// lv_color_t lv_aqi_get_color_begin(lv_obj_t* gauge);

// lv_color_t lv_aqi_get_color_end(lv_obj_t* gauge);

// lv_color_t lv_aqi_get_color_bg(lv_obj_t* gauge);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* LV_AQI_H */
