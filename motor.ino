/*
    Control and interface with motors and servos
*/

#include "header.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_DCMotor *left_motor, *right_motor;
Adafruit_MotorShield AFMS;

void setup_motors() {
    AFMS = Adafruit_MotorShield();
    left_motor = AFMS.getMotor(L_MOTOR_PORT);
    right_motor = AFMS.getMotor(R_MOTOR_PORT);
    AFMS.begin();
}

int set_motor_speeds(int left_motor_speed, int right_motor_speed) { //Parameters are negative if running in reverse, positive if running forwards
    
    //Set left motor
    if (left_motor_speed >= 0) left_motor->run(FORWARD);
    else left_motor->run(BACKWARD);
    left_motor->setSpeed(abs(left_motor_speed));

    //Set right motor
    if (left_motor_speed >= 0) left_motor->run(FORWARD);
    else left_motor->run(BACKWARD);
    left_motor->setSpeed(abs(left_motor_speed));
}