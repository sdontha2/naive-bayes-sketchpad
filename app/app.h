#pragma once

#include <sstream>  // allows us to use stringstream

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "../src/sketchpad.h"

namespace naivebayes {

namespace visualizer {

/**
 * This Cinder app allows a user to draw a digit on a sketchpad
 * and uses Naive Bayes to classify it.
 */
class NaiveBayesApp : public ci::app::App {
   public:
    NaiveBayesApp();

    void draw() override;
    void mouseDown(ci::app::MouseEvent event) override;
    void mouseDrag(ci::app::MouseEvent event) override;
    void keyDown(ci::app::KeyEvent event) override;

    const double kWindowSize = 900;
    const double kMargin = 100;
    const size_t kImageDimension = 28;

   private:
    Sketchpad sketchpad_;
    size_t current_prediction_ = 0;
};

}  // namespace visualizer

}  // namespace naivebayes