#ifndef __PC_MACSERIAL_H__
#define __PC_MACSERIAL_H__

#include <Arduino.h>
#include "Print.h"

#if defined(__APPLE__) || defined(__linux__)
#include <thread>
#include <mutex>
#include <vector>
#include <string>

class MacSerial : public Print {
  public:
    MacSerial() {}
    MacSerial(String dev_path) : _dev_path(dev_path) {}
    ~MacSerial();

    bool begin(uint32_t baud);
    void end();

    void DevPath(String dev_path);
    inline String DevPath() { return _dev_path; }
    inline uint32_t baud() { return _baud; }

    uint32_t available();
    char read();
    String readStringUntil(char terminator);
    size_t readBytes(uint8_t* buffer, size_t length);
    void setTimeout(uint32_t timeout) { if(timeout>0) _timeout=timeout; }

    inline size_t write(uint8_t c) { return this->write((char)c); }
    inline size_t write(char c) { return this->_macserial_write(c); }
    size_t write(const char* str);

    static std::vector<String> listPorts();

  private:
    static constexpr size_t MAX_BUFFER_SIZE = 4096;
    bool _is_inited = false;
    String _dev_path;
    uint32_t _baud = 9600;
    uint32_t _timeout = 1000;
    std::vector<uint8_t> _serial_buffer;
    std::thread _thread;
    std::mutex _mutex;
    int _fd = -1;
    void push_byte(uint8_t b);
    int _macserial_read();
    size_t _macserial_write(char c);
};

#endif // macOS or Linux
#endif // __PC_MACSERIAL_H__
