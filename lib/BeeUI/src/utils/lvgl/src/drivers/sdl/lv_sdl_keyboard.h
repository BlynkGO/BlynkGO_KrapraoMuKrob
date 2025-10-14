/**
 * @file lv_sdl_keyboard.h
 *
 */

#ifndef LV_SDL_KEYBOARD_H
#define LV_SDL_KEYBOARD_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lv_sdl_window.h"
#if LV_USE_SDL

/*********************
 *      DEFINES
 *********************/
#ifndef KEYBOARD_BUFFER_SIZE
#define KEYBOARD_BUFFER_SIZE 32
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_indev_t * lv_sdl_keyboard_create(void);

// BlynkGO
const char * lv_sdl_get_clipboard_text(void);
void lv_sdl_free_clipboard_text(const char* clipboardtext);
bool lv_sdl_set_clipboard_text(const char *text);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_SDL*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_SDL_KEYBOARD_H */
