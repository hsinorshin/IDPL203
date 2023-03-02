#include "header.h" 
//#include <map>

float move_time;
const float k=0.0000102; //this needs to be calibrated
float wheel_vel = WHEEL_RADIUS*k*MOTOR_SPEED_BASE;

void turn(int angle){
//anticlockwise as convention, axle as pivot, width/2 of chassis as radius 
//eg. angle = 90 means turn left 
//width of chassis = 20cm
//radius of wheels = 5cm 

    move_time = 3.14*AXLE_LENGTH*abs(angle)/(360*wheel_vel);
    Serial.println(move_time);
    if (angle>=0){
    
    set_motor_speeds(-MOTOR_SPEED_BASE,MOTOR_SPEED_BASE); 
    delay(move_time); 
    set_motor_speeds(0,0);
    }

    else if (angle<0){
        set_motor_speeds(MOTOR_SPEED_BASE, -MOTOR_SPEED_BASE);
        delay(move_time);
        set_motor_speeds(0,0);
    }

}

void forward(int distance){
    move_time=abs(distance)/(wheel_vel);
    set_motor_speeds(MOTOR_SPEED_BASE,MOTOR_SPEED_BASE);
    delay(move_time);
    set_motor_speeds(0,0);
}

void reverse(int distance){
    move_time=abs(distance)/(wheel_vel);
    set_motor_speeds(-MOTOR_SPEED_BASE, -MOTOR_SPEED_BASE);
    delay(move_time);
    set_motor_speeds(0,0);
}

void stop(){
    set_motor_speeds(0,0);
}