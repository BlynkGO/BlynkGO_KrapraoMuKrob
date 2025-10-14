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
 */

#ifndef __BEENEXT_H__
#define __BEENEXT_H__

/** Major version number (X.x.x) */
#define BEENEXT_VERSION_MAJOR   3
/** Minor version number (x.X.x) */
#define BEENEXT_VERSION_MINOR   0
/** Patch version number (x.x.X) */
#define BEENEXT_VERSION_PATCH   5

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

#if BEENEXT_USE_SOFTWARESERIAL && (CONFIG_IDF_TARGET_ESP32S3==0) 
#include "lib/SoftwareSerial/SoftwareSerial.h"
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

#define BEENEXT_CONNECTION_TIMEOUT      3000

enum BeeNeXT_ReceiveState {
  BEENEXT_WAIT_FOR_PREHEADER,
  BEENEXT_WAIT_FOR_PREHEADER_CHECK,
  BEENEXT_WAIT_FOR_KEY_LENGTH,
  BEENEXT_WAIT_FOR_DATA_LENGTH,
  BEENEXT_WAIT_FOR_KEY,
  BEENEXT_WAIT_FOR_DATA,
  BEENEXT_WAIT_FOR_CHECKSUM
};

class BeeNeXT_Class {

public:

#if BEENEXT_USE_HARDWARESERIAL

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
      #elif defined(BEENEXT_1_28) || defined(BEENEXT_2_4) || defined(BEENEXT_2_4C) || defined(BEENEXT_2_8) || defined(BEENEXT_2_8C) || defined(BEENEXT_3_2) || defined(BEENEXT_3_2C) || defined(BEENEXT_4_3) || defined(BEENEXT_4_3C) || defined(BEENEXT_4_3IPS) || defined(BEENEXT_5_0IPS) || defined(BEENEXT_7_0IPS)
        this->begin(&Serial);  // ให้เอา R หลังขา RX ออก และ short
      #else
        Serial2.begin(9600, SERIAL_8N1, 16,17); // Serial2 ของ ESP32 ให้ทำงานบน ขา RX16, TX17
        this->begin(&Serial2);
      #endif
    #elif defined(__STM32F1__)
      Serial2.begin(9600);  // Serial2 ของ Arduino MEGA ขา PA3, PA2
      this->begin(&Serial2);
    #endif
  }

  void begin(HardwareSerial *hw_serial);
#if BEENEXT_USE_SOFTWARESERIAL && (CONFIG_IDF_TARGET_ESP32S3==0)
  SoftwareSerial * _sw_serial=NULL;
  void begin(SoftwareSerial *sw_serial);
  void begin(unsigned long baud, uint8_t rx, uint8_t tx);
  inline void begin(uint8_t rx, uint8_t tx) { this->begin(9600,rx,tx); }
#endif
  void end();
#endif //#if BEENEXT_USE_HARDWARESERIAL


  void update();

#if BEENEXT_USE_HARDWARESERIAL

  void enable(bool en);
  inline bool enable()                            { return _beenext_enable;               }
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

  static bool   _beenext_enable;

  inline void protocol_write(uint8_t *data, uint16_t data_len){
    if(_hw_serial != NULL)          _hw_serial->write(data, data_len);
#if BEENEXT_USE_SOFTWARESERIAL && (CONFIG_IDF_TARGET_ESP32S3==0)
    else if(_sw_serial != NULL)     _sw_serial->write(data, data_len);
#endif
  }
  inline void protocol_write(uint8_t data) { this->protocol_write(&data, 1); }
  inline void protocol_println()           { uint8_t data[2] = {'\r','\n'}; this->protocol_write(data, 2); }

private:
  HardwareSerial * _hw_serial=NULL;
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
#endif //#if BEENEXT_USE_HARDWARESERIAL

};

extern BeeNeXT_Class BeeNeXT;

#endif  // #if defined(BEENEXT) || BLYNKGO_USE_BEENEXT
#endif // __BEENEXT_H__