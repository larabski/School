//
//  ProcessVideoAgent.cpp
//  Project-CM
//
//  Created by António Ferreira on 13/05/2018.
//

#include "ProcessVideoAgent.hpp"

//--------------------------------------------------------------

Metadata ProcessVideoAgent::process(string fileName) {
  /**
   Extract everything from the video...
   */
  string extractedDate = processDate(fileName);
  std::map<string, string> wholeVideoExtractions = extractThroughWholeVideo(fileName);

  /**
   And put in into a Metadata object.
   */
  Metadata extractedMetadata = Metadata();
  
  extractedMetadata.setName(fileName);
  extractedMetadata.setDate(extractedDate);
  extractedMetadata.setLuminance(wholeVideoExtractions["Luminance"]);
  extractedMetadata.setColorR(wholeVideoExtractions["ColorR"]);
  extractedMetadata.setColorG(wholeVideoExtractions["ColorG"]);
  extractedMetadata.setColorB(wholeVideoExtractions["ColorB"]);
  extractedMetadata.setEdgeDistribution(wholeVideoExtractions["EdgesPercent"]);
  extractedMetadata.setNumberFaces(wholeVideoExtractions["NumberFaces"]);
  extractedMetadata.setTexture(wholeVideoExtractions["Texture"]);
  extractedMetadata.setRythm(wholeVideoExtractions["Rythm"]);

  return extractedMetadata;
}

//--------------------------------------------------------------

string ProcessVideoAgent::processDate(string fileName) {
  const ofFile fileToRead(ofToDataPath("videos/" + fileName));
  const int BUFFER_SIZE = 20;
  char s[BUFFER_SIZE];
  time_t rawTime = std::filesystem::last_write_time(fileToRead);
  strftime(s, BUFFER_SIZE, "%d/%m/%Y", localtime(&rawTime));
  return string(s);
}

//--------------------------------------------------------------

std::map<string, string> ProcessVideoAgent::extractThroughWholeVideo(string fileName) {
  ofVideoPlayer player;
  player.load("videos/" + fileName);
  
  ofImage image = ofImage();
  const double totalNumberPixels = player.getTotalNumFrames() * (player.getWidth() * player.getHeight());
  
  // Scene Cut Detection/Rythm
  vector<double> averageFrameIntensities;
  double totalFrameIntensity;
  
  // Luminance
  double totalPixelsIntensity = 0;
  
  // Color (1st Moment)
  double totalPixelsRed = 0;
  double totalPixelsGreen = 0;
  double totalPixelsBlue = 0;
  
  // Face Detection
  ofxCvHaarFinder finder = ofxCvHaarFinder();
  finder.setup("other/haarcascade_frontalface_default.xml");
  int highestNumFacesInSingleFrame = 0;
  
  // Edge Dectection
  int meanVerticalVideoEdges = 0;
  
  // TODO: Percentage-based frame skipping.
  int i;
  for (i = 0; i < player.getTotalNumFrames(); i++) {

    player.update();
    player.setFrame(i);
    player.setPaused(true);
    
    totalFrameIntensity = 0;
    
    const ofPixels imagePixels = player.getPixels();
    image.setFromPixels(imagePixels);
    
    // Edge Detection
    meanVerticalVideoEdges += getVerticalEdgesPercentage(image);
  
    // Face Detection
    finder.findHaarObjects(image);
    const int numFacesInCurrentFrame = finder.blobs.size();
    if (numFacesInCurrentFrame > highestNumFacesInSingleFrame) {
      highestNumFacesInSingleFrame = numFacesInCurrentFrame;
    }

    const int numChannels = image.getPixels().getNumChannels();
    const int lineWidth = image.getWidth();
    
    for (int x = 0; x < (int) image.getWidth(); x++) {
      for (int y = 0; y < (int) image.getHeight(); y++) {
        
        // Luminance
        const ofColor color = image.getColor(x, y);
        const double pixelIntensity = color.getLightness();
        totalPixelsIntensity += pixelIntensity;
        
        // Scene Cut Detection / Rythm
        totalFrameIntensity += pixelIntensity;
        
        // Color (1st Moment)
        const int pixelRed = imagePixels[(y * lineWidth + x) * numChannels];
        const int pixelGreen = imagePixels[(y * lineWidth + x) * numChannels + 1];
        const int pixelBlue = imagePixels[(y * lineWidth + x) * numChannels + 2];
        totalPixelsRed += pixelRed;
        totalPixelsGreen += pixelGreen;
        totalPixelsBlue += pixelBlue;
      }
    }
    
    // Calculate a single frames's average intensity.
    averageFrameIntensities.push_back(totalFrameIntensity / (image.getWidth() * image.getHeight()));

  }
  
  // Average Rythm.
  vector<double> intensityDifferences = generateIntensityDifferencesArray(averageFrameIntensities);
  double differencesSum = 0;
  double numDifferencesChecked = intensityDifferences.size();
  for (int i = 0; i < numDifferencesChecked; i++) differencesSum += intensityDifferences[i];
  double rythm = differencesSum / numDifferencesChecked;

  // Extract frame indexes for the representative frames (based on rythm spikes).
  vector<int> representativeIndexes = findRepresentativeFrameIndexes(intensityDifferences);
  // Save these frames as PNGs onto "bin/data/videos".
  string extensionFreeVideoName = XMLFileAgent().getExtensionFreeName(fileName);
  for (int i = 0; i < representativeIndexes.size(); i++) {
    player.setFrame(representativeIndexes[i]);
    ofImage repFrame;
    repFrame.setFromPixels(player.getPixels());
    repFrame.save("videos/" + extensionFreeVideoName + "-R" + std::to_string(i + 1) + ".png");
  }
  
  // Average Luminance.
  const float averageLuminance = totalPixelsIntensity / totalNumberPixels;

  // Average Colors Components.
  const float averageColorRed = totalPixelsRed / totalNumberPixels;
  const float averageColorGreen = totalPixelsGreen / totalNumberPixels;
  const float averageColorBlue = totalPixelsBlue / totalNumberPixels;
  
  // Texture
  ofImage firstVideoFrame;
  player.update();
  player.setFrame(0);
  player.setPaused(true);
  firstVideoFrame.setFromPixels(player.getPixels());
  string textureQuantity = processFirstFrameTexture(firstVideoFrame);
  
  // Average Vertical Video Edges
  meanVerticalVideoEdges = meanVerticalVideoEdges/i;
  
  // Put the results into a map and return it.
  std::map<std::string, string> resultsMap;
  resultsMap["Luminance"] = to_string(averageLuminance);
  resultsMap["ColorR"] = to_string(averageColorRed);
  resultsMap["ColorG"] = to_string(averageColorGreen);
  resultsMap["ColorB"] = to_string(averageColorBlue);
  resultsMap["NumberFaces"] = to_string(highestNumFacesInSingleFrame);
  resultsMap["Rythm"] = to_string(rythm);
  resultsMap["Texture"] = textureQuantity;
  resultsMap["EdgesPercent"] = to_string(meanVerticalVideoEdges);
  return resultsMap;
}

//--------------------------------------------------------------

string ProcessVideoAgent::processFirstFrameTexture(ofImage image) {
  /**
   Convert the input ofImage to grayscale and then to a cv::Mat.
   */
  image.setImageType(ofImageType::OF_IMAGE_GRAYSCALE);
  cv::Mat imageMat = ofxCv::toCv(image);
  
  /** Base config of the Gabor kernel. */
  
  cv::Size kernelSize = cv::Size(5, 5); // Usually odd and a square (e.g. 3x3, 5x5 ...)
  const double gamma = 0.5;             // Spatial aspect ratio.
  const double sigma = 20;              // Standard deviation of the Gaussian function used.
  double theta = 0;                     // Orientation.
  double lambda = 40;                   // Wavelength.
  
  vector<float> means;

  /**
   Create and apply Gabor filters with varying lambda.
   */
  for (int i = 0; i < 6; i++) {
    cv::Mat dst;
    cv::Mat gaborKernel = getGaborKernel(kernelSize, sigma, theta, lambda, gamma);
    cv::filter2D(imageMat, dst, -1, gaborKernel);
    means.push_back(cv::mean(dst)[0]);
    lambda += 10;
  }
  
  lambda = 40;
  
  /**
   Create and apply Gabor filters with varying theta.
   */
  for (int i = 0; i < 4; i++) {
    cv::Mat dst;
    cv::Mat gaborKernel = getGaborKernel(kernelSize, sigma, theta, lambda, gamma);
    cv::filter2D(imageMat, dst, -1, gaborKernel);
    means.push_back(cv::mean(dst)[0]);
    theta += 0.78;
  }
  
  float filtersBankMean = 0.0;
  
  int i;
  for (i = 0; !means.empty(); i++) {
    filtersBankMean += means.back();
    means.pop_back();
  }
  
  float meanTextureValue = filtersBankMean / i;
  string textureQuantity;
  
  if (meanTextureValue <= TEXTURE_LOW) {
    textureQuantity = "Low";
  } else if (meanTextureValue <= TEXTURE_MEDIUM) {
    textureQuantity = "Medium";
  } else {
    textureQuantity = "High";
  }
  
  return textureQuantity;
}

//--------------------------------------------------------------

int ProcessVideoAgent::getVerticalEdgesPercentage(ofImage videoFrame) {
  cv::Mat src;
  cv::Mat srcGray;
  int scale = 1;
  int delta = 0;
  int ddepth = CV_16S;
  
  ofxCvColorImage markImg;
  markImg.allocate(videoFrame.getWidth(), videoFrame.getHeight());
  markImg.setFromPixels(videoFrame.getPixels().getData(), videoFrame.getWidth(), videoFrame.getHeight());
  src = cv::Mat(markImg.getCvImage());
  
  /**
   Apply a Gaussian Blur to remove some noise.
   */
  cv::GaussianBlur(src, src, cv::Size(3,3), 0, 0, cv::BORDER_DEFAULT);
  
  /**
    Convert the colored image matrix to grayscale.
   */
  cv::cvtColor(src, srcGray, CV_BGR2GRAY);
  
  cv::Mat gradX, gradY;
  
  /**
   Apply the horizontal & vertical Scharr kernels.
   */
  cv::Scharr(srcGray, gradX, ddepth, 1, 0, scale, delta, cv::BORDER_DEFAULT);
  cv::Scharr(srcGray, gradY, ddepth, 0, 1, scale, delta, cv::BORDER_DEFAULT);
  
  int numberOfHorizontalEdges = 0;
  int numberOfVerticalEdges = 0;
  
  ofImage verticalEdges;
  ofImage horizontalEdges;
  ofxCv::toOf(gradX, verticalEdges);
  ofxCv::toOf(gradY, horizontalEdges);
  
  /**
   Because we're converting ofxCv mat to ofImage, every pixel on the resulting
   image will be in the [0, 255] interval. But we won't count "weaker" edges.
   */
  int EDGE_ACCEPTANCE_THRESHOLD = 50;
  
  for (int i = 0; i < verticalEdges.getHeight(); i++) {
    for (int j = 0; j < verticalEdges.getWidth(); j++) {
      /**
       R/G/B are the same in a grayscale image, so we just check R.
       */
      if (verticalEdges.getColor(i, j).r >= EDGE_ACCEPTANCE_THRESHOLD) {
        numberOfVerticalEdges++;
      }
      if (horizontalEdges.getColor(i, j).r >= EDGE_ACCEPTANCE_THRESHOLD) {
        numberOfHorizontalEdges++;
      }
    }
  }
  
  int totalEdges = numberOfHorizontalEdges + numberOfVerticalEdges;
  return totalEdges == 0 ? 0 : (int) (numberOfVerticalEdges * 100 / totalEdges);
}

//--------------------------------------------------------------

vector<double> ProcessVideoAgent::generateIntensityDifferencesArray(vector<double> averageFrameIntensities) {
  /**
   A vector that will hold the intensity differences between every examined video frame,
   for a particular video.
   - intensityDifferences[x] will necessarily belong to the [0, 255] interval.
   - intensityDifferences[x] reads: how different in intensity frame <x> is from frame <x-1>.
   */
  vector<double> intensityDifferences;
  /**
   The intensityDifferences[0] should always be 0; i.e. difference in intensity from frame 0 to frame... 0?.
   */
  intensityDifferences.push_back(0);
  for (int i = 1; i < averageFrameIntensities.size(); i++) {
    double previousFrameIntensity = averageFrameIntensities[i - 1];
    double currentFrameIntensity = averageFrameIntensities[i];
    double absoluteDifference = std::abs(currentFrameIntensity - previousFrameIntensity);
    intensityDifferences.push_back(absoluteDifference);
  }
  return intensityDifferences;
}

//--------------------------------------------------------------

vector<int> ProcessVideoAgent::findRepresentativeFrameIndexes(vector<double> differences) {
  vector<int> representativeFrameIndexes;
  const int NUM_REPRESENTATIVE_FRAMES = 5;
  for (int i = 0; i < NUM_REPRESENTATIVE_FRAMES; i++) {
    int maxElementIndex = std::max_element(differences.begin(), differences.end()) - differences.begin();
    representativeFrameIndexes.push_back(maxElementIndex);
    // Remove the just-found value (to calc the next max).
    differences.erase(differences.begin() + maxElementIndex);
  }
  // Sort them by frame index (otherwise it would be weird).
  std::sort(representativeFrameIndexes.begin(), representativeFrameIndexes.end());
  return representativeFrameIndexes;
}
