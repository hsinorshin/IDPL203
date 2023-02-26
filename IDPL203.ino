/*
    Main file, containing main setup and line-following loop
*/
#include <ctime>
#include "header.h"

time_t start_time=time(0);



void setup() {
    Serial.begin(9600);
    Serial.print("Hello!");
    setup_motors();
    //setup_sensors();
    //setup_leds();
    //led_connection_test();
    path_test();
    delay(10000);
    set_motor_speeds(MOTOR_SPEED_BASE, MOTOR_SPEED_BASE);

}

void loop() {
    /*we are always in 4 main states 
    1. start/move on line 
    2. find block
    3. drop block
    4. end/ back to base */ 
    /*move-> path detected -> if hold=0 -> find block-> detect block colour-> get block -> */

    //hardware initialisation
    setup_motors();
    setup_leds();
    setup_sensors();
    setup_servo();

    //START
    while(true){
        start=get_sensor_reading(START_BUTTON_PIN);
        if (start==1){
            time_left=MATCH_TIME;
            move_onto_line(); //move from home onto track
            break;
        }
        else{
            ;
        }
    }

    //keep trying to make laps and collect block when there's time
    while(time_left>LAP_TIME){
        
        find_block(); //attempt to find block
        if ((hold==0) && fork_count==2){
            fork_count--;
            find_block();
        }
        drop_block(); //attempt to drop block
        time_left=MATCH_TIME - difftime(time(0),start_time);
    }
    
    //return to START area
    go_back();


}
