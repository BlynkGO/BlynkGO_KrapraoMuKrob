#ifndef _TRIDENT_UNICODE_H__
#define _TRIDENT_UNICODE_H__

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>  // sprintf

/***************************************************************
 * 
 * TridentTD's UNICODE <---> UTF8 Converter (c library)
 *
 *  version 2.0 @13/12/2024
 * 
 ***************************************************************/
// for char
uint32_t      utf8_to_unicode(const char * utf8_char);
const char *  unicode_to_utf8(uint32_t unicode_codepoint );
uint32_t      unicode_to_utf8code(uint32_t unicode_codepoint);

// for string ดึง unicode codepoint ณ ตำแหน่ง letter_id (ไม่ใช่ byte_id)
uint32_t      UTF8_TO_UNICODE(const char* utf8_str, uint32_t letter_id);

// for string
wchar_t *     utf8_str_to_unicode_str(const char* utf8_str, wchar_t * unicode_str, uint32_t unicode_str_len);
char *        unicode_str_to_utf8_str(const wchar_t * unicode_str, char * utf8_str, uint32_t utf8_str_len);

uint32_t UnicodeStrLength(const char* utf8_str);          // จำนวนตัวอักษรตามจริง (ไม่ใช่ความยาว byte)
uint32_t Utf8StrLength(const wchar_t* unicode_str);       // ความยาว byte ของ utf8 string จาก จน.ตัวอักษรของ unicode string

// แปลง utf8 char ไปเป็น unicode codepoint
#ifndef UNICODE
#define UNICODE(utf8)     utf8_to_unicode(utf8)         // for char (utf8 char ไปเป็น unicode codepoint)
#endif

// แปลง unicode codepoint เป็นไป utf8 char
#ifndef UTF8
#define UTF8(unicode)     unicode_to_utf8(unicode)      // for char (unicode ไปเป็น utf8 char)
#endif

// แปลง unicode code เป็นไป utf8 code
#ifndef UTF8CODE
#define UTF8CODE(unicode) unicode_to_utf8code(unicode)  // for char (unicode ไปเป็น utf8 code uint32_t )
#endif

const char* UNICODE_HexString(const char* str);         // ดูรหัส unicode ของ string ที่ต้องการ เช่น "กขคงจฉ" -->   \u0E01\u0E02\u0E04\u0E07\u0E08\u0E09\u0E0A
const char* UTF8_HexString(const char* str);            // ดูรหัส utf8 ของ string ที่ต้องการ เช่น "กขคงจฉ" --> \xE0\xB8\x81\xE0\xB8\x82\xE0\xB8\x84\xE0\xB8\x87\xE0\xB8\x88\xE0\xB8\x89\xE0\xB8\x8A

#ifdef __cplusplus
}
#endif

// Example
//  char* my_text = "กข";
//  size_t unicode_len = UnicodeStrLength( my_text );  // จน.อักขระ ตามจริง ไม่ได้ ความยาว byte
//  for(int i=0; i < unicode_len; i++)
//    Serial.println( UTF8_TO_UNICODE(my_text, i), HEX);

//  หรือ
//  Serial.println( UNICODE_HexString(my_text));

//  Serial.println( UTF8(0x0E01) );         // ---> ก
//  Serial.println( UNICODE("ก"), HEX );    // ---> E01

#endif
