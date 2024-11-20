#include <WiFi.h>
#include <ThingSpeak.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE); 

const char* ssid = "Suda";
const char* password = "";

unsigned long channelID = 2751494;  // Punto y coma añadido
const char* WriteApiKey = "CWEQRQM3GNVKFJBC";  // Punto y coma añadido

WiFiClient client;

void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.println("Sensores Instalados y listos");
  dht.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado al WiFi");
  ThingSpeak.begin(client);
  delay(5000);
}

void loop() {
  delay(5000);
  medicion();
  ThingSpeak.writeFields(channelID, WriteApiKey);
  Serial.println("Datos enviados a ThingSpeak!");
  delay(10000);
}

void medicion() {
  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();

  Serial.print("Temperatura registrada: ");
  Serial.print(temperatura);
  Serial.println("°C");

  Serial.print("Humedad registrada: ");
  Serial.print(humedad);
  Serial.println("%");
  
  Serial.println("-----------------------------------------");

  ThingSpeak.setField(1, temperatura);
  ThingSpeak.setField(2, humedad);
}
