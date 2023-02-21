/*
    Interfacing with LEDs
*/

#include "header.h"

void setup_leds() {
    pinMode(RED_INDICATOR_LED_PIN, OUTPUT);
    pinMode(GREEN_INDICATOR_LED_PIN, OUTPUT);
    pinMode(AMBER_INDICATOR_LED_PIN, OUTPUT);
    pinMode(GREEN_SENSOR_LED_PIN, OUTPUT);
    pinMode(RED_SENSOR_LED_PIN, OUTPUT);
    pinMode(BLUE_SENSOR_LED_PIN, OUTPUT);
}

void set_led_val(int led_pin, bool val) {
    if (val == true) digitalWrite(led_pin, HIGH);
    else digitalWrite(led_pin, LOW);
}