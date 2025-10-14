/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GImageButton.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GIMAGEBUTTON_H__
#define __GIMAGEBUTTON_H__


#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GImageButton : public GObject {
  public:
    GImageButton(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GImageButton(GWidget* parent)                                  : GObject(parent)  {}

    GImageButton( const void *src, GWidget& parent=GScreen) : GObject(&parent)
    {  
      this->_img_btn_released = src;
    }

    GImageButton( const void *src_btn_released, 
                  const void *src_btn_pressed=NULL,
                  const void *src_toggle_released=NULL,
                  const void *src_toggle_pressed=NULL,
                  const void *src_btn_inactive=NULL, 
                  const void *src_toggle_inactive=NULL, 
                  GWidget& parent=GScreen) : GObject(&parent)
    {
      this->_img_btn_released     = src_btn_released;
      this->_img_btn_pressed      = src_btn_pressed;
      this->_img_toggle_released  = src_toggle_released;
      this->_img_toggle_pressed   = src_toggle_pressed;
      this->_img_btn_inactive     = src_btn_inactive;
      this->_img_toggle_inactive  = src_toggle_inactive;
    }

    GImageButton( const img_t &src, GWidget& parent=GScreen) : GObject(&parent)
    {
      this->_img_btn_released = &src;
    }

    GImageButton( const img_t &src, GWidget* parent) : GObject(parent)
    {
      this->_img_btn_released = &src;
    }

    GImageButton( const img_t &src_btn_released, 
                  const img_t &src_btn_pressed,
                  const img_t &src_toggle_released,
                  const img_t &src_toggle_pressed,
                  const img_t &src_btn_inactive, 
                  const img_t &src_toggle_inactive,
                  GWidget& parent=GScreen) : GObject(&parent)
    {
      this->_img_btn_released     = &src_btn_released;
      this->_img_btn_pressed      = &src_btn_pressed;
      this->_img_toggle_released  = &src_toggle_released;
      this->_img_toggle_pressed   = &src_toggle_pressed;
      this->_img_btn_inactive     = &src_btn_inactive;
      this->_img_toggle_inactive  = &src_toggle_inactive;
    }

    GImageButton( button_type_t button_type,         // BUTTON_PUSH or BUTTON_SWITCH
                  const img_t &src_btn_released, 
                  const img_t &src_btn_pressed,
                  GWidget& parent=GScreen) : GObject(&parent)
    {
      this->_btn_type        = button_type;
      switch(this->_btn_type){
        case BUTTON_PUSH:
          this->_img_btn_released   = &src_btn_released;    // ปล่อย
          this->_img_btn_pressed    = &src_btn_pressed;     // กด
          break;
        case BUTTON_SWITCH:
          this->_img_btn_released   = &src_btn_released;    // OFF
          this->_img_btn_pressed    = &src_btn_pressed;     // OFF กด  --> ใช้ภาพ ON
          this->_img_toggle_released = &src_btn_pressed;    // ON
          this->_img_toggle_pressed  = &src_btn_released;   // ON กด --> ใช้ภาพ OFF
          break;
      }
    }


    GImageButton( const img_t &src_btn_released, 
                  const img_t &src_btn_pressed,
                  GWidget& parent=GScreen) : GObject(&parent)
    {
      this->_img_btn_released   = &src_btn_released;
      this->_img_btn_pressed    = &src_btn_pressed;
    }

    GImageButton( button_type_t button_type, 
                  const img_t &src_btn_released, 
                  GWidget& parent=GScreen) : GObject(&parent)
    {
      this->_btn_type        = button_type;
      this->_img_btn_released   = &src_btn_released;
    }

    virtual ~GImageButton();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    GImageButton& operator =(const void * src_mid);
    GImageButton& operator =(const img_t & src_mid);

    /*  button_type_t : BUTTON_PUSH, BUTTON_SWITCH */
    void    button_type(button_type_t type, const img_t *src_btn_released=NULL, const img_t *src_btn_pressed=NULL);
    inline void button_type(button_type_t type, const img_t &src_btn_released, const img_t &src_btn_pressed) {
      this->button_type(type, &src_btn_released, &src_btn_pressed);
    }
    button_type_t button_type();
    
    inline bool isON()                                  { return this->checked();   }
    inline bool isOFF()                                 { return !this->checked() ; }
    inline void ON()                                    { this->checked(true);  this->event_send(EVENT_VALUE_CHANGED);   }
    inline void OFF()                                   { this->checked(false); this->event_send(EVENT_VALUE_CHANGED);   }
    inline void on()                                    { this->checked(true);  }
    inline void off()                                   { this->checked(false); }
    
    /*=====================
    * Setter functions
    *====================*/

    /**
     * Set images for a state of the image button
     * @param state         for which state set the new image
     * @param src_left      pointer to an image source for the left side of the button (a C array or path to
     * a file)
     * @param src_mid       pointer to an image source for the middle of the button (ideally 1px wide) (a C
     * array or path to a file)
     * @param src_right     pointer to an image source for the right side of the button (a C array or path
     * to a file)
     */
    void src(imagebutton_state_t state, const void * src_left,
                                        const void * src_mid,
                                        const void * src_right);
    
    inline void src(imagebutton_state_t state, const void * src_mid)  { this->src(state, NULL, src_mid, NULL);  }
    inline void src(imagebutton_state_t state, const img_t& src_mid)  { this->src(state, NULL, &src_mid, NULL); }
    inline void src(const void * src_mid_released, const void * src_mid_pressed=NULL)  {
      this->src(IMAGEBUTTON_STATE_RELEASED, src_mid_released );
      this->src(IMAGEBUTTON_STATE_PRESSED, src_mid_pressed);
    }

    inline void src(const img_t&  src_mid_released,const img_t&  src_mid_pressed)  {
      this->src(IMAGEBUTTON_STATE_RELEASED, &src_mid_released );
      this->src(IMAGEBUTTON_STATE_PRESSED,  &src_mid_pressed);
    }

    inline void src(const img_t&  src_mid_released)  {
      this->src(IMAGEBUTTON_STATE_RELEASED, &src_mid_released );
    }


    /**
     * Use this function instead of `lv_obj_add/remove_state` to set a state manually
     * @param state         the new state
     */
    void state(imagebutton_state_t state);

    /*=====================
    * Getter functions
    *====================*/

    /**
     * Get the left image in a given state
     * @param state         the state where to get the image (from `button_state_t`) `
     * @return              pointer to the left image source (a C array or path to a file)
     */
    const void * src_left(imagebutton_state_t state);

    /**
     * Get the middle image in a given state
     * @param state         the state where to get the image (from `button_state_t`) `
     * @return              pointer to the middle image source (a C array or path to a file)
     */
    const void * src_middle(imagebutton_state_t state);

    /**
     * Get the right image in a given state
     * @param state         the state where to get the image (from `button_state_t`) `
     * @return              pointer to the left image source (a C array or path to a file)
     */
    const void * src_right(imagebutton_state_t state);

  private:
    button_type_t _btn_type = BUTTON_PUSH;
    const void * _img_btn_released    = NULL;
    const void * _img_btn_pressed     = NULL;
    const void * _img_toggle_released = NULL;
    const void * _img_toggle_pressed  = NULL;
    const void * _img_btn_inactive    = NULL;
    const void * _img_toggle_inactive = NULL;
};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GIMAGEBUTTON_H__
