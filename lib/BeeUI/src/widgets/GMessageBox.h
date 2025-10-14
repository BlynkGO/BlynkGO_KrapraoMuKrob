/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GMessageBox.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
 *   สร้างโดย BlynkGO
 *   
 *   2.ไม่อนุญาต ให้แจกจ่าย สำเนา หรือแก้ไข โดยไม่ได้รับอนุญาต 
 *   
 *   3.สำหรับผู้ได้รับ ลิขสิทธิ์ สามารถนำไปใช้สร้าง firmware/rom 
 *   สำหรับ บอร์ด ESP32 ที่ระบุเท่านั้น เพื่อใช้ทางการค้าต่างๆได้
 *   โดยห้ามแจกจ่าย จำหน่าย ดัดแปลง แก้ไขใดๆ ในตัว source ไลบรารี่ออกไป
 *
 *   4.หากมีการนำไปใช้คอมไพล์ถือว่าได้ยอมรับ ตามเงื่อนไขลิขสิทธิ์ดังกล่าว
 *   เป็นที่เรียบร้อยแล้ว
 * 
 * Version 5.0
 * 
 *********************************************************************************
 */

#ifndef __GMESSAGEBOX_H__
#define __GMESSAGEBOX_H__


#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------
extern style_t style_cir_btn;
extern style_t style_cir_btn_pressed;

class GMessageBox : public GObject {
  public:
    GMessageBox(GWidget& parent)                            : GObject(&parent) {}
    GMessageBox(GWidget* parent=NULL)                       : GObject(parent)  {}
    virtual ~GMessageBox();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }


    /**
     * Add title to the message box. It also creates a header for the title.
     * @param title         the text of the tile
     * @return              the created title label
     */
    obj_t * title(String title);

    void title_center(bool en);

    /**
     * Add a button to the header of to the message box. It also creates a header.
     * @param icon          the icon of the button
     * @return              the created button
     */
    obj_t * header_button(const void * icon);

    obj_t * header_button(const img_t & icon);

    // obj_t * header_button(String text);

    /**
     * Add a text to the content area of message box. Multiply texts will be created below each other.
     * @param title         the text of the content area of message box
     * @return              the created button
     */
    obj_t * text(String text);

    inline obj_t * message(String text)       { return this->text(text);    }

    /**
     * Add a button to the footer of to the message box. It also creates a footer.
     * @param text          the text of the button
     * @return              the created button
     */
    obj_t * footer_button(String text);

    /**
     * Add a close button to the message box. It also create a header.
     * @return              the created close button
     */
    obj_t * close_button(bool en = true);

    /**
     * Get the header widget
     * @return              the header, or NULL if not exists
     */
    obj_t * header();

    inline obj_t * titlebar()          { return this->header();      }

    /**
     * Get the footer widget
     * @return              the footer, or NULL if not exists
     */
    obj_t * footer();

    /**
     * Get the content widget
     * @return              the content, or NULL if not exists
     */
    obj_t * content();

    inline obj_t * body()               { return this->content();     }

    /**
     * Get the title label
     * @return              the title, or NULL if not exists
     */
    obj_t * title();

    /**
     * Close a message box
     */
    void close();

    /**
     * Close a message box in the next call of the message box
     */
    void close_async();


    std::unique_ptr<GRect> _u_parent;
    // GObject _parent;

    obj_t* _close_btn=NULL;
  private:
    

};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GMESSAGEBOX_H__
