#include "Arduino.h"
#include "seven_seg.h"

SevenSegmentDisplay display = {
  51, 53, 50, 48, 46, 49, 47
};

void setupSevenSegmentDisplay() {
  pinMode(display.segmentAPin, OUTPUT);
  pinMode(display.segmentBPin, OUTPUT);
  pinMode(display.segmentCPin, OUTPUT);
  pinMode(display.segmentDPin, OUTPUT);
  pinMode(display.segmentEPin, OUTPUT);
  pinMode(display.segmentFPin, OUTPUT);
  pinMode(display.segmentGPin, OUTPUT);
}

void displayDigit(int digit) {
  switch (digit) {
    case 0:
      digitalWrite(display.segmentAPin, HIGH);
      digitalWrite(display.segmentBPin, HIGH);
      digitalWrite(display.segmentCPin, HIGH);
      digitalWrite(display.segmentDPin, HIGH);
      digitalWrite(display.segmentEPin, HIGH);
      digitalWrite(display.segmentFPin, HIGH);
      digitalWrite(display.segmentGPin, LOW);
      break;
    case 1:
      digitalWrite(display.segmentAPin, LOW);
      digitalWrite(display.segmentBPin, HIGH);
      digitalWrite(display.segmentCPin, HIGH);
      digitalWrite(display.segmentDPin, LOW);
      digitalWrite(display.segmentEPin, LOW);
      digitalWrite(display.segmentFPin, LOW);
      digitalWrite(display.segmentGPin, LOW);
      break;
    case 2:
      digitalWrite(display.segmentAPin, HIGH);
      digitalWrite(display.segmentBPin, HIGH);
      digitalWrite(display.segmentCPin, LOW);
      digitalWrite(display.segmentDPin, HIGH);
      digitalWrite(display.segmentEPin, HIGH);
      digitalWrite(display.segmentFPin, LOW);
      digitalWrite(display.segmentGPin, HIGH);
      break;
    case 3:
      digitalWrite(display.segmentAPin, HIGH);
      digitalWrite(display.segmentBPin, HIGH);
      digitalWrite(display.segmentCPin, HIGH);
      digitalWrite(display.segmentDPin, HIGH);
      digitalWrite(display.segmentEPin, LOW);
      digitalWrite(display.segmentFPin, LOW);
      digitalWrite(display.segmentGPin, HIGH);
      break;
    case 4:
      digitalWrite(display.segmentAPin, LOW);
      digitalWrite(display.segmentBPin, HIGH);
      digitalWrite(display.segmentCPin, HIGH);
      digitalWrite(display.segmentDPin, LOW);
      digitalWrite(display.segmentEPin, LOW);
      digitalWrite(display.segmentFPin, HIGH);
      digitalWrite(display.segmentGPin, HIGH);
      break;
    case 5:
      digitalWrite(display.segmentAPin, HIGH);
      digitalWrite(display.segmentBPin, LOW);
      digitalWrite(display.segmentCPin, HIGH);
      digitalWrite(display.segmentDPin, HIGH);
      digitalWrite(display.segmentEPin, LOW);
      digitalWrite(display.segmentFPin, HIGH);
      digitalWrite(display.segmentGPin, HIGH);
      break;
    case 6:
      digitalWrite(display.segmentAPin, HIGH);
      digitalWrite(display.segmentBPin, LOW);
      digitalWrite(display.segmentCPin, HIGH);
      digitalWrite(display.segmentDPin, HIGH);
      digitalWrite(display.segmentEPin, HIGH);
      digitalWrite(display.segmentFPin, HIGH);
      digitalWrite(display.segmentGPin, HIGH);
      break;
    case 7:
      digitalWrite(display.segmentAPin, HIGH);
      digitalWrite(display.segmentBPin, HIGH);
      digitalWrite(display.segmentCPin, HIGH);
      digitalWrite(display.segmentDPin, LOW);
      digitalWrite(display.segmentEPin, LOW);
      digitalWrite(display.segmentFPin, LOW);
      digitalWrite(display.segmentGPin, LOW);
      break;
    case 8:
      digitalWrite(display.segmentAPin, HIGH);
      digitalWrite(display.segmentBPin, HIGH);
      digitalWrite(display.segmentCPin, HIGH);
      digitalWrite(display.segmentDPin, HIGH);
      digitalWrite(display.segmentEPin, HIGH);
      digitalWrite(display.segmentFPin, HIGH);
      digitalWrite(display.segmentGPin, HIGH);
      break;
    case 9:
      digitalWrite(display.segmentAPin, HIGH);
      digitalWrite(display.segmentBPin, HIGH);
      digitalWrite(display.segmentCPin, HIGH);
      digitalWrite(display.segmentDPin, HIGH);
      digitalWrite(display.segmentEPin, LOW);
      digitalWrite(display.segmentFPin, HIGH);
      digitalWrite(display.segmentGPin, HIGH);
      break;
    default:
      // do nothing if an invalid digit is provided
      break;
  }
}

void clearDisplay() {
  digitalWrite(display.segmentAPin, LOW);
  digitalWrite(display.segmentBPin, LOW);
  digitalWrite(display.segmentCPin, LOW);
  digitalWrite(display.segmentDPin, LOW);
  digitalWrite(display.segmentEPin, LOW);
  digitalWrite(display.segmentFPin, LOW);
  digitalWrite(display.segmentGPin, LOW);
}
