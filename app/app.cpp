#include "app.h"

namespace fonts {

ci::Font roboto("Roboto", 20);
ci::Font courier_new("Courier New", 32);
// Cinder has a memory leak, creating a new ci::Font object on every frame will cause
// the app to run out of memory and crash. Instead, we can create the fonts once and reuse them.

}  // namespace fonts

namespace naivebayes {

namespace visualizer {

NaiveBayesApp::NaiveBayesApp()
    : sketchpad_(glm::vec2(kMargin, kMargin), kImageDimension, kWindowSize - 2 * kMargin) {
    ci::app::setWindowSize(kWindowSize, kWindowSize);
}

void NaiveBayesApp::draw() {
    ci::Color8u background_color(255, 246, 148);
    ci::gl::clear(background_color);

    sketchpad_.Draw();

    ci::gl::drawStringCentered(
        "Press Delete to clear the sketchpad. Press Enter to make a prediction.",
        glm::vec2(kWindowSize / 2, kMargin / 2),
        ci::Color("black"), fonts::roboto);

    ci::gl::drawStringCentered(
        "Prediction: " + std::to_string(current_prediction_),
        glm::vec2(kWindowSize / 2, kWindowSize - kMargin / 2),
        ci::Color("blue"), fonts::courier_new);
}

void NaiveBayesApp::mouseDown(ci::app::MouseEvent event) {
    sketchpad_.HandleBrush(event.getPos());
}

void NaiveBayesApp::mouseDrag(ci::app::MouseEvent event) {
    sketchpad_.HandleBrush(event.getPos());
}

void NaiveBayesApp::keyDown(ci::app::KeyEvent event) {
    switch (event.getCode()) {
        case ci::app::KeyEvent::KEY_RETURN:
            // ask your classifier to classify the image that's currently drawn on the sketchpad
            // and update current_prediction_
            break;
        
        case ci::app::KeyEvent::KEY_DELETE:
            sketchpad_.Clear();
            break;
    }
}

void prepareSettings(NaiveBayesApp::Settings* settings) {
    settings->setResizable(false);
}

}  // namespace visualizer

}  // namespace naivebayes

// This line is a macro that tells Cinder to actually create and run the application.
CINDER_APP(naivebayes::visualizer::NaiveBayesApp, ci::app::RendererGl,
           naivebayes::visualizer::prepareSettings)