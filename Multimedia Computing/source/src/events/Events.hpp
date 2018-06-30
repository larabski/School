//
//  AppEvents.hpp
//  Project-CM
//
//  Created by Francisco Cunha on 13/05/2018.
//

#ifndef AppEvents_hpp
#define AppEvents_hpp

#include <stdio.h>
#include "Metadata.hpp"

namespace Events {
  /**
   Tab Events.
   */
  extern ofEvent<void> allClipsTabClickEvent;
  extern ofEvent<void> timelineClipsTabClickEvent;
  extern ofEvent<void> filtersTabClickEvent;
  extern ofEvent<void> videoSettingsTabClickEvent;
  /**
   Video (Grid Item) Events.
   */
  extern ofEvent<Metadata> videoSingleClickEvent;
  extern ofEvent<Metadata> videoGridItemHoverEvent;
  extern ofEvent<Metadata> videoGridItemRemovedEvent;
  extern ofEvent<Metadata> newVideoImportedEvent;
  /**
   Video (Row Item) Events.
   */
  extern ofEvent<Metadata> videoRowItemHoverEvent;
  extern ofEvent<Metadata> videoRowItemLeftButtonClick;
  extern ofEvent<Metadata> videoRowItemRightButtonClick;
  /**
   Video Player Events
   */
  extern ofEvent<void> playButtonClickEvent;
  extern ofEvent<void> pauseButtonClickEvent;
  extern ofEvent<void> stopButtonClickEvent;
  extern ofEvent<void> playbackStopEvent;
  /**
   Other Events.
   */
  extern ofEvent<void> loadVideoEvent;
  extern ofEvent<vector<Metadata>> filtersAppliedEvent;
  extern ofEvent<vector<string>> playTimelineButtonClickEvent;
  extern ofEvent<vector<string>> playVideoButtonClickEvent;
  extern ofEvent<bool> fadeButtonSelectedEvent;

}

#endif /* AppEvents_hpp */
