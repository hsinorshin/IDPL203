/*
    Main file, containing main setup and line-following loop
*/

#include "header.h"

void setup() {
    Serial.begin(9600);
    Serial.print("Hello!");
    setup_motors();
    //init_motor_history();
    //setup_sensors();
    //setup_leds();
    //led_connection_test();
    //path_test();
    delay(10000);
    set_motor_speeds(MOTOR_SPEED_BASE, MOTOR_SPEED_BASE);

}

void loop() {
  follow_line();
}
