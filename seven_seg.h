#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

struct SevenSegmentDisplay {
  int segmentAPin;
  int segmentBPin;
  int segmentCPin;
  int segmentDPin;
  int segmentEPin;
  int segmentFPin;
  int segmentGPin;
};

extern SevenSegmentDisplay display;

void setupSevenSegmentDisplay();
void displayDigit(int digit);
void clearDisplay();

#endif // SEVEN_SEGMENT_H
