#ifndef WINTIME_H
#define WINTIME_H

int hour();
int minute();
int second();
int day();    // 1-31
int mon();    // 0-11
int month();  // 1-12
int year();   // ei. 2025
int wday();   // 0-6  from sunday
long timestamp();  // เพิ่มฟังก์ชัน timestamp

#endif // WINTIME_H
