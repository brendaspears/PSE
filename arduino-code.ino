#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h> 

#define ONE_WIRE_BUS 8
#define RELAY_ON 0
#define RELAY_OFF 1
#define RELAY_1  2
#define FIREBASE_HOST "pervasive-software-engineering-default-rtdb.firebaseio.com" 
#define FIREBASE_AUTH "AIzaSyBrqMObXKSIfeZvwGex4oIh0K1wkFJGaEU" 
#define WIFI_SSID "Bng"
#define WIFI_PASSWORD "bng010101" 

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

Servo servo_9;

int n = 0; 
float Celsius = 0;
float Fahrenheit = 0;
int pos = 0;

void servo() {
  int i = 0;
  // sweep the servo from 0 to 180 degrees in steps
  // of 1 degrees
  for (pos = 0; pos <= 150; pos += 1) {
    // tell servo to go to position in variable 'pos'
    servo_9.write(pos);
    // wait 15 ms for servo to reach the position
    delay(15); // Wait for 15 millisecond(s)
  }
  delay(100);
  for (pos = 150; pos >= 0; pos -= 1) {
    // tell servo to go to position in variable 'pos'
    servo_9.write(pos);
    // wait 15 ms for servo to reach the position
    delay(15); // Wait for 15 millisecond(s)
  }
  delay(300);
}


void temperature() {
  sensors.requestTemperatures();

  Celsius = sensors.getTempCByIndex(0);
  Fahrenheit = sensors.toFahrenheit(Celsius);

  Serial.print(Celsius);
  Serial.print(" C  ");
  Serial.print(Fahrenheit);
  Serial.println(" F");
  Firebase.setFloat("/tanks/5pDz0ra1U694gHJgQTWX/data/temperature", Celsius);  
}

void intensity() {
  int sensorValue = analogRead(A0);

  if (sensorValue <= 300){
    Firebase.setBool("/tanks/5pDz0ra1U694gHJgQTWX/data/filterStatus", true);  
  }
  else{
    Firebase.setBool("/tanks/5pDz0ra1U694gHJgQTWX/data/filterStatus", false);  
  }

  Serial.println(sensorValue);
}

void filter() {
  if (Firebase.getBool("/tanks/5pDz0ra1U694gHJgQTWX/controls/filterEnabled") == true){
    digitalWrite(RELAY_1, RELAY_ON);
  }
  else{
  }
}

void setup() {
  //  temperature sensors
  sensors.begin();
  Serial.begin(9600);

  servo_9.attach(9);

  // Set pin as output.
  pinMode(RELAY_1, OUTPUT);
  
  // Initialize relay one as off so that on reset it would be off by default
  digitalWrite(RELAY_1, RELAY_OFF);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
   
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
}

void loop() {
  temperature();
  intensity();
  servo();
  filter();
  delay(100);
}
