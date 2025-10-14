#ifndef SYSTEM_SILENTLY_H
#define SYSTEM_SILENTLY_H

#include <string>

// รันคำสั่งแบบไม่โชว์หน้าต่าง และ return stdout
std::string system_silently(const std::string& cmd);

#endif // SYSTEM_SILENTLY_H
