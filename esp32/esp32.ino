#include <ThingerESP32.h>
#include <WiFi.h>

#define USERNAME "nathy"
#define DEVICE_ID "ESP32"
#define DEVICE_CREDENTIAL "ESP32automation"

#define SSID "Bryan Lojano"
#define SSID_PASSWORD "mateo2414"

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

const int pinP1 = 5;
const int pinP2 = 18;
const int pinFR = 4;
const int pinR1 = 22;
const int pinR2 = 23;
const int pinSC = 2;
bool estadoP1 = false;
bool estadoP2 = false;
int sensor_luz = 0;
int sensor_corriente = 0;
float voltajeSC = 0;
float corrienteSC = 0;

void setup() {
    Serial.print("Connecting to ");
    Serial.println(SSID);
    thing.add_wifi(SSID, SSID_PASSWORD);

    pinMode(pinP1, INPUT_PULLDOWN);
    pinMode(pinP2, INPUT_PULLDOWN);
    pinMode(pinR1, OUTPUT);
    pinMode(pinR2, OUTPUT);
    Serial.begin(115200);

    // Definir un recurso en Thinger.io para ver los estados de los relés y los sensores
    thing["estadoP1"] >> outputValue(estadoP1);
    thing["estadoP2"] >> outputValue(estadoP2);
    thing["sensor_luz"] >> outputValue(sensor_luz);
    thing["corrienteSC"] >> outputValue(corrienteSC);
}

void loop() {
    thing.handle();
    
    if (digitalRead(pinP1) == true) {
        estadoP1 = !estadoP1;
        digitalWrite(pinR1, estadoP1);
        Serial.println("Pulsador 1 accionado");
        delay(500);
    }
    if (digitalRead(pinP2) == true) {
        estadoP2 = !estadoP2;
        digitalWrite(pinR2, estadoP2);
        Serial.println("Pulsador 2 accionado");
        delay(500);
    }
    
    sensor_luz = analogRead(pinFR);
    if (sensor_luz < 50) {
        estadoP1 = true;
        estadoP2 = true;
        digitalWrite(pinR1, estadoP1);
        digitalWrite(pinR2, estadoP2);
        Serial.println("Luces encendidas");
    } else if (sensor_luz > 1000) {
        estadoP1 = false;
        estadoP2 = false;
        digitalWrite(pinR1, estadoP1);
        digitalWrite(pinR2, estadoP2);
        Serial.println("Luces apagadas");
    }

    sensor_corriente = analogRead(pinSC);
    voltajeSC = sensor_corriente * (1.1 / 4095);
    corrienteSC = voltajeSC * 20;
    Serial.println(corrienteSC, 3);
    delay(10);
}
