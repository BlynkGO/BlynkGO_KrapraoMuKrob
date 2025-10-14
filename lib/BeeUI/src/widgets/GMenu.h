/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GMenu.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GMENU_H__
#define __GMENU_H__


#include "GObject.h"

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GMenu : public GObject {
  public:
    GMenu(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GMenu(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GMenu();

    virtual void  create();
    inline  void  create(GWidget& parent)                   { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                   { this->_par =  parent; this->create();               }

    /**
     * Create a menu page object
     * @param parent    pointer to menu object
     * @param title     pointer to text for title in header (NULL to not display title)
     * @return          pointer to the created menu page
     */
    obj_t * page_create(obj_t * parent = NULL, char const * const title = NULL);

    inline obj_t * page_create(GWidget& parent, char const * const title = NULL) {  return this->page_create(parent.obj, title);  }
    inline obj_t * page_create(GWidget* parent, char const * const title = NULL) {  return this->page_create(parent->obj, title); }


    /**
     * Create a menu cont object
     * @param parent    pointer to an object, it will be the parent of the new menu cont object
     * @return          pointer to the created menu cont
     */
    obj_t * cont_create(obj_t * parent = NULL);

    inline obj_t * cont_create(GWidget& parent)                                   {  return this->cont_create(parent.obj);  }
    inline obj_t * cont_create(GWidget* parent)                                   {  return this->cont_create(parent->obj); }

    /**
     * Create a menu section object
     * @param parent    pointer to an object, it will be the parent of the new menu section object
     * @return          pointer to the created menu section
     */
    obj_t * section_create(obj_t * parent = NULL);

    inline obj_t * section_create(GWidget& parent)                                {  return this->section_create(parent.obj);  }
    inline obj_t * section_create(GWidget* parent)                                {  return this->section_create(parent->obj); }

    /**
     * Create a menu separator object
     * @param parent    pointer to an object, it will be the parent of the new menu separator object
     * @return          pointer to the created menu separator
     */
    obj_t * separator_create(obj_t * parent = NULL);

    inline obj_t * separator_create(GWidget& parent)                              {  return this->separator_create(parent.obj);  }
    inline obj_t * separator_create(GWidget* parent)                              {  return this->separator_create(parent->obj); }

    /*=====================
    * Setter functions
    *====================*/
    /**
     * Set menu page to display in main
     * @param page      pointer to the menu page to set (NULL to clear main and clear menu history)
     */
    void page(obj_t * page);

    inline void page(GWidget *widget)                                             { this->page(widget->obj);    }
    inline void page(GWidget &widget)                                             { this->page(widget.obj);     }

    /**
     * Set menu page title
     * @param page      pointer to the menu page
     * @param title     pointer to text for title in header (NULL to not display title)
     */
    void page_title(obj_t * page, char const * const title);

    inline void page_title(GWidget *page, char const * const title)               { this->page_title(page->obj, title);    }
    inline void page_title(GWidget &page, char const * const title)               { this->page_title(page.obj, title);     }

    /**
     * Set menu page title with a static text. It will not be saved by the label so the 'text' variable
     * has to be 'alive' while the page exists.
     * @param page      pointer to the menu page
     * @param title     pointer to text for title in header (NULL to not display title)
     */
    void page_title_static(obj_t * page, char const * const title);

    inline void page_title_static(GWidget *page, char const * const title)        { this->page_title_static(page->obj, title);    }
    inline void page_title_static(GWidget &page, char const * const title)        { this->page_title_static(page.obj, title);     }

    /**
     * Set menu page to display in sidebar
     * @param page      pointer to the menu page to set (NULL to clear sidebar)
     */
    void sidebar_page(obj_t * page);

    inline void sidebar_page(GWidget *page)                                       { this->sidebar_page(page->obj);    }
    inline void sidebar_page(GWidget &page)                                       { this->sidebar_page(page.obj);     }

    /**
     * Set the how the header should behave and its position
     * @param mode      MENU_HEADER_TOP_FIXED/TOP_UNFIXED/BOTTOM_FIXED
     */
    void mode_header(menu_mode_header_t mode);

    /**
     * Set whether back button should appear at root
     * @param mode      MENU_ROOT_BACK_BUTTON_DISABLED/ENABLED
     */
    void mode_root_back_button(menu_mode_root_back_button_t mode);

    /**
     * Add menu to the menu item
     * @param obj       pointer to the obj
     * @param page      pointer to the page to load when obj is clicked
     */
    void load_page_event(obj_t * obj, obj_t * page);

    inline void load_page_event(GWidget *widget, GWidget &page)               { this->load_page_event(widget->obj, page.obj);   }
    inline void load_page_event(GWidget &widget, GWidget &page)               { this->load_page_event(widget.obj, page.obj);    }


    /*=====================
    * Getter functions
    *====================*/
    /**
    * Get a pointer to menu page that is currently displayed in main
    * @return           pointer to current page
    */
    obj_t * cur_main_page();

    /**
    * Get a pointer to menu page that is currently displayed in sidebar
    * @return           pointer to current page
    */
    obj_t * cur_sidebar_page();

    /**
    * Get a pointer to main header obj
    * @return           pointer to main header obj
    */
    obj_t * main_header();

    /**
    * Get a pointer to main header back btn obj
    * @return           pointer to main header back btn obj
    */
    obj_t * main_header_back_button();

    /**
    * Get a pointer to sidebar header obj
    * @return           pointer to sidebar header obj
    */
    obj_t * sidebar_header();

    /**
    * Get a pointer to sidebar header obj
    * @return           pointer to sidebar header back btn obj
    */
    obj_t * sidebar_header_back_button();

    /**
     * Check if an obj is a root back btn
     * @param obj       pointer to the back button
     * @return          true if it is a root back btn
     */
    bool back_button_is_root(obj_t * obj);

    /**
     * Clear menu history
     */
    void clear_history();

  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GMENU_H__
