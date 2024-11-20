#include <WiFi.h>
#include <time.h>

// Pines de conexión
const int pinP1 = 5;
const int pinP2 = 18;
const int pinR1 = 22;
const int pinR2 = 23;
const int pinSC = 2;

// Estado de los pulsadores
bool estadoP1 = false;
bool estadoP2 = false;

// Variables para sensores
int sensor_corriente = 0;
float voltajeSC = 0;
float corrienteSC = 0;

// Variables para el tiempo
const char* ssid = "LIKENET-Bryan Lojano";
const char* password = "mateo2414";
const int utcOffsetInSeconds = -18000; // UTC -5

void setup() {
  Serial.begin(115200);

  // Configuración de los pines
  pinMode(pinP1, INPUT_PULLDOWN);
  pinMode(pinP2, INPUT_PULLDOWN);
  pinMode(pinR1, OUTPUT);
  pinMode(pinR2, OUTPUT);

  // Conexión a WiFi
  WiFi.begin(ssid, password);
  int intento = 0;
  while (WiFi.status() != WL_CONNECTED && intento < 20) { // Intentar conectarse durante 20 segundos
    delay(1000);
    Serial.println("Conectando a WiFi...");
    intento++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Conectado a WiFi");
  } else {
    Serial.println("No se pudo conectar a WiFi");
    return;
  }

  // Configuración de tiempo con múltiples servidores NTP
  configTime(utcOffsetInSeconds, 0, "pool.ntp.org", "time.nist.gov", "time.google.com");

  // Esperar a la sincronización de tiempo
  struct tm timeInfo;
  int intentoTiempo = 0;
  while (!getLocalTime(&timeInfo) && intentoTiempo < 10) { // Intentar obtener la hora durante 10 segundos
    Serial.println("Intentando sincronizar el tiempo...");
    delay(1000);
    intentoTiempo++;
  }
  if (intentoTiempo < 10) {
    Serial.println("Sincronización de tiempo exitosa");
    Serial.printf("La hora actual es: %02d:%02d:%02d\n", timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
  } else {
    Serial.println("Fallo la sincronizacion de tiempo");
    return;
  }
}

void loop() {
  // Obtener la hora actual
  struct tm timeInfo;
  if (!getLocalTime(&timeInfo)) {
    Serial.println("Fallo la obtencion de tiempo");
    return;
  }

  int currentHour = timeInfo.tm_hour;
  int currentMinute = timeInfo.tm_min;

  // Control manual con pulsadores
  if (digitalRead(pinP1) == HIGH) {
    estadoP1 = !estadoP1;
    digitalWrite(pinR1, estadoP1);
    Serial.println("Pulsador 1 accionado");
    delay(500);
  }
  if (digitalRead(pinP2) == HIGH) {
    estadoP2 = !estadoP2;
    digitalWrite(pinR2, estadoP2);
    Serial.println("Pulsador 2 accionado");
    delay(500);
  }

  // Control automático de luces basado en la hora y los minutos
  //if ((currentHour == 17 && currentMinute >= 25) || (currentHour == 20 && currentMinute == 30))
  
  if ((currentHour == 17 && currentMinute >= 33 && currentMinute < 34)) {
    estadoP1 = true;
    estadoP2 = true;
    digitalWrite(pinR1, estadoP1);
    digitalWrite(pinR2, estadoP2);
    Serial.println("Luces encendidas por horario");
  } else {
    estadoP1 = false;
    estadoP2 = false;
    digitalWrite(pinR1, estadoP1);
    digitalWrite(pinR2, estadoP2);
    Serial.println("Luces apagadas por horario");
  }

  // Lectura del sensor de corriente
  sensor_corriente = analogRead(pinSC);
  voltajeSC = sensor_corriente * (1.1 / 4095.0);
  corrienteSC = voltajeSC * 20; 
  Serial.print("Corriente: ");
  Serial.println(corrienteSC, 3);

  float Irms = get_corriente();
  float P = Irms * 110.0;
  Serial.print("Irms: ");
  Serial.print(Irms, 3);
  Serial.print("A, Potencia: ");
  Serial.print(P, 3);
  Serial.println("W");

  delay(1000);
}

float get_corriente() {
  float voltajeSensor;
  float corriente = 0;
  float Sumatoria = 0;
  long tiempo = millis();
  int N = 0;
  while (millis() - tiempo < 500) {
    voltajeSensor = analogRead(pinSC) * (1.1 / 4095.0);
    corriente = voltajeSensor * 20; 
    Sumatoria = Sumatoria + sq(corriente);
    N = N + 1;
    delay(1);
  }
  Sumatoria = Sumatoria * 2;
  corriente = sqrt(Sumatoria / N);
  return corriente;
}
