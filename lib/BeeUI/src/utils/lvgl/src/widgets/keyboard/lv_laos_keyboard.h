#ifndef LV_LAOS_KEYBOARD_H
#define LV_LAOS_KEYBOARD_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "lv_keyboard.h"

#if BLYNKGO_DEF_KEYBOARD
extern const char *                 default_kb_map_la_full[];
extern const char *                 default_kb_map_la_full_shift[];
extern const char *                 default_kb_map_la_mini_0[];
extern const char *                 default_kb_map_la_mini_1[];
extern const char *                 default_kb_map_la_mini_2[];
extern const char *                 default_kb_map_la_mini_3[];
extern const char *                 default_kb_map_la_mini_4[];
extern const char *                 default_kb_map_la_mini_5[];
extern const char *                 default_kb_map_la_mini_6[];
extern const char *                 default_kb_map_la_mini_7[];
extern const char *                 default_kb_map_la_mini_8[];
extern const char *                 default_kb_map_la_mini_9[];
extern const char *                 default_kb_map_la_mini_10[];
extern const char *                 default_kb_map_la_mini_11[];
extern const char *                 default_kb_map_la_mini_12[];


extern const lv_buttonmatrix_ctrl_t default_kb_ctrl_map_la_full[];
extern const lv_buttonmatrix_ctrl_t default_kb_ctrl_map_la_mini[];
extern const lv_buttonmatrix_ctrl_t default_kb_ctrl_map_la_mini_vannayuk[];
extern const lv_buttonmatrix_ctrl_t default_kb_ctrl_map_la_mini_numpad[];

#endif


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_LAOS_KEYBOARD_H*/
