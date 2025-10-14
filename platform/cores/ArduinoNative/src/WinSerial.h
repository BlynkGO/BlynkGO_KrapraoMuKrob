#ifndef __PC_WINSERIAL_H__
#define __PC_WINSERIAL_H__

// "-lsetupapi" ต้อง link ด้วย
#include <Arduino.h>  // สำหรับ String, millis()
#include "Print.h"

#ifdef _WIN32

#include <thread>
#include <mutex>
#include <vector>

class WinSerial : public Print {
public:
    WinSerial() {}
    WinSerial(String com_port) : _com_port(com_port) {}
    ~WinSerial();

    bool begin(uint32_t baud);
    void end();

    void ComPort(String com_port);
    inline String ComPort() { return this->_com_port; }
    inline uint32_t baud() { return this->_baud; }

    uint32_t available();
    char read();
    String readStringUntil(char terminator);
    size_t readBytes(uint8_t* buffer, size_t length);
    void setTimeout(uint32_t timeout) { if (timeout > 0) _timeout = timeout; }

    inline size_t write(uint8_t c) { return this->write((char)c); }
    inline size_t write(char c) { return this->_winserial_write(c); }
    size_t write(const char* str);

    static std::vector<String> listPorts();

private:
    static constexpr size_t MAX_BUFFER_SIZE = 4096; // ขนาด buffer สูงสุด
    bool _is_inited = false;
    String _com_port;
    uint32_t _baud = 9600;
    uint32_t _timeout = 1000; // Timeout สำหรับ readStringUntil
    std::vector<uint8_t> _serial_buffer; // FIFO buffer (binary-safe)
    std::thread _thread;
    std::mutex _mutex;
    int32_t _winserial_read();
    size_t _winserial_write(char c);
    void* _hSerial = nullptr; // Handle ของ COM port

    void push_byte(uint8_t b); // เพิ่ม byte ลง buffer แบบ FIFO
};

#endif // _WIN32
#endif // __PC_WINSERIAL_H__
