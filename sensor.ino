/*
    Interfacing with sensors
    LINE_SENSORS : LED + infrared photodiode , output = 0 / 1 
    COLOUR_SENSOR : infrared LED + phototransistor , output = 0 / 1
    US_SENSOR : US emitter + US receiver , output = int distance 
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

int get_sensor_reading(int sensor_pin){

  switch(sensor_pin){
    case START_BUTTON_PIN:
    //high when pressed (start)
    return digitalRead(START_BUTTON_PIN);

    case LINE_SENSOR_1_PIN:
    //high for black, low for white 
    return digitalRead(LINE_SENSOR_1_PIN);

    case LINE_SENSOR_2_PIN:
    //high for black, low for white 
    return digitalRead(LINE_SENSOR_2_PIN);

    case LINE_SENSOR_3_PIN:
    //high for black, low for white 
    return digitalRead(LINE_SENSOR_3_PIN);

    case LINE_SENSOR_4_PIN:
    //high for black, low for white 
    return digitalRead(LINE_SENSOR_4_PIN);

    case COLOUR_SENSOR_PIN:
    //high for blue, low for anything else(red)
    int state=digitalRead(COLOUR_SENSOR_PIN);
    if (state==1){
      return BLUE;
    }
    else{
      return RED;
    }
     

    case US_ECHO_PIN:
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
    return distance; 
    

  }
}
  


