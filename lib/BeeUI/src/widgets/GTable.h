/*
 *********************************************************************************
 * ลิขลิทธิ์ (Commercial License)
 * 
 *   1. โคดไฟล์ GTable.h นี้เป็นไลบรารี่ลิขลิทธิ์ 
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

#ifndef __GTABLE_H__
#define __GTABLE_H__


#include "GObject.h"
#include <vector>     // std::vector
#include <algorithm>  // std::find  , std::remove_if

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

struct table_cell_dsc_t{
  int32_t row;
  int32_t col;
  table_cell_dsc_t() : row(0), col(0), style(nullptr), is_local(0) {}
  table_cell_dsc_t(int32_t r, int32_t c) : row(r), col(c), style(nullptr), is_local(0)  {}

  const style_t *style = nullptr;
  // uint32_t is_local : 1;
  uint8_t is_local;

  // ฟังก์ชันเปรียบเทียบสำหรับการเรียงลำดับ
  bool operator<(const table_cell_dsc_t& other) const {
    return (row < other.row) || (row == other.row && col < other.col);
  }
};

class GFLOAT {
  public:
    GFLOAT(float f_num, uint8_t dec=2) : f(f_num), decimal(dec) {}
    float   f;
    uint8_t decimal;
};

class GTable : public GObject {
  public:
    GTable(GWidget& parent=GScreen)                          : GObject(&parent) {}
    GTable(GWidget* parent)                                  : GObject(parent)  {}
    virtual ~GTable();

    virtual void  create();
    inline  void  create(GWidget& parent)                       { this->_par = &parent; this->create();               }
    inline  void  create(GWidget* parent)                       { this->_par =  parent; this->create();               }



    inline void   cells(uint32_t row_num, uint32_t col_num)     { this->row_count(row_num); this->column_count(col_num);  }
    inline void   rows(uint32_t num)                            { this->row_count(num);                               }
    inline uint32_t rows()                                      { return this->row_count();                           }
    inline void   columns(uint16_t num)                         { this->column_count(num);                            }
    inline uint32_t columns()                                   { return this->column_count();                        }

    inline String cell_str(uint32_t r, uint32_t c)              { return this->cell_value(r,c);                       }
    inline String cell_str(table_cell_dsc_t cell)               { return this->cell_value(cell.row, cell.col);        }
    table_cell_dsc_t  selected_cell();

    inline uint32_t draw_row()                                  { return GObject::draw_id1();                         }
    inline uint32_t draw_col()                                  { return GObject::draw_id2();                         }
    inline table_cell_dsc_t draw_cell()                         { return table_cell_dsc_t(draw_row(), draw_col());    }

    bool cell_checked(uint32_t row, uint32_t col);
    void cell_checked(uint32_t row, uint32_t col, bool enable);

    inline bool cell_checked(table_cell_dsc_t cell)             { return this->cell_checked(cell.row, cell.col);      }
    inline void cell_checked(table_cell_dsc_t cell,bool enable) { this->cell_checked(cell.row, cell.col, enable);     }

    inline bool is_cell_checked(uint32_t row, uint32_t col)     { return this->cell_checked(row, col);                }
    inline bool is_cell_checked(table_cell_dsc_t cell)          { return this->cell_checked(cell.row, cell.col);      }

    inline bool isON(table_cell_dsc_t cell)                     { return this->is_cell_checked(cell);                 }
    inline bool isOFF(table_cell_dsc_t cell)                    { return !this->isON(cell);                           }

    inline void merge_cell_right(uint32_t row, uint32_t col, bool enable)  { 
      (enable) ?  this->add_cell_ctrl  ( row, col, TABLE_CELL_CTRL_MERGE_RIGHT) :
                  this->clear_cell_ctrl( row, col, TABLE_CELL_CTRL_MERGE_RIGHT) ;
    }

    inline bool merge_cell_right(uint32_t row, uint32_t col)    { return this->has_cell_ctrl( row, col, TABLE_CELL_CTRL_MERGE_RIGHT); }

    bool is_cell_merged(uint32_t row, uint32_t col, uint32_t* start_merged_col=NULL, uint32_t* end_merged_col=NULL);

    inline void clear_all_style()                               { this->table_cell_dsc_list.clear(); this->event_send(EVENT_STYLE_CHANGED); this->invalidate(); }

    event_handler_t fn_oncellclicked = NULL;
    inline void onCellClicked(event_handler_t fn)               { if(!this->isCreated()) this->create();  fn_oncellclicked = fn;  }

    /*=====================
    * Setter functions
    *====================*/

    /**
     * Set the value of a cell.
     * @param row           id of the row [0 .. row_cnt -1]
     * @param col           id of the column [0 .. col_cnt -1]
     * @param txt           text to display in the cell. It will be copied and saved so this variable is not required after this function call.
     * @note                New roes/columns are added automatically if required
     */
    void cell_value(uint32_t row, uint32_t col, const char * txt);

    inline void cell_value(uint32_t row, uint32_t col, String txt)    { this->cell_value( row, col, txt.c_str()); }

    // /**
    //  * Set the value of a cell.  Memory will be allocated to store the text by the table.
    //  * @param row           id of the row [0 .. row_cnt -1]
    //  * @param col           id of the column [0 .. col_cnt -1]
    //  * @param fmt           `printf`-like format
    //  * @note                New roes/columns are added automatically if required
    //  */
    // void cell_value_fmt(uint32_t row, uint32_t col, const char * fmt, ...) LV_FORMAT_ATTRIBUTE(4, 5);

    /**
     * Set the number of rows
     * @param row_cnt       number of rows
     */
    void row_count(uint32_t row_cnt);

    /**
     * Set the number of columns
     * @param col_cnt   number of columns.
     */
    void column_count(uint32_t col_cnt);

    /**
     * Set the width of a column
     * @param col_id    id of the column [0 .. LV_TABLE_COL_MAX -1]
     * @param w         width of the column
     */
    void column_width(uint32_t col_id, int32_t w);

    /**
     * Add control bits to the cell.
     * @param row       id of the row [0 .. row_cnt -1]
     * @param col       id of the column [0 .. col_cnt -1]
     * @param ctrl      OR-ed values from ::table_cell_ctrl_t
     */
    void set_cell_ctrl(uint32_t row, uint32_t col, table_cell_ctrl_t ctrl);

    inline void add_cell_ctrl(uint32_t row, uint32_t col, table_cell_ctrl_t ctrl)
    {
      this->set_cell_ctrl(row, col, ctrl);
    }

    /**
     * Clear control bits of the cell.
     * @param row       id of the row [0 .. row_cnt -1]
     * @param col       id of the column [0 .. col_cnt -1]
     * @param ctrl      OR-ed values from ::table_cell_ctrl_t
     */
    void clear_cell_ctrl(uint32_t row, uint32_t col, table_cell_ctrl_t ctrl);

    /**
     * Add custom user data to the cell.
     * @param row       id of the row [0 .. row_cnt -1]
     * @param col       id of the column [0 .. col_cnt -1]
     * @param user_data pointer to the new user_data.
     *                  Should be allocated by `lv_malloc`,
     *                  and it will be freed automatically when the table is deleted or
     *                  when the cell is dropped due to lower row or column count.
     */
    void cell_user_data(uint16_t row, uint16_t col, void * user_data);

    /*=====================
    * Getter functions
    *====================*/

    /**
     * Get the value of a cell.
     * @param row       id of the row [0 .. row_cnt -1]
     * @param col       id of the column [0 .. col_cnt -1]
     * @return          text in the cell
     */
    const char * cell_value(uint32_t row, uint32_t col);

    /**
     * Get the number of rows.
     * @return          number of rows.
     */
    uint32_t row_count();

    /**
     * Get the number of columns.
     * @return          number of columns.
     */
    uint32_t column_count();

    /**
     * Get the width of a column
     * @param col       id of the column [0 .. LV_TABLE_COL_MAX -1]
     * @return          width of the column
     */
    int32_t get_column_width(uint32_t col);

    /**
     * Get whether a cell has the control bits
     * @param row       id of the row [0 .. row_cnt -1]
     * @param col       id of the column [0 .. col_cnt -1]
     * @param ctrl      OR-ed values from ::table_cell_ctrl_t
     * @return          true: all control bits are set; false: not all control bits are set
     */
    bool has_cell_ctrl(uint32_t row, uint32_t col, table_cell_ctrl_t ctrl);

    /**
     * Get the selected cell (pressed and or focused)
     * @param row       pointer to variable to store the selected row (TABLE_CELL_NONE: if no cell selected)
     * @param col       pointer to variable to store the selected column  (TABLE_CELL_NONE: if no cell selected)
     */
    void selected_cell(uint32_t * row, uint32_t * col);

    /**
     * Get custom user data to the cell.
     * @param row       id of the row [0 .. row_cnt -1]
     * @param col       id of the column [0 .. col_cnt -1]
     */
    void * cell_user_data(uint16_t row, uint16_t col);

    /*=====================
    * BlynkGO functions
    *====================*/
    /* BlynkGO */
    /**
     * Set the alignment of the text in the specified row and/or column.
     * This function adjusts the text alignment for all cells in the specified row 
     * and/or column based on the provided parameters.
     *
     * @param row       The ID of the row to set the alignment for, ranging from [0 .. row_cnt - 1].
     *                  If row = -1, the alignment will be applied to all cells in the specified column.
     * @param col       The ID of the column to set the alignment for, ranging from [0 .. col_cnt - 1].
     *                  If col = -1, the alignment will be applied to all cells in the specified row.
     * @param align     The text alignment to be applied, specified as a value of type text_align_t.
     */
    void cell_text_align(int32_t row, int32_t col, text_align_t align);

    void cell_text_offset(int32_t row, int32_t col, int32_t offset_x, int32_t offset_y);

    inline void cell_text_align( int32_t row, int32_t col, text_align_t align, int32_t offset_x, int32_t offset_y) {
      this->cell_text_align(row, col, align);
      this->cell_text_offset(row, col, offset_x, offset_y);
    }

    void cell_font(int32_t row, int32_t col, const font_t& font);

    void cell_font_color(int32_t row, int32_t col, color_t font);

    void cell_text_line_space(int32_t row, int32_t col, int32_t text_line_space);

    void cell_text_letter_space(int32_t row, int32_t col, int32_t text_letter_space);

    void cell_bg_color(int32_t row, int32_t col, color_t color);

    void cell_icon_src(int32_t row, int32_t col, const void* src);

    void cell_icon_offset(int32_t row, int32_t col, int32_t icon_offset_x, int32_t icon_offset_y);

    inline void cell_icon_src(int32_t row, int32_t col, const void* src, int32_t icon_offset_x, int32_t icon_offset_y){
      this->cell_icon_src(row, col, src);
      this->cell_icon_offset(row, col, icon_offset_x, icon_offset_y);
    }

    void cell_decimal(int32_t row, int32_t col, uint8_t decimal);

    void cell_clickable(int32_t row, int32_t col, bool en);


    void row_height(int32_t row, int32_t height);

    inline void row_height(int32_t height)                        { this->row_height(-1, height); }
    inline void column_width(int32_t width)                       { for(uint32_t c=0; c< this->columns(); c++) this->column_width(c, width); }

    bool cell_get_prop(int32_t row, int32_t col, style_prop_t prop, style_value_t * style_value);

    text_align_t  cell_text_align(int32_t row, int32_t col);
    int32_t       cell_text_offset_x(int32_t row, int32_t col);
    int32_t       cell_text_offset_y(int32_t row, int32_t col);
    const font_t* cell_font(int32_t row, int32_t col);
    color_t       cell_font_color(int32_t row, int32_t col);
    int32_t       cell_text_line_space(int32_t row, int32_t col);
    int32_t       cell_text_letter_space(int32_t row, int32_t col);
    color_t       cell_bg_color(int32_t row, int32_t col);
    const void*   cell_icon_src(int32_t row, int32_t col);
    int32_t       cell_icon_offset_x(int32_t row, int32_t col);
    int32_t       cell_icon_offset_y(int32_t row, int32_t col);
    bool          cell_clickable(int32_t row, int32_t col);
    uint8_t       cell_decimal(int32_t row, int32_t col);
    
    int32_t       get_row_height(int32_t row);


    /* BlynkGO */
    /* ดึงค่า cell_label_dsc จาก vector หากไม่มีให้เพิ่มใหม่ พร้อมมีการ sort ตาม r,c */
    table_cell_dsc_t* _get_table_cell_dsc_from_list(int32_t r, int32_t c) {
      // ค้นหา cell ที่มี row และ col ตรงกัน
      auto it = std::find_if(this->table_cell_dsc_list.begin(), this->table_cell_dsc_list.end(),
                             [r, c](const table_cell_dsc_t& cell) { return cell.row == r && cell.col == c; });

      if (it != this->table_cell_dsc_list.end()) {
        // ถ้าพบ cell ที่มี row และ col ตรงกัน
        // Serial.printf("[f1] found (%d,%d)\n", r, c);
        return &(*it);
      } else {
        // Serial.printf("[f2] not found (%d,%d)\n", r, c);    
        this->table_cell_dsc_list.emplace_back(r, c);
    
        std::sort(this->table_cell_dsc_list.begin(), this->table_cell_dsc_list.end(),
                      [](const table_cell_dsc_t& a, const table_cell_dsc_t& b) {
                        // กรณีเมื่อ row หรือ col เท่ากับ -1
                        if (a.row == -1 && b.row != -1) return true; // a.row = -1 ให้อยู่ก่อน
                        if (b.row == -1 && a.row != -1) return false; // b.row = -1 ให้อยู่ก่อน

                        if (a.row == -1 && b.row == -1) {
                          // ถ้า row เป็น -1 ให้พิจารณาตาม col
                          return a.col < b.col; 
                        }

                        // ถ้า row ทั้งคู่ไม่ใช่ -1 ให้เรียงตาม row ก่อน
                        if (a.row != b.row) return a.row < b.row;
                        
                        // ถ้า row เหมือนกันให้เรียงตาม col
                        return a.col < b.col;
                      });
                                            
        // Serial.println("[Debug] Table Cells:");
        // for (const auto& cell : this->table_cell_dsc_list) {
        //   Serial.printf("   Cell: (%d, %d)\n", cell.row, cell.col);
        // }

                      
        // ค้นหา cell ใหม่ในตำแหน่งใหม่หลังจากการเรียงลำดับ
        auto sorted_it = std::find_if(this->table_cell_dsc_list.begin(), this->table_cell_dsc_list.end(),
                                      [r, c](const table_cell_dsc_t& cell) { return cell.row == r && cell.col == c; });
    
        // เพิ่มการตรวจสอบ style
        sorted_it->style = (lv_style_t*)lv_malloc(sizeof(lv_style_t));
        if (sorted_it->style != NULL) {
          lv_style_init((lv_style_t*)sorted_it->style);
          sorted_it->is_local = 1;
        }
        // คืนค่า pointer ของ cell ใหม่ที่ผ่านการเรียงลำดับแล้ว
        return &(*sorted_it);
      }
    }
  
    /*=====================
    * Cell SubClass Helper
    *====================*/
    friend class GTableCellBlock;
    class GTableCellBlock{
      public:
        GTableCellBlock(GTable&table, int32_t r, int32_t c)  : _table(table), _r(r), _c(c) {}
        GTableCellBlock(GTable&table, table_cell_dsc_t cell) : _table(table), _r(cell.row), _c(cell.col) {}

        /* กำหนดค่า ให้ cell */
        void operator=(String data)       { _table.cell_value(_r,_c, data);                                                   }
        void operator=(const char* cstr)  { _table.cell_value(_r,_c, cstr);                                                   }
        void operator=(int num)           { _table.cell_value(_r,_c, String(num));                                            }
        void operator=(double num)        { _table.cell_value(_r,_c, String((double) num, (unsigned int) _table.cell_decimal(_r, _c))); }
        void operator=(GFLOAT float_num)  { _table.cell_value(_r,_c, String(float_num.f , (unsigned int) float_num.decimal)); }

        /* คืนค่า ของ cell */
        inline float toFloat()            { return this->toString().toFloat();      }
        inline int   toInt()              { return this->toString().toInt();        }
        inline double toDouble()          { return this->toString().toDouble();     }
        inline const char* c_str()        { return _table.cell_value(_r,_c);        }
        inline String toString()          { return String(_table.cell_value(_r,_c));}

        inline void align(text_align_t text_align, int32_t ofs_x=0, int32_t ofs_y=0)  { _table.cell_text_align( _r, _c, text_align, ofs_x, ofs_y );             }
        inline void text_offset(int32_t ofs_x=0, int32_t ofs_y=0)                     { _table.cell_text_offset( _r, _c, ofs_x, ofs_y );                        }
        inline void text_color(color_t color)                                         { _table.cell_font_color(_r, _c, color);                                  }
        inline void font_color(color_t color)                                         { this->text_color(color);                                                }
        inline void font(const font_t&font)                                           { _table.cell_font( _r, _c, font);                                        }
        inline void font(const font_t&font, color_t color)                            { _table.cell_font(_r, _c, font); _table.cell_font_color(_r, _c, color);  }
        inline void letter_space(int32_t value)                                       { _table.cell_text_letter_space( _r, _c, value);                          }
        inline void line_space(int32_t value)                                         { _table.cell_text_line_space( _r, _c, value);                            }
        inline void color(color_t color)                                              { _table.cell_bg_color( _r, _c, color);                                   }
        inline void icon_src(const void* src)                                         { _table.cell_icon_src( _r, _c, src);                                     }
        inline void icon_src(const void* src, int32_t ofs_x, int32_t ofs_y)           { _table.cell_icon_src( _r, _c, src, ofs_x, ofs_y);                       }
        inline void icon_src(const img_t& src)                                        { _table.cell_icon_src( _r, _c, &src);                                    }
        inline void icon_src(const img_t& src, int32_t ofs_x, int32_t ofs_y)          { _table.cell_icon_src( _r, _c, &src, ofs_x, ofs_y);                      }
        inline void icon_offset(int32_t ofs_x, int32_t ofs_y)                         { _table.cell_icon_offset( _r, _c, ofs_x, ofs_y);                         }
        inline void decimal(uint8_t decimal)                                          { _table.cell_decimal( _r, _c, decimal);                                  }
        inline void clickable(bool en)                                                { _table.cell_clickable( _r, _c, en);                                     }
        inline void user_data(void * data)                                            { _table.cell_user_data( _r, _c, data);                                   }

        inline text_align_t align()                                                   { return _table.cell_text_align( _r, _c);                                 }
        inline int32_t text_offset_x()                                                { return _table.cell_text_offset_x( _r, _c);                              }
        inline int32_t text_offset_y()                                                { return _table.cell_text_offset_y( _r, _c);                              }
        inline color_t text_color()                                                   { return _table.cell_font_color( _r, _c);                                 } 
        inline color_t font_color()                                                   { return this->text_color();                                              }
        inline int32_t text_letter_space()                                            { return _table.cell_text_letter_space( _r, _c);                          }
        inline int32_t text_line_space()                                              { return _table.cell_text_line_space( _r, _c);                            }
        inline const void* icon_src()                                                 { return _table.cell_icon_src( _r, _c);                                   }
        inline int32_t icon_offset_x()                                                { return _table.cell_icon_offset_x( _r, _c);                              }
        inline int32_t icon_offset_y()                                                { return _table.cell_icon_offset_y( _r, _c);                              }
        inline uint8_t decimal()                                                      { return _table.cell_decimal( _r, _c);                                    }
        inline bool clickable()                                                       { return _table.cell_clickable( _r, _c);                                  }
        inline void* user_data()                                                      { return _table.cell_user_data( _r, _c);                                  }

        inline void ON()                                                              { _table.cell_checked( _r, _c, true);                                     }
        inline void OFF()                                                             { _table.cell_checked( _r, _c, false);                                    }
        inline bool isON()                                                            { return _table.cell_checked( _r, _c);                                    }
        inline bool isOFF()                                                           { return !this->isON();                                                   }
        inline void toggle()                                                          { this->isON()? this->OFF() : this->ON();                                 }
        inline bool isPressed() {
          auto state = _table.getState();
          auto cell = _table.selected_cell();
          return (state & GSTATE_PRESSED) && (_r == cell.row) && (_c == cell.col);
        }

      private:
        GTable& _table;
        int32_t _r;
        int32_t _c;
    };

    class GTableCell {
      public:
        GTableCell() {}
        void init(GTable &table) { this->_table = &table; }
        GTableCellBlock  operator()(int32_t r, int32_t c)       { return GTableCellBlock(*_table, r,c);                       }
        GTableCellBlock  operator()(table_cell_dsc_t cell_dsc)  { return GTableCellBlock(*_table, cell_dsc.row, cell_dsc.col);}
        GTable* _table;
    };

    class GTableRowBlock {
      public:
        GTableRowBlock(GTable&table, int32_t r): _table(table), _r(r) {}

        inline void height(int32_t h)                                                 { _table.row_height( _r, h);                                              }
        inline int32_t height()                                                       { return _table.get_row_height( _r);                                          }

        inline void align(text_align_t text_align, int32_t ofs_x=0, int32_t ofs_y=0)  { _table.cell_text_align( _r, -1, text_align, ofs_x, ofs_y );             }
        inline void text_offset(int32_t ofs_x=0, int32_t ofs_y=0)                     { _table.cell_text_offset( _r, -1, ofs_x, ofs_y );                        }
        inline void text_color(color_t color)                                         { _table.cell_font_color(_r, -1, color);                                  }
        inline void font_color(color_t color)                                         { this->text_color(color);                                                }
        inline void font(const font_t&font)                                           { _table.cell_font( _r, -1, font);                                        }
        inline void font(const font_t&font, color_t color)                            { _table.cell_font(_r, -1, font); _table.cell_font_color(_r, -1, color);  }
        inline void letter_space(int32_t value)                                       { _table.cell_text_letter_space( _r, -1, value);                          }
        inline void line_space(int32_t value)                                         { _table.cell_text_line_space( _r, -1, value);                            }
        inline void color(color_t color)                                              { _table.cell_bg_color( _r, -1, color);                                   }
        inline void icon_src(const void* src)                                         { _table.cell_icon_src( _r, -1, src);                                     }
        inline void icon_src(const void* src, int32_t ofs_x, int32_t ofs_y)           { _table.cell_icon_src( _r, -1, src, ofs_x, ofs_y);                       }
        inline void icon_src(const img_t& src)                                        { _table.cell_icon_src( _r, -1, &src);                                    }
        inline void icon_src(const img_t& src, int32_t ofs_x, int32_t ofs_y)          { _table.cell_icon_src( _r, -1, &src, ofs_x, ofs_y);                      }
        inline void icon_offset(int32_t ofs_x, int32_t ofs_y)                         { _table.cell_icon_offset( _r, -1, ofs_x, ofs_y);                         }
        inline void decimal(uint8_t decimal)                                          { _table.cell_decimal( _r, -1, decimal);                                  }
        inline void clickable(bool en)                                                { _table.cell_clickable( _r, -1, en);                                     }

        inline text_align_t align()                                                   { return _table.cell_text_align( _r, -1);                                 }
        inline int32_t text_offset_x()                                                { return _table.cell_text_offset_x( _r, -1);                              }
        inline int32_t text_offset_y()                                                { return _table.cell_text_offset_y( _r, -1);                              }
        inline color_t text_color()                                                   { return _table.cell_font_color( _r, -1);                                 } 
        inline color_t font_color()                                                   { return this->text_color();                                              }
        inline int32_t text_letter_space()                                            { return _table.cell_text_letter_space( _r, -1);                               }
        inline int32_t text_line_space()                                              { return _table.cell_text_line_space( _r, -1);                                 }
        inline const void* icon_src()                                                 { return _table.cell_icon_src( _r, -1);                                   }
        inline int32_t icon_offset_x()                                                { return _table.cell_icon_offset_x( _r, -1);                              }
        inline int32_t icon_offset_y()                                                { return _table.cell_icon_offset_y( _r, -1);                              }
        inline uint8_t decimal()                                                      { return _table.cell_decimal( _r, -1);                                    }
        inline bool clickable()                                                       { return _table.cell_clickable( _r, -1);                                  }

      private:
        GTable& _table;
        int32_t _r;
    };

    class GTableRow {
      public:
        GTableRow(){}
        void init(GTable &table) { this->_table = &table; }
        GTableRowBlock operator()(int32_t r) { return GTableRowBlock(*_table, r); }
        GTable* _table;
    };

    class GTableColumnBlock {
      public:
        GTableColumnBlock(GTable&table, int32_t c): _table(table), _c(c) {}
        inline void width(int32_t w)          { _table.column_width(_c, w);       }
        inline int32_t width()                { return _table.get_column_width(_c);   }

        inline void align(text_align_t text_align, int32_t ofs_x=0, int32_t ofs_y=0)  { _table.cell_text_align( -1, _c, text_align, ofs_x, ofs_y );             }
        inline void text_offset(int32_t ofs_x=0, int32_t ofs_y=0)                     { _table.cell_text_offset( -1, _c, ofs_x, ofs_y );                        }
        inline void text_color(color_t color)                                         { _table.cell_font_color(-1, _c, color);                                  }
        inline void font_color(color_t color)                                         { this->text_color(color);                                                }
        inline void font(const font_t&font)                                           { _table.cell_font( -1, _c, font);                                        }
        inline void font(const font_t&font, color_t color)                            { _table.cell_font(-1, _c, font); _table.cell_font_color(-1, _c, color);  }
        inline void letter_space(int32_t value)                                       { _table.cell_text_letter_space( -1, _c, value);                          }
        inline void line_space(int32_t value)                                         { _table.cell_text_line_space( -1, _c, value);                            }
        inline void color(color_t color)                                              { _table.cell_bg_color( -1, _c, color);                                   }
        inline void icon_src(const void* src)                                         { _table.cell_icon_src( -1, _c, src);                                     }
        inline void icon_src(const void* src, int32_t ofs_x, int32_t ofs_y)           { _table.cell_icon_src( -1, _c, src, ofs_x, ofs_y);                       }
        inline void icon_src(const img_t& src)                                        { _table.cell_icon_src( -1, _c, &src);                                    }
        inline void icon_src(const img_t& src, int32_t ofs_x, int32_t ofs_y)          { _table.cell_icon_src( -1, _c, &src, ofs_x, ofs_y);                      }
        inline void icon_offset(int32_t ofs_x, int32_t ofs_y)                         { _table.cell_icon_offset( -1, _c, ofs_x, ofs_y);                         }
        inline void decimal(uint8_t decimal)                                          { _table.cell_decimal( -1, _c, decimal);                                  }
        inline void clickable(bool en)                                                { _table.cell_clickable( -1, _c, en);                                     }

        inline text_align_t align()                                                   { return _table.cell_text_align( -1, _c);                                 }
        inline int32_t text_offset_x()                                                { return _table.cell_text_offset_x( -1, _c);                              }
        inline int32_t text_offset_y()                                                { return _table.cell_text_offset_y( -1, _c);                              }
        inline color_t text_color()                                                   { return _table.cell_font_color( -1, _c);                                 } 
        inline color_t font_color()                                                   { return this->text_color();                                              }
        inline int32_t text_letter_space()                                            { return _table.cell_text_letter_space( -1, _c);                               }
        inline int32_t text_line_space()                                              { return _table.cell_text_line_space( -1, _c);                                 }
        inline const void* icon_src()                                                 { return _table.cell_icon_src( -1, _c);                                   }
        inline int32_t icon_offset_x()                                                { return _table.cell_icon_offset_x( -1, _c);                              }
        inline int32_t icon_offset_y()                                                { return _table.cell_icon_offset_y( -1, _c);                              }
        inline uint8_t decimal()                                                      { return _table.cell_decimal( -1, _c);                                    }
        inline bool clickable()                                                       { return _table.cell_clickable( -1, _c);                                  }

      private:
        GTable& _table;
        int32_t _c;
    };

    class GTableColumn {
      public:
        GTableColumn(){}
        void init(GTable &table) { this->_table = &table; }
        GTableColumnBlock operator()(uint16_t c) { return GTableColumnBlock(*_table, c); }
        GTable* _table;
    };

    GTableCell   cell;
    GTableRow    row;
    GTableColumn column;

    std::vector<table_cell_dsc_t> table_cell_dsc_list;

    /*=====================
    * Design API
    *====================*/
    inline void color(color_t color)            { GObject::color(color, GPART_CELL);  }
    using GObject::color;
    

  private:


};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif //__GTABLE_H__
