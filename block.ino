/* 
    File for detecting, locating and dropping blocks, called when junction detected/hold=1  
*/

#include header.h 

void setup(){
    
}

void findblock(){
    //this is called because there is a fork detected and hold=0
    
    int distance;
    distance=get_US_reading();
    if (distance>50){

    }
}

void dropblock(){

}

void detect_block_colour(){

}
