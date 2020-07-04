#pragma once

#include "cinder/gl/gl.h"
#include <vector>

using glm::vec2;
using std::vector;

namespace naivebayes {

namespace visualizer {

/**
 * A sketchpad which will be displayed in the Cinder application and respond to mouse events.
 * Furthermore, the sketchpad can output its current state in the same format
 * as the Naive Bayes image data files.
 */
class Sketchpad {
   public:
    /**
     * Creates a sketchpad. (Note that sketchpad pixels are larger than screen pixels.)
     * 
     * @param top_left_corner the screen coordinates of the top left corner of the sketchpad
     * @param num_pixels_per_side the number of sketchpad pixels in one row/column of the sketchpad
     * @param sketchpad_size the side length of the sketchpad, measured in screen pixels
     * @param brush_radius the maximum distance (measured in sketchpad pixels) from the brush
     *                     that will be shaded
     */
    Sketchpad(const vec2& top_left_corner, size_t num_pixels_per_side,
              double sketchpad_size, double brush_radius = 1.5);

    /**
     * Displays the current state of the sketchpad in the Cinder application.
     */
    void Draw() const;

    /**
     * Shades in the sketchpad pixels whose centers are within brush_radius units of the brush's location.
     * (One unit is equal to the length of one sketchpad pixel.)
     * 
     * @param brush_screen_coords the screen coordinates at which the brush is located
     */
    void HandleBrush(const vec2& brush_screen_coords);

   private:
    vec2 top_left_corner_;

    size_t num_pixels_per_side_;

    /** Number of screen pixels in the width/height of one sketchpad pixel */
    double pixel_side_length_;

    double brush_radius_;

    /** shaded_pixels[i][j] is true if the pixel in row i, column j, has been shaded. */
    vector<vector<bool>> shaded_pixels_;
};

}  // namespace visualizer

}  // namespace naivebayes