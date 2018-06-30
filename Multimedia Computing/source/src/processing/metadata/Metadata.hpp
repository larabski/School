//
//  Metadata.hpp
//  Project-CM
//
//  Created by Francisco Cunha on 04/05/2018.
//

#ifndef Metadata_hpp
#define Metadata_hpp

#include <stdio.h>
#include <string.h>
#include "ofxXmlSettings.h"

class Metadata {
  
public:
  
  Metadata();
  
  /**
   Convenience constructor to pass in the name and sectionName.
   */
  Metadata(string, string);
  
  void setName(std::string);
  void setDate(std::string);
  void setColorR(std::string);
  void setColorG(std::string);
  void setColorB(std::string);
  void setLuminance(std::string);
  void setEdgeDistribution(std::string);
  void setNumberFaces(std::string);
  void setTexture(std::string);
  void setRythm(std::string);
  
  /**
   Dirty hack! Not actually saved to/loaded from XML files.
   */
  void setSectionName(std::string);

  std::string getName();
  std::string getDate();
  std::string getColorR();
  std::string getColorG();
  std::string getColorB();
  std::string getLuminance();
  std::string getEdgeDistribution();
  std::string getNumberFaces();
  std::string getTexture();
  std::string getRythm();
  
  /**
   Dirty hack! Not actually saved to/loaded from XML files.
   */
  std::string getSectionName();
  
  /**
   Convenience function to log the values of each field.
   */
  void logContent();
  
private:
  
  std::string name;
  std::string date;
  std::string colorR;
  std::string colorG;
  std::string colorB;
  std::string luminance;
  std::string edgeDistribution;
  std::string numberFaces;
  std::string texture;
  std::string rythm;
  
  /**
   Dirty hack! Not actually saved to/loaded from XML files.
   */
  std::string sectionName;
  
};

#endif /* Metadata_hpp */
