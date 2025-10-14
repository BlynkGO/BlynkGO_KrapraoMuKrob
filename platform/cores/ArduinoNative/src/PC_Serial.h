#ifndef __PC_ARDUINO_SERIAL_H__
#define __PC_ARDUINO_SERIAL_H__

#include "WString.h"
#include "stdio.h"
#include <string>
#include <locale>
#include <codecvt>
#include <stdarg.h>  // สำหรับ va_list, va_start, va_end, vsnprintf

// #define _SERIAL_MAX_LEN_        256

class PC_Serial {
  public:
    PC_Serial() {}

    inline void begin(int fake_baud)                      { }
    void print(int n);
    void print(uint32_t n);
    void print(long n);
    inline void print(unsigned long n)                    { print((uint32_t) n);            }
    inline void print(std::size_t n)                      { print((int)n);                  }
    void print(String str);
    void print(const char* str);
    void print(char* str);
    void print(float f, int32_t decimal=2);
    void print(double f, int32_t decimal=2);

    inline void println()                                 { std::printf("\n"); fflush(stdout);  }
    inline void println(int n)                            { print(n); println();            }
    inline void println(uint32_t n)                       { print(n); println();            }
    inline void println(long n)                           { print(n); println();            }
    inline void println(unsigned long n)                  { print(n); println();            }
    inline void println(std::size_t n)                    { print((int)n); println();       }
    inline void println(String str)                       { print(str); println();          }
    inline void println(const char* str)                  { print(str); println();          }
    inline void println(char* str)                        { print(str); println();          }
    inline void println(float f, int32_t decimal=2)       { print(f,decimal); println();    }
    inline void println(double f, int32_t decimal=2)      { print(f,decimal); println();    }

    size_t printf(const char *format, ...) {
        char loc_buf[64];
        char * temp = loc_buf;
        va_list arg;
        va_list copy;
        va_start(arg, format);
        va_copy(copy, arg);
        int len = vsnprintf(temp, sizeof(loc_buf), format, copy);
        va_end(copy);
        if(len < 0) {
            va_end(arg);
            return 0;
        }
        if(len >= (int)sizeof(loc_buf)){  // comparation of same sign type for the compiler
            temp = (char*) malloc(len+1);
            if(temp == NULL) {
                va_end(arg);
                return 0;
            }
            len = vsnprintf(temp, len+1, format, arg);
        }
        va_end(arg);
        len = std::printf("%s", temp);
        if(temp != loc_buf){
            free(temp);
        }
        return len;
    }
};

extern PC_Serial Serial;

#endif // __PC_ARDUINO_SERIAL_H__