#include "seven_seg.h"
#include <Arduino_FreeRTOS.h>
#include <Servo.h>

Servo chop_motor;
Servo sensor_motor;

int red_led = 41;
int green_led = 40;
int button = 34;
int buzzer = 3;
int echo_pin = 11;
int trig_pin = 12;

enum SensorState { SCAN,
                   IDLE };
SensorState read_mode = IDLE;

int maximumRange = 200;   // Maximum range needed
int minimumRange = 0;     // Minimum range needed
long duration, distance;  // Duration used to calculate distance

bool start = false;

enum BuzzerState { BUZZER_GREEN,
                   BUZZER_RED,
                   BUZZER_OFF };
BuzzerState buzzer_state = BUZZER_OFF;

/* Tasks */
void updateDisplayTask(void *pvParameters);
void pressButtonTask(void *pvParameters);
void handleLightChange(void *pvParameters);
void toggleBuzzerTask(void *pvParameters);
void scanDistanceTask(void *pvParameters);

int scanUltrasonic(void) {
  digitalWrite(trig_pin, LOW);
  vTaskDelay(2 / portTICK_PERIOD_MS);
  digitalWrite(trig_pin, HIGH);
  vTaskDelay(10 / portTICK_PERIOD_MS);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  distance = duration / 58.2;
  return distance;
}

void setup() {
  Serial.begin(9600);
  setupSevenSegmentDisplay();

  // Create the task to update the display
  xTaskCreate(updateDisplayTask, "UpdateDisplay", 128, NULL, 2, NULL);
  xTaskCreate(pressButtonTask, "ButtonPress", 128, NULL, 3, NULL);
  xTaskCreate(handleLightChange, "HandleLight", 128, NULL, 1, NULL);
  xTaskCreate(scanDistanceTask, "ScanDistance", 128, NULL, 2, NULL);

  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);

  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  chop_motor.attach(8);
  sensor_motor.attach(9);
  chop_motor.write(180);
  sensor_motor.write(180);


  // Start the scheduler
  vTaskStartScheduler();
}

void loop() {}

/**
* Seven Segment Display
*/
void updateDisplayTask(void *pvParameters) {
  while (1) {
    while (!start) {
      clearDisplay();
      chop_motor.write(180);
      sensor_motor.write(180);
      read_mode = IDLE;
      vTaskDelay(200 / portTICK_PERIOD_MS);
    }

    int remainingTime = 60;
    while (start) {
      Serial.println(remainingTime);
      int tensDigit = remainingTime / 10;
      displayDigit(tensDigit);
      remainingTime--;
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      if (remainingTime < 0) {
        start = false;
        read_mode = IDLE;
        chop_motor.write(0);
        vTaskDelay(800 / portTICK_PERIOD_MS);
        break;
      }
    }
  }
}

void handleLightChange(void *pvParameters) {
  while (1) {
    while (!start) {
      digitalWrite(green_led, LOW);
      digitalWrite(red_led, LOW);
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    while (start) {
      for (int i = 0; i < 2; i++) {
        if (!start) break;
        digitalWrite(green_led, HIGH);
        digitalWrite(red_led, LOW);
        sensor_motor.write(180);

        if (i < 1) {
          buzzer_state = BUZZER_GREEN;
          tone(buzzer, 500, 500);
          read_mode = IDLE;
        } else if (i > 0 && i < 2) {
          read_mode = SCAN;
        } else {
          buzzer_state = BUZZER_OFF;
          read_mode = IDLE;
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }

      for (int i = 0; i < 3; i++) {
        if (!start) break;
        digitalWrite(red_led, HIGH);
        digitalWrite(green_led, LOW);
        sensor_motor.write(0);
        if (i < 1) {
          buzzer_state = BUZZER_RED;
          tone(buzzer, 1200, 500);
        } else {
          buzzer_state = BUZZER_OFF;
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
    }

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void pressButtonTask(void *pvParameters) {
  while (1) {
    if (digitalRead(button) == LOW) {
      start = !start;
      delay(1000);
    }
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void scanDistanceTask(void *pvParameters) {
  static int state = 0;
  static int prev_distance = -1;
  static int current_dist = 0;
  while (1) {
    while (read_mode == IDLE) {
      state = 0;
      prev_distance = -1;
      current_dist = 0;
      chop_motor.write(180);
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    while (read_mode == SCAN) {
      if (state == 0) {
        vTaskDelay(1500 / portTICK_PERIOD_MS);
        state = 1;
      }

      current_dist = scanUltrasonic();
      if (prev_distance == -1) {
        prev_distance = current_dist;
      } else if (current_dist > 60 || current_dist < -1) {
        break;
      } else if (current_dist > prev_distance + 2 || current_dist < prev_distance - 2) {
        chop_motor.write(0);
      } else {
        prev_distance = current_dist;
      }

      vTaskDelay(300 / portTICK_PERIOD_MS);
    }
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
