//
//  ImportableFilterItem.hpp
//  Project-CM
//
//  Created by Francisco Cunha on 27/05/2018.
//

#ifndef ImportableFilterItem_hpp
#define ImportableFilterItem_hpp

#include <stdio.h>
#include <string.h>
#include "Colors.h"
#include "ofxDatGui.h"
#include "Dimensions.h"
#include "XMLFileAgent.hpp"

class ImportableFilterItem {
  
public:
  
  ImportableFilterItem(ofxDatGuiComponent*, bool, int, int);
  
  void update();
  void draw();
  
  bool isEnabled();
  void toggleEnabled(ofxDatGuiButtonEvent event);
  ofxDatGuiComponent *getComponent();
  
  std::string getFilePath();
  
private:
  
  int x;
  int y;
  bool enabled;
  ofxDatGuiButton *toggle;
  ofxDatGuiButton *importImageButton;
  ofxDatGuiComponent *component;
  
  std::string fileName;
  std::string filePath;
  
  void setupToggle();
  void setupComponent();
  void setupImportImageButton();
  void importClicked(ofxDatGuiButtonEvent event);
  
  std::string NO_FILE = ":: NO FILE ::";

};

#endif /* ImportableFilterItem_hpp */
