const int Trigger = 7;
const int Echo = 6;
const int potPin = A1;

#define BUZZER 3

void setup() {
  Serial.begin(9600);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(potPin, INPUT);
  digitalWrite(Trigger, LOW);
}

void loop() {
  long t; // tiempo que demora en llegar el eco
  long d; // distancia en centímetros

  // Enviamos un pulso de 10us al trigger
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);

  // OBTENEMOS EL ANCHO DE PULSO
  t = pulseIn(Echo, HIGH);
  d = t / 59; // escalamos el tiempo en una distancia en cm

  // Leemos el valor del potenciómetro y lo mapeamos para ajustar el umbral
  int readPot = analogRead(potPin);
  int threshold = map(readPot, 0, 1023, 0, 50);
  Serial.print("Umbral de distancia: ");
  Serial.println(threshold);

  // Mapeamos la distancia para el control del buzzer
  int buzzerValue = map(d, 0, 20, 255, 0);
  
  if (d <= threshold) {
    analogWrite(BUZZER, buzzerValue);
  } else {
    analogWrite(BUZZER, LOW);
  }

  // Imprimimos la distancia en el monitor serial
  Serial.print("Distancia: ");
  Serial.print(d);
  Serial.println(" cm");

  delay(100);
}
