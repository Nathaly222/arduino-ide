#include <DHT.h>
#include <DHT_U.h>

const int LDR = A1;
const int SensorIR = 5;
const int PinButton = 6;
const int LED = 7;
bool programaEncendido = false;
bool estadoBotonAnterior = HIGH;



#define DHTPIN 2
#define DHTTYPE DHT11
#define BUZZER 3

DHT dht(DHTPIN, DHTTYPE);

void setup() {
pinMode(LDR, OUTPUT);
pinMode(SensorIR, INPUT);
pinMode (BUZZER, OUTPUT);
pinMode (PinButton, INPUT);
pinMode (LED, INPUT);

digitalWrite(BUZZER, LOW);

Serial.begin(9600);
dht.begin();
}

void loop() {

// BUTTON TO INICIALIZE THE PROGRAM

  bool estadoBotonActual = digitalRead(PinButton);
  int ButtonState = digitalRead(PinButton);

  if (estadoBotonAnterior == HIGH && estadoBotonActual == LOW) {
    programaEncendido = !programaEncendido;
    Serial.print("Programa ");
    Serial.println(programaEncendido ? "Encendido" : "Apagado");
  }
  
  estadoBotonAnterior = estadoBotonActual;
  
  if (programaEncendido) {
    Serial.println("Programa Encendido");
  
  
  delay(50);
  delay(1000);

//  SENSOR IR -- BUZZER

  int SensorIRState = digitalRead(SensorIR);

  if (SensorIRState == LOW) { 
    digitalWrite(BUZZER, HIGH);
  } else if(SensorIRState == HIGH){
    digitalWrite(BUZZER, LOW);
  }
    delay(100);

// SENSOR DHT11 -- Humidity - Temperature / LED STATE

  int LEDState = digitalRead(LED);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if ( isnan(t)){
  Serial.println("Error obteniendo los datos del sensor DHT11");
  return;
  }
  if(t >= 27){
    digitalWrite(LED, HIGH);

  }else{
    digitalWrite(LED, LOW);
  }

  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println("*C ");

// FOTORESISTENCIA - LDR

  int read = analogRead(LDR);
  read = map(read, 0,100, 0, 100);
  analogWrite(BUZZER, read);
  Serial.print("Porcentaje de Luz: ");
  Serial.print(read);
  Serial.println("%");
  } else {
    Serial.println("Programa Apagado");
  }
}