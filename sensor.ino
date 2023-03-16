/*
    Interfacing with sensors
    LINE_SENSORS : LED + infrared photodiode , output = 0 / 1 
    COLOUR_SENSOR : infrared LED + phototransistor , output = 0 / 1
    US_SENSOR : US emitter + US receiver , output = int distance 
*/

#include <hcsr04.h>
#include "header.h"
HCSR04 hcsr04(US_TRIG_PIN, US_ECHO_PIN, 20, 4000); //Ultrasound sensor


void setup_sensors() {
  pinMode(START_BUTTON_PIN, INPUT);
  pinMode(LINE_SENSOR_1_PIN, INPUT);
  pinMode(LINE_SENSOR_2_PIN, INPUT);
  pinMode(LINE_SENSOR_3_PIN, INPUT);
  pinMode(LINE_SENSOR_4_PIN, INPUT);
  pinMode(COLOUR_SENSOR_PIN, INPUT);
}

int get_sensor_reading(int sensor_pin){ //Integer value of pin readings, method of measurement depends on pin

  switch(sensor_pin){
    case US_ECHO_PIN:
      return (int)hcsr04.distanceInMillimeters();
      
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
    return state;
    
  }
}
  


