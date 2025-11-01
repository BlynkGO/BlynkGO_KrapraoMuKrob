/*
 * เขียนใหม่เป็นอีก protocol นึง เพื่อรองรับ สามารถส่งเป็น data byte array 
 * ตามจำนวนขนาด data size ได้
 *
 * Version 3.0.0 :
 *    - ใช้ BeeNeXT Protocol รันบน UART Bus 
 *
 * Version 3.0.1 : @ 20/09/66
 *    - ให้สามารถปรับเพิ่ม buffer เองได้ กำหนดใน beenext_config.h
 *
 * Versoin 3.0.2 : @ 30/09/66
 *    - เพิ่ม mem.h,mem.c ให้ ไม่ต้องติด warning
 *
 * Versoin 3.0.3 : @ 30/09/66
 *    - ยกเลิก mem.h,mem.c กลับไปใน free(..) แทน
 *    - fix ปัญหาสำคัญใช้ memset(..) ผิด แก้ให้ถูกแล้ว (สลับ 2 parameter สุดท้าย)
 *
 * Version 3.0.4 : @19/10/66
 *    - เพิ่ม MCU_DATA, LCD_DATA ซึ่ง alias ไปยัง BEENEXT_DATA
 *    - เพิ่ม MCU, LCD  ซึ่ง alias ไปยัง BeeNeXT
 * 
 * Version 3.0.5 : @06/01/67
 *    - สนับสนุน ESP32S2, ESP32C3 ได้ด้วย
 *
 * Version 3.0.6 : @04/03/67
 *    - เพิ่ม #include <stdlib.h> ให้ linklist 
 *      ช่วยป้องกันบาง MCU เช่น UNO รัน SoftTimer ไปราว 4-5นาที บ้าง อยู่ๆ timer หยุดทำงาน
 *      ต้องมีการเรียก timer กลับมาทำงานซ้ำจึงทำงานใหม่ได้  แต่พอเพิ่มแล้วดูจะไม่เกิดอาการอีก
 * 
 * Version 3.1.0 : @04/03/67
 *    - ปรับปรุง SoftTimer ให้ แบบ setInterval(..) สามารถกำหนดรอบที่จะทำงานมากสุดกี่รอบได้
 *      โดย สามารถกำหนด ready_cb(..) เพื่อ ไว้ทำงานตอนหลังจากครบรอบทั้งหมดแล้ว
 * 
 * Version 3.1.1 : @05/03/67
 *    - fix เวลา ล้าง timer ออกไป free mem ที่จอง ไม่ให้เกิด mem รั่ว
 * 
 * Version 3.1.2 : @26/06/67
 *    - เปลี่ยน คำสั่ง SoftTimer เมื่อมีการ pause() แล้วให้กลับมาทำงานด้วยคำสั่ง resume()  ไม่ใช่ replay()
 *
 * Version 3.1.3 : @21/12/67
 *    - ESP32 รองรับ CDC  ( HWCDC, USBCDC )
 *
 * Version 3.1.4 : @17/03/68
 *    - ESP8266 / ESP32 เพิ่ม ::delay(1) ขณะ run ป้องกัน WDT ให้สามารถกระจายไปยัง task อื่นทำงานได้
 *
 * Version 3.1.5  @21/03/68
 *    - รองรับ ESP32P4, ESP32C6 ด้วย
 *
 * Version 3.1.6  @23/03/68
 *    - รองรับ BEENEXT_USE_BEEI2C (default) แต่แรก  
 *    - รองรับ BEENEXT_USE_BEEMQTT เชื่อมต่อแบบไร้สาย 
 *    - รองรับ BEENEXT_USE_BEEUART_CRC16   
 *    - SoftTimer มี onFinished แทน ready_cb  
 *
 * Version 3.1.7  @28/03/68
 *    - เพิ่มขา 20 ให้เป็น OUTPUT LOW เพื่อทำเป็น GND สำหรับ BeeNeXT4.3,4.3C,4.3IPS
 * 
 * Version 3.1.8  @29/03/68
 *    - เอาขา 20 เป็น OUTPUT LOW ออก เนื่องจากไปชน ขา I2C ของ Touch สำหรับ BeeNeXT4.3,4.3C,4.3IPS
 *    - เพิ่ม BeeUART.h/.cpp  BEENEXT_USE_BEEUART
 * 
 * Version 3.1.9  @29/03/68
 *    - fix BEENEXT_USE_BEEUART เพิ่ม onData ฝั่งจอ BeeNeXT
 *    - ปรับแก้ตัวอย่าง
 * 
 * Version 3.1.10  @04/04/68
 *    - fix BEENEXT_USE_BEEUART สำหรับ ESP32P4
 *    - fix BeeMQTT ฝั่ง MCU หลัก;
 * 
 * Version 3.1.11  @04/04/68
 *    - fix BeeMQTT ฝั่ง จอ BeeNeXT ไม่ให้ มี error BeeMQTT ที่จะไม่มีให้ใช้;
 * 
 * Version 3.1.12  @27/06/68
 *    - fix for BeeNeXT1.9IPS, BeeNeXT3.5, BeeNeXT3.5C
 * 
 * Version 3.1.13  @22/09/68
 *    - fix BeeUart ให้มีคำสัง print, และ กรอง [BN] ออก
 * 
 * Version 3.1.14  @24/09/68
 *    - รองรับ USB CDC on boot : Enable  ได้ด้วย
 * 
 * Version 3.1.15  @01/11/68
 *    - fix SoftTimer delay(...) ที่บน PC รัน nested lambda ไม่ได้
 */

#ifndef __BEENEXT_H__
#define __BEENEXT_H__

/** Major version number (X.x.x) */
#define BEENEXT_VERSION_MAJOR   3
/** Minor version number (x.X.x) */
#define BEENEXT_VERSION_MINOR   1
/** Patch version number (x.x.X) */
#define BEENEXT_VERSION_PATCH   15

#define BEENEXT_VERSION_TEXT    (String(BEENEXT_VERSION_MAJOR)+"."+String(BEENEXT_VERSION_MINOR)+"."+String(BEENEXT_VERSION_PATCH))

/**
 * Macro to convert IDF version number into an integer
 *
 * To be used in comparisons, such as BEENEXT_VERSION >= BEENEXT_VERSION_VAL(3, 0, 0)
 */
#define BEENEXT_VERSION_VAL(major, minor, patch) ((major << 16) | (minor << 8) | (patch))

/**
 * Current IDF version, as an integer
 *
 * To be used in comparisons, such as BLYNKGO_VERSION >= BLYNKGO_VERSION_VAL(3, 0, 0)
 */
#define BEENEXT_VERSION  BEENEXT_VERSION_VAL( BLYNKGO_VERSION_MAJOR, \
                                              BLYNKGO_VERSION_MINOR, \
                                              BLYNKGO_VERSION_PATCH)

#define BEENEXT

/**********************************************/
#if defined(BEENEXT) || BLYNKGO_USE_BEENEXT

#include <Arduino.h>
#include "beenext_config.h"

#if BEENEXT_USE_BEEUART
#include "BeeUART.h"
#elif BEENEXT_USE_BEEUART_CRC16 
#include <HardwareSerial.h>
#if BEENEXT_USE_SOFTWARESERIAL && (CONFIG_IDF_TARGET_ESP32S3==0) 
#include "lib/SoftwareSerial/SoftwareSerial.h"
#endif
#elif BEENEXT_USE_BEEI2C
#include "BeeI2C.h"
#elif BEENEXT_USE_BEEMQTT
#include "BeeMQTT.h"
#endif


#if BEENEXT_USE_SOFTTIMER
#include "lib/BeeNeXT_SoftTimer/BeeNeXT_SoftTimer.h"
#endif

/******************************************************/
#define BEENEXT_DATA()          void BeeNeXT_onData()
#define BEENEXT_CONNECTED()     void BeeNeXT_onConnected()
#define BEENEXT_DISCONNECTED()  void BeeNeXT_onDisconnected()
#ifdef __cplusplus
extern "C" {
#endif
  void BeeNeXT_NoOpCbk();
  BEENEXT_DATA();
  BEENEXT_CONNECTED();
  BEENEXT_DISCONNECTED();
#ifdef __cplusplus
}
#endif
/******************************************************/


#define MCU_DATA      BEENEXT_DATA 
#define LCD_DATA      BEENEXT_DATA
#define LCD           BeeNeXT
#define MCU           BeeNeXT

#if BEENEXT_USE_BEEI2C
#define BeeI2C        BeeNeXT
#elif BEENEXT_USE_BEEUART
#define BeeUART       BeeNeXT
#endif

#define BEENEXT_CONNECTION_TIMEOUT      3000


#if BEENEXT_USE_BEEUART_CRC16
enum BeeNeXT_ReceiveState {
  BEENEXT_WAIT_FOR_PREHEADER,
  BEENEXT_WAIT_FOR_PREHEADER_CHECK,
  BEENEXT_WAIT_FOR_KEY_LENGTH,
  BEENEXT_WAIT_FOR_DATA_LENGTH,
  BEENEXT_WAIT_FOR_KEY,
  BEENEXT_WAIT_FOR_DATA,
  BEENEXT_WAIT_FOR_CHECKSUM
};
#endif

class BeeNeXT_Class {

public:

#if BEENEXT_USE_BEEUART_CRC16
  inline void begin(){
    this->end();
    #if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO)
      #if BEENEXT_USE_SOFTWARESERIAL && (CONFIG_IDF_TARGET_ESP32S3==0)
        this->begin(6,7);
      #else
        this->begin(&Serial);
      #endif
    #elif defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_MEGA2560)
        Serial2.begin(9600);    // Serial2 ของ Arduino MEGA ขา RX16, TX17
        this->begin(&Serial2);
    #elif defined(ESP8266)
      #if BEENEXT_USE_SOFTWARESERIAL && (CONFIG_IDF_TARGET_ESP32S3==0)
        this->begin(4,5);
      #else
        this->begin(&Serial);
      #endif
    #elif defined(ESP32)
      #if CONFIG_IDF_TARGET_ESP32S2
        Serial1.begin(9600, SERIAL_8N1, 18,17);
      #elif CONFIG_IDF_TARGET_ESP32C3
        Serial1.begin(9600, SERIAL_8N1, 18,19);
      #elif CONFIG_IDF_TARGET_ESP32C6

      #elif defined(BEENEXT_2_4) || defined(BEENEXT_2_4C) || defined(BEENEXT_2_8) || defined(BEENEXT_2_8C) || defined(BEENEXT_3_2) || defined(BEENEXT_3_2C) || defined(BEENEXT_3_5) || defined(BEENEXT_3_5C) || defined(BEENEXT_4_3) || defined(BEENEXT_4_3C) || defined(BEENEXT_4_3IPS) || defined(BEENEXT_5_0IPS) || defined(BEENEXT_7_0IPS)

      this->begin(&Serial);  // ให้เอา R หลังขา RX ออก และ short
      #else
        #if ARDUINO_USB_CDC_ON_BOOT
          #if ARDUINO_USB_MODE   // Hardware CDC mode
          //...
          #else  // !ARDUINO_USB_MODE -- Native USB Mode
          //...
          #endif
        #else   // !ARDUINO_USB_CDC_ON_BOOT -- Serial is used from UART0
          Serial2.begin(9600, SERIAL_8N1, 16,17); // Serial2 ของ ESP32 ให้ทำงานบน ขา RX16, TX17
          this->begin(&Serial2);
        #endif
      #endif
    #elif defined(__STM32F1__)
      Serial2.begin(9600);  // Serial2 ของ Arduino MEGA ขา PA3, PA2
      this->begin(&Serial2);
    #endif
  }

#if ARDUINO_USB_CDC_ON_BOOT
#if ARDUINO_USB_MODE   // Hardware CDC mode
  void begin(HWCDC *hw_serial);
#else  // !ARDUINO_USB_MODE -- Native USB Mode
  void begin(USBCDC *hw_serial);
#endif
#else   // !ARDUINO_USB_CDC_ON_BOOT -- Serial is used from UART0
  void begin(HardwareSerial *hw_serial);
#endif


#if BEENEXT_USE_SOFTWARESERIAL && (CONFIG_IDF_TARGET_ESP32S3==0)
  SoftwareSerial * _sw_serial=NULL;
  void begin(SoftwareSerial *sw_serial);
  void begin(unsigned long baud, uint8_t rx, uint8_t tx);
  inline void begin(uint8_t rx, uint8_t tx) { this->begin(9600,rx,tx); }
#endif
  void end();
#endif // #if BEENEXT_USE_BEEUART_CRC16

  void update();

  void enable(bool en);
  inline bool enable()                            { return _beenext_enable;               }

#if BEENEXT_USE_BEEUART_CRC16
  inline void heartbeat(bool en){
#if BEENEXT_USE_HEARTBEAT && BEENEXT_USE_SOFTTIMER
    _heartbeat_enable = !!en;
    if(_heartbeat_enable) {
      this->init_heartbeat();
    }else{
      this->stop_heartbeat();
    }
#endif
  }
  inline bool heartbeat() {
#if BEENEXT_USE_HEARTBEAT && BEENEXT_USE_SOFTTIMER
    return _heartbeat_enable;
#endif
    return false;
  }

  inline String key()                             { return _recv_KeyBuffer;               }
  
  inline String value()                           { return (char*)_recv_DataBuffer;       }  
  size_t value(uint8_t* value, uint16_t valueLength);


  inline String toString()                        { return this->value();                 }
  inline const char* c_str()                      { return (const char*)_recv_DataBuffer; }  

  template <typename T = int32_t>
  T toInt() {
    if (_recv_DataLength == sizeof(int8_t)) {
      int8_t n = *(int8_t*)_recv_DataBuffer;
      return static_cast<T>(n);
    } else if (_recv_DataLength == sizeof(int16_t)) {
      int16_t n = *(int16_t*)_recv_DataBuffer;
      return static_cast<T>(n);
    } else if (_recv_DataLength == sizeof(int32_t)) {
      int32_t n = *(int32_t*)_recv_DataBuffer;
      return static_cast<T>(n);
    } else if (_recv_DataLength == sizeof(int64_t)) {
      int64_t n = *(int64_t*)_recv_DataBuffer;
      return static_cast<T>(n);
    } else {
      return static_cast<T>(0); // Return 0 for unsupported data lengths
    }
  }

  template <typename T = float>
  T toFloat() {
    if (_recv_DataLength == sizeof(float)) {
      float n = *(float*)_recv_DataBuffer;
      return static_cast<T>(n);
    } else if (_recv_DataLength == sizeof(double)) {
      double n = *(double*)_recv_DataBuffer;
      return static_cast<T>(n);
    } else {
      return static_cast<T>(0.0); // Return 0.0 for unsupported data lengths
    }
  }

  inline double toDouble()  { return toFloat<double>();             }
  inline bool toBool()      { return (bool) this->toInt<int8_t>();  }


  void send(String key, uint8_t *data, uint16_t data_len);
  template <typename T>
  inline void send(String key, T data)            { send(key, (uint8_t*)&data, sizeof(data));         }

  inline void send(String key, String data)       { send(key, (uint8_t *)data.c_str(), data.length());}
  inline void send(String key, bool   value)      { send(key, (uint8_t) value);                       }

#if BEENEXT_USE_HEARTBEAT && BEENEXT_USE_SOFTTIMER
  inline bool isConnected()     { return _bee_connected;                                          }
  inline bool connected()       { return _bee_connected;                                          }
#else
  inline bool isConnected()     { return true;                                                    }
  inline bool connected()       { return true;                                                    }
#endif //#if BEENEXT_USE_HEARTBEAT && BEENEXT_USE_SOFTTIMER


  // don't call
#if BEENEXT_USE_HEARTBEAT && BEENEXT_USE_SOFTTIMER
  void   init_heartbeat();
  void   stop_heartbeat();
  void   set_heartbeat(uint32_t heartbeat_interval);
  void   set_heartbeat_checker();
  bool   _bee_connected=false;
  uint32_t  _millis_heartbeat;
  bool   _heartbeat_enable = true;
#endif

  inline void protocol_write(uint8_t *data, uint16_t data_len){
    if(_hw_serial != NULL)          _hw_serial->write(data, data_len);
    #if BEENEXT_USE_SOFTWARESERIAL && (CONFIG_IDF_TARGET_ESP32S3==0)
      else if(_sw_serial != NULL)     _sw_serial->write(data, data_len);
    #endif
  }
  inline void protocol_write(uint8_t data) { this->protocol_write(&data, 1); }
  inline void protocol_println()           { uint8_t data[2] = {'\r','\n'}; this->protocol_write(data, 2); }

  //------------------------------------------------------------------------- BeeI2C
  #elif BEENEXT_USE_BEEI2C   //#if BEENEXT_USE_BEEUART_CRC16
  inline void begin(void(*fn)(String key, String value)) {
    McuI2C_Master::init(fn);
    this->_is_i2c_master = true;
  }

  #if defined(ESP32)
  inline void begin(uint8_t sda, uint8_t scl, void(*fn)(String key, String value)) {
    McuI2C_Master::init(sda, scl, fn);
    this->_is_i2c_master = true;
  }
  #endif

  #if defined(ESP32)
  #if defined(BEENEXT_2_4) || defined(BEENEXT_2_4C) || defined(BEENEXT_3_2) || defined(BEENEXT_3_2C) || defined(BEENEXT_3_5)  || defined(BEENEXT_3_5C) || defined(BEENEXT_4_3) || defined(BEENEXT_4_3C) || defined(BEENEXT_4_3IPS) || defined(BEENEXT_5_0IPS)  || defined(BEENEXT_7_0IPS) || defined(BEENEXT_7_0MAX)
  inline void onData(void(*fn)(String key, String value)) {
    BeeI2C_Slave::init(fn);
  }
  #endif // #if defined(BEENEXT_3_2) || defined(BEENEXT_3_2C) || defined(BEENEXT_3_5)  || defined(BEENEXT_3_5C)

  inline void onData(uint8_t sda, uint8_t scl, void(*fn)(String key, String value)){
    BeeI2C_Slave::init(sda, scl, fn);
  }
  #endif// ESP32

  inline void print(String key, String value){
    if(this->_is_i2c_master) {
      McuI2C_Master::print(key, value);
    }
    #if defined(ESP32)
    else{
      BeeI2C_Slave::print(key, value);
    }
    #endif
  }

  inline void print(String key, float value, int decimalPlaces=2){
    this->print(key, String(value, decimalPlaces));
  }

  inline void print(String key, double value, int decimalPlaces=2){
    this->print(key, String(value, decimalPlaces));
  }

  inline void print(String key, int value){
    this->print(key, String(value));
  }
      // end of #elif BEENEXT_USE_BEEI2C
  //------------------------------------------------------------------------- BeeUART
  #elif BEENEXT_USE_BEEUART

  // ใช้ Serial หลัก เป็น BeeUART
  inline void begin(void(*fn)(String key, String value)) {
    beeuart::init(fn);
  }

  #if ARDUINO_USB_CDC_ON_BOOT
    #if ARDUINO_USB_MODE   // Hardware CDC mode
      // HWCDC * _hw_serial = NULL;
      inline void begin(HWCDC *hw_serial, void(*fn)(String key, String value)){
        beeuart::init(hw_serial, fn);
      }

    #else  // !ARDUINO_USB_MODE -- Native USB Mode
      // USBCDC * _hw_serial = NULL;
      inline void begin(USBCDC *hw_serial, void(*fn)(String key, String value)){
        beeuart::init(hw_serial, fn);
      }
    #endif
  #else   // !ARDUINO_USB_CDC_ON_BOOT -- Serial is used from UART0
    // HardwareSerial * _hw_serial=NULL;
    inline void begin(HardwareSerial *hw_serial, void(*fn)(String key, String value)){
      beeuart::init(hw_serial, fn);
    }
  #endif

  #if BEENEXT_USE_SOFTWARESERIAL && (CONFIG_IDF_TARGET_ESP32S3==0)
    inline void begin(int8_t rx, int8_t tx, void(*fn)(String key, String value)){
      beeuart::init(rx, tx, fn);
    }

    inline void begin(int8_t rx, int8_t tx, uint32_t baud, void(*fn)(String key, String value)){
      beeuart::init(rx, tx, baud, fn);
    }
  #endif

  #if defined(ESP32)
  //#if defined(BEENEXT_2_4) || defined(BEENEXT_2_4C) || defined(BEENEXT_2_8) || defined(BEENEXT_2_8C) || defined(BEENEXT_3_2) || defined(BEENEXT_3_2C) || defined(BEENEXT_4_3) || defined(BEENEXT_4_3C) || defined(BEENEXT_4_3IPS) || defined(BEENEXT_5_0IPS) || defined(BEENEXT_7_0IPS)
  inline void onData(void(*fn)(String key, String value)) {
    beeuart::init(fn);
  }
  #if ARDUINO_USB_CDC_ON_BOOT
  #else
    #if SOC_UART_NUM > 2
    inline void onData(uint8_t rx, uint8_t tx, void(*fn)(String key, String value)){
      Serial2.begin(9600, SERIAL_8N1, rx, tx);
      beeuart::init(&Serial2, fn);
    }
    inline void onData(uint8_t rx, uint8_t tx, uint32_t baud, void(*fn)(String key, String value)){
      Serial2.begin(baud, SERIAL_8N1, rx, tx);
      beeuart::init(&Serial2, fn);
    }
    #endif // #if SOC_UART_NUM > 2
  #endif
  #endif

  inline void print(String key, String value){
    beeuart::print(key, value);
  }

  inline void print(String key, float value, int decimalPlaces=2){
    this->print(key, String(value, decimalPlaces));
  }

  inline void print(String key, double value, int decimalPlaces=2){
    this->print(key, String(value, decimalPlaces));
  }

  inline void print(String key, int value){
    this->print(key, String(value));
  }

  //------------------------------------------------------------------------- BeeMQTT
  #elif BEENEXT_USE_BEEMQTT
  #if defined(BEENEXT_2_4) || defined(BEENEXT_2_4C) || defined(BEENEXT_2_8) || defined(BEENEXT_2_8C) || defined(BEENEXT_3_2) || defined(BEENEXT_3_2C) || defined(BEENEXT_3_5) || defined(BEENEXT_3_5C) || defined(BEENEXT_4_3) || defined(BEENEXT_4_3C) || defined(BEENEXT_4_3IPS) || defined(BEENEXT_5_0IPS) || defined(BEENEXT_7_0IPS)
  #else

  #if defined(ESP8266) || defined(ESP32)
    inline void client_id(String client_id) {
      BeeMQTT::client_id(client_id);
    }

    inline void begin(String ssid, String pass, String mqtt_host, uint16_t mqtt_port, String mqtt_user, String mqtt_pass, void(*fn)(String topic, String message))
    {
      BeeMQTT::init(ssid, pass, mqtt_host, mqtt_port, mqtt_user, mqtt_pass, fn);
    }

    inline void begin(String ssid, String pass, String mqtt_host, uint16_t mqtt_port, void(*fn)(String topic, String message))
    {
      BeeMQTT::init(ssid, pass, mqtt_host, mqtt_port, fn);
    }

    inline void begin(String mqtt_host, uint16_t mqtt_port, String mqtt_user, String mqtt_pass, void(*fn)(String topic, String message))
    {
      BeeMQTT::init(mqtt_host, mqtt_port, mqtt_user, mqtt_pass, fn);
    }

    inline void begin(String mqtt_host, uint16_t mqtt_port, void(*fn)(String topic, String message))
    {
      BeeMQTT::init(mqtt_host, mqtt_port, "", "", fn);
    }

    inline void begin(String mqtt_host, void(*fn)(String topic, String message))
    {
      BeeMQTT::init(mqtt_host, 1883, "", "", fn);
    }
    
    inline void subscribe(String topic, uint8_t qos=0){
      BeeMQTT::subscribe(topic, qos);
    }

    inline bool publish(String topic, String message, bool retained=false){
      return BeeMQTT::publish(topic, message, retained);
    }
    inline void publish(String topic, float value, int decimalPlaces=2){
      this->publish(topic, String(value, decimalPlaces));
    }
  
    inline void publish(String topic, double value, int decimalPlaces=2){
      this->publish(topic, String(value, decimalPlaces));
    }
  
    inline void publish(String topic, int value){
      this->publish(topic, String(value));
    }

    inline void print(String topic, String message, bool retained =false){
      this->publish(topic, message, retained);
    }

    inline void print(String key, float value, int decimalPlaces=2){
      this->print(key, String(value, decimalPlaces));
    }
  
    inline void print(String key, double value, int decimalPlaces=2){
      this->print(key, String(value, decimalPlaces));
    }
  
    inline void print(String key, int value){
      this->print(key, String(value));
    }

  #endif //  #if defined(ESP8266) || defined(ESP32)
  #endif // defined(BEENEXT_2_4) || defined(BEENEXT_2_4C) || defined(BEENEXT_2_8) || defined(BEENEXT_2_8C) || defined(BEENEXT_3_2) || defined(BEENEXT_3_2C) || defined(BEENEXT_4_3) || defined(BEENEXT_4_3C) || defined(BEENEXT_4_3IPS) || defined(BEENEXT_5_0IPS) || defined(BEENEXT_7_0IPS)
  #endif  // BEENEXT_USE_BEEMQTT

static bool   _beenext_enable;

private:
#if BEENEXT_USE_BEEUART_CRC16
  #if ARDUINO_USB_CDC_ON_BOOT
    #if ARDUINO_USB_MODE   // Hardware CDC mode
    HWCDC * _hw_serial = NULL;
    #else  // !ARDUINO_USB_MODE -- Native USB Mode
    USBCDC * _hw_serial = NULL;
    #endif
  #else   // !ARDUINO_USB_CDC_ON_BOOT -- Serial is used from UART0
    HardwareSerial * _hw_serial=NULL;
  #endif

  #if BEENEXT_USE_SOFTWARESERIAL && (CONFIG_IDF_TARGET_ESP32S3==0)
    bool  _is_swserial_alloced=false;
  #endif

  const char _preHeader[5] = "[BN]";
  char     _recv_PreHeader[5] = {0}; // สำหรับเก็บค่า pre-header ที่ส่งเข้ามา
  char     _recv_KeyBuffer[32];     // กำหนดขนาดสูงสุดของ key เป็น 32 (ความยาว key ที่รองรับได้มากที่สุด)
  uint8_t  _recv_DataBuffer[BEENEXT_BUFFER_MAX];   // กำหนดขนาดสูงสุดของ data เป็น BEENEXT_BUFFER_MAX (ความยาวข้อมูลที่รองรับได้มากที่สุด กำหนดใน beenext_config.h)
  uint8_t  _recv_KeyLength;
  uint16_t _recv_DataLength;


  #if BEENEXT_USE_HEARTBEAT && BEENEXT_USE_SOFTTIMER
    SoftTimer _timer_heartbeat;
    SoftTimer _timer_heartbeat_checker; 
  #endif //#if BEENEXT_USE_HEARTBEAT && BEENEXT_USE_SOFTTIMER

  uint16_t CRC16(uint16_t crc /*0 = init*/, uint8_t *data, size_t length);
  uint16_t CRC16(uint16_t crc /*0 = init*/, uint8_t data);

  void _updateChar(char ch);

#elif BEENEXT_USE_BEEI2C 
  bool _is_i2c_master=false;
#endif //#if BEENEXT_USE_BEEI2C
};

extern BeeNeXT_Class BeeNeXT;

#endif  // #if defined(BEENEXT) || BLYNKGO_USE_BEENEXT
#endif // __BEENEXT_H__