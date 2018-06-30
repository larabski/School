#include "ImageButton.hpp"

ImageButton::ImageButton(string imagePath, ImageButtonProps props) {
  
  this->props = props;
  
  button = new ofxDatGuiButton("");
  button->setWidth(props.buttonWidth);
  button->setPosition(props.buttonX, props.buttonY);
  button->setStripeVisible(false);
  image.load(imagePath);
}

//--------------------------------------------------------------

void ImageButton::attachToEvent(ofEvent<void> event) {
  attachedEvent = event;
  button->onButtonEvent(this, &ImageButton::onImageButtonClicked);
}

//--------------------------------------------------------------

void ImageButton::onImageButtonClicked(ofxDatGuiButtonEvent event) {
  ofNotifyEvent(attachedEvent);
}

//--------------------------------------------------------------

void ImageButton::setupButton(int backgroundColor, int backgroundColorMouseOver, int backgroundColorMouseDown, float opacity) {
  button->setBackgroundColor(Colors::DARK_GRAY);
  button->setBackgroundColorOnMouseOver(Colors::CHARCOAL_GRAY);
  button->setBackgroundColorOnMouseDown(Colors::CHARCOAL_GRAY);
  button->setOpacity(opacity);
}

//--------------------------------------------------------------

int ImageButton::getX() {
  return button->getX();
}

//--------------------------------------------------------------

int ImageButton::getY() {
  return button->getY();
}

//--------------------------------------------------------------

int ImageButton::getWidth() {
  return button->getWidth();
}

//--------------------------------------------------------------

int ImageButton::getHeight() {
  return button->getHeight();
}

//--------------------------------------------------------------

void ImageButton::update() {
  button->update();
  image.update();
}

//--------------------------------------------------------------

void ImageButton::draw() {
  button->draw();
  const int x = (button->getWidth()-props.imageWidth) / 2 + props.buttonX;
  const int y = (button->getHeight()-props.imageHeight) / 2 + props.buttonY;
  ofSetColor(255, 255, 255);
  image.draw(x, y, props.imageWidth, props.imageHeight);
}




