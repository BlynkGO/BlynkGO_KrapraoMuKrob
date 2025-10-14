/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GAnimation.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GANIMATION_H___
#define __GANIMATION_H___

#include "GObject.h"
#include "GWidgets.h"


//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

void ANIM_X(GWidget* widget, int32_t value);
void ANIM_Y(GWidget* widget, int32_t value);
void ANIM_WIDTH(GWidget* widget, int32_t value);
void ANIM_HEIGHT(GWidget* widget, int32_t value);
void ANIM_ANGLE(GWidget* widget, int32_t value);
void ANIM_OPA(GWidget* widget, int32_t value);

class GAnimation;
class GTimeline;

#define GANIMATION      GAnimation*a
#define GTIMELINE       GTimeline*at
#define GAnim           GAnimation
#define GANIM           GANIMATION


typedef void (*anim_exec_cb_t)(GWidget*widget, int32_t value);
typedef void (*anim_exec2_cb_t)(GAnimation *a, int32_t value);
typedef void (*anim_completed_cb_t)(GAnimation *a);
typedef void (*anim_start_cb_t)(GAnimation *a);
typedef void (*anim_deleted_cb_t)(GAnimation *a);
typedef int32_t (*anim_path_cb_t)(int32_t cur_time, int32_t total_time, int32_t start_value, int32_t end_value);
typedef void (*anim_timeline_cb_t)(GTimeline *timeline);

#define REPEAT_ON         0xFFFF
#define REPEAT_OFF        1
#define PLAYBACK_ON       1
#define PLAYBACK_OFF      0
#define PROGRESS_MAX      0xFFFF

class GAnimation {
  public:
    GAnimation() { this->init(); }

    void init(GWidget *widget, anim_exec_cb_t fn, int32_t start, int32_t end, uint32_t time, bool repeat=false, bool reverse=false);
    void init(GWidget *widget, anim_exec_cb_t fn, int32_t start, int32_t end, uint32_t time, anim_path_type_t path_type);

    inline void init(GWidget &widget, anim_exec_cb_t fn, int32_t start, int32_t end, uint32_t time, bool repeat=false, bool reverse=false)
    {
      this->init(&widget,fn, start, end, time, repeat, reverse);
    }
    inline void init(GWidget &widget, anim_exec_cb_t fn, int32_t start, int32_t end, uint32_t time, anim_path_type_t path_type )
    {
      this->init(&widget, fn, start, end, time, path_type);
    }
    inline void init(anim_exec_cb_t fn, int32_t start, int32_t end, uint32_t time, bool repeat=false, bool reverse=false)
    {
      this->init(NULL, fn, start, end, time, repeat, reverse );
    }
    inline void init(anim_exec_cb_t fn, int32_t start, int32_t end, uint32_t time, anim_path_type_t path_type ){
      this->init(NULL, fn, start, end, time, path_type);
    }

    void init(GWidget *widget, anim_exec_xcb_t fn, int32_t start, int32_t end, uint32_t time, bool repeat=false, bool reverse=false);
    void init(GWidget *widget, anim_exec_xcb_t fn, int32_t start, int32_t end, uint32_t time, anim_path_type_t path_type);
    inline void init(GWidget &widget, anim_exec_xcb_t fn, int32_t start, int32_t end, uint32_t time, bool repeat=false, bool reverse=false)
    {
      this->init(&widget,fn, start, end, time, repeat, reverse);
    }
    inline void init(GWidget &widget, anim_exec_xcb_t fn, int32_t start, int32_t end, uint32_t time, anim_path_type_t path_type )
    {
      this->init(&widget, fn, start, end, time, path_type);
    }
    void init(anim_exec_xcb_t fn, int32_t start, int32_t end, uint32_t time, bool repeat=false, bool reverse=false);
    void init(anim_exec_xcb_t fn, int32_t start, int32_t end, uint32_t time, anim_path_type_t path_type );

    // void init(GWidget *widget, anim_exec2_cb_t fn, int32_t start, int32_t end, uint32_t time, bool repeat=false, bool reverse=false);
    // inline void init(GWidget &widget, anim_exec2_cb_t fn, int32_t start, int32_t end, uint32_t time, bool repeat=false, bool reverse=false)
    // {
    //   this->init(&widget,fn, start, end, time, repeat, reverse);
    // }

    void path_type(anim_path_type_t path_type);
    inline void start_cb(anim_start_cb_t fn)              { this->_start_cb = fn;     }
    inline void completed_cb(anim_completed_cb_t fn)      { this->_completed_cb = fn; }
    inline void ready_cb(anim_completed_cb_t fn)          { this->completed_cb(fn);   }
    inline void deleted_cb(anim_deleted_cb_t fn)          { this->_deleted_cb = fn;   }
    inline void path_cb(anim_path_cb_t fn)                { this->_path_cb = fn;      }

    inline void start_cb(anim_start_cb_t fn, void* user_data)              { this->_start_cb = fn;     this->user_data(user_data); }
    inline void completed_cb(anim_completed_cb_t fn, void* user_data)      { this->_completed_cb = fn; this->user_data(user_data); }
    inline void ready_cb(anim_completed_cb_t fn, void* user_data)          { this->completed_cb(fn);   this->user_data(user_data); }
    inline void deleted_cb(anim_deleted_cb_t fn, void* user_data)          { this->_deleted_cb = fn;   this->user_data(user_data); }
    inline void path_cb(anim_path_cb_t fn, void* user_data)                { this->_path_cb = fn;      this->user_data(user_data); }
    
    inline void onStart(anim_start_cb_t fn)               { this->start_cb(fn);       }
    inline void onCompleted(anim_completed_cb_t fn)       { this->completed_cb(fn);   }
    inline void onReady(anim_completed_cb_t fn)           { this->onCompleted(fn);    }
    inline void onDelete(anim_deleted_cb_t fn)            { this->deleted_cb(fn);     }
    inline void onPath(anim_path_cb_t fn)                 { this->path_cb(fn);        }

    inline void onStart(anim_start_cb_t fn, void* user_data)               { this->start_cb(fn, user_data);       }
    inline void onCompleted(anim_completed_cb_t fn, void* user_data)       { this->completed_cb(fn, user_data);   }
    inline void onReady(anim_completed_cb_t fn, void* user_data)           { this->onCompleted(fn, user_data);    }
    inline void onDelete(anim_deleted_cb_t fn, void* user_data)            { this->deleted_cb(fn, user_data);     }
    inline void onPath(anim_path_cb_t fn, void* user_data)                 { this->path_cb(fn, user_data);        }

    inline anim_t* raw()                                  { return &a;                }

    anim_start_cb_t _start_cb= NULL;
    anim_completed_cb_t _completed_cb= NULL;
    anim_deleted_cb_t _deleted_cb = NULL;
    anim_path_cb_t  _path_cb = NULL;

    //----------------------------------------------
    /**
     * Initialize an animation variable.
     */
    void init();

    void del();

    inline bool isCreated()                                         { return this->_created;          }

    /**
     * Set a variable to animate
     * @param var   pointer to a variable to animate
     */
    inline void var(void * var)                                     { a.var = var;                    }

    /**
     * Set a function to animate `var`
     * @param exec_cb   a function to execute during animation
     *                  LVGL's built-in functions can be used.
     *                  E.g. lv_obj_set_x
     */
    inline void exec_cb(anim_exec_xcb_t exec_cb)                    { a.exec_cb = exec_cb;            }

    void exec_cb(anim_exec_xcb_t fn,  int32_t start, int32_t end);
    inline void exec_cb(anim_exec_cb_t fn,  int32_t start, int32_t end){
      this->exec_cb((anim_exec_xcb_t)fn, start, end);
    }

    /**
     * Set the duration of an animation
     * @param duration  duration of the animation in milliseconds
     */
    inline void duration(uint32_t duration)                         { a.duration = duration;          }

    inline void time(uint32_t time)                                 { this->duration(time);           }

    /**
     * Set a delay before starting the animation
     * @param delay     delay before the animation in milliseconds
     */
    inline void delay(uint32_t delay)                               { a.act_time = -(int32_t)(delay); }

    /**
     * Set the start and end values of an animation
     * @param start     the start value
     * @param end       the end value
     */
    inline void values(int32_t start, int32_t end)                  { a.start_value = start; a.current_value = INT32_MIN; a.end_value = end; }

    /**
     * Similar to `anim_set_exec_cb` but `anim_custom_exec_cb_t` receives
     * `anim_t * ` as its first parameter instead of `void *`.
     * This function might be used when LVGL is bound to other languages because
     * it's more consistent to have `anim_t *` as first parameter.
     * @param exec_cb   a function to execute.
     */
    inline void custom_exec_cb(anim_custom_exec_cb_t exec_cb)       { a.custom_exec_cb = exec_cb;     }

    /**
     * Set the path (curve) of the animation.
     * @param path_cb a function to set the current value of the animation.
     */
    inline void path_cb(lv_anim_path_cb_t path_cb)                  { a.path_cb = path_cb;            }

    /**
     * Set a function call when the animation really starts (considering `delay`)
     * @param start_cb  a function call when the animation starts
     */
    inline void start_cb(lv_anim_start_cb_t start_cb)               { a.start_cb = start_cb;          }

    /**
     * Set a function to use the current value of the variable and make start and end value
     * relative to the returned current value.
     * @param get_value_cb  a function call when the animation starts
     */
    inline void value_cb(lv_anim_get_value_cb_t get_value_cb)       { a.get_value_cb = get_value_cb;  }

    /**
     * Set a function call when the animation is completed
     * @param completed_cb  a function call when the animation is fully completed
     */
    inline void completed_cb(lv_anim_completed_cb_t completed_cb)   { a.completed_cb = completed_cb;  }

    /**
     * Set a function call when the animation is deleted.
     * @param deleted_cb  a function call when the animation is deleted
     */
    inline void deleted_cb(lv_anim_deleted_cb_t deleted_cb)         { a.deleted_cb = deleted_cb;      }

    /**
     * Make the animation to play back to when the forward direction is ready
     * @param time      the duration of the reverse animation in milliseconds. 0: disable reverse
     */
    inline void reverse_duration(uint32_t duration)                 { a.reverse_duration = duration;  }

    inline void reverse_time(uint32_t duration)                     { reverse_duration(duration);    }

    inline void reverse(bool reverse)                               { this->reverse_duration( reverse? this->duration(): 0);  }

    /**
     * Make the animation to play back to when the forward direction is ready
     * @param delay     delay in milliseconds before starting the reverse animation.
     */
    inline void reverse_delay(uint32_t delay)                      { a.reverse_delay = delay;       }

    inline void reverse_pause(uint32_t delay)                      { this->reverse_delay(delay);    }

    /**
     * Make the animation repeat itself.
     * @param cnt       repeat count or `LV_ANIM_REPEAT_INFINITE` for infinite repetition. 0: to disable repetition.
     */
    inline void repeat_count(uint16_t cnt)                          { a.repeat_cnt = cnt;             }

    inline void repeat(uint16_t cnt)                                { this->repeat_count(cnt);        }

    /**
     * Set a delay before repeating the animation.
     * @param delay     delay in milliseconds before repeating the animation.
     */
    inline void repeat_delay(uint32_t delay)                        { a.repeat_delay = delay;         }

    inline void repeat_pause(uint32_t delay)                        { this->repeat_delay(delay);      }

    /**
     * Set a whether the animation's should be applied immediately or only when the delay expired.
     * @param en        true: apply the start value immediately in `anim_start`;
     *                  false: apply the start value only when `delay` ms is elapsed and the animations really starts
     */
    inline void early_apply(bool en)                                { a.early_apply = en;             }

    /**
     * Set the custom user data field of the animation.
     * @param user_data   pointer to the new user_data.
     */
    inline void user_data(void * user_data)                         { this->_user_data = user_data;   }

    /**
     * Set parameter for cubic bezier path
     * @param x1        first control point
     * @param y1
     * @param y1        second control point
     */
    inline void bezier3_param(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
    {
      auto para = &a.parameter.bezier3;
      para->x1 = x1;
      para->x2 = x2;
      para->y1 = y1;
      para->y2 = y2;
    }

    /**
     * Create an animation
     */
    void start();

    inline void create()                                          { this->start();                    }

    /**
     * Get a delay before starting the animation
     * @return delay before the animation in milliseconds
     */
    inline uint32_t delay()                                       { return -a.act_time;               }

    /**
     * Get the time used to play the animation.
     * @return the play time in milliseconds.
     */
    uint32_t playtime();

    /**
     * Get the duration of an animation
     * @return the duration of the animation in milliseconds
     */
    inline uint32_t duration()                                    { return a.duration;                }
    inline uint32_t time()                                        { return a.duration;                }

    /**
     * Get the repeat count of the animation.
     * @return the repeat count or `LV_ANIM_REPEAT_INFINITE` for infinite repetition. 0: disabled repetition.
     */
    inline uint16_t repeat_count()                                { return a.repeat_cnt;              }

    /**
     * Get the var field of the animation
     * @return  the pointer to the var of the animation
     */
    inline void * var()                                           { return a.var;                     }

    /**
     * Get the user_data field of the animation
     * @return  the pointer to the custom user_data of the animation
     */
    inline void * user_data()                                     { return this->_user_data;          }

    /**
     * Delete animation(s) of a variable with a given animator function
     * @param var       pointer to variable
     * @param exec_cb   a function pointer which is animating 'var',
     *                  or NULL to ignore it and delete all the animations of 'var
     * @return          true: at least 1 animation is deleted, false: no animation is deleted
     */
    bool _del(void * var, lv_anim_exec_xcb_t exec_cb);

    /**
     * Delete all the animations
     */
    void delete_all(void);

    /**
     * Get the animation of a variable and its `exec_cb`.
     * @param var       pointer to variable
     * @param exec_cb   a function pointer which is animating 'var', or NULL to return first matching 'var'
     * @return          pointer to the animation.
     */
    anim_t * get(void * var, lv_anim_exec_xcb_t exec_cb);

    /**
     * Get global animation refresher timer.
     * @return pointer to the animation refresher timer.
     */
    lv_timer_t * get_timer();

    /**
     * Delete an animation by getting the animated variable from `a`.
     * Only animations with `exec_cb` will be deleted.
     * This function exists because it's logical that all anim. functions receives an
     * `anim_t` as their first parameter. It's not practical in C but might make
     * the API more consequent and makes easier to generate bindings.
     * @param exec_cb   a function pointer which is animating 'var',
     *                  or NULL to ignore it and delete all the animations of 'var
     * @return          true: at least 1 animation is deleted, false: no animation is deleted
     */
    inline bool custom_delete(lv_anim_custom_exec_cb_t exec_cb)
    {
      return this->_del( a.var, (lv_anim_exec_xcb_t)exec_cb);
    }

    /**
     * Get the animation of a variable and its `exec_cb`.
     * This function exists because it's logical that all anim. functions receives an
     * `lv_anim_t` as their first parameter. It's not practical in C but might make
     * the API more consequent and makes easier to generate bindings.
     * @param exec_cb   a function pointer which is animating 'var', or NULL to return first matching 'var'
     * @return          pointer to the animation.
     */
    inline anim_t * custom_get(lv_anim_custom_exec_cb_t exec_cb)
    {
        return this->get(a.var, (lv_anim_exec_xcb_t)exec_cb);
    }

    /**
     * Get the number of currently running animations
     * @return      the number of running animations
     */
    uint16_t count_running(void);

    /**
     * Store the speed as a special value which can be used as time in animations.
     * It will be converted to time internally based on the start and end values
     * @param speed         the speed of the animation in with unit / sec resolution in 0..10k range
     * @return              a special value which can be used as an animation time
     */
    uint32_t speed(uint32_t speed);

    /**
     * Store the speed as a special value which can be used as time in animations.
     * It will be converted to time internally based on the start and end values
     * @param speed         the speed of the animation in as unit / sec resolution in 0..10k range
     * @param min_time      the minimum time in 0..10k range
     * @param max_time      the maximum time in 0..10k range
     * @return              a special value in where all three values are stored and can be used as an animation time
     * @note                internally speed is stored as 10 unit/sec
     * @note                internally min/max_time are stored with 10 ms unit
     *
     */
    uint32_t speed_clamped(uint32_t speed, uint32_t min_time, uint32_t max_time);

    /**
     * Manually refresh the state of the animations.
     * Useful to make the animations running in a blocking process where
     * `lv_timer_handler` can't run for a while.
     * Shouldn't be used directly because it is called in `lv_refr_now()`.
     */
    void refr_now(void);

    anim_exec2_cb_t _custom_exec_cb = NULL;

  private:
    bool   _created = false;
    void*  _user_data = NULL;
    anim_t a;
    static void     ganim_start_cb(anim_t *a);
    static void     ganim_completed_cb(anim_t *a);
    static void     ganim_deleted_cb(anim_t *a);
    static int32_t  ganim_path_cb(const anim_t *a);
};


/**
 * Store the speed as a special value which can be used as time in animations.
 * It will be converted to time internally based on the start and end values
 * @param speed         the speed of the animation in with unit / sec resolution in 0..10k range
 * @return              a special value which can be used as an animation time
 */
inline uint32_t anim_speed(uint32_t speed)                                                  { return lv_anim_speed(speed); }


/**
 * Store the speed as a special value which can be used as time in animations.
 * It will be converted to time internally based on the start and end values
 * @param speed         the speed of the animation in as unit / sec resolution in 0..10k range
 * @param min_time      the minimum time in 0..10k range
 * @param max_time      the maximum time in 0..10k range
 * @return              a special value in where all three values are stored and can be used as an animation time
 * @note                internally speed is stored as 10 unit/sec
 * @note                internally min/max_time are stored with 10 ms unit
 *
 */
inline uint32_t anim_speed_clamped(uint32_t speed, uint32_t min_time, uint32_t max_time)    { return lv_anim_speed_clamped(speed, min_time, max_time); }


//-------------------------------------------------------------------------------------
class GTimeline {
  public:
    GTimeline() {}

    /**
     * Create an animation timeline.
     */
    void create(void);

    inline bool isCreated()                 { return (this->_at != NULL && _created);  }

    /**
     * Delete animation timeline.
     */
    void del();

    void clear();

    /**
     * Add animation to the animation timeline.
     * @param start_time    the time the animation started on the timeline, note that start_time will override the value of delay.
     * @param a             pointer to an animation.
     */
    void add(uint32_t start_time, const anim_t * a);

    void add(uint32_t start_time, GAnimation &a);

    /**
     * Start the animation timeline.
     * @return total time spent in animation timeline.
     */
    uint32_t start();

    /**
     * Pause the animation timeline.
     * @return pause time.
     */
    uint32_t pause();

    void stop();

    /**
     * Set the reverse direction of the animation timeline.
     * @param reverse   whether to play in reverse.
     */
    void reverse(bool reverse);

    /**
     * Set the progress of the animation timeline.
     * @param progress  set value 0~65535 to map 0~100% animation progress.
     */
    void progress(uint16_t progress);

    /**
     * Set the action time of the animation timeline.
     * @param act_time  set value 0~playtime of animation timeline.
     */
    void action_time(uint32_t act_time);

    void operator=(uint16_t progress);

    /**
     * Get the time used to play the animation timeline.
     * @return total time spent in animation timeline.
     */
    uint32_t playtime();

    /**
     * Get whether the animation timeline is played in reverse.
     * @return return true if it is reverse reverse.
     */
    bool reverse();

    /**
     * Get the progress of the animation timeline.
     * @return return value 0~65535 to map 0~100% animation progress.
     */
    uint16_t progress();

    /**
     * Get the action time of the animation timeline.
     * @return return action time (0~playtime).
     */
    uint32_t action_time();

    inline uint16_t toInt()                             { return this->progress();      }
    inline void onProgress(anim_timeline_cb_t fn)       { this->_progress_cb = fn;      }
    inline void onStart(anim_timeline_cb_t fn)          { this->_start_cb = fn;         }
    inline void onCompleted(anim_timeline_cb_t fn)      { this->_completed_cb = fn;     }
    inline void onReady(anim_timeline_cb_t fn)          { this->onCompleted(fn);        }
    inline void user_data(void * user_data)             { this->_user_data = user_data; }
    inline void * user_data()                           { return this->_user_data;      }

    bool isProgressing();
    bool isGAnimProgressing(GAnimation *anim);
    inline bool isGAnimProgressing(GAnimation &anim)    { return this->isGAnimProgressing(&anim);   }

    anim_timeline_cb_t _progress_cb = NULL;
    anim_timeline_cb_t _start_cb = NULL;
    anim_timeline_cb_t _completed_cb = NULL;
    anim_timeline_t * _at=NULL;

  private:
    void * _user_data = NULL;
    bool _created = false;
    anim_t  _anim_main;
};



//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------



#endif
