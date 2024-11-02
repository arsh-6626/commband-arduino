#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

#define WIFI_SSID "mi"
#define WIFI_PASSWORD "qwertyuiop"
#define DATABASE_URL "commwatch-acfad-default-rtdb.firebaseio.com"
#define API_KEY "AIzaSyDPtH-m8MbT2a2IvPHzLss7hl70641qkOE"
#define USER_EMAIL "arshabbas636@gmail.com"
#define USER_PASSWORD "arshabbas1005"
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
unsigned long count = 0;

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;
int gest = 0;
struct MyData {
  byte X;
  byte Y;
};

MyData data;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;
   Firebase.begin(&config, &auth);
   Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);
  config.timeout.wifiReconnect = 10 * 1000;
  config.timeout.socketConnection = 10 * 1000;
  config.timeout.serverResponse = 10 * 1000;
  config.timeout.rtdbKeepAlive = 45 * 1000;
  config.timeout.rtdbStreamReconnect = 1 * 1000;
  config.timeout.rtdbStreamError = 3 * 1000;
 
  }

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -17000, 17000, 0, 255);  // X axis data
  data.Y = map(ay, -17000, 17000, 0, 255);  // Y axis data
  // delay(100);
  int xr = data.X;
  int yr = data.Y;

  //data analysis
  // Serial.print("Axis X = ");
  // Serial.print(xr);
  // Serial.print("  ");
  // Serial.print("Axis Y = ");
  // Serial.println(yr);


  //gesture  - right turn(x unchanged, y (0-20)
  if (yr < 20) {
    gest = 1;
  }
  // gesture - left turn
  else if (yr > 230 and yr < 250) {
    gest = 2;
  }
  //gesture - 3 frontflip
  else if (xr > 225 and xr < 250) {
    gest = 3;
  }

  //gesture 4 - backflip
  else if (xr < 30) {
    gest = 4;
  } 
  else {
    gest = 0;
  }
   if (Firebase.ready() && (millis() - sendDataPrevMillis > 100 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    Serial.printf("Set int... %s\n", Firebase.setInt(fbdo, F("comm/gest"), gest) ? "ok" : fbdo.errorReason().c_str());
    Serial.println(gest);
    Serial.println(xr);
    Serial.println(yr);
  }
delay(1000);
}
