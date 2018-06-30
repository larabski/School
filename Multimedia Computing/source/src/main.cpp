#include "ofMain.h"
#include "ofApp.h"
#include "Dimensions.h"

//--------------------------------------------------------------

int main() {
  ofGLFWWindowSettings settings;
  settings.resizable = false;
  settings.width = Dimensions::WINDOW_WIDTH;
  settings.height = Dimensions::WINDOW_HEIGHT;
  ofCreateWindow(settings);
  ofRunApp(new ofApp());
}
