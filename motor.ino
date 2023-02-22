/*
    Control and interface with motors and servos
*/

#include "header.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

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

int set_motor_speeds(int left_val, int right_val) { //Parameters are negative if running in reverse, positive if running forwards
    
    //Set left motor
    if (left_val >= 0) left_motor->run(FORWARD);
    else left_motor->run(BACKWARD);
    left_motor->setSpeed(abs(left_val));

    //Set right motor
    if (left_val >= 0) left_motor->run(FORWARD);
    else left_motor->run(BACKWARD);
    left_motor->setSpeed(abs(left_val));

    left_motor_speed = left_val;
    right_motor_speed = right_val;
    int update_time = millis();

    update_motor_history(left_motor_speed, right_motor_speed, update_time);
}

int get_left_motor_speed() {
    return left_motor_speed;
}

int get_right_motor_speed() {
    return right_motor_speed;
}