//
//  AppEvents.cpp
//  Project-CM
//
//  Created by Francisco Cunha on 13/05/2018.
//

#include "Events.hpp"

namespace Events {
  /**
   Tab Events.
   */
  ofEvent<void> allClipsTabClickEvent = ofEvent<void>();
  ofEvent<void> timelineClipsTabClickEvent = ofEvent<void>();
  ofEvent<void> filtersTabClickEvent = ofEvent<void>();
  ofEvent<void> videoSettingsTabClickEvent = ofEvent<void>();
  /**
   Video (Grid Item) Events.
   */
  ofEvent<Metadata> videoSingleClickEvent = ofEvent<Metadata>();
  ofEvent<Metadata> videoGridItemHoverEvent = ofEvent<Metadata>();
  ofEvent<Metadata> videoGridItemRemovedEvent = ofEvent<Metadata>();
  ofEvent<Metadata> newVideoImportedEvent = ofEvent<Metadata>();
  /**
   Video (Row Item) Events.
   */
  ofEvent<Metadata> videoRowItemHoverEvent = ofEvent<Metadata>();
  ofEvent<Metadata> videoRowItemLeftButtonClick = ofEvent<Metadata>();
  ofEvent<Metadata> videoRowItemRightButtonClick = ofEvent<Metadata>();
  /**
   Video Player Events
   */
  ofEvent<void> playButtonClickEvent = ofEvent<void>();
  ofEvent<void> pauseButtonClickEvent = ofEvent<void>();
  ofEvent<void> stopButtonClickEvent = ofEvent<void>();
  ofEvent<void> playbackStopEvent = ofEvent<void>();
  /**
   Other Events.
   */
  ofEvent<void> loadVideoEvent = ofEvent<void>();
  ofEvent<vector<Metadata>> filtersAppliedEvent = ofEvent<vector<Metadata>>();
  ofEvent<vector<string>> playTimelineButtonClickEvent = ofEvent<vector<string>>();
  ofEvent<vector<string>> playVideoButtonClickEvent = ofEvent<vector<string>>();
  ofEvent<bool> fadeButtonSelectedEvent = ofEvent<bool>();
  
}
