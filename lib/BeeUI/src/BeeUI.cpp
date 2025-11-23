#include "BeeUI.h"
#include "utils/lvgl/src/display/lv_display.h"
#include "utils/lvgl/src/drivers/sdl/lv_sdl_window.h"
#include "utils/lvgl/src/drivers/sdl/lv_sdl_keyboard.h"
#include "utils/lvgl/src/drivers/sdl/lv_sdl_mouse.h"
#include "utils/lvgl/src/drivers/sdl/lv_sdl_mousewheel.h"

#if LV_USE_SDL
#include <stdbool.h>

#include "utils/lvgl/src/core/lv_refr.h"
#include "utils/lvgl/src/stdlib/lv_string.h"
#include "utils/lvgl/src/core/lv_global.h"
#include "utils/lvgl/src/lv_init.h"



#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" issue*/
#include LV_SDL_INCLUDE_PATH

#if LV_USE_DRAW_SDL
    #include <SDL2/SDL_image.h>
#endif
#endif  //#if LV_USE_SDL

#define WINDOW_ICON_PATH  R"(D:\BackUP_HDD500\BlynkGO_Labs\BlynkGO_Boards\BeeNeXT\icon_beenext.bmp)"

BeeUI BlynkGO;

GLabel lb_status;
GLabel lb_mouse;

extern int32_t lcd_width;
extern int32_t lcd_height;

/**
 * เริ่มต้น ระบบการทำงานของ BlynkGO ให้ทำงาน
 */
void BeeUI::begin(){
  this->window_resizable(false);
  this->window_icon(WINDOW_ICON_PATH);
  this->window_position(950,120);
  this->window_title(StringX::printf("BlynkGO กระเพราหมูกรอบ v%s", blynkgo_kmk_version.c_str()));

  if(GScreen.isCreated()) return;

  GScreen.setObject(lv_scr_act());  // กำหนด obj เท่าน้น และให้เป็น created ไปเลย จะได้ใช้ style ได้
  GScreen.color(TFT_BLACK);
  GScreen.size(LCD_WIDTH,LCD_HEIGHT);
  GScreen.scrollable(false);

  //-------------------------------------------------------
  lb_mouse.ignore_layout(true);      // กันไม่ให้ เปลี่ยนตำแหน่งตาม layout ของ GScreen
  lb_mouse.align(ALIGN_BOTTOM_LEFT, LCD_WIDTH-100);
  lb_mouse.font(prasanmit_20);
  static SoftTimer timer_mouse;
  timer_mouse.setInterval(3, [lb_mouse]() {
    if(GScreen.color() == lb_mouse.color()){
      if(GScreen.color() == TFT_WHITE)       { lb_mouse.color(TFT_BLACK); lb_status.color(TFT_BLACK); }
      else if (GScreen.color() == TFT_BLACK) { lb_mouse.color(TFT_WHITE); lb_status.color(TFT_WHITE); }
    }
    lb_mouse = StringX::printf("พิกัด %d,%d",
                               windows_mouseX, windows_mouseY);
    lb_mouse.toForeground();
    lb_mouse.align(ALIGN_BOTTOM_LEFT, LCD_WIDTH-100 - GScreen.pad_right(), GScreen.pad_bottom());  //ทดระยะ pad_right และ pad_bottom คืน
  });
  //-------------------------------------------------------
  lb_status.font(prasanmit_20);
  lb_status.ignore_layout(true);
  lb_status.align(ALIGN_BOTTOM_LEFT, 10);

#if LV_USE_SDL
  empty_group       = lv_group_create();
  pc_keyboard_group = lv_group_create();
#endif

}

/**
 * สำหรับ update ระบบการทำงานของ BlynkGO
 */
void BeeUI::update(){
  BeeNeXT.update();
}

// /**
//  * คืนค่า ขนาดความกว้างของจอ
//  * @return   ขนาดความกว้างจอ
//  */
// int32_t BeeUI::width(){
//   return lcd_width;
// }

// /**
//  * คืนค่า ขนาดความสูงของจอ
//  * @return   ขนาดความสูงของจอ
//  */
// int32_t BeeUI::height(){
//   return lcd_width;
// }

/**
 * กำหนด window title
 * @param title  windows title
 */
void BeeUI::window_title(String title){
  lv_display_t* display = lv_display_get_default();
  lv_sdl_window_set_title(display, title.c_str());
}

/**
 * ปรับขนาด window ได้หรือไม่
 * @param en  true : ได้ , false ไม่ได้
 */
void BeeUI::window_resizable(bool en){
  lv_display_t* display = lv_display_get_default();
  lv_sdl_window_set_resizeable(display,en);
}

/**
 * กำหนด icon ของ window
 * @param filename  path ของ ไฟล์ bmp ที่จะทำ icon ของ window
 */
void BeeUI::window_icon(String filename){
  // SDL_SetWindowIcon(SDL_Window * window,SDL_Surface * icon);  
  lv_display_t* display = lv_display_get_default();
  SDL_Window * sdl_window = lv_sdl_window_get_sdl_window(display);
  SDL_Surface* iconSurface = SDL_LoadBMP(filename.c_str());

  if (iconSurface == NULL) {
      printf("Unable to load image %s! SDL Error: %s\n", filename.c_str(), SDL_GetError());
      return;
  }
  SDL_SetWindowIcon(sdl_window, iconSurface);
}

/**
 * กำหนด ตำแหน่ง ของ window บนหน้าจอ Computer
 * @param x   พิกัด x
 * @param y   พิกัด y
 */
void BeeUI::window_position(int x, int y){
  lv_display_t* display = lv_display_get_default();
  SDL_Window * sdl_window = lv_sdl_window_get_sdl_window(display);
  SDL_SetWindowPosition(sdl_window,x,y);
}

Point touch_point(){
  lv_indev_t * indev = lv_indev_active();
  lv_point_t  pt;
  lv_indev_get_point(indev, &pt);
  Point p = { p.x,p.y};
  return p;
}

void BeeUI::show_mouse_info(bool en){
  if(!GScreen.isCreated())  this->begin();
  lb_mouse.show(en);
}

point_t touch_vect(){
  lv_indev_t * indev = lv_indev_get_act();
  return (point_t){indev->pointer.vect.x, indev->pointer.vect.y};  
}

GWidget* BeeUI::mouse_search_widget(){
  lv_point_t p;
  lv_indev_get_point(mouse, &p);
  auto _obj = lv_indev_search_obj(lv_screen_active(),&p);
  if(_obj) {
    return (GWidget*)  lv_obj_get_user_data(_obj);
  }
  return NULL;
}
