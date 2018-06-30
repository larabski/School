#ifndef Tab_hpp
#define Tab_hpp

#include <stdio.h>
#include <string>
#include "ofxDatGui.h"
#include "Colors.h"
#include "Dimensions.h"

class Tab {
  
public:
  
  /**
   The constructor takes in (label text, x, y).
   */
  Tab(std::string, int, int, bool);

  void setActive();
  void setInactive();
  void update();
  void draw();
  
  /**
   We attach a data-free #ofEvent to each of our tabs in order to define
   the tab's tabButton#onButtonEvent. When the button is clicked, the tab itself will
   fire the event (through #ofNotifyEvent), and the interested listeners will react accordingly.
   */
  void attachToEvent(ofEvent<void> event);
  
  /**
   This is the function that will actually broadcast the attachedEvent.
   The ofxDatGuiButtonEvent passed as parameter is NOT actually used. However,
   it cannot be removed due to the original mehtod signature:
   void (ListenerClass::*listenerMethod)(args)
   */
  void onTabClicked(ofxDatGuiButtonEvent event);
  
  bool isActive();

private:

  /**
   The tab itself is not a ofxDatGuiComponent. Thus, in order to listen to input events,
   we need to address those events to the ofxDatGuiButton "underneath" it.
   */
  ofxDatGuiButton *tabButton;
  ofEvent<void> attachedEvent;
  bool active;
  
};

#endif /* Tab_hpp */
