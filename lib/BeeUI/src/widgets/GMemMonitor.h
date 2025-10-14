/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GMemMonitor.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GMEMMONITOR_H__
#define __GMEMMONITOR_H__

#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GMemMonitor {
  public:
    GMemMonitor()                                   { this->init();               }
    inline void init()                              { mem_monitor(&this->mon);    }
    inline size_t used(GMemMonitor &mem_monitor2)   { return (this->free_size()- mem_monitor2.free_size()); }
    inline size_t free_size()                       { return this->mon.free_size; }

  private:
    mem_monitor_t mon;
};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GMEMMONITOR_H__