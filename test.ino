/* 
    File for unit tests, these are carried out every time the robot starts up
*/

#include "header.h"



void led_connection_test() { //Will attempt to flash LEDs for 500ms at a time **Idt u need void in front when u call the cmd 
  set_led_val(RED_INDICATOR_LED_PIN, true);
  delay(500);
  set_led_val(RED_INDICATOR_LED_PIN, false);
  set_led_val(GREEN_INDICATOR_LED_PIN, true);
  delay(500);
  set_led_val(GREEN_INDICATOR_LED_PIN, false);
  set_led_val(AMBER_INDICATOR_LED_PIN, true);
  delay(500);
  set_led_val(AMBER_INDICATOR_LED_PIN, false);
}

void motor_servo_test() {
  setup_motors();
  setup_servo();
  set_servo_position(20);
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

void path_test() 
{
  Serial.print("Starting path test");
  set_motor_speeds(MOTOR_SPEED_BASE,MOTOR_SPEED_BASE); //go straight 
  delay(4000); //pause
  Serial.print("Turning left");
  set_motor_speeds(0,MOTOR_SPEED_BASE); //turn left
  delay(1000);//pause
  Serial.print("Turning right");
  set_motor_speeds(MOTOR_SPEED_BASE,0);//right
  delay(1000);
  Serial.print("Reversing");
  set_motor_speeds(-MOTOR_SPEED_BASE,-MOTOR_SPEED_BASE);//reverse
  delay(1000);
  Serial.print("Left");
  set_motor_speeds(0,0); //stop
  Serial.print("Path test ended");
}


