#ifndef __GDATAMONITOR_H__
#define __GDATAMONITOR_H__

#include "GObject.h"
#include "GContainer.h"
#include "GPage.h"
#include "GLabel.h"
#include <vector>

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GDataMonitor : public GContainer {
  public:
    GDataMonitor(GWidget& parent=GScreen) : GContainer(parent)  {} // บังคับให้มี
    GLabel lb_title;
    GLabel lb_control;
    GLabel lb_clear;
    GPage  page_body;
    GLabel lb_data_monitor;
    std::vector<String> data_list;
    uint8_t _max_data_count = 50;
    void create(){
      if(this->isCreated()) return;     // บังคับให้มี
      GContainer::create();             // บังคับ
      GContainer::size(300,200);
      GContainer::min_size(150,150);
      GContainer::GRID_CELL(GRID_COL{GRID_FR(1), GRID_CONTENT, GRID_CONTENT}, GRID_ROW{GRID_CONTENT, GRID_FR(1)});
      GContainer::padding(2);
      GContainer::radius(7);
      GContainer::flag_widget1(true);
      GContainer::font(prasanmit_20, TFT_WHITE);
        lb_title.parent(this);          // บังคับ
        lb_title.grid_cell(0,0,3,1, GRID_ALIGN_STRETCH, GRID_ALIGN_CENTER);
        lb_title.text_align(TEXT_ALIGN_CENTER);
        lb_title.bg_opa(255);
        lb_title.bg_color(TFT_PALETTE(TFT_PALETTE_BLUE));
        lb_title.radius(5);
        lb_title.font(prasanmit_25, TFT_WHITE);
        lb_title = "Data Monitor";

        lb_control.parent(this);
        lb_control = SYMBOL_PLAY;
        lb_control.font(prasanmit_20, TFT_WHITE);
        lb_control.color(TFT_COLOR_HSV(0,0,20), GSTATE_PRESSED);
        lb_control.padding_left(5);
        lb_control.padding_right(10);
        lb_control.grid_cell(2,0, GRID_ALIGN_STRETCH, GRID_ALIGN_CENTER);
        lb_control.clickable(true);
        lb_control.onClicked(GWIDGET_CB{
          GDataMonitor* _p_mon = (GDataMonitor*) (widget->user_data());
          _p_mon->flag_widget1(!_p_mon->flag_widget1());
          _p_mon->lb_control = _p_mon->flag_widget1()?  SYMBOL_PLAY : SYMBOL_PAUSE;
        }, this);

        lb_clear.parent(this);
        lb_clear = SYMBOL_TRASH;
        lb_clear.font(prasanmit_20, TFT_WHITE);
        lb_clear.color(TFT_COLOR_HSV(0,0,20), GSTATE_PRESSED);
        lb_clear.padding_left(5);
        lb_clear.padding_right(5);
        lb_clear.grid_cell(1,0, GRID_ALIGN_STRETCH, GRID_ALIGN_CENTER);
        lb_clear.clickable(true);
        lb_clear.onClicked(GWIDGET_CB{
          GDataMonitor* _p_mon = (GDataMonitor*) (widget->user_data());
          _p_mon->clear();
        }, this);

        page_body.parent(this);         // บังคับ
        page_body.grid_cell(0,1, 3, 1, GRID_ALIGN_STRETCH, GRID_ALIGN_STRETCH);
        page_body.color(TFT_COLOR_HSV(0,0,20));
        page_body.radius(5);
        page_body.layout(LAYOUT_COL_L,5,5,10,10,0);
          lb_data_monitor.parent(page_body);
          lb_data_monitor = "";
    }
    // พิมพ์ธรรมดา (ไม่ขึ้นบรรทัดใหม่)
    inline void print(String new_data) {
      create();
      if (data_list.empty()) data_list.push_back("");
      data_list.back() += new_data;
      update_label_and_scroll();
    }

    // ขึ้นบรรทัดใหม่
    inline void println(String new_data) {
      create();
      push_data(new_data);
    }

    // print แบบ float/double
    inline void print(float value, uint8_t decimal_places = 2)      { print(String(value, (unsigned int) decimal_places)); }
    inline void print(double value, uint8_t decimal_places = 2)     { print(String(value, (unsigned int) decimal_places)); }
    inline void println(float value, uint8_t decimal_places = 2)    { println(String(value, (unsigned int) decimal_places)); }
    inline void println(double value, uint8_t decimal_places = 2)   { println(String(value, (unsigned int) decimal_places)); }

    // print แบบ int / const char*
    inline void print(int value)              { print(String(value));   }
    inline void println(int value)            { println(String(value)); }
    inline void print(const char* value)      { print(String(value));   }
    inline void println(const char* value)    { println(String(value)); }

    // printf style
    inline void printf(const char* format, ...) {
      create();
      char buf[256];
      va_list args;
      va_start(args, format);
      vsnprintf(buf, sizeof(buf), format, args);
      va_end(args);
      print(String(buf)); // ไม่ขึ้นบรรทัดใหม่
    }

    inline void clear(){
      create();
      data_list.clear();
      lb_data_monitor = "";
      page_body.scroll_to_y(COORD_MAX, ANIM_OFF);
    }

    inline void max_data_count(uint8_t max_count){
      create();
      if(max_count < 20 || max_count > 100) return;
      _max_data_count = max_count;
      this->clear();
    }
    inline uint8_t max_data_count() const {
      return _max_data_count;
    }

  private:
    // ฟังก์ชันภายในใช้ update GLabel และ scroll
    inline void update_label_and_scroll() {
      create();
      String combined;
      for (size_t i = 0; i < data_list.size(); ++i) {
        combined += data_list[i];
        if (i != data_list.size() - 1) {
          combined += "\n";
        }
      }
      lb_data_monitor = combined;
      lb_data_monitor.color(GContainer::font_color());

      if(lb_data_monitor.width() > page_body.content_width()){
        page_body.scrollbar(SCROLLBAR_AUTO, true, true);
      }else{
        page_body.scrollbar(SCROLLBAR_AUTO, false, true);
      }
      // scroll เฉพาะตอนอยู่ในสถานะ run
      if (this->flag_widget1()) {
        page_body.scroll_to_y(COORD_MAX, ANIM_OFF);
        if(lb_data_monitor.width() > page_body.content_width()){
          page_body.scroll_to_x(COORD_MAX, ANIM_OFF);
        }
      }
    }

    inline void push_data(String new_data) {
      if (data_list.size() >= _max_data_count) {
        data_list.erase(data_list.begin());
      }
      data_list.push_back(new_data);
      update_label_and_scroll();
    }
};


//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif // __GDATAMONITOR_H__
