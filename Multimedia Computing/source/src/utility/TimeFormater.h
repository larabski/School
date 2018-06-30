#ifndef TimeFormater_h
#define TimeFormater_h

#include <string>

struct TimeFormater {
  
  const int TIME_CONSTANT = 60;
  
  int getSeconds(int totalSeconds) {
    return totalSeconds % TIME_CONSTANT;
  }
  
  int getMinutes(int totalSeconds) {
    return (totalSeconds / TIME_CONSTANT) % TIME_CONSTANT;
  }
  
  std::string formatWithTwoDecimalNumbers(int number) {
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%02d", number);
    const std::string numberToString = buffer;
    return numberToString;
    
  }
  
  int getElapsingBarWidth(int elapsedTime, int totalTime, int totalWidth) {
    return (elapsedTime * totalWidth) / totalTime;
  }
};


#endif /* TimeFormater_h */
