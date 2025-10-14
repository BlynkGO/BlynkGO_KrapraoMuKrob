#ifndef __BEENEXT_SOFTTIMER_H__
#define __BEENEXT_SOFTTIMER_H__

#include "../../beenext_config.h"

#if BEENEXT_USE_SOFTTIMER

#include <Arduino.h>
#include "linklist.h"

#define CNT_INFINITY    -1

enum { SWTIMER_TYPE_INTERVAL, SWTIMER_TYPE_DELAY };
typedef uint8_t swtimer_type_t;
typedef void(*swtimer_cb_t)(void);
typedef void(*swtimer_param_cb_t)(void* param);
typedef struct _swtimer {
  uint16_t        id;
  bool            pause;
  swtimer_type_t  type;
  unsigned long   timeout;
  unsigned long   timer;
  int16_t         max_cnt;
  swtimer_cb_t    fn_cb;
  swtimer_param_cb_t fn_param_cb;
  swtimer_cb_t    fn_ready_cb;
  swtimer_param_cb_t fn_ready_param_cb;
  void*           param;
} swtimer_t;

class SoftTimer {
  public:
    SoftTimer();

    void init();

    void setInterval(unsigned long period_ms, swtimer_cb_t fn, bool start_first=false);
    void setInterval(unsigned long period_ms, swtimer_param_cb_t fn, void* param, bool start_first=false);

    void setInterval(unsigned long period_ms, int16_t max_cnt, swtimer_cb_t fn, bool start_first=false);
    void setInterval(unsigned long period_ms, int16_t max_cnt, swtimer_param_cb_t fn, void* param, bool start_first=false);

    void ready_cb(swtimer_cb_t fn_ready);
    void ready_cb(swtimer_param_cb_t fn_ready_param);

    void pause();       // สำหรับ timer ที่ setInterval แล้วต้องการให้หยุดทำงานชั่วคราว
    void resume();      // สำหรับ timer ที่ setInterval หลังมีการ pause() ต้องการให้กลับมาทำงานต่อ

    [[deprecated("The API replay() is deprecated and will be removed soon. Please use the API resume() instead.")]]
    void replay()       {  this->resume(); }

    void delay(unsigned long delay_ms, swtimer_cb_t fn, bool start_first=false);
    void delay(unsigned long delay_ms, swtimer_param_cb_t fn, void* param, bool start_first=false);
    void del();

    inline void setOnce(unsigned long delay_ms, swtimer_cb_t fn, bool start_first=false){
      this->delay(delay_ms, fn, start_first);
    }
    inline void setOnce(unsigned long delay_ms, swtimer_param_cb_t fn, void* param, bool start_first=false){
      this->delay(delay_ms, fn, param, start_first);
    }
    static void       run();

    static bool       _ll_inited;
    static ll_t       swtimer_ll;
    static uint16_t   add_swtimer(swtimer_type_t type, unsigned long timeout, swtimer_cb_t fn_cb);
    static uint16_t   add_swtimer(swtimer_type_t type, unsigned long timeout, swtimer_param_cb_t fn_cb, void* param);
    static uint16_t   add_swtimer(swtimer_type_t type, unsigned long timeout, int16_t max_cnt, swtimer_cb_t fn_cb);
    static uint16_t   add_swtimer(swtimer_type_t type, unsigned long timeout, int16_t max_cnt, swtimer_param_cb_t fn_cb, void* param);

    static swtimer_t* find_swtimer(uint16_t id);
    static bool       del_swtimer(uint16_t id);
    static uint32_t   count_swtimer();
    static void       listall_swtimer();
    static void       clear_swtimer();
  private:
    uint16_t _swtimer_id = 0;
};


#endif // BEENEXT_USE_SOFTTIMER

#endif // __BEENEXT_SOFTTIMER_H__
