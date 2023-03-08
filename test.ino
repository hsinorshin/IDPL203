/* 
    File for unit tests, these are carried out every time the robot starts up
*/

#include "header.h"



void led_connection_test() { //Will attempt to flash LEDs for 500ms at a time 
  set_led_val(RED_INDICATOR_LED_PIN, true);
  delay(5000);
  set_led_val(RED_INDICATOR_LED_PIN, false);
  set_led_val(GREEN_INDICATOR_LED_PIN, true);
  delay(5000);
  set_led_val(GREEN_INDICATOR_LED_PIN, false);
  set_led_val(AMBER_INDICATOR_LED_PIN, true);
  delay(5000);
  set_led_val(AMBER_INDICATOR_LED_PIN, false);
}

void motor_servo_test() {
  set_servo_position(10);
  /*
  Serial.println("at 0 degree");
  set_servo_position(0);
  delay(3000);
  Serial.println("Go to 270 degrees");
  set_servo_position(180);
  delay(3000);
  Serial.println("Go to 135 degrees");
  set_servo_position(90);
  delay(3000);
  //set_motor_speeds(50,50);
  //delay(3000);
  */
}

void sensor_test() {
  //COLOUR_SENSOR_PIN = 26
  //read the input on colour_sensor_pin
  for (int i = 0; i <= 20; i++) {
    int sensorValue = get_sensor_reading(US_ECHO_PIN);
    //print out the value you read
    Serial.println(sensorValue);
    delay(1000); //delay in between reads for stability 
  }

}

void path_test() //Path test for testing basic movement functions of the robot, examined by eye
{
  Serial.println("Starting path test");
  Serial.println("Move forward 80cm");
  forward(70);
  delay(3000);
  Serial.println("Move backward 800cm");
  reverse(70);
  delay(3000);
  Serial.println("Turning left");
  turn(90, false);
  delay(3000);
  turn(-90, false);
  delay(3000);
  /*
  Serial.println("Turning right");
  turn(-90);
  turn(90);
  */
  Serial.println("Stopping");
  stop();
  Serial.print("Path test ended");
}

void block_handling_test() {
  Serial.println("Start block handling test");
  Serial.println("Grab the block");
  grab_block();
  Serial.println("Release the block");
  release_block();
  Serial.println("test ended");
}


