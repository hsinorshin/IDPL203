/* 
    File for detecting, locating and dropping blocks, called when junction detected/hold=1  
*/

#include "header.h" 

int distance;
int block_colour; 


void find_block(){
    //called when hold=0
    fork_count=0;
    //while(fork_count<2) works for now... but is there a way to make it more general(?)
    while(fork_count<2){
        delay(50);
        follow_line();
        if (get_sensor_reading(LINE_SENSOR_3_PIN) ^ get_sensor_reading(LINE_SENSOR_4_PIN)){
            fork_count++;
            reverse(5);
            turn(BLOCK_ROTATION_ANGLE); //pivot to face end of fork
            distance=get_sensor_reading(US_ECHO_PIN);
            if (distance>10){
                //there's no block there!
                turn(-BLOCK_ROTATION_ANGLE);
                continue;
            }
    
            else if(distance<=10){
                //there is a block!
                //get block colour 
                block_colour=get_sensor_reading(COLOUR_SENSOR_PIN); //need to convert analogue reading to int 
                blink(block_colour,5);
                grab_block();
                turn(-BLOCK_ROTATION_ANGLE); 
                hold=1;
                break;
                
            }
        }
    }

    
}

void drop_block(){
    //called when hold=1 
    fork_count=0;
    while (fork_count!=block_colour){
        delay(50);
        follow_line();
        if (get_sensor_reading(LINE_SENSOR_3_PIN) ^ get_sensor_reading(LINE_SENSOR_4_PIN))fork_count++;
        
    }
    //found correct fork for block
        turn(-BLOCK_ROTATION_ANGLE);
        release_block();
        turn(BLOCK_ROTATION_ANGLE);
        follow_line();
        hold=0;    
   
}


void grab_block(){
    //controlling servos/claw position to grab the block 
    //open claw
    set_servo_position(180);
    delay(50);
    //close claw
    set_servo_position(50);

}

void release_block(){
    //open claw
    set_servo_position(180);
    delay(50);
}
