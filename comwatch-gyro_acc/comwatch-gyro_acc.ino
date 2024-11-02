/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Pitch & Roll Accelerometer Example.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <MPU6050.h>
float yaw = 0;
int gest = 0;
unsigned long timer = 0;
float timeStep = 0.01;

MPU6050 mpu;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Initialize MPU6050");
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  mpu.calibrateGyro();
  mpu.setThreshold(3);
}

void loop()
{
  // Read normalized values 
  timer = millis();
  Vector normAccel = mpu.readNormalizeAccel();
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Pitch & Roll
  int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
  int roll = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;
  yaw = yaw + norm.ZAxis * timeStep;
  // Output
//  Serial.print(" Pitch = ");
//  Serial.println(pitch);
//  Serial.print(" Roll = ");
//  Serial.println(roll);
//  Serial.print("yaw = ");
//  Serial.println(yaw);
  delay((timeStep*1000) - (millis() - timer));


  if (pitch < -30){gest = 1;} //up
  else if (pitch > 30){gest = 2;} //down
  else if (roll > 100){gest = 3;}//left
  else if (roll < 10){gest = 4;}//right
  int yawsum = 0;
  for (int i = 0; i < 11; i++){
      yawsum = yawsum + yaw;
  }
  if((yaw-(yawsum/10))>8){gest =5;}
  
  Serial.println(gest);
  delay(1000);
  gest = 0;
}
