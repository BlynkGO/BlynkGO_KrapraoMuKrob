#ifndef __GLAYER_H__
#define __GLAYER_H__

#include "GObject.h"

class GLayer {
  public:
    GLayer(layer_t* layer) : _p_layer(layer)    { }
    GLayer()                                    { _p_layer = &_layer;}
    void drawRect(const draw_rect_dsc_t& rect_dsc, const area_t &area);
    void drawRect(const draw_rect_dsc_t& rect_dsc, int32_t w, int32_t h, align_t Align=ALIGN_CENTER, int32_t ofs_x=0, int32_t ofs_y=0);

    void drawLabel(const draw_label_dsc_t&label_dsc, area_t& area);
    void drawLabel(const draw_label_dsc_t&label_dsc, align_t Align=ALIGN_CENTER, int32_t ofs_x=0, int32_t ofs_y=0);
    void drawLabel(String label, const font_t& font, color_t color, align_t Align=ALIGN_CENTER, int32_t ofs_x=0, int32_t ofs_y=0);

    void drawImage(const draw_image_dsc_t&image_dsc, area_t& area);
    void drawImage(const draw_image_dsc_t&image_dsc, align_t Align=ALIGN_CENTER, int32_t ofs_x=0, int32_t ofs_y=0);
    void drawImage(const img_t & image_src, align_t Align=ALIGN_CENTER, int32_t ofs_x=0, int32_t ofs_y=0);
    void drawImage(const img_t & image_src, float angle /* 0.0-360.0 deg*/, align_t Align=ALIGN_CENTER, int32_t ofs_x=0, int32_t ofs_y=0);
    void drawImage(const img_t & image_src, Point pivot, float angle /* 0.0-360.0 deg*/, align_t Align=ALIGN_CENTER, int32_t ofs_x=0, int32_t ofs_y=0);

    void drawLine(const draw_line_dsc_t& line_dsc);
    void drawArc(const draw_arc_dsc_t&arc_dsc);
    void drawTriangle(const draw_triangle_dsc_t& triangle_dsc);
    void drawMaskRect(const draw_mask_rect_dsc_t& mask_rect_dsc);


    GLayer& operator=(layer_t* layer);

    void create(layer_t* parent_layer, area_t &layer_area);
    void render();

    bool isNULL();

    layer_t _layer;
    layer_t *_p_layer;
    layer_t *_p_parent_layer;
    area_t  *_p_area;
  private:
};

#endif
