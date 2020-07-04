#include "sketchpad.h"

namespace naivebayes {

namespace visualizer {

Sketchpad::Sketchpad(const vec2& top_left_corner, size_t num_pixels_per_side,
                     double sketchpad_size, double brush_radius)
    : top_left_corner_(top_left_corner),
      num_pixels_per_side_(num_pixels_per_side),
      pixel_side_length_(sketchpad_size / num_pixels_per_side),
      brush_radius_(brush_radius),
      shaded_pixels_(num_pixels_per_side_,
                     vector<bool>(num_pixels_per_side_, false)) {}

void Sketchpad::Draw() const {
    for (size_t row = 0; row < num_pixels_per_side_; ++row) {
        for (size_t col = 0; col < num_pixels_per_side_; ++col) {
            if (shaded_pixels_[row][col]) {
                ci::gl::color(ci::Color("black"));
            } else {
                ci::gl::color(ci::Color("white"));
            }

            vec2 pixel_top_left = top_left_corner_ +
                                  vec2(col * pixel_side_length_, row * pixel_side_length_);

            vec2 pixel_bottom_right = pixel_top_left + vec2(pixel_side_length_, pixel_side_length_);

            ci::gl::drawSolidRect(ci::Rectf(pixel_top_left, pixel_bottom_right));
        }
    }
}

void Sketchpad::HandleBrush(const vec2& brush_screen_coords) {
    vec2 brush_sketchpad_coords = (brush_screen_coords - top_left_corner_) / (float)pixel_side_length_;

    for (size_t row = 0; row < num_pixels_per_side_; ++row) {
        for (size_t col = 0; col < num_pixels_per_side_; ++col) {
            vec2 pixel_center = {col + 0.5, row + 0.5};

            if (glm::distance(brush_sketchpad_coords, pixel_center) <= brush_radius_) {
                shaded_pixels_[row][col] = true;
            }
        }
    }
}

std::ostream& operator<<(std::ostream& output, const Sketchpad& sketchpad) {
    for (size_t row = 0; row < sketchpad.num_pixels_per_side_; ++row) {
        for (size_t col = 0; col < sketchpad.num_pixels_per_side_; ++col) {
            if (sketchpad.shaded_pixels_[row][col]) {
                output << '#';
            } else {
                output << ' ';
            }
        }
        output << std::endl;
    }

    return output;
}

}  // namespace visualizer

}  // namespace naivebayes