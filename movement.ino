/*
  Movement function for 
*/

#include "header.h" 


float move_time;
const float k=0.0000185; //this needs to be calibrated
float wheel_vel = WHEEL_RADIUS*k*MOTOR_SPEED_BASE;

void turn(int angle, bool keep_moving){ //To turn a specified angle, pivoting around the centre of the rear axle
//anticlockwise as convention, axle as pivot, width/2 of chassis as radius 
//eg. angle = 90 means turn left 
//width of chassis = 20cm
//radius of wheels = 5cm 
//keep_moving if you want to keep the motor speeds the same at the end (i.e., not stop)

    move_time = 3.14*AXLE_LENGTH*abs(angle)/(360*wheel_vel); //Calculate time to move for
    if (angle>=0) set_motor_speeds(-MOTOR_SPEED_BASE,MOTOR_SPEED_BASE);
    else set_motor_speeds(MOTOR_SPEED_BASE, -MOTOR_SPEED_BASE);

    delay(move_time); 
    if (!keep_moving) set_motor_speeds(0,0);

}

void forward(int distance){ //To move forward a specified distance 
    move_time=abs(distance)/(wheel_vel); //Calculate time to move for
    set_motor_speeds(MOTOR_SPEED_BASE,MOTOR_SPEED_BASE);
    delay(move_time);
    stop();
}

void reverse(int distance){ //To move forward a specified distance 
    move_time=abs(distance)/(wheel_vel); //Calculate time to move for
    set_motor_speeds(-MOTOR_SPEED_BASE, -MOTOR_SPEED_BASE);
    delay(move_time);
    stop();
}

void stop(){
    set_motor_speeds(0,0);
}