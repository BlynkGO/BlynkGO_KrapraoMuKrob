/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GTransition.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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


#ifndef __GTRANSITION_H__
#define __GTRANSITION_H__

#include <Arduino.h>
#include "GUtils.h"
#include "GLVGL.h"
#include <memory>

class GTransition {
  public:
    GTransition() {}
    void create();
    inline bool isCreated()                           { return this->_u_raw_trans.get() !=nullptr; }  

    void init(style_prop_t props[], _anim_path_cb_t path_cb, uint32_t time, uint32_t delay=0, void * user_data=NULL);
    void init(style_prop_t props[], anim_path_type_t path, uint32_t time, uint32_t delay=0, void * user_data=NULL);


    inline style_transition_t* raw()       { return this->_u_raw_trans.get(); }
    std::unique_ptr<style_transition_t>  _u_raw_trans;
  private:


};

#endif // __GTRANSITION_H__