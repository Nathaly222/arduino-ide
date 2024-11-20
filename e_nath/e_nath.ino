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
  pinMode(pinP1, INPUT_PULLDOWN);
  pinMode(pinP2, INPUT_PULLDOWN);
  pinMode(pinR1, OUTPUT);
  pinMode(pinR2, OUTPUT);
  Serial.begin(115200);
}

void loop() {
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
  voltajeSC = sensor_corriente * (1.1 / 4095.0);
  corrienteSC = voltajeSC * 20;
  Serial.print("Corriente: ");
  Serial.println(corrienteSC, 3);
  
  float Irms = get_corriente();
  float P = Irms * 110.0;
  Serial.print("Irms: ");
  Serial.print(Irms, 3);
  Serial.print(" A, Potencia: ");
  Serial.print(P, 3);
  Serial.println(" W");

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
