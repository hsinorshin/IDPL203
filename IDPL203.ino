
/*
    Main file, containing main setup and line-following loop
*/
#include <time.h>
#include "header.h"
#include <hcsr04.h>

time_t start_time=time(0);
HCSR04 hcsr04(US_TRIG_PIN, US_ECHO_PIN, 20, 4000);
int hold;

void setup() {
    Serial.begin(9600);
    Serial.print("Hello!");
    setup_motors();
    setup_servo();
    setup_sensors();
    setup_leds();
    //for (int i=0; i<6; i++){
      //delay(1000);
      //set_servo_position(i*10);
    //}

    set_servo_position(OPEN_CLAW_POSITION);

/*
    set_servo_position(OPEN_CLAW_POSITION);
    delay(3000);
    set_servo_position(CLOSE_CLAW_POSITION);
    */

    //led_connection_test();
    //block_handling_test();
    //path_test();
    //delay(5000);

    while(true){
        int start=get_sensor_reading(START_BUTTON_PIN);
        delay(DELAY);
         if (start==0){ //TODO change to 0
            //time_left=MATCH_TIME;
            move_onto_line(); //move from home onto track
            break;
         }
    }

    hold = 0;

    //while(time_left>LAP_TIME){
    find_block(); //attempt to find block
    // if ((hold==0) && fork_count==2){ //If block not found, try to find block at next left fork
    //     fork_count--;
    //     reverse(20);
    //     find_block();
    // }
    drop_block(); //attempt to drop block
      //time_left=MATCH_TIME - difftime(time(0),start_time);
    //}
    go_back();

}

void loop() {
  //follow_line();
  //find_block();
  //drop_block();
    /*we are always in 4 main states 
    1. start/move on line 
    2. find block
    3. drop block
    4. end/ back to base */ 
    /*move-> path detected -> if hold=0 -> find block-> detect block colour-> get block -> */
/*
    //hardware initialisation
    //
    setup_motors();
    setup_leds();
    setup_sensors();
    setup_servo();

    //START
    bool started = false;
    while(!started){
        start=get_sensor_reading(START_BUTTON_PIN);
        if (start==1){
            time_left=MATCH_TIME;
            move_onto_line(); //move from home onto track
            started = true;
            break;
        }
        else{
            ;
        }
        */
    }

//void loop() {
    /*we are always in 4 main states 
        1. start/move on line 
     2. find block
     3. drop block
     4. end/ back to base */ 
     /*move-> path detected -> if hold=0 -> find block-> detect block colour-> get block -> */

     //START
     /*while(true){
        start=get_sensor_reading(START_BUTTON_PIN);
         if (start==1){
            time_left=MATCH_TIME;
             move_onto_line(); //move from home onto track
             break;
         }
         else{
             ;
         }
     }*/

     //keep trying to make laps and collect block when there's time
     //while(time_left>LAP_TIME){
     /*   
        find_block(); //attempt to find block
        if ((hold==0) && fork_count==2){ //If block not found, try to find block at next left fork
            fork_count--;
            find_block();
        }
        drop_block(); //attempt to drop block
        time_left=MATCH_TIME - difftime(time(0),start_time);
    }
    */
    
     //return to START area
     //go_back();


  //}*/
