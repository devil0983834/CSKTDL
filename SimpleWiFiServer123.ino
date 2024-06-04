#include "DHT.h"
#include "ArduinoJson.h"
#include "WiFi.h"
#include "ThingSpeak.h"


#define DHTPIN 23     

#define DHTTYPE DHT11   // DHT 11 
const char* ssid = "P312";
const char* password = "0374458897";
const unsigned long channelID = 2560219;
const char* apiKey = "BJ1BH4TRLKQE5Q4Y";
const int fieldId = 1;
WiFiClient client;

DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(9600);
  dht.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  ThingSpeak.begin(client);
}

void loop() {
  float t =  dht.readTemperature();
  if(!std::isnan(t)){
  ThingSpeak.setField(1, t);
  int httpCode = ThingSpeak.writeFields(channelID, apiKey);
  if (httpCode == 200) {
      Serial.println("Data sent to Thingspeak");
    } else {
      Serial.println("Error sending data to Thingspeak");
    }
  }
    delay(30000);
}