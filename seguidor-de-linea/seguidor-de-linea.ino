const int LED = 3;
#define sensor_pin 2

void setup() {
  pinMode (sensor_pin, INPUT);
  pinMode (LED, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  int followLine = digitalRead(sensor_pin);
  Serial.println(followLine);
if(followLine == 0){
  digitalWrite(LED, HIGH);
}else{
  digitalWrite(LED, LOW);
}
  

  delay(100);
}
