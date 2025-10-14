/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ lv_passcodelock.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef LV_PASSCODELOCK_H
#define LV_PASSCODELOCK_H

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
  LV_PASSCODELOCK_STATE_LOCK, 
  LV_PASSCODELOCK_STATE_SETTING,

  // สำหรับใช้ภายใน
  LV_PASSCODELOCK_STATE_SETTING_FIRST,
  LV_PASSCODELOCK_STATE_SETTING_SECOND,
  LV_PASSCODELOCK_STATE_CHECK_PREVKEY,
  LV_PASSCODELOCK_STATE_PRE_LOCK,
  LV_PASSCODELOCK_STATE_PRE_SETTING,
  LV_PASSCODELOCK_STATE_PRE_CHECK_PREVKEY,
  LV_PASSCODELOCK_STATE_PRE_UNLOCK,
  LV_PASSCODELOCK_STATE_PRE_DEL, 
}  passcodelock_state_t;

typedef struct _lv_passcodelock_t {
  lv_obj_t    obj;
  lv_obj_t *  label;
  lv_obj_t *  cont_dot;
  lv_obj_t *  btn[10];
  lv_obj_t *  btn_cancel;
  uint32_t    passcode;
  uint8_t     passcode_len;
  uint32_t    usercode;
  int8_t      cur_id;
  void        (*fn_auth_cb)(void);   /* function callback สำหรับ เมื่อใส่รหัสถูกต้อง */
  void        (*fn_cancel_cb)(void); /* function callback สำหรับ เมื่อ cancel หรือ เมื่อใส่รหัสไม่ถูกต้องครบ 3 ครั้ง */

  uint32_t      usercode_timer;    /* timer แบบ millis */
  bool          usercode_checker;  /* ตัวเช็คเพื่อสั่งให้มีการเช็ค usercode */
  passcodelock_state_t state;
  lv_timer_t   *periodic_timer;    /* timer แบบทำงานเป็นช่วงๆ */
} lv_passcodelock_t;

enum {
  PASSCODE_4_DIGITS,
  PASSCODE_6_DIGITS,
};
typedef uint8_t passcode_digits_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
lv_obj_t* lv_passcodelock_create(lv_obj_t*parent);

/*=====================
 * Setter functions
 *====================*/

/**
 * Set the value of a passcodelock
 * @param passcodelock pointer to passcodelock object
 * @param passcode     : the passcode for the passcodelock
 */
void lv_passcodelock_set_passcode(lv_obj_t* passcodelock, uint32_t passcode);

/**
 * Set the value of a passcodelock
 * @param passcodelock pointer to passcodelock object
 * @param passcode_digits  : the passcode digits ( PASSCODE_4_DIGITS or PASSCODE_6_DIGITS )
 */
void lv_passcodelock_set_passcode_digits(lv_obj_t* passcodelock, passcode_digits_t passcode_digits);

/**
 * Set the authentication callback for a passcodelock
 * @param passcodelock Pointer to passcodelock object
 * @param fn          Function to call when authentication succeeds
 */
void lv_passcodelock_set_auth_cb(lv_obj_t* passcodelock, void (*fn)(void));


/**
 * Set the authentication failure callback for a passcodelock
 * @param passcodelock Pointer to passcodelock object
 * @param fn          Function to call when authentication is canceled or failed
 */
void lv_passcodelock_set_cancel_cb(lv_obj_t* passcodelock, void (*fn)(void));

/**
 * Set the value of a keyunlocker
 * @param passcodelock pointer to passcodelock object
 * @param state     : the state for the passcodelock
 */
void lv_passcodelock_set_state(lv_obj_t* keyunlocker, passcodelock_state_t state );

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the value of a passcodelock
 * @param passcodelock pointer to passcodelock object
 * @return the value of the passcodelock's passcode
 */
 
uint32_t lv_passcodelock_get_passcode(lv_obj_t* passcodelock);


/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* LV_PASSCODELOCK_H */


// [example]
//   lv_obj_t* passcodelock = lv_passcodelock_create(lv_screen_active());
//   lv_passcodelock_set_passcode(passcodelock, 123456);  // ตั้งรหัสลับ ใส่เลข 4 หลัก หรือ 6 หลัก เท่านั้น

//   lv_obj_set_style_size(passcodelock, 80, 80, LV_PART_ITEMS);
//   // lv_obj_set_style_text_font(passcodelock, &prasanmit_20, LV_PART_MAIN);
//   lv_obj_set_style_text_font(passcodelock, &prasanmit_40, LV_PART_ITEMS);
//   lv_obj_set_style_text_color(passcodelock, lv_color_make(0,255,0), LV_PART_ITEMS);
//
//   lv_obj_set_style_size(passcodelock, 50, 50, LV_PART_INDICATOR);
//   lv_obj_set_style_pad_column(passcodelock, 10, LV_PART_INDICATOR);

//   lv_obj_send_event(passcodelock, LV_EVENT_STYLE_CHANGED, NULL);
