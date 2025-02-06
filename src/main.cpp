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
  int startIndex = data.indexOf(key) + key.length() + 1;
  int endIndex = data.indexOf(",", startIndex);
  if (endIndex == -1) endIndex = data.length();
  return data.substring(startIndex, endIndex).toInt();
}

// Scale two values to fit between -1 and 1 while maintaining their ratio
void scaleValues(double &val1, double &val2) {
    double maxAbs = max(abs(val1), abs(val2));
    if (maxAbs > 1.0 || maxAbs < -1.0) {
        double scale = 1.0 / maxAbs;
        val1 *= scale;
        val2 *= scale;
    }
}

void loop() {
  String data = "";
  while (HC12.available()) {
    Serial.write(HC12.read());
    data = HC12.readString();
  }

  if (data.length() > 0) {
    // Parse the received data
    double FORWARD = extractValue(data, "F");
    double TURN = extractValue(data, "T");

    // Scale the values while maintaining their ratio
    scaleValues(FORWARD, TURN);

    // Control motors with scaled values
    RightMotor.write((FORWARD - TURN));  // Convert -1 to 1 range to 0-180 range
    LeftMotor.write((FORWARD + TURN));
  }
  delay(1);
}