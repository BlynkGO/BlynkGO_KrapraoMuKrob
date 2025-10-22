#pragma once
#include <functional>
#include <Arduino.h>  // สำหรับ String

class BeeExec {
public:
    // รัน command พร้อม callback
    static void start(const String& command, std::function<void(const String&)> cb);

    // รัน command แบบไม่มี callback
    static void start(const String& command);

    // ตรวจสอบและเรียก callback จาก queue
    static void update();

    // ยกเลิก process ทั้งหมด
    static void cleanup();
};
