/*
    Main file, containing main setup and line-following loop
*/

#include "header.h"

void setup() {
    setup_motors();
    init_motor_history();
    setup_sensors();
    setup_leds();
    led_connection_test();

}

void loop() {
  follow_line();
}
