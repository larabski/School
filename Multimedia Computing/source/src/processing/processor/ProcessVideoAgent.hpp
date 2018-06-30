//
//  ProcessVideoAgent.hpp
//  Project-CM
//
//  Created by António Ferreira on 13/05/2018.
//

#ifndef ProcessVideoAgent_hpp
#define ProcessVideoAgent_hpp

#include <stdio.h>
#include <string.h>
#include "ofMain.h"
#include "Metadata.hpp"
#include "XMLFileAgent.hpp"
#include "ofxCv.h"

// OpenCV
#include "ofxCvHaarFinder.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class ProcessVideoAgent {
  
public:
  
  /**
   Processes a video file once it has been imported onto the app. the file name should include the extension, e.g. process("myVideo.mp4").
   */
  Metadata process(string);
  
  const int TEXTURE_LOW = 5;
  const int TEXTURE_MEDIUM = 10;
  
private:
  
  /**
   Extract the file's date and return it as a string "DD/MM/YYYY".
   This operation does not require full-video traversals.
   */
  string processDate(string);
  
  /**
   To make this whole extraction process a bit more efficient, we'll handle every extraction
   that requires full-video walkthrough in a single place (this method). Even though it will be a huge,
   ugly method, it's much more time and space efficient that separating every extraction and iterating
   through the whole thing every single time... Here we'll handle:
   
   - Luminance extraction
   - Color (1st moment) extraction
   - Number of Faces extraction
   - Edge Distribution extraction
   - Rythm extraction
   
   The output will be a string-to-string map like this:
   - "Luminance" --> "some value"
   - "ColorR" --> "some value"
   - ... repeat for all the rest ...
   */
  std::map<string, string> extractThroughWholeVideo(string);
  
  // Helper Methods
  
  int getVerticalEdgesPercentage(ofImage);
  
  string processFirstFrameTexture(ofImage);
  
  vector<double> generateIntensityDifferencesArray(vector<double>);
  
  vector<int> findRepresentativeFrameIndexes(vector<double>);

};

#endif /* ProcessVideoAgent_hpp */
