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
  pinMode(US_TRIG_PIN, OUTPUT);
}

void loop(){

}

int get_US_reading(){
  //range of US is 2cm - 400cm
  long duration;
  int distance;

  //Clears the trigPin 
  digitalWrite(US_TRIG_PIN,LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(US_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(US_TRIG_PIN, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(US_ECHO_PIN, HIGH);
  // Calculating the distance in cm 
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  return distance

}
int get_sensor_reading(int sensor_pin){
  return analogRead(sensor_pin);
  //switch case for different sensors when we are done writing function for each type of sensor 
}

int get_line_sensor_reading(int sensor_pin){
  return digitalRead(sensor_pin)
}

int get_US_reading(){
  long duration;
  int distance;

  // Clears the trigPin
  digitalWrite(US_TRIG_PIN, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(US_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(US_TRIG_PIN, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(US_ECHO_PIN, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  return distance;
}

