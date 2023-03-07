/* 
    File for detecting, locating and dropping blocks, called when junction detected/hold=1  
*/

#include "header.h" 

int distance;
int block_colour; 
int fork_count;


void find_block(){
    const int BLOCK_THRESHOLD_DETECT = 30;
    const int BLOCK_THRESHOLD_COLLECT = 30;
    //called when hold=0
    fork_count=0;
    //while(fork_count<2) works for now... but is there a way to make it more general(?)
    while(fork_count<2){
        delay(DELAY);
        follow_line();
        if (get_sensor_reading(LINE_SENSOR_3_PIN)==0 && get_sensor_reading(LINE_SENSOR_4_PIN)==1){
            fork_count++;
            stop();
            int normal_distance = get_sensor_reading(US_ECHO_PIN);
            delay(1000);
            reverse(5);
            turn(BLOCK_ROTATION_ANGLE, false); //pivot to face end of fork
            int forward_count = 0;
            const int MAX_FORWARD_COUNT = 20;
            bool block_found = false;
            while(!block_found && forward_count < MAX_FORWARD_COUNT) {
              forward_count++;
              forward(1);
              stop();
              int distance = get_sensor_reading(US_ECHO_PIN);
              Serial.println(distance);
              if (normal_distance - distance > BLOCK_THRESHOLD_COLLECT) block_found = true;
            }
            if (!block_found){
                //there's no block there!
                //turn(-BLOCK_ROTATION_ANGLE, false);
                Serial.println("No block");
                reverse(1*forward_count);
                turn(-BLOCK_ROTATION_ANGLE, false);
                forward(20);
                continue;
            }
    
            else{
                //there is a block!
                //get block colour 
                reverse(2); //Slight move backward for detecting
                set_servo_position(DETECTION_CLAW_POSITION); //Set claw to be in position to detect block
                delay(1000);
                int block_colour=get_sensor_reading(COLOUR_SENSOR_PIN); //need to convert analogue reading to int 
                int led_pin;
                Serial.println(block_colour);
                if (block_colour == 0) 
                {
                  block_colour = 3;
                  led_pin = RED_INDICATOR_LED_PIN;
                }
                else {
                  block_colour = 1;
                  led_pin = GREEN_INDICATOR_LED_PIN;
                }
                set_led_val(led_pin, true);
                delay(5000);
                set_led_val(led_pin, false);
            
                 //Slight move forward for grabbing
                grab_block();
                hold=1;
                reverse(2*forward_count);
                turn(-BLOCK_ROTATION_ANGLE, false);
                forward(10);
                Serial.println("Yes block");
                break;

                
            }
        }
    }
}

void drop_block(){
    //called when hold=1 
    fork_count=0;
    block_colour = 3;
    //while (fork_count!=block_colour){
    while (fork_count<3) {
        delay(DELAY);
        follow_line();
        if (get_sensor_reading(LINE_SENSOR_3_PIN)==1 && get_sensor_reading(LINE_SENSOR_4_PIN)==0) {
            fork_count++;
            Serial.print(fork_count);
            Serial.print(" ");
            Serial.println(block_colour);
            if (fork_count == block_colour) {
              stop();
              turn(-70, false);
              forward(15);
              release_block();
              reverse(15);
              turn(70, false);
              //hold=0;   
              delay(1000);
              forward(5);
              break;
            }
            else delay(3000);
        }

        
    }

   
}


void grab_block(){
    //controlling servos/claw position to grab the block 
    //open claw
    set_servo_position(OPEN_CLAW_POSITION);
    forward(3);
    //close claw
    set_servo_position(CLOSE_CLAW_POSITION);
    delay(1000);

}

void release_block(){
    //open claw
    set_servo_position(OPEN_CLAW_POSITION);
    delay(1000);

}
