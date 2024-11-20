const int buttonPin1 = 2;
const int buttonPin2 = 3;
const int ledPin = 7;

int buttonState1 = 0;
int buttonState2 = 0;

int variable = 0;

void setup() {
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  if (buttonState1 == HIGH) {
    variable += 2000;
    delay(500);
    Serial.println(variable);
  }

  if (buttonState2 == HIGH && buttonState1 == LOW) {
    for(int i = 0;i<10; i++){
    blinkLED(variable);
    }
  }
  
  if (buttonState1 == HIGH && buttonState2 == HIGH) {
    variable = 0;
    delay(500);
    Serial.println(variable);
  }
}

void blinkLED(int interval) {
  digitalWrite(ledPin, HIGH);
  delay(interval);
  digitalWrite(ledPin, LOW);
  delay(interval);
}
