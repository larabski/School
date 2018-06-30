//
//  Filters.hpp
//  Project-CM
//
//  Created by Francisco Cunha on 15/05/2018.
//

#ifndef Filters_hpp
#define Filters_hpp

#include <stdio.h>
#include <string>
#include "ofMain.h"
#include "Metadata.hpp"

// OpenCV & ofxCV
#include "ofxCV.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp> // FOR SURF (because of our OpenCV version)
#include <opencv2/legacy/legacy.hpp>      // FOR BRUTE FORCE MATCHING (because of our OpenCV version)

/**
 A Filters object representes the values of all filters applied in
 a given moment in time after the "Apply Filters" button is clicked.
 ------------------------------------------------------------------------
 This is very similar to a Metadata object. The differences are:
 - Here we don't have a name field.
 - Here we need a custom "equals".
 - We will also use this class to check if a video's metadata matches the
 filter parameters well enough to make it to the generated timeline.
 ------------------------------------------------------------------------
 */
class Filters {
  
public:
  
  void setFromDate(std::string);
  void setUntilDate(std::string);
  void setColorR(std::string);
  void setColorG(std::string);
  void setColorB(std::string);
  void setLuminance(std::string);
  void setEdgeDistribution(std::string);
  void setNumberFaces(std::string);
  void setTexture(std::string);
  void setRythm(std::string);
  
  /**
   When the "Number of Times a Specific Object Appears" filter is active,
   the Filters object needs to know the image's path and the number of times
   we want the object to appear.
   */
  void setTargetNumTimesObjectAppears(std::string, int);

  /**
   Returns whether or not the given video metadata match the filters' parameters well enough
   to make it to the generated timeline.
   */
  bool acceptsVideo(Metadata);
  
private:
  
  std::string fromDate;
  std::string untilDate;
  std::string colorR;
  std::string colorG;
  std::string colorB;
  std::string luminance;
  std::string edgeDistribution;
  std::string numberFaces;
  std::string texture;
  std::string rythm;
  
  /**
   Specifically for the "Num Times Object Appears" filter. This is the
   only filter that needs processing in runtime after the initial import...
   */
  std::string imageToCheckAgainstPath;
  int numTimesAppearsUpperBound;
  
  /**
   Utility methods that will be called onlu on #acceptsVideo.
   */
  
  bool acceptableDate(Metadata);
  bool equalOrMoreRecent(string, string);
  
  bool acceptableLuminance(Metadata);
  bool acceptableEdgeDistribution(Metadata);
  bool acceptableNumberFaces(Metadata);
  bool acceptableColorR(Metadata);
  bool acceptableColorG(Metadata);
  bool acceptableColorB(Metadata);
  bool acceptableTexture(Metadata);
  bool acceptableRythm(Metadata);
  
  bool acceptableNumTimesObjectAppears(Metadata);
  int calcTimesObjectAppearsInVideo(Metadata);
  
};

#endif /* Filters_hpp */
