#include "LoadVideoButton.hpp"

//--------------------------------------------------------------

LoadVideoButton::LoadVideoButton(string imagePath, ImageButtonProps props) {
  imageButton = new ImageButton(imagePath, props);
}

//--------------------------------------------------------------

void LoadVideoButton::update() {
  imageButton->update();
}

//--------------------------------------------------------------

void LoadVideoButton::draw() {
  imageButton->draw();
}

//--------------------------------------------------------------

void LoadVideoButton::setupButton(int backgroundColor, int backgroundColorMouseOver, int backgroundColorMouseDown, float opacity){
  imageButton->setupButton(backgroundColor, backgroundColorMouseOver, backgroundColorMouseDown, opacity);
}

//--------------------------------------------------------------

void LoadVideoButton::attachToEvent(ofEvent<void> loadVideoEvent) {
  imageButton->attachToEvent(loadVideoEvent);
}

//--------------------------------------------------------------

void LoadVideoButton::processOpenFileSelection() {
  // Open the Open File Dialog.
  ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a video file");
  
  // Check if the user opened a file.
  if (openFileResult.bSuccess) {
    
    ofFile videoFile(openFileResult.getPath());

    if (videoFile.exists()) {
      string fileExtension = ofToUpper(videoFile.getExtension());

      // We only want video files.
      if (fileExtension == "MOV" || fileExtension == "MP4" || fileExtension == "MPEG" || fileExtension == "AVI") {
        XMLFileAgent fileAgent = XMLFileAgent();
        
        // Copy file to videos folder.
        string fileName = openFileResult.getName();
        fileAgent.copyFileToVideos(openFileResult.getPath(), fileName);
    
        // Process video and obtain its metadata. This takes ...a while.
        Metadata extractedMetadata = ProcessVideoAgent().process(fileName);
        extractedMetadata.logContent();

        // Save the metadata object to an XML file.
        string xmlFileName = fileAgent.setExtension(fileName, "xml");
        fileAgent.saveMetadataToFile(extractedMetadata, xmlFileName);
        
        // Only after the metadata is extracted and our XML file is built
        // and saved, we can notify newVideoImportedEvent.
        ofNotifyEvent(Events::newVideoImportedEvent, extractedMetadata, this);
      }
    }
  }
}

