#include "header.h" 
#include <map>

int time;
int k=1; //this needs to be calibrated 
int wheel_ang_vel= k*150; 

void turn(int angle){
//we take anticlockwise as convention, and one of the wheels as pivot, width of chassis as radius 
//eg. angle = 90 means turn left 
//width of chassis = 20cm
//radius of wheels = 5cm 

    time = 4*abs(angle)/wheel_ang_vel;
    
if (angle>=0){
   
   set_motor_speeds(0,150); 
   delay(time); 
   set_motor_speeds(0,0);
}

else if (angle<0){
    set_motor_speeds(150,0);
    delay(time);
    set_motor_speeds(0,0);
}


}

void reverse(int distance){
    time=abs(distance)/(5*wheel_ang_vel);
    set_motor_speeds(150,150);
    delay(time);
    set_motor_speeds(0,0);
}

void stop(){
    set_motor_speeds(0,0);
}