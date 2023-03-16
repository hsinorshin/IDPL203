/* 
    File for detecting, locating and dropping blocks, called when junction detected/hold=1  
*/

#include "header.h" 

int block_colour; /*Integer representation of the identified block - starts as 0 or 1 depending on if the block
is blue or brown, then is converted to the fork number of the correct bay to put the block in */
int fork_count; //To count the number of forks on the right or left passed to ensure we stop at the correct one

void find_block(){ //Behaviour for finding where the block is and picking up a block
    const int BLOCK_THRESHOLD_COLLECT = 30;
    fork_count=0; 
    while(fork_count<2){ //Will check at a maximum of 2 forks
        delay(DELAY); //Delay for line following loop to reducing processing
        follow_line(); //Line following loop until fork found
        if (get_sensor_reading(LINE_SENSOR_3_PIN)==0 && get_sensor_reading(LINE_SENSOR_4_PIN)==1){ //If fork detected
            fork_count++;
            stop();
            int normal_distance = get_sensor_reading(US_ECHO_PIN); //Baseline US distance reading (i.e., distance to floor)
            delay(1000);
            reverse(5);
            turn(BLOCK_ROTATION_ANGLE, false); //reverse and pivot to face end of fork
            int forward_count = 0;
            const int FORWARD_STEP = 1; //in cm, how far the robot moves forward with each step before checking for a block again (Should be much less than the width of the block)
            const int MAX_FORWARD_COUNT = 20 / FORWARD_STEP; //Set max number of iterations so robot moves forward at most 20cm
            bool block_found = false;
            while(!block_found && forward_count < MAX_FORWARD_COUNT) { //Keep moving forward until block found or moved forward max distance
              forward_count++;
              forward(FORWARD_STEP);
              stop();
              int distance = get_sensor_reading(US_ECHO_PIN);
              Serial.println(distance);
              if (normal_distance - distance > BLOCK_THRESHOLD_COLLECT) block_found = true; //Block found if significant reducing in the distance reading, defined by BLOCK_THRESHOLD_COLLECT
            }
            if (!block_found){
                //there's no block there! Return and try the next one
                reverse(1*forward_count+3);
                turn(-BLOCK_ROTATION_ANGLE, false);
                forward(15); //Forward past fork so we don't accidentally start following the fork!
                continue;
            }
    
            else{
                //there is a block!
                //get block colour 
                reverse(2.5); //Slight move backward for detecting
                set_servo_position(DETECTION_CLAW_POSITION); //Set claw to be in position to detect block
                reverse(1); //Reverse to push the block back into the correct place for colour detection
                delay(1000);
                block_colour=get_sensor_reading(COLOUR_SENSOR_PIN); //need to convert analogue reading to int 
                int led_pin; 
                //Convert block colour and set correct LED to flash
                if (block_colour == 0) //If brown
                {
                  block_colour = 3;
                  led_pin = RED_INDICATOR_LED_PIN;
                }
                else { //If blue
                  block_colour = 1;
                  led_pin = GREEN_INDICATOR_LED_PIN;
                }
                //Flash LED for 5 seconds
                set_led_val(led_pin, true);
                delay(5000);
                set_led_val(led_pin, false);
            
                 //Slight move forward for grabbing
                grab_block();
                //Return to start area
                reverse(1*forward_count+3);
                turn(-BLOCK_ROTATION_ANGLE, false);
                forward(15); //Forward past fork so we don't accidentally start following the fork!
                break;              
            }
        }
    }
}

void drop_block(){ //Behaviour for carrying the block to the correct place and dropping it off
    fork_count=0; //Reset fork count
    while (fork_count<3) { //Iterate until block dropped
        delay(DELAY);
        follow_line(); //Line following loop
        if (get_sensor_reading(LINE_SENSOR_3_PIN)==1 && get_sensor_reading(LINE_SENSOR_4_PIN)==0) { //Detect fork on right
            fork_count++;
            if (fork_count == block_colour) { //Drop if at correct fork
              stop();
              turn(-70, false); //Clockwise
              forward(15);
              release_block();
              reverse(15);
              turn(70, false); //Anticlockwise
              delay(1000);
              forward(5);
              break;
            }
            else forward(3); //If at incorrect fork, hard code small forward movement so the line sensors are off line
                             //So we dont accidentally detect and increment on the same fork multiple times!
        }
    }
}


void grab_block(){ //controlling servos/claw position to grab the block 
    //open claw
    set_servo_position(OPEN_CLAW_POSITION);
    //close claw
    set_servo_position(CLOSE_CLAW_POSITION);
    delay(1000);

}

void release_block(){ //controlling servos/claw position to release the block 
    //open claw
    set_servo_position(OPEN_CLAW_POSITION);
    delay(1000);

}

