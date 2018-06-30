#include "VideoGridItem.hpp"

//--------------------------------------------------------------

VideoGridItem::VideoGridItem(Metadata metadata, string sectionName) {
  string fileName = metadata.getName();
  XMLFileAgent fileAgent = XMLFileAgent();
  
  // Load the video's thumbnail.
  string thumbnailFileName = fileAgent.getThumbnailNameForVideo(fileName);
  thumbnail.load(thumbnailFileName);
  
  // Load the video's representative frames.
  frameLoopCounter = 0;
  vector<string> repFrameFileNames = fileAgent.getRepresentativeFrameNamesForVideo(fileName);
  for (int i = 0; i < repFrameFileNames.size(); i++) {
    string frameName = repFrameFileNames[i];
    representativeFrames.push_back(ofImage());
    representativeFrames[i].load(frameName);
  }
  
  // And all the rest.
  titleLabel = new ofxDatGuiLabel(fileName);
  removeButton = new ofxDatGuiButton("X");
  this->isHovered = false;
  this->metadata = metadata;
  this->metadata.setSectionName(sectionName);
  
  
}

//--------------------------------------------------------------

void VideoGridItem::setupTitleLabel() {
  titleLabel->setWidth(bounds.width);
  titleLabel->setLabelAlignment(ofxDatGuiAlignment::CENTER);
  titleLabel->setLabelColor(Colors::BLACK);
  titleLabel->setBackgroundColor(Colors::WHITE);
  titleLabel->setStripeVisible(false);
  titleLabel->setPosition(bounds.x, (bounds.y + bounds.height) - Dimensions::TAB_HEIGHT);
}

//--------------------------------------------------------------

void VideoGridItem::setupRemoveButton() {
  const int removeButtonWidth = Dimensions::TAB_HEIGHT;
  removeButton->setWidth(removeButtonWidth);
  removeButton->setLabelAlignment(ofxDatGuiAlignment::CENTER);
  removeButton->setBackgroundColor(Colors::BLACK);
  removeButton->setStripeVisible(false);
  removeButton->setPosition((bounds.x + bounds.width) - removeButtonWidth, bounds.y);
  removeButton->onButtonEvent(this, &VideoGridItem::onRemoveButtonClicked);
}

//--------------------------------------------------------------

void VideoGridItem::onRemoveButtonClicked(ofxDatGuiButtonEvent event) {
  Metadata clonedMetadata = Metadata(metadata.getName(), metadata.getSectionName());
  ofNotifyEvent(Events::videoGridItemRemovedEvent, clonedMetadata, this);
}

//--------------------------------------------------------------

void VideoGridItem::setupPlayButton() {
  ImageButtonProps props;
  props.imageWidth = 40;
  props.imageHeight = 40;
  props.buttonX = bounds.x + ((bounds.width - props.imageWidth) / 2);
  props.buttonY = bounds.y + ((bounds.height - titleLabel->getHeight()) / 2) - ((props.imageHeight) / 3);
  props.buttonWidth = 40;
  props.buttonHeight = 40;
  playButton = new ImageButton("images/play.png", props);
  playButton->setupButton(Colors::NONE, Colors::BLACK, Colors::BLACK, 0.0);
  playButton->onButtonEvent(this, &VideoGridItem::onPlayButtonClicked);
}

//--------------------------------------------------------------

void VideoGridItem::onPlayButtonClicked(ofxDatGuiButtonEvent event) {
  vector<string> videoName;
  videoName.push_back(metadata.getName());
  ofNotifyEvent(Events::playVideoButtonClickEvent, videoName, this);
  bool isSetToFade = false;
  ofNotifyEvent(Events::fadeButtonSelectedEvent, isSetToFade, this);
}

//--------------------------------------------------------------

void VideoGridItem::setBounds(Bounds bounds) {
  this->bounds = bounds;
}

//--------------------------------------------------------------

Metadata VideoGridItem::getMetadata() {
  return this->metadata;
}

//--------------------------------------------------------------

void VideoGridItem::setHovered(bool value) {
  this->isHovered = value;
  this->titleLabel->setBackgroundColor(isHovered ? ofColor(235, 235, 235) : Colors::WHITE);
}

//--------------------------------------------------------------

void VideoGridItem::update() {
  playButton->update();
  removeButton->update();
  thumbnail.update();
  /**
   Check for mouse events (hover, single click ...).
   */
  bool mouseOverRemoveButton = bounds.isMouseInBoxArea(removeButton->getX(), removeButton->getY(), removeButton->getWidth(), removeButton->getHeight());
  bool mouseOverPlayButton = bounds.isMouseInBoxArea(playButton->getX(), playButton->getY(), playButton->getWidth(), playButton->getHeight());
  
  if (bounds.containsMouse()) {
    /**
     Mouse hover feedback.
     */
    ofNotifyEvent(Events::videoGridItemHoverEvent, metadata, this);
    
    if (!mouseOverRemoveButton && !mouseOverPlayButton) {
      /**
       On video single-click, broadcast an event that will have the video's metadata attached.
       */
      if (ofGetMousePressed()) {
        ofNotifyEvent(Events::videoSingleClickEvent, metadata, this);
      } else {
        // Mouse hover video area: display representative frames.
        int maxAcceptableFrameCounter = representativeFrames.size() * SPOTLIGHT_TIME_PER_FRAME;
        if (++frameLoopCounter >= maxAcceptableFrameCounter) frameLoopCounter = 0;
      }
    }
  } else {
    this->isHovered = false;
    this->titleLabel->setBackgroundColor(Colors::WHITE);
    this->frameLoopCounter = 0;
  }
}

//--------------------------------------------------------------

void VideoGridItem::draw() {
  if (isHovered) {
    ofSetColor(235, 235, 235);
    ofDrawRectangle(bounds.x - 8, bounds.y - 8, bounds.width + 16, bounds.height + 16);
  }
  ofSetColor(255, 255, 255);
  if (isHovered) {
    int indexOfRepFrameToDraw = (int) frameLoopCounter / SPOTLIGHT_TIME_PER_FRAME;
    representativeFrames[indexOfRepFrameToDraw].draw(bounds.x, bounds.y, bounds.width, bounds.height);
  } else {
    thumbnail.draw(bounds.x, bounds.y, bounds.width, bounds.height);
  }
  titleLabel->draw();
  removeButton->draw();
  playButton->draw();
}
