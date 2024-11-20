int transistor = 7;

void setup() {
pinMode(transistor, OUTPUT);
Serial.begin(9600);

}

void loop() {

  digitalWrite(transistor, HIGH);
  delay(3000);
  digitalWrite(transistor, LOW);
  delay(3000);

}
