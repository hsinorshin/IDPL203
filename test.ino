/* 
    File for unit tests, these are carried out every time the robot starts up
*/

#include "header.h"

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void led_connection_test() { //Will attempt to flash LEDs for 500ms at a time **Idt u need void in front when u call the cmd 
  void set_led_val(RED_INDICATOR_LED_PIN, true);
  delay(500);
  void set_led_val(RED_INDICATOR_LED_PIN, false);
  void set_led_val(GREEN_INDICATOR_LED_PIN, true);
  delay(500);
  void set_led_val(GREEN_INDICATOR_LED_PIN, false);
  void set_led_val(AMBER_INDICATOR_LED_PIN, true);
  delay(500);
  void set_led_val(AMBER_INDICATOR_LED_PIN, false);
  void set_led_val(RED_SENSOR_LED_PIN, true);
  delay(500);
  void set_led_val(RED_SENSOR_LED_PIN, false);
  void set_led_val(GREEN_SENSOR_LED_PIN, true);
  delay(500);
  void set_led_val(GREEN_SENSOR_LED_PIN, false);
  void set_led_val(AMBER_SENSOR_LED_PIN, true);
  delay(500);
  void set_led_val(AMBER_SENSOR_LED_PIN, false);
}

void motor_servo_test() {
  setup_motors();
  set_motor_speeds(50,50);

}

void sensor_test() {
  //COLOUR_SENSOR_PIN = 26
  //read the input on colour_sensor_pin
  int sensorValue= get_sensor_reading(COLOUR_SENSOR_PIN);
  //print out the value you read
  Serial.println(sensorValue);
  delay(1); //delay in between reads for stability 
}

void path_test() {
  

}