/*
    Interfacing with sensors
*/

#include "header.h"

void setup_sensors() {
  pinMode(START_BUTTON_PIN, INPUT);
  pinMode(LINE_SENSOR_1_PIN, INPUT);
  pinMode(LINE_SENSOR_2_PIN, INPUT);
  pinMode(LINE_SENSOR_3_PIN, INPUT);
  pinMode(LINE_SENSOR_4_PIN, INPUT);
  pinMode(COLOUR_SENSOR_PIN, INPUT);
  pinMode(US_ECHO_PIN, INPUT);
}

int get_sensor_reading(int sensor_pin){
  return digitalRead(sensor_pin);
}