/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GQRCode.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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
 * 
 *********************************************************************************
 */

#ifndef __GQRCODE_H__
#define __GQRCODE_H__


#include "GObject.h"
#include "GImage.h"

IMG_DECLARE(ico_th_qrpayment);
IMG_DECLARE(ico_wifi);
IMG_DECLARE(ico_line);

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

typedef enum {
  WIFI_NOPASS,
  WIFI_WEB,
  WIFI_WPA,
} wifi_type_t;

class GQRCode : public GObject {
  public:
    GQRCode(GWidget& parent=GScreen)                        : GObject(&parent) {}
    GQRCode(GWidget* parent)                                : GObject(parent)  {}
    virtual ~GQRCode();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }


    inline void size(int32_t w, int32_t h)                  { this->size(min(w,h));                               }
    inline void color(color_t color)                        { this->dark_color(color);                            }

    inline void encode(String txt)                          { this->encode((const void*)txt.c_str(),txt.length());}
           void encode(String txt, const img_t&logo);
    inline void encode(String txt, const img_t*logo)        { this->encode(txt,*logo);                            }


    void encodeWiFi(String ssid, String password="", wifi_type_t wifi_type=WIFI_WPA);
    void encodeLine(String line_id);
    void encodePromptPay(String id, float amount, bool multi_use=true); // สำหรับโอนเงิน
    void encodePromptPay(String biller_id, String reference_id1, String reference_id2, float amount, bool multi_use=false, String terminal_label= "");
    void encodeKPlusShop(String MerchantID, String bill_id, float amount, bool multi_use=false, String terminal_label= "");


    GQRCode& operator =(const String txt);
    GQRCode& operator =(const img_t * logo);
    GQRCode& operator =(const img_t & logo);

    /**
     * Set QR code size.
     * @param size width and height of the QR code
     */
    void size(int32_t size);

    /**
     * Set QR code dark color.
     * @param color dark color of the QR code
     */
    void dark_color(color_t color);

    /**
     * Set QR code light color.
     * @param color light color of the QR code
     */
    void light_color(color_t color);

    /**
     * Set QR code version
     * @param qr_version QR code version  1-40  ;  0 = AUTO
     */
    void version(uint8_t qr_version);

    /**
     * Set the data of a QR code object
     * @param data data to display
     * @param data_len length of data in bytes
     * @return LV_RESULT_OK: if no error; LV_RESULT_INVALID: on error
     */
    void encode(const void * data, uint32_t data_len);

    // std::unique_ptr<GImage> _u_logo;
    const img_t* _logo=NULL;
  private:
    int32_t _sz = -1;

};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GQRCODE_H__
