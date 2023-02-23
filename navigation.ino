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
    Serial.print(left_sensor_val);
    Serial.println(right_sensor_val);
    if (left_sensor_val == 1 && right_sensor_val == 1) {
        right_speed = MOTOR_SPEED_BASE;
        left_speed = MOTOR_SPEED_BASE;
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
    bool direction = current_right_speed > current_right_speed; //Rotate left if true, right if false
    int angle_delta = 5;
    if (!direction) angle_delta *= -1;
    bool line_found = false;
    while(!line_found){
        turn(angle_delta);
        int left_sensor_val = get_sensor_reading(LINE_SENSOR_1_PIN);
        int right_sensor_val = get_sensor_reading(LINE_SENSOR_2_PIN);
        line_found = left_sensor_val == 1 && right_sensor_val == 1;
    }
}

void move_onto_line() { //For when moving out of start box and on to the line
    set_motor_speeds(MOTOR_SPEED_BASE, MOTOR_SPEED_BASE); //Initial movement
    //Before we have a to follow (just keep going forward)
    bool line_reached_left = false;
    bool line_reached_right = false;
    while(!line_reached_left && !line_reached_right) {
        delay(50);
        if (!line_reached_left){
            int outer_left_sensor_val = get_sensor_reading(LINE_SENSOR_3_PIN);
            line_reached_left = outer_left_sensor_val == 1;
        }
        if (!line_reached_right){
            int outer_right_sensor_val = get_sensor_reading(LINE_SENSOR_4_PIN);
            line_reached_right = outer_right_sensor_val == 1;
        }
    }
    //Now there is a line to follow, until main line reached
    line_reached_left = true;
    line_reached_right = true;
    while(!line_reached_left && !line_reached_right) {
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
    //Main line reached, turn right on to line
    forward(WHEELBASE); //Move forward wheelbase of car (rear axle now over line)
    turn(-90); //Pivot round to face lin
}