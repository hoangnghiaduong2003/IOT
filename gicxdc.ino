#define BLYNK_TEMPLATE_ID "TMPL6qMyoxRQ3"
#define BLYNK_TEMPLATE_NAME "Water Pump Tree"
#define BLYNK_AUTH_TOKEN "laA86D2qcalJ8vPGbtnRqSj5UcxkOQ8t" // dong 1 2 3 là kết nối blynk

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "laA86D2qcalJ8vPGbtnRqSj5UcxkOQ8t"; // Enter your Auth token
char ssid[] = "Dai Duong"; // Enter your WIFI name
char pass[] = "88888888"; // Enter your WIFI password

BlynkTimer timer;
bool Relay = 0;

// Define component pins
#define sensor A0
#define waterPump D3

void setup() {
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, HIGH);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  // Call the function
  timer.setInterval(100L, soilMoistureSensor);
}

// Get the button value
BLYNK_WRITE(V1) {
  Relay = param.asInt();

  if (Relay == 1) {
    digitalWrite(waterPump, LOW);
  } else {
    digitalWrite(waterPump, HIGH);
  }
}

// Get the soil moisture values
void soilMoistureSensor() {
  int value = analogRead(sensor);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;

  Blynk.virtualWrite(V0, value);
}

void loop() {
  Blynk.run(); // Run the Blynk library
  timer.run(); // Run the Blynk timer
}