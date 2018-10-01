#include "GY_85.h"
#include <Wire.h>
#include <math.h>

GY_85 GY85;     //create the object
const int motorIn1 = 9;
const int motorIn2 = 10;


void setup()

{
  Wire.begin();
  Serial.begin(9600);
  GY85.init();
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);

}

double last_ang;
double rp = 1.2;
double rd = 0.6;


void loop() {
  int a = GY85.readFromAccelerometer();
  int ax = GY85.accelerometer_x( a );
  int ay = GY85.accelerometer_y( a );
  double ang = atan2(ay, ax) / PI * 180;
  double dif = ang - last_ang;
  double ro = rp * -ang + rd * -dif;
  last_ang = ang;

  if (ro < 0) {
    analogWrite(motorIn1, -ro);
    analogWrite(motorIn2, 0);
  }
  else {
    analogWrite(motorIn1, 0);
    analogWrite(motorIn2, ro);
  }

  char tbs[100];
  sprintf(tbs, "ax:%4d ay:%4d", ax, ay);
  Serial.print(tbs);
  Serial.print(" ang:");
  Serial.print(ang);
  Serial.print(" dif:");
  Serial.print(dif);
  Serial.print(" ro:");
  Serial.println(ro);
}

