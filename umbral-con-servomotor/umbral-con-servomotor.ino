#include <Servo.h>
Servo servoMotor;
const int Trigger = 5;
const int Echo = 6;
const int potPin = A1;

void setup() {
  Serial.begin(9600);
  servoMotor.attach(9);
  servoMotor.write(0);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(potPin, INPUT);
  digitalWrite(Trigger, LOW);

}

void loop(){
   long t; // tiempo que demora en llegar el 
  long d; // distancia en centímetros
  
    // Enviamos un pulso de 10us al trigger
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);

  // OBTENEMOS EL ANCHO DE PULSO
  t = pulseIn(Echo, HIGH);
  d = t / 59; // escalamos el tiempo en una distancia en cm

  if(d <= 10){
  for (int i = 0; i <= 90; i++){
    servoMotor.write(i);
    delay(25);
  }
  delay(3000);
  for (int i = 89; i >= 0 ; i--){
    servoMotor.write(i);
    delay(25);
  }
  }

    Serial.print("Distancia: ");
  Serial.print(d);
  Serial.println(" cm");

  delay(100);
}
