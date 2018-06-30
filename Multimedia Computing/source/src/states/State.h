#ifndef State_h
#define State_h

class State {
  
public:
  
  virtual ~State() {}
  virtual void setup() = 0;
  virtual void update() = 0;
  virtual void draw() = 0;
  
};

#endif /* State_h */
