//Arduino pin constants

#define START_BUTTON_PIN 2
#define RED_INDICATOR_LED_PIN 5
#define GREEN_INDICATOR_LED_PIN 4
#define AMBER_INDICATOR_LED_PIN 3 
#define LINE_SENSOR_1_PIN 13 //Inner left line sensor
#define LINE_SENSOR_2_PIN 12 //Inner right line sensor
#define LINE_SENSOR_3_PIN A3//Outer left line sensor
#define LINE_SENSOR_4_PIN A2 //Outer right line sensor
#define COLOUR_SENSOR_PIN 11
#define US_TRIG_PIN 6
#define US_ECHO_PIN 7
#define L_MOTOR_PORT 1
#define R_MOTOR_PORT 3
#define SERVO_PIN 9

//Other constants
//all distances in cm, angle in degrees, time in seconds
#define DELAY 25 //in ms, how long to wait between iterations
#define WHEELBASE 13 //Distance from rake to point of contact of rear wheels
#define BLOCK_ROTATION_ANGLE 45 //Angle to rotate to point towards block for picking up
#define MOTOR_SPEED_BASE 250 //Motor values
#define OPEN_CLAW_POSITION 65 //These claw positions need to be amended during servo calibration
#define CLOSE_CLAW_POSITION 10 //Ideally have these values around mid-range, i.e., 90
#define DETECTION_CLAW_POSITION 10 

#define BLUE 1 //The positions of the different bays i.e., traversing anticlockwise, blue is first, then the home bay, then red
#define HOME 2
#define RED 3
#define MATCH_TIME 300 //The 
#define LAP_TIME 70 //Upper bound on the time to complete a lap, including picking up and dropping off black
#define RETURN_TIME 20 //Upper bound on the time needed after dropping of a block to return to the start box
#define AXLE_LENGTH 25.7 //From one rear wheel to another
#define WHEEL_RADIUS 4

extern double time_left;
extern int start;
extern int fork_count;
extern bool last_offset; //true if to the right, false if to the left

//FUNCTION PROTOTYPES

//test.ino
void led_connection_test();
void motor_servo_test();
void sensor_test();
void path_test();
void block_handling_test();

//navigation.ino
void follow_line();
void recover_to_line();
void move_onto_line();
void go_back();

//motor.ino
void setup_motors();
void setup_servo();
void set_motor_speeds(int left_motor_speed, int right_motor_speed);
void set_servo_position(int angle);
int get_left_motor_speed();
int get_right_motor_speed();
void clap();

//sensor.ino
void setup_sensors();
int get_sensor_reading(int sensor_pin);
int get_US_reading();
int get_line_sensor_reading(int sensor_pin);

//led.ino
void setup_leds();
void set_led_val(int led_pin, bool val);
void blink(int led_pin, int times);


//block.ino
void find_block();
void drop_block();
void grab_block();
void release_block();

//movement.ino
void turn(int angle);
void reverse(int distance);
void forward(int distance);
void stop(); 