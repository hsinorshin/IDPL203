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
int left_motor_speed, right_motor_speed; //Store current motor speed values


void setup_motors() {
    AFMS = Adafruit_MotorShield();
    left_motor = AFMS.getMotor(L_MOTOR_PORT);
    right_motor = AFMS.getMotor(R_MOTOR_PORT);
    AFMS.begin();
    set_motor_speeds(0,0); //Ensure not moving to begin with!
}


void set_motor_speeds(int left_val, int right_val) { //Parameters are negative if running in reverse, positive if running forwards
    // The speed parameter is a value between 0 and 255.
    //Note that setSpeed just controls the power delivered to the motor. The actual speed of the motor will depend on several factors, including: The motor, the power supply and the load.
    //Set left motor
    if (left_val >= 0) left_motor->run(BACKWARD);
    else left_motor->run(FORWARD);
    left_motor->setSpeed(abs(left_val));

    //Set right motor
    if (right_val <= 0) right_motor->run(BACKWARD);
    else right_motor->run(FORWARD);
    right_motor->setSpeed(abs(0.93*right_val)); 
    /* Need slight reduction in power on the right motor, as it seemed to have a slightly greater power
    than the left motor if set to the same value (the robot would slightly veer to the left). The factor
    of 0.93 may need to be changed. */

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

void clap() { //To celebrate at the end, the robot claps with its grabbers!
  for (int i=0; i<4; i++) {
    set_servo_position(CLOSE_CLAW_POSITION);
    delay(500);
    set_servo_position(OPEN_CLAW_POSITION);
    delay(500);
  }
}