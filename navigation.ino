/* 
    Line following, reference line detection
*/

#include "header.h"

#define MS_HISTORY_LENGTH 100 //length of history arrays

int left_ms_history[MS_HISTORY_LENGTH], right_ms_history[MS_HISTORY_LENGTH];
int times[MS_HISTORY_LENGTH]; //millis() values for every data entry
int front_history_pointer, rear_history_pointer;

void follow_line(){
    int left_sensor_val = get_sensor_reading(LINE_SENSOR_1_PIN);
    int right_sensor_val = get_sensor_reading(LINE_SENSOR_2_PIN);
    int left_speed = get_left_motor_speed();
    int right_speed = get_right_motor_speed();
    if (left_sensor_val == 1 && right_sensor_val == 1) {
        //Great, its on the path!
        
    }
    else if (left_sensor_val == 0 && right_sensor_val == 1) {
        //Too far to the right, moving left 
        right_speed = MOTOR_SPEED_BASE + MOTOR_SPEED_TURNING_DIFF / 2;
        left_speed = MOTOR_SPEED_BASE - MOTOR_SPEED_TURNING_DIFF / 2;
    }
    else if (left_sensor_val == 1 && right_sensor_val == 0) {
        //Too far to the left, moving right
        right_speed = MOTOR_SPEED_BASE - MOTOR_SPEED_TURNING_DIFF / 2;
        left_speed = MOTOR_SPEED_BASE + MOTOR_SPEED_TURNING_DIFF / 2;
    }
    else if (left_sensor_val == 1 && right_sensor_val == 1) {
        //Lost track, start reverse sequence
        recover_to_line();
    }
    set_motor_speeds(left_speed, right_speed);
}
void recover_to_line() {
    ;
}

void move_onto_line() {
    ;
}

void init_motor_history() {
    rear_history_pointer = -1;
    front_history_pointer = 0;
}

void update_motor_history(int left_val, int right_val, int time) {
    rear_history_pointer = (rear_history_pointer + 1) % MS_HISTORY_LENGTH;
}