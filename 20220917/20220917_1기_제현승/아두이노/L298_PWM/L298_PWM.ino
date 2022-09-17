#define IN1 8
#define IN2 9
#define ENA 10

int motor_pwm = 127;

void setup() {
  // put your setup code here, to run once:
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
 
}

void loop() {
  // put your main code here, to run repeatedly:

analogWrite(ENA,motor_pwm);
delay(0.5);
}
