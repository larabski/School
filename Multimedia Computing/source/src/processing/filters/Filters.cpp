//
//  Filters.cpp
//  Project-CM
//
//  Created by Francisco Cunha on 15/05/2018.
//

#include "Filters.hpp"

//--------------------------------------------------------------

bool Filters::acceptsVideo(Metadata videoMetadata) {
  return acceptableDate(videoMetadata)
    && acceptableLuminance(videoMetadata)
    && acceptableColorR(videoMetadata)
    && acceptableColorG(videoMetadata)
    && acceptableColorB(videoMetadata)
    && acceptableEdgeDistribution(videoMetadata)
    && acceptableNumberFaces(videoMetadata)
    && acceptableTexture(videoMetadata)
    && acceptableRythm(videoMetadata)
    /** Full usage of short-circuiting. */
    && acceptableNumTimesObjectAppears(videoMetadata);
}

//--------------------------------------------------------------

bool Filters::acceptableDate(Metadata videoMetadata) {
  if (fromDate == "DISABLED" && untilDate == "DISABLED") return true;
  string videoDate = videoMetadata.getDate();
  bool acceptableFromDate = equalOrMoreRecent(videoDate, fromDate);
  bool acceptableUntilDate = equalOrMoreRecent(untilDate, videoDate);
  return acceptableFromDate && acceptableUntilDate;
}

//--------------------------------------------------------------

bool Filters::acceptableLuminance(Metadata videoMetadata) {
  if (luminance == "DISABLED") return true;
  const int inputLuminance = std::stoi(luminance);
  const int videoLuminance = std::stoi(videoMetadata.getLuminance());
  const int acceptableMin = inputLuminance - 20;
  const int acceptableMax = inputLuminance + 20;
  return videoLuminance >= acceptableMin && videoLuminance <= acceptableMax;
}

//--------------------------------------------------------------

bool Filters::acceptableColorR(Metadata videoMetadata) {
  if (colorR == "DISABLED") return true;
  const int inputColorR = std::stoi(colorR);
  const int videoColorR = std::stoi(videoMetadata.getColorR());
  const int acceptableMin = inputColorR - 20;
  const int acceptableMax = inputColorR + 20;
  return videoColorR >= acceptableMin && videoColorR <= acceptableMax;
}

//--------------------------------------------------------------

bool Filters::acceptableColorG(Metadata videoMetadata) {
  if (colorG == "DISABLED") return true;
  const int inputColorG = std::stoi(colorG);
  const int videoColorG = std::stoi(videoMetadata.getColorG());
  const int acceptableMin = inputColorG - 20;
  const int acceptableMax = inputColorG + 20;
  return videoColorG >= acceptableMin && videoColorG <= acceptableMax;
}

//--------------------------------------------------------------

bool Filters::acceptableColorB(Metadata videoMetadata) {
  if (colorB == "DISABLED") return true;
  const int inputColorB = std::stoi(colorB);
  const int videoColorB = std::stoi(videoMetadata.getColorB());
  const int acceptableMin = inputColorB - 20;
  const int acceptableMax = inputColorB + 20;
  return videoColorB >= acceptableMin && videoColorB <= acceptableMax;
}

//--------------------------------------------------------------

bool Filters::acceptableEdgeDistribution(Metadata videoMetadata) {
  if (edgeDistribution == "DISABLED") return true;
  const int inputEdgeDist = std::stoi(edgeDistribution);
  const int videoEdgeDist = std::stoi(videoMetadata.getEdgeDistribution());
  const int acceptableMin = inputEdgeDist - 10;
  const int acceptableMax = inputEdgeDist + 10;
  return videoEdgeDist >= acceptableMin && videoEdgeDist <= acceptableMax;
}

//--------------------------------------------------------------

bool Filters::acceptableNumberFaces(Metadata videoMetadata) {
  if (numberFaces == "DISABLED") return true;
  const int inputNumberFaces = std::stoi(numberFaces);
  const int videoNumberFaces = std::stoi(videoMetadata.getNumberFaces());
  const int acceptableMin = inputNumberFaces - 1;
  const int acceptableMax = inputNumberFaces + 1;
  return videoNumberFaces >= acceptableMin && videoNumberFaces <= acceptableMax;
}

//--------------------------------------------------------------

bool Filters::acceptableTexture(Metadata videoMetadata) {
  string inputTexture = texture.substr(0, texture.find(' '));
  cout << inputTexture << "\n";
  return inputTexture == "DISABLED" || inputTexture == videoMetadata.getTexture();
}

//--------------------------------------------------------------

bool Filters::acceptableRythm(Metadata videoMetadata) {
  if (rythm == "DISABLED") return true;
  const double inputRythm = std::stod(rythm);
  const double videoRythm = std::stod(videoMetadata.getRythm());
  const double acceptableMin = inputRythm - 0.15;
  const double acceptableMax = inputRythm + 0.15;
  return videoRythm >= acceptableMin && videoRythm <= acceptableMax;
}

//--------------------------------------------------------------

bool Filters::acceptableNumTimesObjectAppears(Metadata videoMetadata) {
  if (imageToCheckAgainstPath == "DISABLED") return true;
  const int inputNumTimes = this->numTimesAppearsUpperBound;
  const int numTimesItAppearsOnVideo = calcTimesObjectAppearsInVideo(videoMetadata);
  const int acceptableMin = inputNumTimes - 1;
  const int acceptableMax = inputNumTimes + 1;
  return numTimesItAppearsOnVideo >= acceptableMin && numTimesItAppearsOnVideo <= acceptableMax;
}

//--------------------------------------------------------------

int Filters::calcTimesObjectAppearsInVideo(Metadata videoMetadata) {
  /**
   Load the video.
   */
  ofVideoPlayer player;
  player.load("videos/" + videoMetadata.getName());
  
  /**
   Convert the image to check against into a grayscale cv::Mat.
   */
  ofImage imageToCheckAgainst;
  imageToCheckAgainst.load(this->imageToCheckAgainstPath);
  imageToCheckAgainst.setImageType(ofImageType::OF_IMAGE_GRAYSCALE);
  cv::Mat checkAgainsMat = ofxCv::toCv(imageToCheckAgainst);
  
  ofImage frame;
  /** 20+ good matches in a single frame are counted as an appearance. */
  const int APPEARENCE_THRESHOLD = 20;
  int totalTimesObjectAppears = 0;

  /**
   This is the only place where we actually skip frames, because this is
   done in runtime multiple times (and not only in the initial processing
   step, like all other filters...).
   */
  for (int i = 0; i < player.getTotalNumFrames(); i += 20) {
    player.update();
    player.setFrame(i);
    player.setPaused(true);
    
    const ofPixels imagePixels = player.getPixels();
    frame.setFromPixels(imagePixels);
    frame.setImageType(ofImageType::OF_IMAGE_GRAYSCALE);
    cv::Mat frameMat = ofxCv::toCv(frame);
    
    cv::SurfFeatureDetector detector(400);
    vector<cv::KeyPoint> keypoints1, keypoints2;
    detector.detect(checkAgainsMat, keypoints1);
    detector.detect(frameMat, keypoints2);
    
    cv::SurfDescriptorExtractor extractor;
    cv::Mat descriptors1, descriptors2;
    extractor.compute(checkAgainsMat, keypoints1, descriptors1);
    extractor.compute(frameMat, keypoints2, descriptors2);
    
    if (descriptors1.empty() || descriptors2.empty()) continue;
    
    cv::BFMatcher matcher(cv::NORM_L2, true);
    cv::vector<cv::DMatch> allMatches;
    matcher.match(descriptors1, descriptors2, allMatches);
    
    // Now that we have ALL matches, filter wich ones are worth using...
    
    std::vector<cv::DMatch> goodMatches;
    for (int i = 0; i < allMatches.size() - 1; i++) {
      cv::DMatch current = allMatches[i];
      cv::DMatch next = allMatches[i + 1];
      if (current.distance < 0.75 * next.distance) {
        goodMatches.push_back(current);
      }
    }
    if (goodMatches.size() >= APPEARENCE_THRESHOLD) {
      totalTimesObjectAppears++;
    }
  }
  return totalTimesObjectAppears;
}

//--------------------------------------------------------------

void Filters::setFromDate(string date) {
  this->fromDate = date;
}

//--------------------------------------------------------------

void Filters::setUntilDate(string date) {
  this->untilDate = date;
}

//--------------------------------------------------------------

void Filters::setColorR(string color) {
  this->colorR = color;
}

//--------------------------------------------------------------

void Filters::setColorG(string color) {
  this->colorG = color;
}

//--------------------------------------------------------------

void Filters::setColorB(string color) {
  this->colorB = color;
}

//--------------------------------------------------------------

void Filters::setLuminance(string luminance) {
  this->luminance = luminance;
}

//--------------------------------------------------------------

void Filters::setEdgeDistribution(string edgeDistribution) {
  this->edgeDistribution = edgeDistribution;
}

//--------------------------------------------------------------

void Filters::setNumberFaces(string numberFaces) {
  this->numberFaces = numberFaces;
}

//--------------------------------------------------------------

void Filters::setTexture(string texture) {
  this->texture = texture;
}

//--------------------------------------------------------------

void Filters::setRythm(string rythm) {
  this->rythm = rythm;
}

//--------------------------------------------------------------

void Filters::setTargetNumTimesObjectAppears(string imagePath, int numTimes) {
  this->imageToCheckAgainstPath = imagePath;
  this->numTimesAppearsUpperBound = numTimes;
}

//--------------------------------------------------------------

bool Filters::equalOrMoreRecent(string date1, string date2) {
  string normalizedDate1 = date1.substr(6, 4) + "/" + date1.substr(0, 2) + "/" + date1.substr(3, 2);
  string normalizedDate2 = date2.substr(6, 4) + "/" + date2.substr(0, 2) + "/" + date2.substr(3, 2);
  return normalizedDate1 >= normalizedDate2;
}
