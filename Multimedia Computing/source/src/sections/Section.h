#ifndef Section_h
#define Section_h

#include "Bounds.h"
#include "ofMain.h"

class Section {
  
public:
  
  virtual ~Section() {}
  virtual void setup() = 0;
  virtual void update() = 0;
  virtual void draw() = 0;
  
protected:
  
  Bounds bounds;

};

#endif /* Section_h */
