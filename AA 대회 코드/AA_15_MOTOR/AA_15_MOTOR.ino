/*
   rosserial Publisher Example
   Prints "hello world!"
*/
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int16.h>

//Steer

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from the pot
int Steer_Angle_Measure = 0;        // value output to the PWM (analog out)

#define NEURAL_ANGLE -1
#define LEFT_STEER_ANGLE  -30
#define RIGHT_STEER_ANGLE  30
#define MOTOR2_PWM 9
#define MOTOR2_ENA 10

int Steering_Angle = NEURAL_ANGLE;

/////////////////////////////////////// PID 제어 /////////////////////////////////////////////
float Kp = 3.5;
float Ki = 2.0;
float Kd = 7; //PID 상수 설정, 실험에 따라 정해야 함 중요!
double Setpoint, Input, Output; //PID 제어 변수
double error, error_old;
double error_s, error_d;
int pwm_output;
/////////////////////////////////////// stearing PID 제어 /////////////////////////////////////////////
void motor_control(int motor_pwm)
{
  if (motor_pwm > 0) // forward
  {
    digitalWrite(MOTOR2_ENA, HIGH);
    //digitalWrite(MOTOR2_ENB, LOW);
    analogWrite(MOTOR2_PWM, motor_pwm);
  }
  else if (motor_pwm < 0) // backward
  {
    digitalWrite(MOTOR2_ENA, LOW);
    //digitalWrite(MOTOR2_ENB, HIGH);
    analogWrite(MOTOR2_PWM, -motor_pwm);
  }
  else // stop
  {
    //digitalWrite(MOTOR2_ENA, LOW);
    //digitalWrite(MOTOR2_ENB, LOW);
    analogWrite(MOTOR2_PWM, 0);
  }
}

void PID_Control()
{
  error = Steering_Angle - Steer_Angle_Measure ;

  error_s += error;
  error_d = error - error_old;
  error_s = (error_s >=  100) ?  100 : error_s;
  error_s = (error_s <= -100) ? -100 : error_s;

  pwm_output = Kp * error + Kd * error_d + Ki * error_s;
  pwm_output = (pwm_output >=  255) ?  255 : pwm_output;
  pwm_output = (pwm_output <= -255) ? -255 : pwm_output;

  //if(pwm_output >=255) pwm_output = 255;
  //if(pwm_output <=-255) pwm_output = -255;
  if (error == 0)
  {
    motor_control(0);
    error_s = 0;
  }

  else          motor_control(pwm_output);
  error_old = error;

  //Serial.println(pwm_output);
}

void steering_control()
{
  if (Steering_Angle <= LEFT_STEER_ANGLE + NEURAL_ANGLE)  Steering_Angle  = LEFT_STEER_ANGLE + NEURAL_ANGLE;
  if (Steering_Angle >= RIGHT_STEER_ANGLE + NEURAL_ANGLE)  Steering_Angle = RIGHT_STEER_ANGLE + NEURAL_ANGLE;
  PID_Control();

  /*
    if(Steer_Angle_Measure == 0)
    {
    motor_control(0);
    }
    else if(Steer_Angle_Measure > 0)
    {
    motor_control(100);
    }
    else
    {
    motor_control(-100);
    }*/
}

//

/////arduino
#define encodPinA1 2                       // Quadrature encoder A pin
#define encodPinB1 3
#define encodPinA2 4                       // Quadrature encoder A pin
#define encodPinB2 5

//구
#define MOTOR1_PWM 11
#define MOTOR1_ENA 12

//구
#define MOTOR3_PWM 6
#define MOTOR3_ENA 7

volatile long encoderPos = 0;

void interrupt_setup(void)
{
  pinMode(encodPinA1, INPUT_PULLUP);                  // quadrature encoder input A
  pinMode(encodPinB1, INPUT_PULLUP);       // quadrature encoder input B
  pinMode(encodPinA2, INPUT_PULLUP);                  // quadrature encoder input A
  pinMode(encodPinB2, INPUT_PULLUP);
  attachInterrupt(0, encoder, FALLING);               // update encoder position
  TCCR1B = TCCR1B & 0b11111000 | 1;                   // To prevent Motor Noise
}

void encoder()
{ // pulse and direction, direct port reading to save cycles
  //Serial.println("interrupt");
  if (digitalRead(encodPinB1) == HIGH)    encoderPos--;          // if(digitalRead(encodPinB1)==HIGH)   count --;
  else                                 encoderPos++;             // if(digitalRead(encodPinB1)==LOW)   count ++;
  if (digitalRead(encodPinB2) == HIGH)    encoderPos--;          // if(digitalRead(encodPinB1)==HIGH)   count --;
  else                                 encoderPos++;             // if(digitalRead(encodPinB1)==LOW)   count ++;
}

void motor2_control(int motor2_pwm)
{

   if (motor2_pwm > 0) // forward
  {
    digitalWrite(MOTOR1_ENA, HIGH);
    //digitalWrite(MOTOR1_ENB, LOW);
    analogWrite(MOTOR1_PWM, motor2_pwm);

    digitalWrite(MOTOR3_ENA, HIGH);
    //digitalWrite(MOTOR3_ENB, LOW);
    analogWrite(MOTOR3_PWM, motor2_pwm);
  }
  else if (motor2_pwm < 0) // backward
  {

    digitalWrite(MOTOR1_ENA, LOW);
    //digitalWrite(MOTOR1_ENB, HIGH);
    analogWrite(MOTOR1_PWM, -motor2_pwm);

    digitalWrite(MOTOR3_ENA, LOW);
    //digitalWrite(MOTOR3_ENB, HIGH);
    analogWrite(MOTOR3_PWM, -motor2_pwm);
  }
  else
  {
    analogWrite(MOTOR1_PWM, 0);
    analogWrite(MOTOR3_PWM, 0);
  }

  

}


///



ros::NodeHandle  nh;

geometry_msgs::Twist cmd_vel;

/* rosserial test
  float cmd_velo;
  float cmd_ang;
*/
int velocity = -999;
int steer = 0;
void velCb(const geometry_msgs::Twist& msg) {
  velocity = (int)msg.linear.x;
  steer = (int)msg.angular.z;
  // cmd_ang = msg.angular.z;

}

void steervelCb(const std_msgs::Int16& msg) {

  steer = -(int)msg.data;
  // cmd_ang = msg.angular.z;
  if(steer >= RIGHT_STEER_ANGLE)  steer = RIGHT_STEER_ANGLE;
  if(steer <= LEFT_STEER_ANGLE)  steer = LEFT_STEER_ANGLE;
}

void speedvelCb(const std_msgs::Int16& msg) {
  velocity = (int)msg.data;
  // cmd_ang = msg.angular.z;
  
  if(velocity>=100) velocity =100;
  if(velocity<=-100) velocity =-100;
  
  

}

ros::Subscriber<geometry_msgs::Twist> cmd_sub("cmd_vel_out", velCb);
ros::Subscriber<std_msgs::Int16> cmd_sub2("Car_Control_cmd/SteerAngle_Int16", steervelCb);
ros::Subscriber<std_msgs::Int16> cmd_sub3("Car_Control_cmd/Speed_Int16", speedvelCb);
ros::Publisher cmd_pub("cmd_vel2", &cmd_vel);


void setup()
{
  Serial.begin(9600);
  // read the analog in value:
  //sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
 // Steer_Angle_Measure = map(sensorValue, 50, 1050, LEFT_STEER_ANGLE, RIGHT_STEER_ANGLE);

  // drive
  pinMode(MOTOR1_PWM, OUTPUT);
  pinMode(MOTOR1_ENA, OUTPUT);  // L298 motor control direction
  //pinMode(MOTOR1_ENB, OUTPUT);

  pinMode(MOTOR3_PWM, OUTPUT);
  pinMode(MOTOR3_ENA, OUTPUT);  // L298 motor control direction
  //pinMode(MOTOR3_ENB, OUTPUT);

  interrupt_setup();

  //Steer
  pinMode(MOTOR2_PWM, OUTPUT);
  pinMode(MOTOR2_ENA, OUTPUT);  // L298 motor control direction
  //pinMode(MOTOR2_ENB, OUTPUT);  // L298 motor control PWM

  error = error_s = error_d = error_old = 0.0;
  pwm_output = 0;


  nh.initNode();
  nh.advertise(cmd_pub);
  nh.subscribe(cmd_sub);
   nh.subscribe(cmd_sub2);
    nh.subscribe(cmd_sub3);

 //motor_control(50);
}

void loop()  
{
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  Steer_Angle_Measure = map(sensorValue, 50, 1050, LEFT_STEER_ANGLE, RIGHT_STEER_ANGLE);
  /*
  //rosserial test
  cmd_vel.linear.x = velocity;
  cmd_vel.angular.z = steer;
  cmd_pub.publish(&cmd_vel);
  //motor2_control(velocity);
*/
  if (velocity != -999)
    motor2_control(velocity);

 // motor_control(steer);P```````````````````````````````````
  Steering_Angle = NEURAL_ANGLE + steer;
  Serial.println(sensorValue);
  steering_control();

  nh.spinOnce();

/*
  Serial.print("pwm: ");
  Serial.println(motor2_pwm);
  delay(100);
*/

}
