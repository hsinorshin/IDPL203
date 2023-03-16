
/*
    Main file, containing main setup and loop
    Note that the actual arduino loop function is not used - line-following iterations occur in the find_block() 
    and drop_block() functions
*/
#include "header.h"

double start_time; //millis() value of the time when the button is pressed, when the competition is started
double time_left; //Calculated after every block is dropped off to check if there is time for another go round

void setup() { //Essentially the main function
    Serial.begin(9600); //Serial connection used in testing and debugging
    Serial.print("Hello!");

    //Setup
    setup_leds();
    setup_motors();
    setup_servo();
    setup_sensors();

} 

void loop() {

    //Start in open position for travelling (needs to open to traverse ramp)
    set_servo_position(OPEN_CLAW_POSITION);

    while(true){ //Wait for start button press
        int start=get_sensor_reading(START_BUTTON_PIN); 
        delay(DELAY);
         if (start==0){ 
            start_time = millis()/1000; //Get reference start time in seconds
            time_left=MATCH_TIME; //Start timer
            move_onto_line(); //move from home onto track
            break;
         }
    }

    //Main loop - each loop is a lap
    while(time_left>LAP_TIME + RETURN_TIME){ //Do another run there is time to both do another lap and return to start box
        find_block(); //attempt to find block
        drop_block(); //attempt to drop block
        time_left=MATCH_TIME - (millis()/1000 - start_time); //Calculate time left
    }

    //After n loops, return to the start box
    go_back();
    clap(); //Celebrate at the end!

}
