#include "Arduino.h"

#if defined(LCD_WIDTH) && defined(LCD_HEIGHT)
  #if defined(LCD_ROTATION)
    #if (LCD_ROTATION == 0)
      int32_t lcd_width = LCD_WIDTH;
      int32_t lcd_height = LCD_HEIGHT;
    #else
      int32_t lcd_width = LCD_HEIGHT;
      int32_t lcd_height = LCD_WIDTH;
    #endif
  #else
    int32_t lcd_width = LCD_WIDTH;
    int32_t lcd_height = LCD_HEIGHT;
  #endif

#else
  int32_t lcd_width = 800;
  int32_t lcd_height = 480;
#endif

#include "../../../../blyngko_kmk_version.h"
String blynkgo_kmk_version = (String(BLYNKGO_KMK_VERSION_MAJOR)+"."+String(BLYNKGO_KMK_VERSION_MINOR)+"."+String(BLYNKGO_KMK_VERSION_PATCH));
