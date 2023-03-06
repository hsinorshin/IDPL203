/*
    Control and interface with motors and servos
*/

#include "header.h"
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Servo myservo; //create servo object to control a servo
Adafruit_DCMotor *left_motor, *right_motor;
Adafruit_MotorShield AFMS;
int left_motor_speed, right_motor_speed;


void setup_motors() {
    AFMS = Adafruit_MotorShield();
    left_motor = AFMS.getMotor(L_MOTOR_PORT);
    right_motor = AFMS.getMotor(R_MOTOR_PORT);
    AFMS.begin();
    left_motor_speed = 0;
    right_motor_speed = 0;
}


void set_motor_speeds(int left_val, int right_val) { //Parameters are negative if running in reverse, positive if running forwards
    // The speed parameter is a value between 0 and 255.
    //Note that setSpeed just controls the power delivered to the motor. The actual speed of the motor will depend on several factors, including: The motor, the power supply and the load.
    //Set left motor
    if (left_val <= 0) left_motor->run(BACKWARD);
    else left_motor->run(FORWARD);
    left_motor->setSpeed(abs(left_val));

    //Set right motor
    if (right_val >= 0) right_motor->run(BACKWARD);
    else right_motor->run(FORWARD);
    right_motor->setSpeed(abs(right_val));

    left_motor_speed = left_val;
    right_motor_speed = right_val;

    //Set amber LED based on whether moving or not
    if(left_motor_speed == 0 && right_motor_speed == 0) set_led_val(AMBER_INDICATOR_LED_PIN, false);
    else set_led_val(AMBER_INDICATOR_LED_PIN, true);
    
}

int get_left_motor_speed() {
    return left_motor_speed;
}

int get_right_motor_speed() {
    return right_motor_speed;
}

void setup_servo(){
    myservo.attach(SERVO_PIN);
}

void set_servo_position(int angle){
    //degree should be a value between 0 to 180 
    myservo.write(angle);
}