#include <SoftPWM.h>
#include <SoftPWM_timer.h>


#include <ArduinoBlue.h>




#include <Servo.h>
#include <SoftwareSerial.h>




const int servoPin = 11;
const int BLUETOOTH_TX = 2;
const int BLUETOOTH_RX = 3;


//const int ENA = A2;
//const int ENB = A3;
const int IN1 = 4;
const int IN2 = 5;
const int IN3 = 7;
const int IN4 = 6;
const int MINIMUM_MOTOR_SPEED = 40;




//variable
Servo myServo;
SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);
ArduinoBlue phone(bluetooth); // pass reference of bluetooth object to ArduinoBlue constructor.




//Senssor set up start
const int trigPin = 13;
const int echoPin = 12;
const int buzzer = 8;




const int redLED = 9;
long duration;
double distance;
double maxDistanceInches = 10; // this is how far we want our sensor to read, ignore everything farther than 10 inches.


void setup() {


  myServo.attach(servoPin);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzer, OUTPUT);
  pinMode(redLED, OUTPUT);
  digitalWrite(buzzer, LOW); // set all outputs low
  digitalWrite(redLED, LOW);


  //pinMode(ENA,OUTPUT);
  //pinMode(ENB,OUTPUT);
  pinMode(IN1,OUTPUT); //Logic pins are also set as output
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  //SoftPWMSet(ENA,50);
  //SoftPWMSet(ENB,50);


  Serial.begin(9600);
  bluetooth.begin(9600);// Bluetooth
  Serial.println("Setup complete");
  Serial.println("Button is ready");


}


int turn;
int button;


void motorBrake() {
  //digitalWrite(ENA, LOW);
  //digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  //digitalWrite(ENA, HIGH);
  //digitalWrite(ENB, HIGH);
  // Do not write the motor speeds on this function. It simply configures the motor controller.
}


// Configures the motor controller to have the robot move forward.
void motorSetForward() {
  delay(10);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // Do not write the motor speeds on this function. It simply configures the motor controller.
}


// Configures the motor controller to have the robot move backwards.
void motorSetBackward() {
  delay(10);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  // Do not write the motor speeds on this function. It simply configures the motor controller.
}


void driveControl() {
  // THROTTLE AND STEERING CONTROL
  // throttle values after subtracting 49:
  //     50 = max forward throttle
  //     0 = no throttle
  //     -49 = max reverse throttle
  // steering values after subtracting 49:
  //     50 = max right
  //     0 = straight
  //     -49 = max left
  int throttle = phone.getThrottle() - 49;
  int steering = phone.getSteering() - 49;


  if (throttle == 0) {
    // If the throttle is zero, don't move.
    motorBrake();
    return;
  }


  // Determine forwards or backwards.
  if (throttle > 0) {
    // Forward
    motorSetForward();
    delay(10);
  }
  else {
    // Backward
    motorSetBackward();
    delay(10);
  }


  // Map throttle to PWM range.
  int mappedSpeed = map(abs(throttle), 0, 50, MINIMUM_MOTOR_SPEED, 255);
  // Map steering to PWM range.
  int reducedSpeed = map(abs(steering), 0, 50, mappedSpeed, MINIMUM_MOTOR_SPEED);


  int leftMotorSpeed, rightMotorSpeed;
  if (steering > 0) {
    // Turn Right: reduce right motor speed
    leftMotorSpeed = mappedSpeed;
    rightMotorSpeed = reducedSpeed;
  }
  else {
    // Turn Left: reduce left motor speed
    leftMotorSpeed = reducedSpeed;
    rightMotorSpeed = mappedSpeed;
  }




  // Set motor speeds
  //analogWrite(ENB, 50);
  //analogWrite(ENA, 50);


  // Print Debug Info
  Serial.print("throttle: "); Serial.print(throttle);
  Serial.print("\tsteering: "); Serial.print(steering);
  /*Serial.print("\tmappedSpeed: "); Serial.print(mappedSpeed);
  Serial.print("\treducedSpeed: "); Serial.print(reducedSpeed);
  Serial.print("\tleftMotorSpeed: "); Serial.print(leftMotorSpeed);
  Serial.print("\trightMotorSpeed: "); Serial.println(rightMotorSpeed);*/
  }


int pos = 0;
void CW(){
  for (pos = 0; pos <= 180; pos += 10) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myServo.write(pos);// tell servo to go to position in variable 'pos'
    delay(15);
  }
}
void CCW(){
  for (pos = 180; pos >= 0; pos -= 10) { // goes from 180 degrees to 0 degrees
    myServo.write(pos);// tell servo to go to position in variable 'pos'
    delay(15);// waits 15ms for the servo to reach the position
  }
}


void loop() {
  driveControl();
  button = phone.getButton();
  delay(10);


  if (button == 1){
  CW();
  }
  else if(button == 2){
  CCW();
  }




  digitalWrite(trigPin, LOW);
  delayMicroseconds(15);  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(15);




  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);


  // Calculating the distance in cm
  distance = duration * 0.034 / 2;


  //to convert cm to inches
  distance = distance / 2.54;


  //Light up light depending on distance!
  if(distance < maxDistanceInches*0.3){
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzer, HIGH); // if box too close to sensor start the alarm!!
  }
  else{
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer,LOW); // if not close turn off alaram
  }
  //Serial.println(ENA);
  //Serial.println(ENB);
  //Serial.print("Distance: ");
  //Serial.println(distance);


  /*turn = map(steering,0,49,0,99);
  Serial.println("Throttle: ");
  Serial.print(throttle);
  Serial.println("Steering: ");
  Serial.print(steering);
  //myServo.write(turn);*/
}
