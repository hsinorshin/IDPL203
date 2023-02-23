//Arduino pin constants

#define START_BUTTON_PIN 17
#define AMBER_INDICATOR_LED_PIN 18
#define RED_INDICATOR_LED_PIN 19
#define GREEN_INDICATOR_LED_PIN 20
#define LINE_SENSOR_1_PIN 27 //Inner left line sensor
#define LINE_SENSOR_2_PIN 28 //Inner right line sensor
#define LINE_SENSOR_3_PIN 12 //Outer left line sensor
#define LINE_SENSOR_4_PIN 11 //Outer right line sensor
#define RED_SENSOR_LED_PIN 23
#define GREEN_SENSOR_LED_PIN 24
#define BLUE_SENSOR_LED_PIN 25
#define COLOUR_SENSOR_PIN 26
#define US_TRIG_PIN 21
#define US_ECHO_PIN 22
#define L_MOTOR_PORT 1
#define R_MOTOR_PORT 3

//Other constants

#define BLOCK_ROTATION_ANGLE 45
#define MOTOR_SPEED_TURNING_DIFF 250
#define MOTOR_SPEED_BASE 50


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
void update_motor_history(int left_val, int right_val, int time);
void init_motor_history();

//motor.ino
void setup_motors();
void setup_servo();
void set_motor_speeds(int left_motor_speed, int right_motor_speed);
void set_servo_position();
int get_left_motor_speed();
int get_right_motor_speed();

//sensor.ino
void setup_sensors();
int get_sensor_reading(int sensor_pin);

//led.ino
void setup_leds();
void set_led_val(int led_pin, bool val);



