#include <Arduino.h>
#include <Servo.h>

//Motor Pins
byte RightMotorID = 9;
byte LeftMotorID = 10;
byte BallastLeftID = 11;
byte BallastRightID = 12;

//Controller Pins (Y=Up/Down, X=Left/Right)
byte LXID = A1; // Left X
byte LYID = A2; // Left Y
byte RXID = A3; // Right X


//Motors
Servo RightMotor;
Servo LeftMotor;
Servo BallastLeft;
Servo BallastRight;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  RightMotor.attach(RightMotorID);
  LeftMotor.attach(LeftMotorID);
  BallastLeft.attach(BallastLeftID);
  BallastRight.attach(BallastRightID);

 RightMotor.writeMicroseconds(1500);
 LeftMotor.writeMicroseconds(1500);
 BallastLeft.writeMicroseconds(1500);
 BallastRight.writeMicroseconds(1500);

 delay(7000); // delay to allow the ESC to recognize the stopped signal
  
}

void loop() {
int RightX = analogRead(A0);
int RightY = analogRead(A1);
int LeftX = analogRead(A2);
int LeftY = analogRead(A3);
  // put your main code here, to run repeatedly:
  Serial.println("RX:"+String(RightX)+"\n"+"RY:" + String(RightY) + "\n"+"LX:" + String(LeftX) + "\n"+"LY:" + String(LeftY));
servo.writeMicroseconds(val);
  delay(1);
}

