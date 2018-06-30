//
//  XMLFileAgent.hpp
//  Project-CM
//
//  Created by Francisco Cunha on 04/05/2018.
//

#ifndef XMLFileAgent_hpp
#define XMLFileAgent_hpp

#include <stdio.h>
#include <string>
#include "Metadata.hpp"

class XMLFileAgent {
  
public:
  
  XMLFileAgent();
  
  /**
   Transform a Metadata object into a XML file and save it with the desired name.
   Returns whether or not the saving operation was successful.
   - The string is of type "test.xml".
   */
  bool saveMetadataToFile(Metadata, std::string);
  
  /**
   Load an XML file located at a given path and map its values onto
   a brand new Metadata object.
   - The string passed is of type "myVideo.mp4" or whatever video file format.
   - The string that is actually loaded is "myVideo.xml".
   */
  Metadata loadMetadataForVideo(std::string);
  
  /**
   Calls Metadata#loadMetadataForVideo for all videos.
   */
  vector<Metadata> loadMetadataForAllVideos();
  
  /**
   Copy file with Path=filePath and Name=name, from the system to our app's video folder.
   */
  void copyFileToVideos(string filePath, string name);
  
  /**
   Delete everything related to the video passed:
   - The video file itself (e.g. myVideo.mp4)
   - The video's XML file (e.g. myVideo.xml)
   - All of the video's representative frames (myVideo-R1.png, myVideo-R2.png, ...).
   */
  void deleteEverythingForVideo(std::string);
  
  /**
   Get a vector with the names of all the video files that exist in bin/data/videos/.
   Note that #getName is used, and not #getPath. Thus, each name will be of the type
   "myVideo1.mp4" and not "videos/myVideo1.mp4"!
   */
  vector<string> getVideoFileNames();
  
  /**
   Get a vector with the names of all representative frame name for a specific video. If the video is called myVideo.mp4,
   the result will be something like ["myVideo-Rep1.png", "myVideo-Rep2.png", ...].
   */
  vector<string> getRepresentativeFrameNamesForVideo(std::string);
  
  /**
   Returns the name of the image file that will be used as a thumbnail
   for the given video. The name will be of type "videoName-RX.png"."
   */
  string getThumbnailNameForVideo(std::string);
  
  /**
   Takes a string such as "myVideo.mp4" and returns another string named "myVideo.xxx",
   where xxx is the desired extension.
   E.g.: setExtension("myVideo.mp4", "xml") --> "myVideo.xml".
   */
  std::string setExtension(std::string, std::string);
  
  /**
   Returns a file name without the extension.
   E.g. "myVideo.mp4" --> "myVideo".
   */
  std::string getExtensionFreeName(std::string);
  
private:

  ofxXmlSettings settings;
  ofDirectory directory;
  
};

#endif /* XMLFileAgent_hpp */
