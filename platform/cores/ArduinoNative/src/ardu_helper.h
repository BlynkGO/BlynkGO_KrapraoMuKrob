#ifndef __ARDU_TIME_H__
#define __ARDU_TIME_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

unsigned long millis();
inline void delay(unsigned int milliseconds)    {  usleep(milliseconds * 1000); }

// FAKE API
inline void pinMode(uint8_t pin, uint8_t type)          { }
inline void digitalWrite(uint8_t pin, uint8_t state)    { }
inline bool digitalRead(uint8_t pin)                    {  return true; }

#ifdef INPUT
#undef INPUT
#endif

#ifdef boolean
#undef boolean
#endif

#define INPUT         1
#define INPUT_PULLUP  2
#define OUTPUT        3

#ifdef __cplusplus
} // extern "C"
#endif



#endif
