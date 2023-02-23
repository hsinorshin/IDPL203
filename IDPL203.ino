/*
    Main file, containing main setup and line-following loop
*/

#include "header.h"

void setup() {
    Serial.begin(9600);
    Serial.print("Hello!");
    setup_motors();
    //setup_sensors();
    //setup_leds();
    //led_connection_test();
    path_test();
    delay(10000);
    set_motor_speeds(MOTOR_SPEED_BASE, MOTOR_SPEED_BASE);

}

void loop() {
    //pseudocode to test out block finding
    //there are only three reasons why we would get values for L3,L4, 1. no block trying to get block 2. w block trying to drop block 3.leaving starting area 
    /*move-> path detected -> if hold=0 -> find block-> detect block colour-> get block -> */
}
