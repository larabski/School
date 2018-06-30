#ifndef LoadVideoButton_hpp
#define LoadVideoButton_hpp

#include <stdio.h>
#include "ImageButtonProps.h"
#include "Events.hpp"
#include "ImageButton.hpp"
#include "XMLFileAgent.hpp"
#include "ProcessVideoAgent.hpp"

class LoadVideoButton {
  
public:
  
  LoadVideoButton(std::string, ImageButtonProps);
  
  void update();
  void draw();
  void attachToEvent(ofEvent<void> event);
  void setupButton(int backgroundColor, int backgroundColorMouseOver, int backgroundColorMouseDown, float opacity);
  void processOpenFileSelection();
  
private:
  
  ImageButton *imageButton;
  
};

#endif /* LoadVideoButton_hpp */
