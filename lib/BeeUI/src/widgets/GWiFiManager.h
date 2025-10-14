/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GWiFiManager.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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
 *   [Version5.0 beta1] @24/01/25
 *     - GWiFiSetting เชื่อมต่อไวไฟได้, scan wifi ได้, แสดง wifi info ได้ สำหรับ ESP32
 *       สำหรับ PC ยัง
 *     - แก้เม็มรั่วได้แล้ว จาก onBack ต้องปิด timer ก่อน ออก
 *       และไม่จำเป็นต้อง clear mem ที่จองเอง เพราะใช้ unique pointer
 *  
 * 
 *********************************************************************************
 */

#ifndef __GWIFIMANAGER_H__
#define __GWIFIMANAGER_H__


#include "GObject.h"
#include "GLabel.h"
#include "GButton.h"
#include "GTextArea.h"
#include "GPage.h"
#include "GContainer.h"
#include "GList.h"
#include "GSwitch.h"

#include "widgets_extra/wifimanager/lv_wifimanager.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------
class GWiFiSetting;

typedef struct _wifimanager_config{
  char      ssid[33];
  char      password[65];
  uint8_t   bssid[6];
  bool      ssid_enable;
  bool      auto_ip_enable;
  uint32_t  fixed_ip32;
  uint32_t  gateway_ip32;
  uint32_t  subnet32;
  uint32_t  dns32;
} wifimanager_config_t;

class GWiFiManager : public GObject {
  public:
    GWiFiManager(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GWiFiManager(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GWiFiManager();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }


    void wifi_rssi_cb(fn_get_wifi_rssi_t cb);
    void wifi_connection_cb(fn_get_wifi_connection_t cb);
    void color(color_t color_wifi_connected, color_t color_wifi_disconnected=  TFT_RED, color_t color_wifi_bg= TFT_DARKGRAY);
    fn_get_wifi_rssi_t wifi_rssi_cb();
    fn_get_wifi_connection_t wifi_connection_cb();
    color_t color_wifi_connected();
    color_t color_wifi_disconnected();
    color_t color_wifi_bg();

    std::unique_ptr<GWiFiSetting> _u_wifisetting;             // วิตเจ็ต GWiFiSetting
    static  void    onWiFiConnected();                        // เชื่อมเสร็จได้ จะมา run WiFiSignalUpdate_Task_cb() เป็นระยะให้อัตโนมัติ
    static  void    onWiFiDisconnected();  

  private:
};


/******************************************************
 * GWiFiSetting
 ******************************************************/

class GWiFiSetting : public GObject {
  public:
    GWiFiSetting(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GWiFiSetting(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GWiFiSetting();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    void onBack(event_handler_t fn)                         { if(!this->isCreated()) this->create();  this->fn_onback = fn; }
    event_handler_t fn_onback = NULL;

    static void onWiFiConnected();
    static void onWiFiDisconnected();
    static void update_WiFiInfo();
    static void ta_onValueChanged(GWidget*w);

    static void scan_WiFiNetworks();
    static void update_NetworkList();
    static void WiFiReScan(uint32_t period=10000);

    static wifimanager_config_t wifi_config;
    static void autoconnection();                         // คำสั่งให้โหลด load_WiFiConfig() แล้วทำการเชื่อมต่อ connect_WiFi()
    static void load_WiFiConfig();                        // สำหรับโหลด WiFiConfig
    static void save_WiFiConfig();                        // สำหรับบันทึก WiFiConfig
    static void save_WiFiConfig(String ssid, String pass);// สำหรับบันทึก WiFiConfig
    static void clean_WiFiConfig();                       // สำหรับล้าง WiFiConfig
    static void display_WiFiConfig();                     // สำหรับแสดง WiFiConfig ออก Serial Monitor
    static void connect_WiFi(bool force_reconnect=false); // คำสั่ง สำหรับเชื่อมต่อ WiFi จาก WiFiConfig ; force_reconnect = true คือบังคับตัด wifi แล้วเชื่อมต่อใหม่
    static void disconnect_WiFi();                         // คำสั่ง สำหรับตัดการเชื่อมต่อ WiFi

    // เลเยอร์ลูก สำหรับหน้า WiFiSetting
    // ส่วน Title Bar
    std::unique_ptr<GButton> _u_btn_back;                 // วิตเจ็ตปุ่มกด สำหรับ back ไปหน้าหลัก ให้เป็น ลูกของ GWiFiSetting
    std::unique_ptr<GLabel> _u_lb_wifisetting_title;      // วิตเจ็ตข้อความ "ตั้งค่า WiFi"  ให้เป็น ลูกของ GWiFiSetting
    std::unique_ptr<GButton> _u_btn_wifiscan;             // วิตเจ็ดปุ่มกด สำหรับ wifi scan  ให้เป็น ลูกของ GWiFiSetting
    std::unique_ptr<GButton> _u_btn_wifistatus;           // วิตเจ็ดปุ่มกด สำหรับ สถานะว่า wifi เชื่อมต่อสำเร็จหรือไม่ กดเข้าไปให้บอก ข้อมูลเชื่อมต่อ ให้เป็น ลูกของ GWiFiSetting

    // ส่วน Body
    std::unique_ptr<GPage> _u_page_body;                  // วิตเจ็ต Page ส่วน body สำหรับ WiFiManager  ให้เป็น ลูกของ GWiFiSetting
      std::unique_ptr<GContainer> _u_cont_ssid;           // วิตเจ็ต Container ส่วน ssid/password สำหรับ WiFiManager ให้เป็นลูกของ page_body
        std::unique_ptr<GSwitch> _u_sw_ssid_enable;       // วิตเจ็ตสวิตซ์เลื่อน สำหรับ สั่งเปิด/ปิด การเชื่อมต่อ ssid ให้เป็นลูกของ cont_ssid
        std::unique_ptr<GLabel> _u_lb_ssid_info;          // วิตเจ็ตข้อความ "SSID :"  ให้เป็น ลูกของ page_body
        std::unique_ptr<GLabel> _u_lb_pass_info;          // วิตเจ็ตข้อความ "Password :" ให้เป็น ลูกของ page_body
        std::unique_ptr<GTextArea> _u_ta_ssid;            // วิตเจ็ตช่องใส่ข้อความ สำหรับให้ผู้ใช้ เติม ssid ให้เป็น ลูกของ page_body
        std::unique_ptr<GTextArea> _u_ta_password;        // วิตเจ็ตช่องใส่ข้อความ สำหรับให้ผู้ใช้ เติม password ให้เป็น ลูกของ page_body
      std::unique_ptr<GContainer> _u_cont_auto_ip;        // วิตเจ็ต Container ส่วน auto ip/fix ip ให้เป็นลูกของ page_body
        std::unique_ptr<GLabel> _u_lb_auto_ip;            // วิตเจ็ตข้อความ "Auto IP "  ให้เป็นลูกของ cont_auto_ip
        std::unique_ptr<GSwitch> _u_sw_auto_ip;           // วิตเจ็ตสวิตซ์เลื่อน ให้เป็นลูกของ cont_auto_ip
      std::unique_ptr<GContainer> _u_cont_fix_ip;         // วิตเจ็ต Container ใช้เป็นพื้นที่ สำหรับกรอก fix ip ต่างๆ
        std::unique_ptr<GLabel> _u_lb_fix_ip;             // วิตเจ็ตข้อความ "Fixed IP :" ให้เป็นลูกของ rect_fix_ip
        std::unique_ptr<GLabel> _u_lb_gateway_ip;         // วิตเจ็ตข้อความ "Gateway IP :" ให้เป็นลูกของ rect_fix_ip
        std::unique_ptr<GLabel> _u_lb_subnet;             // วิตเจ็ตข้อความ "Net Mask :" ให้เป็นลูกของ rect_fix_ip
        std::unique_ptr<GLabel> _u_lb_dns_ip;
        std::unique_ptr<GTextArea> _u_ta_fix_ip;          // วิตเจ็ตช่องใส่ข้อความ สำหรับให้ผู้ใช้แก้ fixed ip  ให้เป็นลูกของ rect_fix_ip
        std::unique_ptr<GTextArea> _u_ta_gateway_ip;      // วิตเจ็ตช่องใส่ข้อความ สำหรับให้ผู้ใช้แก้ gateway ip  ให้เป็นลูกของ rect_fix_ip
        std::unique_ptr<GTextArea> _u_ta_subnet;          // วิตเจ็ตช่องใส่ข้อความ สำหรับให้ผู้ใช้แก้ Net Mask  ให้เป็นลูกของ rect_fix_ip
        std::unique_ptr<GTextArea> _u_ta_dns_ip;

    // ตัวช่วยไว้บังไม่ให้กดได้
    std::unique_ptr<GRect> _u_rect_disable_click;         // วิตเจ็ตสี่เหลี่ยม สำหรับบังไม่ให้สามารถ click อะไรๆได้ ให้เป็น ลูกของ GWiFiSetting

    // ส่วนของ msgbox สำหรับ WiFi Scan และ WiFi Info (ใช้ร่วมกัน)
    std::unique_ptr<GRect> _u_app_wifi_msgbox;            // วิตเจ็ตสี่เหลี่ยม สำหรับเป็นพื้นที่ จัดการ WiFi Scan ให้เป็น ลูกของ GWiFiSetting
      // ส่วน Title Bar
      std::unique_ptr<GButton> _u_btn_wifi_msgbox_back;   // วิตเจ็ตปุ่มกด สำหรับ back ไปก่อนหน้า ให้เป็น ลูกของ app_wifi_msgbox
      std::unique_ptr<GLabel> _u_lb_wifi_msgbox_title;    // วิตเจ็ตข้อความ สำหรับเป็น title ของ app_wifi_msgbox ให้เป็น ลูกของ app_wifi_msgbox
      std::unique_ptr<GLabel> _u_lb_wifi_msgbox_status;   // วิตเจ็ตข้อความ สำหรับเป็น status ด้านล่าง ของ app_wifi_msgbox ให้เป็น ลูกของ app_wifi_msgbox

      // ส่วน Body สำหรับ WiFi Scan
      std::unique_ptr<GList> _u_list_wifiscan;            // วิตเจ็ต List ส่วน body สำหรับ WiFi Scan เวลา scan พบ ssid จะมาใส่ใน list นี้ ให้เป็น ลูกของ app_wifi_msgbox

      // ส่วน Body สำหรับ WiFi Info
      std::unique_ptr<GPage> _u_page_wifiinfo;            // วิตเจ็ต Page ให้เป็นส่วน body สำหรับ WiFi Info หากเชื่อมต่อสำเร็จจะไว้บอก IP, SubNet Mask, Domain IP เป็นต้น  ให้เป็น ลูกของ app_wifi_msgbox
        std::unique_ptr<GLabel> _u_lb_wifiinfo;           // วิตเจ็ตข้อความ ไว้รวบรวมข้อมูล WiFi info เมื่อมีการเชื่อมต่อสำเร็จ ให้เป็นลูกของ page_wifiinfo

  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GWIFIMANAGER_H__
