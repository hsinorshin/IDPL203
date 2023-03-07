/* 
    Line following, reference line detection
*/

#include "header.h"

bool last_offset;

void follow_line(){
    //Values from sensors are HIGH if line detected, LOW if not
    int left_sensor_val = get_sensor_reading(LINE_SENSOR_1_PIN);
    int right_sensor_val = get_sensor_reading(LINE_SENSOR_2_PIN);
    int left_speed = get_left_motor_speed();
    int right_speed = get_right_motor_speed();    
    if (left_sensor_val == 1 && right_sensor_val == 1) {
        right_speed = MOTOR_SPEED_BASE;
        left_speed = MOTOR_SPEED_BASE;
        //hsin: i recommend we find a way to avoid sending the instruction set_motor_speeds if we are on track to avoid overcrowding the communication channel/sending too many instructions 
    }
    else if (left_sensor_val == 1 && right_sensor_val == 0) {
        //Too far to the right, moving left 
        right_speed = MOTOR_SPEED_BASE;
        left_speed = 0;
        last_offset = true;
    }
    else if (left_sensor_val == 0 && right_sensor_val == 1) {
        //Too far to the left, moving right
        right_speed = 0;
        left_speed = MOTOR_SPEED_BASE;
        last_offset = false;
    }
    else if (left_sensor_val == 0 && right_sensor_val == 0) {
        //Lost track, start reverse sequence
        recover_to_line();
        right_speed = MOTOR_SPEED_BASE;
        left_speed = MOTOR_SPEED_BASE;
    }
    set_motor_speeds(left_speed, right_speed);
}
void recover_to_line() { //Recovery algorithm for if we lose track of the line
    int current_left_speed = get_left_motor_speed();
    int current_right_speed = get_right_motor_speed();
    bool direction =  last_offset; //Turn in opposite direction to direction of previous offset (turn left if true, turn right if false)
    float angle_delta = 1;
    if (!direction) angle_delta = -angle_delta;
    bool line_found = false;
    while(!line_found) {
      int count = 0; //Limit iterations in one direction
      const int MAX_COUNT = 90 / abs(angle_delta); //Do enough iterations to rotate 90 degrees
      while(!line_found && count < MAX_COUNT){
          turn(angle_delta, true);
          int left_sensor_val = get_sensor_reading(LINE_SENSOR_1_PIN);
          int right_sensor_val = get_sensor_reading(LINE_SENSOR_2_PIN);
          line_found = left_sensor_val == 1 && right_sensor_val == 1;
          count++;
      }
      if (!line_found) { //Try opposite direction if line not found
          angle_delta *= -1;
          count = 0;
          while(!line_found && count < MAX_COUNT * 2.2){ //Try going 1.5x the rotation in opposite direction (360)
              turn(angle_delta, true);
              int left_sensor_val = get_sensor_reading(LINE_SENSOR_1_PIN);
              int right_sensor_val = get_sensor_reading(LINE_SENSOR_2_PIN);
              line_found = left_sensor_val == 1 && right_sensor_val == 1;
              count++;
          }   
      }
    }

}

void move_onto_line() { //For when moving out of start box and on to the line

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
        if (!line_reached_left && !line_reached_right) reverse(WHEELBASE); //Line missed, backtrack a bit
        else part_done = true;
    }
    forward(5); //Move forward 5cm
    //Now there is a line to follow, until main line reached
    line_reached_left = false;
    line_reached_right = false;
    part_done = false;
    set_motor_speeds(MOTOR_SPEED_BASE, MOTOR_SPEED_BASE); //Initial movement
    while (!part_done) {
        int count = 0;
        while(!line_reached_left && !line_reached_right && count < MAX_COUNT_2) {
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
        if (!line_reached_left && !line_reached_right) reverse(WHEELBASE); //Gone too far, bactrack a bit
        else part_done = true;
    }
    //Main line reached, turn right on to line
    forward(WHEELBASE); //Move forward wheelbase of car (rear axle now over line)
    turn(-90, false); //Pivot round to face line
}

void go_back(){
    //to return to home
    //we are either at fork w green/red box after dropping off block#
    Serial.println("Starting back");
    bool cont = true;
    fork_count=3;
    if (fork_count<HOME){ //at green block
        forward(WHEELBASE); //So it does not accidentally read the fork for the green block twice
        while(cont) { //While yet to detect home fork
            follow_line(); //Line following loop
            cont = !(get_sensor_reading(LINE_SENSOR_4_PIN) == 0 && get_sensor_reading(LINE_SENSOR_3_PIN) == 1);
            Serial.println(get_sensor_reading(LINE_SENSOR_4_PIN));
            delay(DELAY/3);
        }
    }
    else if(fork_count>HOME){
        turn(180, false); //Spin to face line
        while (cont){ //While yet to detect home fork (on left now)
            follow_line(); //Line following loop
            delay(DELAY);
            cont = !(get_sensor_reading(LINE_SENSOR_3_PIN) == 0 && get_sensor_reading(LINE_SENSOR_4_PIN) == 1);
        }
    }

    forward(WHEELBASE); //Move forward wheelbase of car (rear axle now over line)
    if (fork_count<HOME) turn(-90, false); //Turn to face box
    else turn(90, false);

    forward(2.2*WHEELBASE); //Move forward into box
  


    
        
        
}