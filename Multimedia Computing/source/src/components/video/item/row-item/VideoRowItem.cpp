#include "VideoRowItem.hpp"

//--------------------------------------------------------------

VideoRowItem::VideoRowItem(Metadata metadata) {
  string fileName = metadata.getName();
  string thumbnailFileName = XMLFileAgent().getThumbnailNameForVideo(fileName);
  thumbnail.load(thumbnailFileName);
  this->metadata = metadata;
  this->isHovered = false;
}

//--------------------------------------------------------------

void VideoRowItem::setupPositioningButtons() {
  moveLeftButton = new ofxDatGuiButton("<<");
  moveRightButton = new ofxDatGuiButton(">>");
  
  const int GAP = 5;
  const int BUTTON_WIDTH = (bounds.width - 3 * GAP) / 2;
  const int BUTTON_HEIGHT = Dimensions::TAB_HEIGHT;
  const int BUTTON_Y = bounds.y + bounds.height - Dimensions::TAB_HEIGHT - 5;
  
  moveLeftButton->setPosition(bounds.x + 5, BUTTON_Y);
  moveRightButton->setPosition(bounds.x + bounds.width - BUTTON_WIDTH - 5, BUTTON_Y);
  
  moveLeftButton->setWidth(BUTTON_WIDTH);
  moveRightButton->setWidth(BUTTON_WIDTH);
  moveLeftButton->setLabelAlignment(ofxDatGuiAlignment::CENTER);
  moveRightButton->setLabelAlignment(ofxDatGuiAlignment::CENTER);
  moveLeftButton->setStripeVisible(false);
  moveRightButton->setStripeVisible(false);
  
  moveLeftButton->onButtonEvent(this, &VideoRowItem::onLeftButtonClicked);
  moveRightButton->onButtonEvent(this, &VideoRowItem::onRightButtonClicked);
}

//--------------------------------------------------------------

void VideoRowItem::onLeftButtonClicked(ofxDatGuiButtonEvent event) {
  ofNotifyEvent(Events::videoRowItemLeftButtonClick, metadata, this);
}

//--------------------------------------------------------------

void VideoRowItem::onRightButtonClicked(ofxDatGuiButtonEvent event) {
  ofNotifyEvent(Events::videoRowItemRightButtonClick, metadata, this);
}

//--------------------------------------------------------------

void VideoRowItem::setBounds(Bounds bounds) {
  this->bounds = bounds;
}

//--------------------------------------------------------------

Metadata VideoRowItem::getMetadata() {
  return this->metadata;
}

//--------------------------------------------------------------

void VideoRowItem::setHovered(bool value) {
  this->isHovered = value;
}

//--------------------------------------------------------------

void VideoRowItem::update() {
  if (bounds.containsMouse()) {
    ofNotifyEvent(Events::videoRowItemHoverEvent, metadata, this);
  } else {
    isHovered = false;
  }

  if (isHovered) {
    moveLeftButton->update();
    moveRightButton->update();
  }
}

//--------------------------------------------------------------

void VideoRowItem::draw() {
  ofSetColor(255, 255, 255);
  thumbnail.draw(bounds.x, bounds.y, bounds.width, bounds.height);
  if (isHovered) {
    moveLeftButton->draw();
    moveRightButton->draw();
  }
}

