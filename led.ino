/*
    Interfacing with LEDs
*/

#include "header.h"

void setup_leds() {
    pinMode(RED_INDICATOR_LED_PIN, OUTPUT);
    pinMode(GREEN_INDICATOR_LED_PIN, OUTPUT);
    pinMode(AMBER_INDICATOR_LED_PIN, OUTPUT);
}

void set_led_val(int led_pin, bool val) {
    if (val == true) digitalWrite(led_pin, HIGH);
    else digitalWrite(led_pin, LOW);
}

void blink(int led_pin,int times){
    while(times>=0){
    digitalWrite(led_pin, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);                      // wait for a second
    digitalWrite(led_pin, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);                      // wait for a second
    times--;
    }
    
}
