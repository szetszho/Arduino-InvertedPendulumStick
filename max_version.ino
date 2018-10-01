#include <Wire.h>
#include "GY_85.h"
#include <PID_v1.h>

const int motorIn1 = 9;
const int motorIn2 = 10;
double Setpoint, Input, Output, ang;
int a, ax, ay;

GY_85 GY85;
PID stickPID(&Input, &Output, &Setpoint, 1 , 0.06, 0.003, DIRECT);

void setup() {
  Wire.begin();
  Serial.begin(9600);
  GY85.init();
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  a = GY85.readFromAccelerometer();
  ax = GY85.accelerometer_x( a );
  ay = GY85.accelerometer_y( a );
  Input = (atan2(ay, ax) / PI * 180) + 90;
  Setpoint = 90;
  stickPID.SetMode(AUTOMATIC);
  stickPID.SetSampleTime(10);
}

void loop() {
  a = GY85.readFromAccelerometer();
  ax = GY85.accelerometer_x( a );
  ay = GY85.accelerometer_y( a );
  Input = (atan2(ay, ax) / PI * 180) + 90;
  if (Input < 90) {
    stickPID.SetControllerDirection(DIRECT);
    stickPID.Compute();
    analogWrite(motorIn1, 0);
    analogWrite(motorIn2, Output);
  } else
  {
    stickPID.SetControllerDirection(REVERSE);
    stickPID.Compute();
    analogWrite(motorIn1, Output);
    analogWrite(motorIn2, 0);
  }
  Serial.print(" Input:");
  Serial.print(Input);
  Serial.print(" Output:");
  Serial.println(Output);
}
