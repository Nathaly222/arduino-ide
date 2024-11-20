#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
void setup() {
Serial.begin(9600);
dht.begin();
}

void loop() {

  delay(5000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();



if ( isnan(t)){
  Serial.println("Error obteniendo los datos del sensor DHT11");
  return;
}

Serial.print("Humedad: ");
Serial.print(h);
Serial.print("%\t");
Serial.print("Temperatura: ");
Serial.print(t);
Serial.println("*C ");
}
