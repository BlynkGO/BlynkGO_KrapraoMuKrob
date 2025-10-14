/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ lv_keyunlocker.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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
 * [History]
 *    [Version 5.0.0] @03/02/25
 *       - รองรับตั้ง setting เปลี่อน รหัสได้ และโหมด lock ได้
 *       - ใส่รหัสผิด 3 ครั้ง ออกจากหน้าตั้ง
 *       - มีปุ่ม cancel ออกได้  (แต่ไม่มีจำเวลา)
 * 
 *********************************************************************************
 */

#ifndef LV_KEYUNLOCKER_H
#define LV_KEYUNLOCKER_H

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

/**********************
 *      TYPEDEFS
 **********************/
typedef enum { 
  LV_KEYUNLOCKER_STATE_LOCK, 
  LV_KEYUNLOCKER_STATE_SETTING,

  // สำหรับใช้ภายใน
  LV_KEYUNLOCKER_STATE_SETTING_FIRST,
  LV_KEYUNLOCKER_STATE_SETTING_SECOND,
  LV_KEYUNLOCKER_STATE_CHECK_PREVKEY,
  LV_KEYUNLOCKER_STATE_PRE_LOCK,
  LV_KEYUNLOCKER_STATE_PRE_SETTING,
  LV_KEYUNLOCKER_STATE_PRE_CHECK_PREVKEY,
  LV_KEYUNLOCKER_STATE_PRE_UNLOCK,
  LV_KEYUNLOCKER_STATE_PRE_DEL, 
}  keyunlocker_state_t;

typedef struct _lv_keyunlocker_t {
  lv_obj_t      obj;
  lv_obj_t*     label;          /* วิตเจ็ต label สำหรับแสดง info ด้านบน */
  lv_obj_t*     btnm;           /* วิตเจ็ต button matrix สำหรับปุ่ม 9 key*/
  lv_obj_t*     line;           /* วิตเจ็ต เส้น ไว้แสดงการลากเส้น*/
  lv_obj_t*     btn_cancel;     /* วิตเจ็ต ปุ่ม cancel */
  lv_point_precise_t * line_points;    /* จุดสำหรับลากเส้น ให้วิตเจ็ตเส้น */
  uint8_t *     key_inputs;     /* key ที่ user ใส่เข้ามา */
  uint8_t       key_count;      /* จำนวน key/จุด ที่ user ใส่เข้ามา */
  uint32_t      secretkey;      /* รหัสลับ */
  void          (*fn_auth_cb)(void);   /* function callback สำหรับ เมื่อใส่รหัสถูกต้อง */
  void          (*fn_cancel_cb)(void); /* function callback สำหรับ เมื่อ cancel หรือ เมื่อใส่รหัสไม่ถูกต้องครบ 3 ครั้ง */

  uint32_t      released_timer; /* timer แบบ millis */
  bool          released_checker; /* ตัวเช็คสถานะปล่อย */
  keyunlocker_state_t state;
  lv_timer_t   *periodic_timer; /* timer แบบทำงานเป็นช่วงๆ */
} lv_keyunlocker_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
lv_obj_t* lv_keyunlocker_create(lv_obj_t*parent);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the value of a keyunlocker
 * @param keyunlocker pointer to keyunlocker object
 * @param secretkey     : the secretkey for the keyunlocker
 */
void lv_keyunlocker_set_secretkey(lv_obj_t* keyunlocker, uint32_t secretkey);

/**
 * Set the authentication callback for a keyunlocker
 * @param keyunlocker Pointer to keyunlocker object
 * @param fn          Function to call when authentication succeeds
 */
void lv_keyunlocker_set_auth_cb(lv_obj_t* keyunlocker, void (*fn)(void));


/**
 * Set the authentication failure callback for a keyunlocker
 * @param keyunlocker Pointer to keyunlocker object
 * @param fn          Function to call when authentication is canceled or failed
 */
void lv_keyunlocker_set_cancel_cb(lv_obj_t* keyunlocker, void (*fn)(void));

/**
 * Set the value of a keyunlocker
 * @param keyunlocker pointer to keyunlocker object
 * @param state     : the state for the keyunlocker
 */
void lv_keyunlocker_set_state(lv_obj_t* keyunlocker, keyunlocker_state_t state );

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the value of a keyunlocker
 * @param keyunlocker pointer to keyunlocker object
 * @return the value of the keyunlocker's secretkey
 */
 
uint32_t lv_keyunlocker_get_secretkey(lv_obj_t* keyunlocker);


/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* LV_KEYUNLOCKER_H */
