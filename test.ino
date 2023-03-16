/* 
    File for unit tests, these are carried out every time the robot starts up
*/

#include "header.h"


void led_connection_test() { //Will attempt to flash LEDs for 500ms at a time, check if they are working
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

void sensor_test() { //For testing the ultrasound sensor, get 20 readings with a second between them
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
  forward(80);
  delay(3000);

  Serial.println("Move backward 800cm");
  reverse(80);
  delay(3000);

  Serial.println("Turning"); //Left 90, Right 90
  turn(90, false);
  delay(3000);
  turn(-90, false);
  delay(3000);

  Serial.println("Stopping");
  stop();

  Serial.print("Path test ended");
}

void block_handling_test() { //Test for checking if the robot can pick up a block, and release it, examined by eye
  Serial.println("Start block handling test");
  Serial.println("Grab the block");
  grab_block();
  Serial.println("Release the block");
  release_block();
  Serial.println("test ended");
}
