#ifndef __BEEUI_H__
#define __BEEUI_H__

#include "Arduino.h"
#include <BeeNeXT.h>
#include <WinTime.h>
#include <tinyfiledialogs.h>
#include <system_silently.h>
#include "./utils/lvgl/lvgl.h"
#include "./widgets/GWidgets.h"
#include <cstdlib>
#include "SDL.h"
#include <vector>

#include "../../../blyngko_kmk_version.h"

#define BLYNKGO_KMK_VERSION_TEXT    (String(BLYNKGO_KMK_VERSION_MAJOR)+"."+String(BLYNKGO_KMK_VERSION_MINOR)+"."+String(BLYNKGO_KMK_VERSION_PATCH))

/**
 * Macro to convert IDF version number into an integer
 *
 * To be used in comparisons, such as BLYNKGO_VERSION >= BLYNKGO_KMK_VERSION_VAL(5, 0, 0)
 */
#define BLYNKGO_KMK_VERSION_VAL(major, minor, patch) ((major << 16) | (minor << 8) | (patch))

/**
 * Current IDF version, as an integer
 *
 * To be used in comparisons, such as BLYNKGO_KMK_VERSION >= BLYNKGO_KMK_VERSION_VAL(5, 0, 0)
 */
#define BLYNKGO_KMK_VERSION     BLYNKGO_KMK_VERSION_VAL(  BLYNKGO_KMK_VERSION_MAJOR, \
                                                          BLYNKGO_KMK_VERSION_MINOR, \
                                                          BLYNKGO_KMK_VERSION_PATCH)


extern String blynkgo_kmk_version;

using namespace BLYNKGO_V5;

FONT_DECLARE(prasanmit_15);
FONT_DECLARE(prasanmit_18);

typedef void (*WiFiConnectedCb)(void);
typedef void (*WiFiDisconnectedCb)(void);

#define ROTATION_DEFAULT      0
#define ROTATION_VERTICAL     1

class BeeUI {
  public:
    BeeUI() {}
    void begin();
    void update();

    int32_t width();
    int32_t height();

    __attribute__ ((always_inline)) inline Point center()                   { return Point(width()/2, height()/2);  }
    __attribute__ ((always_inline)) inline Point centerpoint()              { return GScreen.centerpoint();         }
    
    void window_title(String title);
    void window_resizable(bool en);
    void window_icon(String filename);
    void window_position(int x, int y);

    inline void fillScreen(color_t color)         { GScreen.color(color);   }
    inline void rotation(int8_t r)                { }

    GWidget* mouse_search_widget();

    void show_mouse_info(bool en);


    inline void onWiFiConnected    (WiFiConnectedCb cbConnected)                            { this->wifi_connected_cb     = cbConnected;      }
    inline void onWiFiDisconnected (WiFiDisconnectedCb cbDisconnected)                      { this->wifi_disconnected_cb  = cbDisconnected;   }
    WiFiConnectedCb     wifi_connected_cb;
    WiFiDisconnectedCb  wifi_disconnected_cb;

  private:

};

extern BeeUI BlynkGO;
extern int windows_mouseX, windows_mouseY;
void Windows_CopyTextToClipboard(const char* text);
extern lv_indev_t * mouse;
extern lv_indev_t * pc_keyboard;
extern GLabel lb_status;

#endif
