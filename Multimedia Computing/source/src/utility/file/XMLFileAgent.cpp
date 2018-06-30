//
//  XMLFileAgent.cpp
//  Project-CM
//
//  Created by Francisco Cunha on 04/05/2018.
//

#include "XMLFileAgent.hpp"

//--------------------------------------------------------------

XMLFileAgent::XMLFileAgent() {
  directory = ofDirectory("videos/");
}

//--------------------------------------------------------------

bool XMLFileAgent::saveMetadataToFile(Metadata metadata, std::string fileName) {
  /**
   Save each setting onto an XML file.
   */
  settings.setValue("metadata:name", metadata.getName());
  settings.setValue("metadata:luminance", metadata.getLuminance());
  settings.setValue("metadata:date", metadata.getDate());
  settings.setValue("metadata:colorR", metadata.getColorR());
  settings.setValue("metadata:colorG", metadata.getColorG());
  settings.setValue("metadata:colorB", metadata.getColorB());
  settings.setValue("metadata:faces", metadata.getNumberFaces());
  settings.setValue("metadata:texture", metadata.getTexture());
  settings.setValue("metadata:rythm", metadata.getRythm());
  settings.setValue("metadata:edges", metadata.getEdgeDistribution());
  /**
   (Try to) save the file and return whether or not it was successful.
   */
  return settings.saveFile("videos/" + fileName);
}

//--------------------------------------------------------------

Metadata XMLFileAgent::loadMetadataForVideo(std::string videoName) {
  /**
   Load the XML file. If the video is called "myVideo.mp4", the XML is "myVideo.xml".
   */
  string metadataFileName = setExtension(videoName, "xml");
  settings.loadFile("videos/" + metadataFileName);
  /**
   Create a new Metadata object and populate it with the stuff read from the XML file.
   */
  Metadata metadata = Metadata();
  metadata.setName(videoName);
  metadata.setDate(settings.getValue("metadata:date", "NONE"));
  metadata.setLuminance(settings.getValue("metadata:luminance", "NONE"));
  metadata.setColorR(settings.getValue("metadata:colorR", "NONE"));
  metadata.setColorG(settings.getValue("metadata:colorG", "NONE"));
  metadata.setColorB(settings.getValue("metadata:colorB", "NONE"));
  metadata.setNumberFaces(settings.getValue("metadata:faces", "NONE"));
  metadata.setTexture(settings.getValue("metadata:texture", "NONE"));
  metadata.setRythm(settings.getValue("metadata:rythm", "NONE"));
  metadata.setEdgeDistribution(settings.getValue("metadata:edges", "NONE"));
  
  return metadata;
}

//--------------------------------------------------------------

vector<Metadata> XMLFileAgent::loadMetadataForAllVideos() {
  vector<Metadata> allMetadatas;
  vector<string> videoNames = getVideoFileNames();
  for (int i = 0; i < videoNames.size(); i++) {
    const Metadata videoMetadata = loadMetadataForVideo(videoNames[i]);
    allMetadatas.push_back(videoMetadata);
  }
  return allMetadatas;
}

//--------------------------------------------------------------

vector<string> XMLFileAgent::getVideoFileNames() {
  directory.allowExt("mov");
  directory.allowExt("mp4");
  directory.allowExt("mpeg");
  directory.allowExt("avi");
  directory.listDir();
  directory.sort();

  vector<string> fileNames;
  fileNames.assign(directory.size(), string());
  for (int i = 0; i < (int) directory.size(); i++) {
    fileNames[i] = directory.getName(i);
  }
  
  return fileNames;
}

//--------------------------------------------------------------

vector<string> XMLFileAgent::getRepresentativeFrameNamesForVideo(string videoName) {
  vector<string> repFrameNames;
  string extensionFreeName = getExtensionFreeName(videoName);
  const int NUM_REP_FRAMES = 5;
  for (int i = 0; i < NUM_REP_FRAMES; i++) {
    /** Frames are named "myVideo-R1.png", "myVideo-R2.png"... */
    string frameName = "videos/" + extensionFreeName + "-R" + std::to_string(i + 1) + ".png";
    repFrameNames.push_back(frameName);
  }
  return repFrameNames;
}

//--------------------------------------------------------------

string XMLFileAgent::getThumbnailNameForVideo(string videoName) {
  return getRepresentativeFrameNamesForVideo(videoName)[0];
}

//--------------------------------------------------------------

void XMLFileAgent::copyFileToVideos(string filePath, string name){
  boost::filesystem::path from = filePath;
  boost::filesystem::path to = ofDirectory("videos/").getAbsolutePath() + "/" + name;
  boost::filesystem::copy_file(from, to);
}

//--------------------------------------------------------------

void XMLFileAgent::deleteEverythingForVideo(std::string fileName) {
  /**
   Delete the video file itself (e.g. "myVideo.mp4").
   */
  string videoFileName = "videos/" + fileName;
  ofFile().removeFile(videoFileName);
  /**
   Delete the XML file (e.g. "myVideo.xml").
   */
  string xmlFileName = setExtension(videoFileName, "xml");
  ofFile().removeFile(xmlFileName);
  /**
   Delete the representative frames (e.g. "myVideo-R1.png", ...).
   */
  string extensionFreeVideoName = getExtensionFreeName(fileName);
  const int NUM_REP_FRAMES = 5;
  for (int i = 0; i < NUM_REP_FRAMES; i++) {
    string repFrameName = "videos/" + extensionFreeVideoName + "-R" + std::to_string(i + 1) + ".png";
    ofFile().removeFile(repFrameName);
  }
}

//--------------------------------------------------------------

std::string XMLFileAgent::getExtensionFreeName(std::string fileName) {
  size_t pos = fileName.find_last_of(".");
  if (pos == std::string::npos) throw;
  return fileName.substr(0, pos);
}

//--------------------------------------------------------------

std::string XMLFileAgent::setExtension(std::string myString, std::string newExtension) {
  std::string extensionFreeString = getExtensionFreeName(myString);
  return extensionFreeString + "." + newExtension;
}
