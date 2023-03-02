//Arduino pin constants

#define START_BUTTON_PIN 2
#define AMBER_INDICATOR_LED_PIN 3
#define RED_INDICATOR_LED_PIN 4
#define GREEN_INDICATOR_LED_PIN 5
#define LINE_SENSOR_1_PIN A2 //Inner left line sensor
#define LINE_SENSOR_2_PIN A3 //Inner right line sensor
#define LINE_SENSOR_3_PIN 12 //Outer left line sensor
#define LINE_SENSOR_4_PIN 13 //Outer right line sensor
#define COLOUR_SENSOR_PIN 11
#define US_TRIG_PIN 6
#define US_ECHO_PIN 7
#define L_MOTOR_PORT 1
#define R_MOTOR_PORT 3
#define SERVO_PIN 9

//Other constants
//all distances in cm, angle in degrees, time in seconds
#define DELAY 50 //in ms, how long to wait between iterations
#define WHEELBASE 12.5
#define BLOCK_ROTATION_ANGLE 45
#define MOTOR_SPEED_TURNING_DIFF 150
#define MOTOR_SPEED_BASE 255
#define GRABBER_BLOCK_DIST 1
#define OPEN_CLAW_POSITION 180
#define CLOSE_CLAW_POSITION 0
#define DETECTION_CLAW_POSITION 10
#define SERVO_GEAR_RATIO 1.5
#define FORK_DISTANCE 50
#define BLUE 1
#define HOME 2
#define RED 3
#define MATCH_TIME 300
#define LAP_TIME 60
#define AXLE_LENGTH 25.7
#define WHEEL_RADIUS 4
extern double time_left;
extern int start;
extern int hold; //1 if the robot is handling a block
extern int fork_count;
extern bool last_offset; //true if to the right, false if to the left

//FUNCTION PROTOTYPES

//test.ino
void led_connection_test();
void motor_servo_test();
void sensor_test();
void path_test();

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