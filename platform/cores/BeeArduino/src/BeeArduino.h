#ifndef __BEEARDUINO_H__
#define __BEEARDUINO_H__

/*************************************************************************
 * Version 1.0 @ 02/02/2024
 *     - รองรับ lvgl9
 *     - รองรับ WString ที่เลียนแบบคล้าย String ของ Arduino
 * 
 * Version 1.1 @05/10/2025
 *     - toolchain buildin
 *     - BeeCreator --> BeeArduino 
 *     - BEEARDUINO_USE_NOLOOP  support
 * 
 ************************************************************************/

#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <unistd.h>
// #include "lvgl.h"

void _FnNoOpCbk();
void setup();
void loop();


#ifdef __cplusplus
} /*extern "C"*/
#endif



#endif // __BEEARDUINO_H__