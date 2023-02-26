/* 
    Line following, reference line detection
*/

#include "header.h"

void follow_line(){
    //Values from sensors are HIGH if line detected, LOW if not
    int left_sensor_val = get_sensor_reading(LINE_SENSOR_1_PIN);
    int right_sensor_val = get_sensor_reading(LINE_SENSOR_2_PIN);
    int left_speed = get_left_motor_speed();
    int right_speed = get_right_motor_speed();    
    Serial.println(left_sensor_val);
    Serial.println(right_sensor_val);
    if (left_sensor_val == 1 && right_sensor_val == 1) {
        right_speed = MOTOR_SPEED_BASE;
        left_speed = MOTOR_SPEED_BASE;
        //hsin: i recommend we find a way to avoid sending the instruction set_motor_speeds if we are on track to avoid overcrowding the communication channel/sending too many instructions 
    }
    else if (left_sensor_val == 1 && right_sensor_val == 0) {
        //Too far to the right, moving left 
        right_speed = MOTOR_SPEED_BASE + MOTOR_SPEED_TURNING_DIFF / 2;
        left_speed = MOTOR_SPEED_BASE - MOTOR_SPEED_TURNING_DIFF / 2;
    }
    else if (left_sensor_val == 0 && right_sensor_val == 1) {
        //Too far to the left, moving right
        right_speed = MOTOR_SPEED_BASE - MOTOR_SPEED_TURNING_DIFF / 2;
        left_speed = MOTOR_SPEED_BASE + MOTOR_SPEED_TURNING_DIFF / 2;
    }
    else if (left_sensor_val == 0 && right_sensor_val == 0) {
        //Lost track, start reverse sequence
        //recover_to_line();
        right_speed = MOTOR_SPEED_BASE;
        left_speed = MOTOR_SPEED_BASE;
    }
    set_motor_speeds(left_speed, right_speed);
}
void recover_to_line() { //Recovery algorithm for if we lose track of the line
    int current_left_speed = get_left_motor_speed();
    int current_right_speed = get_right_motor_speed();
    bool direction = current_right_speed > current_right_speed; //Turn left if true, right if false (first try)
    int angle_delta = 5;
    if (!direction) angle_delta *= -1;
    bool line_found = false;
    int count = 0; //Limit iterations in one direction
    const int MAX_COUNT = 180 / angle_delta; //Do enough iterations to rotate 180 degrees
    while(!line_found && count < MAX_COUNT){
        turn(angle_delta);
        int left_sensor_val = get_sensor_reading(LINE_SENSOR_1_PIN);
        int right_sensor_val = get_sensor_reading(LINE_SENSOR_2_PIN);
        line_found = left_sensor_val == 1 && right_sensor_val == 1;
        count++;
    }
    if (!line_found) { //Try opposite direction if line not found
        angle_delta *= -1;
        count = 0;
        while(!line_found && count < MAX_COUNT * 1.5){ //Try going 1.5x the rotation in opposite direction (360)
            turn(angle_delta);
            int left_sensor_val = get_sensor_reading(LINE_SENSOR_1_PIN);
            int right_sensor_val = get_sensor_reading(LINE_SENSOR_2_PIN);
            line_found = left_sensor_val == 1 && right_sensor_val == 1;
            count++;
        }   
    }
}

void move_onto_line() { //For when moving out of start box and on to the line

    const int DELAY = 50; //in ms, how much to wait between iterations
    const int MAX_TIME_TO_LINE_1 = 5000; //in ms, how long it is expected to take to get to line (maximum, worry if it takes this long!)
    const int MAX_TIME_TO_LINE_2 = 5000;
    const int MAX_COUNT_1 = MAX_TIME_TO_LINE_1 / DELAY;
    const int MAX_COUNT_2 = MAX_TIME_TO_LINE_2 / DELAY;

    bool line_reached_left = false;
    bool line_reached_right = false;
    bool part_done = false;

    set_motor_speeds(MOTOR_SPEED_BASE, MOTOR_SPEED_BASE); //Initial movement
    while (!part_done) {
        int count = 0;
        while(!line_reached_left && !line_reached_right && count < MAX_COUNT_1) {
            count++;
            delay(DELAY);
            if (!line_reached_left){
                int outer_left_sensor_val = get_sensor_reading(LINE_SENSOR_3_PIN);
                line_reached_left = outer_left_sensor_val == 1;
            }
            if (!line_reached_right){
                int outer_right_sensor_val = get_sensor_reading(LINE_SENSOR_4_PIN);
                line_reached_right = outer_right_sensor_val == 1;
            }
        }
        if (!line_reached_left && !line_reached_right) set_motor_speeds(-MOTOR_SPEED_BASE, -MOTOR_SPEED_BASE);
        else part_done = true;
    }
    //Now there is a line to follow, until main line reached
    line_reached_left = true;
    line_reached_right = true;
    part_done = false;
    set_motor_speeds(MOTOR_SPEED_BASE, MOTOR_SPEED_BASE); //Initial movement
    while (!part_done) {
        int count = 0;
        while(!line_reached_left && !line_reached_right && MAX_COUNT_2) {
        follow_line();
        if (!line_reached_left){
            int outer_left_sensor_val = get_sensor_reading(LINE_SENSOR_3_PIN);
            line_reached_left = outer_left_sensor_val == 1;
        }
        if (!line_reached_right){
            int outer_right_sensor_val = get_sensor_reading(LINE_SENSOR_4_PIN);
            line_reached_right = outer_right_sensor_val == 1;
        }
        }  
        if (!line_reached_left && !line_reached_right) set_motor_speeds(-MOTOR_SPEED_BASE, -MOTOR_SPEED_BASE);
        else part_done = true;
    }
    //Main line reached, turn right on to line
    forward(WHEELBASE); //Move forward wheelbase of car (rear axle now over line)
    turn(-90); //Pivot round to face line
}

void go_back(){
    //to return to home
    //we are either at fork w green/red box after dropping off block
    if (fork_count<HOME){
        follow_line();
        if (get_sensor_reading(LINE_SENSOR_3_PIN) ^ get_sensor_reading(LINE_SENSOR_4_PIN)){
            turn(-BLOCK_ROTATION_ANGLE);
            //some algo to make robot get in the white square 
            }
        
    }

    else if(fork_count>HOME){
        reverse(FORK_DISTANCE);
         if (get_sensor_reading(LINE_SENSOR_3_PIN) ^ get_sensor_reading(LINE_SENSOR_4_PIN)){
            turn(-BLOCK_ROTATION_ANGLE);
            //some algo to make robot get in the white square 
            }
        
    }
    
        
        
}