/* 
    File for unit tests, these are carried out every time the robot starts up
*/

#include "header.h"

void led_connection_test() { //Will attempt to flash LEDs for 500ms at a time
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

}

void sensor_test() {

}

void path_test() {

}