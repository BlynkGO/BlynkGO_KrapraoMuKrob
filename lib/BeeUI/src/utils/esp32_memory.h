#ifndef __ESP32_MEMORY_H___
#define __ESP32_MEMORY_H___


#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stddef.h>

#if defined(ESP32)
#include "sdkconfig.h"
#endif

void* esp32_malloc(size_t size);
void* esp32_calloc(size_t n, size_t size);
void* esp32_realloc(void *ptr, size_t size);
void  esp32_free(void *ptr);

#ifdef __cplusplus
}
#endif

#endif //__ESP32_MEMORY_H___
