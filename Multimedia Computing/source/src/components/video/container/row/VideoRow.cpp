//
//  VideoRow.cpp
//  Project-CM
//
//  Created by Francisco Cunha on 17/05/2018.
//

#include "VideoRow.hpp"

//--------------------------------------------------------------

VideoRow::VideoRow() {
  // Nothing.
}

//--------------------------------------------------------------

VideoRow::VideoRow(vector<Metadata> videoMetadatas) {
  setupRow(videoMetadatas);
  computeItemBounds();
  ofAddListener(Events::videoGridItemRemovedEvent, this, &VideoRow::onClipRemoved);
  ofAddListener(Events::videoRowItemHoverEvent, this, &VideoRow::onClipHovered);
  ofAddListener(Events::videoRowItemLeftButtonClick, this, &VideoRow::onClipLeftButtonClicked);
  ofAddListener(Events::videoRowItemRightButtonClick, this, &VideoRow::onClipRightButtonClicked);
}

//--------------------------------------------------------------

void VideoRow::setupRow(vector<Metadata> videoMetadatas) {
  videos.clear();
  for (int i = 0; i < videoMetadatas.size(); i++) {
    videos.push_back(VideoRowItem(videoMetadatas[i]));
  }
}

//--------------------------------------------------------------

void VideoRow::computeItemBounds() {
  const int ITEM_HEIGHT = bounds.height - (3 * GAP) - Dimensions::TAB_HEIGHT;
  const int Y = bounds.y + (2 * GAP) + Dimensions::TAB_HEIGHT;
  
  for (int i = 0; i < videos.size(); i++) {
    int X = ((i + 1) * GAP) + (i * ITEM_WIDTH);
    const Bounds itemBounds = { X, Y, ITEM_WIDTH, ITEM_HEIGHT };
    videos[i].setBounds(itemBounds);
    videos[i].setupPositioningButtons();
  }
}

//--------------------------------------------------------------

void VideoRow::onClipRemoved(Metadata &metadata) {
  string videoName = metadata.getName();
  int indexToRemove = getIndexByName(videoName);
  if (indexToRemove == -1) return;
  videos.erase(videos.begin() + indexToRemove);
  /** We need to compute each grid item's bounds again... */
  computeItemBounds();
}

//--------------------------------------------------------------

void VideoRow::onClipHovered(Metadata &metadata) {
  string videoName = metadata.getName();
  for (int i = 0; i < videos.size(); i++) {
    videos[i].setHovered(videos[i].getMetadata().getName() == videoName);
  }
}

//--------------------------------------------------------------

void VideoRow::onClipLeftButtonClicked(Metadata &metadata) {
  int sourceVideoIndex = getIndexByName(metadata.getName());
  /**
   We cant move the very first clip to the left...
   In theory, there would be no need to check for -1, because that would never happen.
   However, in Windows, if we click the left/right arrows straight after generating
   the timeline, sourceVideoIndex returns -1 (???).
   */
  if (sourceVideoIndex == -1 || sourceVideoIndex == 0) return;
  /**
   Do the shifting...
   */
  int indexToTheLeft = sourceVideoIndex - 1;
  VideoRowItem leftCopy = videos[indexToTheLeft];
  videos[indexToTheLeft] = videos[sourceVideoIndex];
  videos[sourceVideoIndex] = leftCopy;
  computeItemBounds();
}

//--------------------------------------------------------------

void VideoRow::onClipRightButtonClicked(Metadata &metadata) {
  int sourceVideoIndex = getIndexByName(metadata.getName());
  /**
   We cant move the very last clip to the right...
   In theory, there would be no need to check for -1, because that would never happen.
   However, in Windows, if we click the left/right arrows straight after generating
   the timeline, sourceVideoIndex returns -1 (???).
   */
  if (sourceVideoIndex == -1 || sourceVideoIndex == videos.size() - 1) return;
  /**
   Do the shifting...
   */
  int indexToTheRight = sourceVideoIndex + 1;
  VideoRowItem rightCopy = videos[indexToTheRight];
  videos[indexToTheRight] = videos[sourceVideoIndex];
  videos[sourceVideoIndex] = rightCopy;
  computeItemBounds();
}

//--------------------------------------------------------------

int VideoRow::getIndexByName(string videoName) {
  for (int i = 0; i < videos.size(); i++) {
    if (videos[i].getMetadata().getName() == videoName) {
      return i;
    }
  }
  return -1;
}

//--------------------------------------------------------------

vector<string> VideoRow::getVideoNames() {
  vector<string> videoNames;
  videoNames.assign(videos.size(), string());
  for (int i = 0; i < videos.size(); i++) {
    videoNames[i] = videos[i].getMetadata().getName();
  }
  return videoNames;
}

//--------------------------------------------------------------

void VideoRow::update() {
  for (int i = 0; i < videos.size(); i++) {
    videos[i].update();
  }
}

//--------------------------------------------------------------

void VideoRow::draw() {
  for (int i = 0; i < videos.size(); i++) {
    videos[i].draw();
  }
}
