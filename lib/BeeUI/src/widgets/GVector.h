
#ifndef __GVECTOR_H__
#define __GVECTOR_H__

#include <Arduino.h>
#include "GUtils.h"
#include "GLVGL.h"
#include <memory>
#include <cstdlib>
#include <cstddef>
#include "Point.h"

#if LV_USE_VECTOR_GRAPHIC

//----------------------------------------
namespace BLYNKGO_V5 {
//----------------------------------------

class GVectorPath {
  public:
    GVectorPath()   {}
    ~GVectorPath()  { this->del();}

    void create(vector_path_quality_t quality= VECTOR_PATH_QUALITY_MEDIUM);
    void del();

    inline bool isCreated()            { return (this->_vect_path != NULL); }
    inline vector_path_t* raw()        { return this->_vect_path;           }

    /**
     * Begin a new sub path and set a point to path
     * @param p                 Point variable
     */
    void move_to(Point p);

    inline void move_to(float x, float y)       { this->move_to(Point(x,y));    }

    /**
     * Add a line to the path from last point to the point
     * @param p                 Point variable
     */
    void line_to(Point p);

    inline void line_to(float x, float y){ this->line_to(Point(x,y));    }

    /**
     * Add a quadratic bezier line to the path from last point to the point
     * @param p1                Point variable for control point
     * @param p2                Point variable for end point
     */
    void quad_to(Point p1, Point p2);

    inline void quad_to(float x1, float y1, float x2, float y2)       
    { this->quad_to(Point(x1,y1),Point(x2,y2));    }

    /**
     * Add a cubic bezier line to the path from last point to the point
     * @param p1                Point variable for first control point
     * @param p2                Point variable for second control point
     * @param p3                Point variable for end point
     */
    void cubic_to(Point p1, Point p2, Point p3);

    inline void cubic_to(float x1, float y1,float x2, float y2,float x3, float y3)
    { this->cubic_to(Point(x1,y1),Point(x2,y2),Point(x3,y3));    }

    /**
     * Close the sub path
     */
    void close();

    /**
     * Copy a path data to another
     * @param target_path       pointer to a path
     * @param path              pointer to source path
     */
    void copy(const lv_vector_path_t * path);

    /**
     * Copy a path data to another
     * @param target_path       pointer to a path
     * @param path              GVectorPath variable
     */
    void copy(GVectorPath& path);

    /**
     * Clear path data
     */
    void clear();

    /**
     * Get the bounding box of a path
     * @param area              pointer to a `lv_area_t` variable for bounding box
     */
    void get_bounding(area_t * area);

    /**
     * Add a rectangle to the path
     * @param rx                the horizontal radius for rounded rectangle
     * @param ry                the vertical radius for rounded rectangle
     */
    void append_rect(const area_t * rect, float rx, float ry);

    /**
     * Add a circle to the path
     * @param c                 pointer to a `lv_fpoint_t` variable for center of the circle
     * @param rx                the horizontal radius for circle
     * @param ry                the vertical radius for circle
     */
    void append_circle(const lv_fpoint_t * c, float rx, float ry);

    void append_circle(Point c, float rx, float ry);
    inline void append_circle(Point c, float r)             {  this->append_circle(c,r,r);    }

    /**
     * Add a arc to the path
     * @param c                 pointer to a `lv_fpoint_t` variable for center of the circle
     * @param radius            the radius for arc
     * @param start_angle       the start angle for arc
     * @param sweep             the sweep angle for arc, could be negative
     * @param pie               true: draw a pie, false: draw a arc
     */
    void append_arc(const lv_fpoint_t * c, float radius, float start_angle,
                                  float sweep, bool pie);

    void append_arc(Point c, float radius, float start_angle,
                                  float sweep, bool pie);

    /**
     * Add an sub path to the path
     * @param subpath           pointer to another path which will be added
     */
    void append_path(const vector_path_t * subpath);

    void append_path(GVectorPath& subpath);
  public:
    vector_path_t*  _vect_path = NULL;
};

class GVector {
  public:
    GVector()   {}
    GVector(layer_t& layer) : _layer(&layer)   {}
    GVector(layer_t* layer) : _layer(layer)    {}
    ~GVector()  { this->del();}

    void create(layer_t * layer=NULL);
    void del();

    inline bool isCreated()             { return (this->_vect_dsc != NULL); }
    inline vector_dsc_t* raw()          { return this->_vect_dsc;           }

    /**
     * Set a matrix to current transformation matrix
     * @param matrix           pointer to a matrix
     */
    void transform(const lv_matrix_t * matrix);

    /**
     * Set blend mode for descriptor
     * @param blend            the blend mode to be set in `lv_vector_blend_t`
     */
    void blend_mode(lv_vector_blend_t blend);

    /**
     * Set fill color for descriptor
     * @param color            the color to be set in lv_color32_t format
     */
    void fill_color32(lv_color32_t color);

    /**
     * Set fill color for descriptor
     * @param color            the color to be set in lv_color_t format
     */
    void fill_color(lv_color_t color);

    void fill_color(color_t color);

    /**
     * Set fill opacity for descriptor
     * @param opa              the opacity to be set in lv_opa_t format
     */
    void fill_opa(opa_t opa);

    inline void fill(color_t color)                     { this->fill_color(color);                        }
    inline void fill(color_t color, opa_t opa)          { this->fill_color(color); this->fill_opa(opa);   }

    /**
     * Set fill rule for descriptor
     * @param rule             the fill rule to be set in lv_vector_fill_t format
     */
    void fill_rule(lv_vector_fill_t rule);

    /**
     * Set fill image for descriptor
     * @param img_dsc          pointer to a `lv_draw_image_dsc_t` variable
     */
    void fill_image(const draw_image_dsc_t * img_dsc);

    // /**
    //  * Set fill linear gradient for descriptor
    //  * @param grad             pointer to a `lv_grad_dsc_t` variable
    //  * @param spread           the gradient spread to be set in lv_vector_gradient_spread_t format
    //  */
    // void fill_linear_gradient(const lv_grad_dsc_t * grad,
    //                                             lv_vector_gradient_spread_t spread);

    // /**
    //  * Set fill radial gradient for descriptor
    //  * @param grad             pointer to a `lv_grad_dsc_t` variable
    //  * @param cx               the x for center of the circle
    //  * @param cy               the y for center of the circle
    //  * @param radius           the radius for circle
    //  * @param spread           the gradient spread to be set in lv_vector_gradient_spread_t format
    //  */
    // void fill_radial_gradient(const lv_grad_dsc_t * grad, float cx, float cy,
    //                                             float radius, lv_vector_gradient_spread_t spread);

    /**
     * Set fill linear gradient for descriptor
     * @param x1 the x for start point
     * @param y1 the y for start point
     * @param x2 the x for end point
     * @param y2 the y for end point
     */
    void fill_linear_gradient(float x1, float y1, float x2, float y2);

    /**

    * Set fill radial gradient radius for descriptor
    * @param cx the x for center of the circle
    * @param cy the y for center of the circle
    * @param radius the radius for circle
    */
    void fill_radial_gradient(float cx, float cy, float radius);

    /**
     * Set fill radial gradient spread for descriptor
     * @param spread the gradient spread to be set in lv_vector_gradient_spread_t format
     */
    void fill_gradient_spread(vector_gradient_spread_t spread);

    /**
     * Set fill gradient color stops for descriptor
     * @param stops            an array of `lv_gradient_stop_t` variables
     * @param count            the number of stops in the array, range: 0..LV_GRADIENT_MAX_STOPS
     */
    void fill_gradient_color_stops(const gradient_stop_t * stops, uint16_t count);


    /**
     * Set a matrix to current fill transformation matrix
     * @param matrix           pointer to a matrix
     */
    void fill_transform(const lv_matrix_t * matrix);

    /**
     * Set stroke color for descriptor
     * @param color            the color to be set in lv_color32_t format
     */
    void stroke_color32(lv_color32_t color);

    /**
     * Set stroke color for descriptor
     * @param color            the color to be set in lv_color_t format
     */
    void stroke_color(lv_color_t color);

    void stroke_color(color_t color);

    /**
     * Set stroke opacity for descriptor
     * @param opa              the opacity to be set in lv_opa_t format
     */
    void stroke_opa(opa_t opa);

    /**
     * Set stroke line width for descriptor
     * @param width            the stroke line width
     */
    void stroke_width(float width);

    inline void stroke(float width)                                 { this->stroke_width(width);                                                    }
    inline void stroke(float width, color_t color)                  { this->stroke_width(width); this->stroke_color(color);                         }
    inline void stroke(float width, color_t color, opa_t opa)       { this->stroke_width(width); this->stroke_color(color);  this->stroke_opa(opa); }

    /**
     * Set stroke line dash pattern for descriptor
     * @param dash_pattern     an array of values that specify the segments of dash line
     * @param dash_count       the length of dash pattern array
     */
    void stroke_dash(float * dash_pattern, uint16_t dash_count);

    /**
     * Set stroke line cap style for descriptor
     * @param cap              the line cap to be set in lv_vector_stroke_cap_t format
     */
    void stroke_cap(lv_vector_stroke_cap_t cap);

    /**
     * Set stroke line join style for descriptor
     * @param join             the line join to be set in lv_vector_stroke_join_t format
     */
    void stroke_join(lv_vector_stroke_join_t join);

    /**
     * Set stroke miter limit for descriptor
     * @param miter_limit      the stroke miter_limit
     */
    void stroke_miter_limit(uint16_t miter_limit);

    // /**
    //  * Set stroke linear gradient for descriptor
    //  * @param grad             pointer to a `lv_grad_dsc_t` variable
    //  * @param spread           the gradient spread to be set in lv_vector_gradient_spread_t format
    //  */
    // void stroke_linear_gradient(const lv_grad_dsc_t * grad,
    //                                               lv_vector_gradient_spread_t spread);
    // /**
    //  * Set stroke radial gradient for descriptor
    //  * @param grad             pointer to a `lv_grad_dsc_t` variable
    //  * @param cx               the x for center of the circle
    //  * @param cy               the y for center of the circle
    //  * @param radius           the radius for circle
    //  * @param spread           the gradient spread to be set in lv_vector_gradient_spread_t format
    //  */
    // void stroke_radial_gradient(const lv_grad_dsc_t * grad, float cx, float cy,
    //                                               float radius, lv_vector_gradient_spread_t spread);

    /**
     * Set stroke linear gradient for descriptor
     * @param x1               the x for start point
     * @param y1               the y for start point
     * @param x2               the x for end point
     * @param y2               the y for end point
     */
    void stroke_linear_gradient(float x1, float y1, float x2, float y2);
    /**
     * Set stroke radial gradient for descriptor
     * @param cx               the x for center of the circle
     * @param cy               the y for center of the circle
     * @param radius           the radius for circle
     */
    void stroke_radial_gradient(float cx, float cy, float radius);

    /**
     * Set stroke color stops for descriptor
     * @param spread           the gradient spread to be set in lv_vector_gradient_spread_t format
     */
    void stroke_gradient_spread(vector_gradient_spread_t spread);

    /**
     * Set stroke color stops for descriptor
     * @param stops            an array of `lv_gradient_stop_t` variables
     * @param count            the number of stops in the array
     */
    void stroke_gradient_color_stops(const gradient_stop_t * stops, uint16_t count);


    /**
     * Set a matrix to current stroke transformation matrix
     * @param matrix           pointer to a matrix
     */
    void stroke_transform(const lv_matrix_t * matrix);

    /**
     * Set current transformation matrix to identity matrix
     */
    void identity();

    /**
     * Change the scale factor of current transformation matrix
     * @param scale_x       the scale factor for the X direction
     * @param scale_y       the scale factor for the Y direction
     */
    void scale(float scale_x, float scale_y);

    /**
     * Rotate current transformation matrix with origin
     * @param degree        angle to rotate
     */
    void rotate(float degree);

    /**
     * Rotate current transformation matrix with origin
     * @param degree        angle to rotate
     */
    inline void rotation(float degree)        { this->rotate(degree);     }

    /**
     * Translate current transformation matrix to new position
     * @param tx            the amount of translate in x direction
     * @param tx            the amount of translate in y direction
     */
    void translate(float tx, float ty);

    /**
     * Change the skew factor of current transformation matrix
     * @param skew_x        the skew factor for x direction
     * @param skew_y        the skew factor for y direction
     */
    void skew(float skew_x, float skew_y);

    /**
     * Add a graphic path to the draw list
     * @param path          pointer to a path
     */
    void add_path(const lv_vector_path_t * path);


    void add_path(GVectorPath &path);
    void add_path(GVectorPath &path, color_t color);

    /**
     * Clear a rectangle area use current fill color
     * @param rect          the area to clear in the buffer
     */
    void clear_area(const lv_area_t * rect);

    /**
     * Draw all the vector graphic paths
     */
    void draw();


    // /**
    //  * Rotate current transformation matrix with origin
    //  * @param degree        angle to rotate
    //  */
    // void rotation(float degree);

    // /**
    //  * Translate current transformation matrix to new position
    //  * @param tx            the amount of translate in x direction
    //  * @param tx            the amount of translate in y direction
    //  */
    // void translate( float tx, float ty);

  private:
    vector_dsc_t*  _vect_dsc = NULL;
    layer_t*   _layer = NULL;
};

//----------------------------------------
} //namespace BLYNKGO_V5
//----------------------------------------

#endif // LV_USE_VECTOR_GRAPHIC

#endif //__GVECTOR_H__
