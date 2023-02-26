/* 
    File for detecting, locating and dropping blocks, called when junction detected/hold=1  
*/

#include "header.h" 

int distance;
int block_colour; 
int fork_count;


void find_block(){
    //called because there is a fork detected and hold=0
    reverse(5);
    turn(BLOCK_ROTATION_ANGLE); //pivot to face end of fork
    distance=get_sensor_reading(US_ECHO_PIN);
    if (distance>10){
        //there's no block there!
        turn(-BLOCK_ROTATION_ANGLE);
        follow_line();
    }

    else if(distance<=10){
        //there is a block!
        
        // while(distance>GRABBER_BLOCK_DIST){
        //     follow_line();
        //     distance=get_sensor_reading(US_ECHO_PIN);
        //     move_onto_line(); //I'm assuming this means we move onto the fork for now 
        //     follow_line();
        // }

        //get block colour 
        block_colour=get_sensor_reading(COLOUR_SENSOR_PIN); //need to convert analogue reading to int 
        blink(block_colour,5);
        grabblock();
        turn(-BLOCK_ROTATION_ANGLE); 
        follow_line();
        hold=1;

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
        releaseblock();
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
