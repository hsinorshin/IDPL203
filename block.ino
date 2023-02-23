/* 
    File for detecting, locating and dropping blocks, called when junction detected/hold=1  
*/

#include "header.h" 

int distance;
int block_colour; 
int fork_count;

void setup(){
    
}

void findblock(){
    //this is called because there is a fork detected and hold=0
    turn(BLOCK_ROTATION_ANGLE); //turn to face end of white line/potential object location 
    distance=get_US_reading();
    if (distance>50){
        //there's no block there!
        recover_to_line();
    }

    else if(distance<=50){
        //there is a block!
        //start recording movement 
        init_motor_history(); //
        update_motor_history();
        
        while(distance>2){
            follow_line();
            distance=get_US_reading();
            move_onto_line(); //I'm assuming this means we move onto the fork for now 
            follow_line();
        }
        //we're close enough to the block, stop
        set_motor_speeds(0,0);
        //get block colour 
        block_colour=get_sensor_reading(COLOUR_SENSOR_PIN); //need to convert analogue reading to int 
        blink(block_colour,5);
        grabblock();
        recover_to_line(); //change to reverse_movement 
        hold=1;

    }
}

void dropblock(){
    //called when hold=1 and first fork detected 
    fork_count=1;
    while (fork_count!=block_colour){
        follow_line();
        delay(50); //keep checking every 50ms 
        if (get_line_sensor_reading(LINE_SENSOR_3_PIN) ^ get_line_sensor_reading(LINE_SENSOR_4_PIN))fork_count++;
        
    }
    //found correct fork for block,start recording movement 
        init_motor_history();
        update_motor_history();
        turn(90);
        move_onto_line(); //I'm assuming this means we move onto the fork for now 
        follow_line();
        //if (line colour == block colour)
        stop();
        releaseblock();
        recover_to_line();
        hold=0;

    
}



void grabblock(){
    //controlling servos/claw position to grab the block 
    //open claw
    set_servo_position(150);
    delay(50);
    //close claw
    set_servo_position(50);

}

void releaseblock(){
    //open claw
    set_servo_position(150);
    delay(50);
    //close claw
    set_servo_position(50);
}
