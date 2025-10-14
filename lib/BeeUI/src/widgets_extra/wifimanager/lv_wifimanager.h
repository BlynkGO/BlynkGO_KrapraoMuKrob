/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ lv_wifimanager.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef LV_WIFIMANAGER_H
#define LV_WIFIMANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"
#include "utils/lvgl/src/core/lv_obj.h"
#include "utils/lvgl/src/core/lv_obj_private.h"   /* ต้องมี ไม่งั้น error */
#include "utils/lvgl/src/misc/lv_timer.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef int8_t (*fn_get_wifi_rssi_t)(void);
typedef bool (*fn_get_wifi_connection_t)(void);

typedef struct _lv_wifimanager_t {
  lv_obj_t obj;
  lv_obj_t *lb_wifi_signal[2];
  lv_color_t color_wifi_connected;      /**< Color wifi-signal when connected */
  lv_color_t color_wifi_disconnected;   /**< Color wifi-signal when disconnected */
  lv_color_t color_wifi_bg;             /**< Color wifi-signal at background */
  fn_get_wifi_rssi_t fn_get_wifi_rssi;
  fn_get_wifi_connection_t fn_get_wifi_connection;
  lv_timer_t * timer_update_rssi;
} lv_wifimanager_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
lv_obj_t* lv_wifimanager_create(lv_obj_t*parent);

/*=====================
 * Setter functions
 *====================*/
void lv_wifimanager_set_wifi_rssi_cb(lv_obj_t* wifimanager, fn_get_wifi_rssi_t cb);

void lv_wifimanager_set_wifi_connection_cb(lv_obj_t* wifimanager, fn_get_wifi_connection_t cb);

void lv_wifimanager_set_color_wifi_connected(lv_obj_t* wifimanager, lv_color_t color_wifi_connected);

void lv_wifimanager_set_color_wifi_disconnected(lv_obj_t* wifimanager, lv_color_t color_wifi_disconnected);

void lv_wifimanager_set_color_wifi_bg(lv_obj_t* wifimanager, lv_color_t color_wifi_bg);

void lv_wifimanager_update_rssi(lv_obj_t* wifimanager);       // เรียก update rssi ครั้งเดียว

void lv_wifimanager_start_update_rssi(lv_obj_t* wifimanager); // เริ่มให้ timer ทำการ update rssi เป็นช่วงๆ

void lv_wifimanager_pause_update_rssi(lv_obj_t* wifimanager);  // หยุดชั่วคราว timer ที่ทำการ update rssi เป็นช่วงๆ

void lv_wifimanager_resume_update_rssi(lv_obj_t* wifimanager);  // กลับมาทำงานต่อ timer ที่ทำการ update rssi เป็นช่วงๆ

/*=====================
 * Getter functions
 *====================*/
fn_get_wifi_rssi_t lv_wifimanager_get_wifi_rssi_cb(lv_obj_t* wifimanager);

fn_get_wifi_connection_t lv_wifimanager_get_wifi_connection_cb(lv_obj_t* wifimanager);

lv_color_t lv_wifimanager_get_color_wifi_connected(lv_obj_t* wifimanager);

lv_color_t lv_wifimanager_get_color_wifi_disconnected(lv_obj_t* wifimanager);

lv_color_t lv_wifimanager_get_color_wifi_bg(lv_obj_t* wifimanager);

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* LV_WIFIMANAGER_H */
