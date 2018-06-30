#ifndef Dimensions_h
#define Dimensions_h

namespace Dimensions {
  
  // Window.
  const int WINDOW_WIDTH = 1032;
  const int WINDOW_HEIGHT = 644;
  
  // Upper tabs & import button.
  const int IMPORT_FILE_BUTTON_WIDTH = 40;
  
  const int NUM_LARGE_TABS = 2;
  const int NUM_SMALL_TABS = 2;
  const int LARGE_TAB_WIDTH = (WINDOW_WIDTH / 1.55) / NUM_LARGE_TABS;
  const int SMALL_TAB_WIDTH = (WINDOW_WIDTH - (NUM_LARGE_TABS * LARGE_TAB_WIDTH) - IMPORT_FILE_BUTTON_WIDTH) / NUM_SMALL_TABS;
  const int TAB_HEIGHT = 26;
  
  // MainState's Properties Section.
  const int PROPERTIES_SECTION_WIDTH = 2 * LARGE_TAB_WIDTH + IMPORT_FILE_BUTTON_WIDTH;
  const int PROPERTIES_SECTION_HEIGHT = 444;
  
  // MainState's Video Section.
  const int VIDEO_SECTION_WIDTH = (NUM_LARGE_TABS * LARGE_TAB_WIDTH) + IMPORT_FILE_BUTTON_WIDTH;
  const int VIDEO_SECTION_HEIGHT = 444;
  
  // MainState's Timeline Section.
  const int TIMELINE_SECTION_HEIGHT = WINDOW_HEIGHT - PROPERTIES_SECTION_HEIGHT;
  
  // Other.
  const int UI_PANEL_PADDING = 15;

}

#endif
