//
//  VideoGrid.cpp
//  Project-CM
//
//  Created by Francisco Cunha on 27/04/2018.
//

#include "VideoGrid.hpp"

//--------------------------------------------------------------

VideoGrid::VideoGrid(string sectionName) {
  this->sectionName = sectionName;
}

//--------------------------------------------------------------

VideoGrid::VideoGrid(vector<Metadata> videoMetadatas, string sectionName) {
  this->sectionName = sectionName;
  setupGrid(videoMetadatas);
  computeItemBounds();
  ofAddListener(Events::newVideoImportedEvent, this, &VideoGrid::onClipImported);
  ofAddListener(Events::videoGridItemHoverEvent, this, &VideoGrid::onClipHovered);
  ofAddListener(Events::videoGridItemRemovedEvent, this, &VideoGrid::onClipRemoved);
}

//--------------------------------------------------------------

void VideoGrid::setupGrid(vector<Metadata> videoMetadatas) {
  videos.clear();
  for (int i = 0; i < videoMetadatas.size(); i++) {
    videos.push_back(VideoGridItem(videoMetadatas[i], this->sectionName));
  }
}

//--------------------------------------------------------------

/**
 Don't compute the grid's bounds in #draw, of course.
 This method is expensive, and thus should ONLY be called:
 - Once on setup, for all the video loaded.
 - When a clip is removed or a new one is added.
 */
void VideoGrid::computeItemBounds() {
  const int ITEM_WIDTH = (Dimensions::VIDEO_SECTION_WIDTH - ((NUM_COLUMNS + 1) * GAP)) / NUM_COLUMNS;
  const int BASE_X = Dimensions::NUM_SMALL_TABS * Dimensions::SMALL_TAB_WIDTH;
  
  int currentRow = 0;
  int currentCol = 0;
  
  for (int i = 0; i < videos.size(); i++) {
    const int x = BASE_X + ((currentCol + 1) * GAP) + (currentCol * ITEM_WIDTH);
    const int y = bounds.y + ((currentRow + 1) * GAP) + (currentRow * ITEM_HEIGHT);
    const Bounds itemBounds = { x, y, ITEM_WIDTH, ITEM_HEIGHT };
    videos[i].setBounds(itemBounds);
    videos[i].setupTitleLabel();
    videos[i].setupRemoveButton();
    videos[i].setupPlayButton();
    
    if (++currentCol == NUM_COLUMNS) {
      currentRow++;
      currentCol = 0;
    }
  }
}

//--------------------------------------------------------------

void VideoGrid::onClipHovered(Metadata &metadata) {
  string videoName = metadata.getName();
  for (int i = 0; i < videos.size(); i++) {
    videos[i].setHovered(videos[i].getMetadata().getName() == videoName);
  }
}

//--------------------------------------------------------------

void VideoGrid::onClipRemoved(Metadata &metadata) {
  string videoName = metadata.getName();
  int indexToRemove = getIndexByName(videoName);
  if (indexToRemove == -1) return;
  
  string triggerOrigin = metadata.getSectionName();
  
  if (triggerOrigin == "TimelineClips" && this->sectionName == "TimelineClips") {
    /** Erase from the timeline clips ONLY. */
    videos.erase(videos.begin() + indexToRemove);
  } else if (triggerOrigin == "AllClips") {
    /** Erase from the timeline clips AND all clips. */
    videos.erase(videos.begin() + indexToRemove);
    if (this->sectionName == "AllClips") {
      /** Actually erase the video + XML files + representative frames. */
      XMLFileAgent().deleteEverythingForVideo(videoName);
    }
  }
  computeItemBounds();
}

void VideoGrid::onClipImported(Metadata &metadata) {
  /**
   Only add the newly imported clip to the "All Clips" section.
   */
  if (this->sectionName == "AllClips") {
    videos.push_back(VideoGridItem(metadata, this->sectionName));
    computeItemBounds();
  }
}

//--------------------------------------------------------------

int VideoGrid::getIndexByName(string videoName) {
  for (int i = 0; i < videos.size(); i++) {
    if (videos[i].getMetadata().getName() == videoName) {
      return i;
    }
  }
  return -1;
}

//--------------------------------------------------------------

bool VideoGrid::isEmpty() {
  return videos.empty();
}

//--------------------------------------------------------------

void VideoGrid::update() {
  for (int i = 0; i < videos.size(); i++) {
    videos[i].update();
  }
}

//--------------------------------------------------------------

void VideoGrid::draw() {
  for (int i = 0; i < videos.size(); i++) {
    videos[i].draw();
  }
}

