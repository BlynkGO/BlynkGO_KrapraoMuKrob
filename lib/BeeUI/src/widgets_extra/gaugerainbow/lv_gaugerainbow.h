/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ lv_gaugerainbow.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef LV_GAUGERAINBOW_H
#define LV_GAUGERAINBOW_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"
#include "utils/lvgl/src/core/lv_obj.h"
#include "utils/lvgl/src/core/lv_obj_private.h"   /* ต้องมี ไม่งั้น error */

/*********************
 *      DEFINES
 *********************/
#ifndef LV_GAUGE_TYPE_ARC_MAX_ARC
# define LV_GAUGE_TYPE_ARC_MAX_ARC     30
#endif

#ifndef LV_GAUGE_TYPE_FULL_MAX_ARC
# define LV_GAUGE_TYPE_FULL_MAX_ARC    40
#endif

/**********************
 *      TYPEDEFS
 **********************/
enum {
  LV_GAUGE_TYPE_ARC,
  LV_GAUGE_TYPE_FULL,
};
typedef uint8_t lv_gauge_type_t;

typedef struct _lv_gaugerainbow_t {
  lv_obj_t obj;
  lv_color_t color_begin;   /**< Color begin of the gaugerainbow*/
  lv_color_t color_end;     /**< Color end of the gaugerainbow*/
  lv_color_t color_bg;      /**< Color background of the gaugerainbow*/
  float cur_value;          /**< Current value of the gaugerainbow*/
  float min_value;          /**< Minimum value of the gaugerainbow*/
  float max_value;          /**< Maximum value of the gaugerainbow*/
  uint8_t  decimal;
  float   angle_offset;
  float   angle_total;
  float   angle_space;
  float   angle_unit;
  uint8_t arc_max_num;
  lv_gauge_type_t type;
} lv_gaugerainbow_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
lv_obj_t* lv_gaugerainbow_create(lv_obj_t*parent);

/*=====================
 * Setter functions
 *====================*/
void lv_gaugerainbow_set_type(lv_obj_t* gauge, lv_gauge_type_t type);

void lv_gaugerainbow_set_value(lv_obj_t* gauge, float value);

void lv_gaugerainbow_set_range(lv_obj_t* gauge, float min_value, float max_value);

void lv_gaugerainbow_set_min_value(lv_obj_t* gauge, float value);

void lv_gaugerainbow_set_max_value(lv_obj_t* gauge, float value);

void lv_gaugerainbow_set_decimal(lv_obj_t* gauge, uint8_t decimal);

void lv_gaugerainbow_set_angle_offset(lv_obj_t* gauge, float value);

void lv_gaugerainbow_set_angle_total(lv_obj_t* gauge, float value);

void lv_gaugerainbow_set_color(lv_obj_t* gauge, lv_color_t color_begin, lv_color_t color_end, lv_color_t color_bg);

void lv_gaugerainbow_set_color_begin(lv_obj_t* gauge, lv_color_t color_begin);

void lv_gaugerainbow_set_color_end(lv_obj_t* gauge, lv_color_t color_end);

void lv_gaugerainbow_set_color_bg(lv_obj_t* gauge, lv_color_t color_bg);

/*=====================
 * Getter functions
 *====================*/
lv_gauge_type_t lv_gaugerainbow_get_type(lv_obj_t* gauge);

float lv_gaugerainbow_get_value(lv_obj_t* gauge);

float lv_gaugerainbow_get_min_value(lv_obj_t* gauge);

float lv_gaugerainbow_get_max_value(lv_obj_t* gauge);

uint8_t lv_gaugerainbow_get_decimal(lv_obj_t* gauge);

float lv_gaugerainbow_get_angle_offset(lv_obj_t* gauge);

float lv_gaugerainbow_get_angle_total(lv_obj_t* gauge);

lv_color_t lv_gaugerainbow_get_color_begin(lv_obj_t* gauge);

lv_color_t lv_gaugerainbow_get_color_end(lv_obj_t* gauge);

lv_color_t lv_gaugerainbow_get_color_bg(lv_obj_t* gauge);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* LV_GAUGERAINBOW_H */
