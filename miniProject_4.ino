#include <FirebaseESP8266.h>
#include <Arduino.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <Servo.h>

int dht=2,motor=13;
float temperatur=0.0;
DHT suhu(dht, DHT11);
WiFiClient net;
Servo myservo;
FirebaseData firebase;

void setup() {
  Serial.begin(9600);
  WiFi.begin("sotomie","kuahnyasedep");
  Firebase.begin("https://miniproject4-iot.firebaseio.com/","7G1uoIXmdF5LelYUVfxv2G2cZtipMODIDXwo2IHZ");
  pinMode(dht,INPUT_PULLUP);
  myservo.attach(motor);
  suhu.begin();
}

void loop() {
  float t=suhu.readTemperature();
  if(!isnan(t)){
    if(temperatur!=t){
      temperatur=t;
      Firebase.setFloat(firebase,"Suhu",temperatur);
    }
  }
  Firebase.getString(firebase,"Motor");
  if(firebase.stringData()=="On"){
    for(int angle = 0; angle < 180; angle+=5){                          
      myservo.write(angle);
      delay(5);                       
    } 
    delay(500);
    for(int angle = 180; angle>=1; angle-=5){                                
      myservo.write(angle);
      delay(5);                       
    }
    Firebase.setString(firebase,"Motor","Off");
    delay(500);
  }
}
