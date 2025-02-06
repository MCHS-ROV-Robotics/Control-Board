#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>


//Motor Pins
byte RightMotorID = 9;
byte LeftMotorID = 10;
byte BallastLeftID = 11;
byte BallastRightID = 12;

SoftwareSerial HC12(16, 17); // HC-12 TX Pin, HC-12 RX Pin

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
  HC12.begin(9600);               // Serial port to HC12
  
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

// Helper function to extract value from data string
int extractValue(String data, String key) {
  int startIndex = data.indexOf(key + ":") + key.length() + 1;
  int endIndex = data.indexOf(",", startIndex);
  if (endIndex == -1) endIndex = data.length();
  return data.substring(startIndex, endIndex).toInt();
}

void loop() {
  String data = "";
  while (HC12.available()) {
    Serial.write(HC12.read());
    data = HC12.readString();
  }

  if (data.length() > 0) {
    // Parse the received data
    int RightX = extractValue(data, "RX");
    int RightY = extractValue(data, "RY");
    int LeftX = extractValue(data, "LX");
    int LeftY = extractValue(data, "LY");

    // Control motors with parsed values
    RightMotor.writeMicroseconds(LeftX-LeftY);
    LeftMotor.writeMicroseconds(LeftY);
    // You can add control for other motors here
    
    Serial.println("Parsed - RX:" + String(RightX) + ",RY:" + String(RightY) + 
                  ",LX:" + String(LeftX) + ",LY:" + String(LeftY));
  }
  delay(1);
}