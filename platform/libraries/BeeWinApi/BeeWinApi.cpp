#include <windows.h>
#include "BeeWinApi.h"

bool BeeWinAPI::setWindowPos(String title,  int X, int Y, int cx, int cy){
  HWND hwnd = FindWindowA(NULL, title.c_str()); // NULL = title ใดก็ได้
  if (hwnd != NULL) {
    return  SetWindowPos(hwnd, NULL, X, Y, cx, cy, SWP_NOZORDER | SWP_SHOWWINDOW);
  }
  return false;
}
