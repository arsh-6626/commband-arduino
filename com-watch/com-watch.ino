#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;
struct MyData {
  byte X;
  byte Y;
  byte Z;
};

MyData data;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  }

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -17000, 17000, 0, 255);  // X axis data
  data.Y = map(ay, -17000, 17000, 0, 255); // Y axis data
  data.Z = map(az, -17000, 17000, 0, 255);   // delay(100);

  int xr = data.X;
  int yr = data.Y;
  int zr = data.Z;

 Serial.println(zr);
  delay(100);
}