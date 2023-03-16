/* 
    Line following, reference line detection
*/

#include "header.h"

bool last_offset; /* Used for knowing which way to turn initially in case of the line being lost
True if need to turn left, false if need to turn right */

void follow_line(){ //One iteration of the line sensor - outcome will be to set the motor speeds to the required value to be on track
    //Values from sensors are HIGH if line detected, LOW if not
    //Pseudo-proportional control
    int left_sensor_val = get_sensor_reading(LINE_SENSOR_1_PIN);
    int right_sensor_val = get_sensor_reading(LINE_SENSOR_2_PIN);
    int left_speed = get_left_motor_speed();
    int right_speed = get_right_motor_speed();    
    if (left_sensor_val == 1 && right_sensor_val == 1) {
        //On track! Move in a straight line
        right_speed = MOTOR_SPEED_BASE;
        left_speed = MOTOR_SPEED_BASE;
    }
    else if (left_sensor_val == 1 && right_sensor_val == 0) {
        //Too far to the right, moving left 
        right_speed = MOTOR_SPEED_BASE;
        left_speed = 150;
        last_offset = true; //Need to rotate left if we lose track of the line
    }
    else if (left_sensor_val == 0 && right_sensor_val == 1) {
        //Too far to the left, moving right
        right_speed = 150;
        left_speed = MOTOR_SPEED_BASE;
        last_offset = false; //Need to rotate right if we lose track of the line
    }
    else if (left_sensor_val == 0 && right_sensor_val == 0) {
        //Lost track, recover to line
        recover_to_line();
        right_speed = MOTOR_SPEED_BASE; //Move in straight line once found line
        left_speed = MOTOR_SPEED_BASE;

    }
    set_motor_speeds(left_speed, right_speed);
}

void recover_to_line() { //Recovery algorithm for if we lose track of the line
    //Involves rotating on spot until line found again
    int current_left_speed = get_left_motor_speed();
    int current_right_speed = get_right_motor_speed();
    bool direction =  last_offset; //Turn in opposite direction to direction of previous offset (turn left if true, turn right if false)
    float angle_delta = 1; //Rotate this angle (in degrees) before checking if we're on the line again
    if (!direction) angle_delta = -angle_delta;
    bool line_found = false;
    while(!line_found) { //Rotate until we find the line
      int count = 0; //Limit iterations in one direction
      const int MAX_COUNT = 80 / abs(angle_delta); //Do enough iterations to rotate 90 degrees
      while(!line_found && count < MAX_COUNT){
          turn(angle_delta, true);
          int left_sensor_val = get_sensor_reading(LINE_SENSOR_1_PIN);
          int right_sensor_val = get_sensor_reading(LINE_SENSOR_2_PIN);
          line_found = left_sensor_val == 1 && right_sensor_val == 1; //If both inner sensor detect the line, we can stop!
          count++;
      }
      if (!line_found) { //Try opposite direction if line not found
          angle_delta *= -1;
          count = 0;
          while(!line_found && count < MAX_COUNT * 2.5){ //Try going 1.5x the rotation in opposite direction (360)
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
    const int MAX_TIME_TO_LINE_2 = 5000; //1 for reaching edge of start box, 2 for reaching line to follow
    const int MAX_COUNT_1 = MAX_TIME_TO_LINE_1 / DELAY; //Number of iteratons until the maximum is reached
    const int MAX_COUNT_2 = MAX_TIME_TO_LINE_2 / DELAY;

    bool line_reached_left = false;
    bool line_reached_right = false;
    bool part_done = false;

    set_motor_speeds(MOTOR_SPEED_BASE, MOTOR_SPEED_BASE); //Initial movement
    while (!part_done) { //First part is to move to start box 
        int count = 0;
        while(!line_reached_left && !line_reached_right && count < MAX_COUNT_1) { //Iterate until line is detected by BOTH outer line sensors
            count++;
            delay(DELAY);
            if (!line_reached_left){ //Check for left detection if not detected already
                int outer_left_sensor_val = get_sensor_reading(LINE_SENSOR_3_PIN);
                line_reached_left = outer_left_sensor_val == 1;
            }
            if (!line_reached_right){ //Check for right detection if not detected already
                int outer_right_sensor_val = get_sensor_reading(LINE_SENSOR_4_PIN);
                line_reached_right = outer_right_sensor_val == 1;
            }
        }
        if (!line_reached_left && !line_reached_right) reverse(WHEELBASE); //Line missed, backtrack a bit
        else part_done = true;
    }
    forward(5); //Move forward 5cm, off start area line so its not detected again in the second part"
    //Now there is a line to follow, until main line reached
    line_reached_left = false;
    line_reached_right = false;
    part_done = false;
    set_motor_speeds(MOTOR_SPEED_BASE, MOTOR_SPEED_BASE); //Initial movement
    while (!part_done) { //Second part is to move to the line to follow
        int count = 0;
        while(!line_reached_left && !line_reached_right && count < MAX_COUNT_2) {
            count++;
            delay(DELAY);
            if (!line_reached_left){ //Check for left detection if not detected already
                int outer_left_sensor_val = get_sensor_reading(LINE_SENSOR_3_PIN);
                line_reached_left = outer_left_sensor_val == 1;
            }
            if (!line_reached_right){ //Check for right detection if not detected already
                int outer_right_sensor_val = get_sensor_reading(LINE_SENSOR_4_PIN);
                line_reached_right = outer_right_sensor_val == 1;
            }
        }  
        if (!line_reached_left && !line_reached_right) reverse(WHEELBASE); //Gone too far, bactrack a bit
        else part_done = true;
    }
    //Main line reached, turn right on to line
    forward(WHEELBASE); //Move forward wheelbase of car (rear axle now over line)
    turn(-85, false); //Pivot round to face line
}

void go_back(){
    //to return to home at the end
    //we are either at fork with green/red box after dropping off block
    bool cont = true;

    if (fork_count<HOME){ //at green box
        forward(WHEELBASE); //So it does not accidentally read the fork for the green block twice
        while(cont) { //While yet to detect home fork
            follow_line(); //Line following loop
            delay(DELAY);
            cont = !(get_sensor_reading(LINE_SENSOR_4_PIN) == 0 && get_sensor_reading(LINE_SENSOR_3_PIN) == 1); //Check for fork on right (stop loop if there is)
        }
    }
    else if(fork_count>HOME){ //at red box
        turn(160, false); //Spin to face line
        delay(2000);
        while (cont){ //While yet to detect home fork (on left now)
            follow_line(); //Line following loop
            delay(DELAY);
            cont = !(get_sensor_reading(LINE_SENSOR_3_PIN) == 0 && get_sensor_reading(LINE_SENSOR_4_PIN) == 1); //Check for fork on left (stop loop if there is)
        }
    }

    forward(WHEELBASE); //Move forward wheelbase of car (rear axle now over line)
    if (fork_count<HOME) turn(-85, false); //Turn to face box (turn left if from red box, turn right if from green box)
    else turn(85, false); 

    forward(2.1*WHEELBASE); //Move forward into box        
}