const int potPin = A5;     // Pin donde está conectado el potenciómetro
const int buttonPin = 2;   // Pin donde está conectado el pulsador
int secretNumber;          // Variable para almacenar el número secreto

void setup() {
  pinMode(potPin, INPUT);        // Configura el pin del potenciómetro como entrada
  pinMode(buttonPin, INPUT); // Configura el pin del pulsador como entrada con resistencia pull-up
  Serial.begin(9600);            // Inicializa la comunicación serie a 9600 baudios

  // Inicializar el generador de números aleatorios
  randomSeed(analogRead(0));  // Usa una lectura del pin A0 para inicializar la semilla de números aleatorios

  // Generar un número aleatorio entre 0 y 1023
    secretNumber = random(0, 1023); // Genera el número aleatorio
}

void loop() {
  int potValue = analogRead(potPin); // Lee el valor del potenciómetro
  Serial.print("Valor del potenciómetro: ");
  Serial.println(potValue); // Muestra el valor del potenciómetro en la consola serie
  Serial.println(secretNumber);
  int buttonState = digitalRead(buttonPin); // Lee el estado del pulsador

  // Verifica si el pulsador está presionado (estado LOW debido a la resistencia pull-up)
  if (buttonState == HIGH) {
    if (potValue >= (secretNumber - 10) && potValue <= (secretNumber + 10)) {
      Serial.println("Adivinaste el Número!");
      secretNumber = random(0, 1023);
    } else {
      Serial.println("Intenta de nuevo!");
    }
    delay(200); // Pequeño retraso para evitar múltiples lecturas debido a rebotes del pulsador
  }
  delay(1000); // Pequeño retraso para evitar la saturación de la consola serie
}

