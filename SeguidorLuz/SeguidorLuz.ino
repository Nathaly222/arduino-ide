#include <Servo.h>

const int LDR_PIN1 = A0; // Norte
const int LDR_PIN2 = A1; // Sur
const int LDR_PIN3 = A2; // Este
const int LDR_PIN4 = A3; // Oeste
const int BUTTON_PIN = 7; // Pin del pulsador

Servo servo1; // Servo para Norte-Sur
Servo servo2; // Servo para Este-Oeste

bool slowMovement = false; // Estado inicial del movimiento

void setup() {
  servo1.attach(4);
  servo2.attach(2);
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Configurar el pulsador con pull-up interno
  servo1.write(90); // Posición neutral
  servo2.write(90); // Posición neutral
}

void loop() {
  static bool lastButtonState = HIGH; // Estado anterior del pulsador
  bool buttonState = digitalRead(BUTTON_PIN); // Leer el estado del pulsador

  if (buttonState == LOW && lastButtonState == HIGH) { // Detección de pulsación
    slowMovement = !slowMovement; // Alternar el estado del movimiento
    delay(50); // Debounce delay
  }
  lastButtonState = buttonState; // Actualizar el estado anterior del pulsador
  int norte = analogRead(LDR_PIN1);
  int sur = analogRead(LDR_PIN2);
  int este = analogRead(LDR_PIN3);
  int oeste = analogRead(LDR_PIN4);

  delay(1000);

  Serial.println(lastButtonState);
  Serial.print("Norte: "); Serial.print(norte);
  Serial.print(" | Sur: "); Serial.print(sur);
  Serial.print(" | Este: "); Serial.print(este);
  Serial.print(" | Oeste: "); Serial.println(oeste);

  // Control del servo para Norte-Sur
  if (norte > sur) {
    if (slowMovement) {
      int currentPos = servo1.read();
      for (int pos = currentPos; pos <= 180; pos++) {
        servo1.write(pos);
        delay(15);
      }
    } else {
      servo1.write(180);
    }
  } else if (sur > norte) {
    if (slowMovement) {
      int currentPos = servo1.read();
      for (int pos = currentPos; pos >= 0; pos--) {
        servo1.write(pos);
        delay(15);
      }
    } else {
      servo1.write(0);
    }
  } else {
    servo1.write(90); // Posición neutral si están iguales
  }

  // Control del servo para Este-Oeste
  if (este > oeste) {
    if (slowMovement) {
      int currentPos = servo2.read();
      for (int pos = currentPos; pos <= 180; pos++) {
        servo2.write(pos);
        delay(15);
      }
    } else {
      servo2.write(180);
    }
  } else if (oeste > este) {
    if (slowMovement) {
      int currentPos = servo2.read();
      for (int pos = currentPos; pos >= 0; pos--) {
        servo2.write(pos);
        delay(15);
      }
    } else {
      servo2.write(0);
    }
  } else {
    servo2.write(90); // Posición neutral si están iguales
  }

  delay(1000);
}
