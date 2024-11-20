const int pinP1=5;
const int pinP2=18;
const int pinR1=22;
const int pinR2=23;
const  int pinFR = 4;
const int pinSC=2;
bool estadoP1=false;
bool estadoP2=false;
int sensor_luz=0;
int sensor_corriente=0;
float voltajeSC=0;
float corrienteSC=0;

void setup() {

  pinMode(pinP1, INPUT_PULLDOWN); 
  pinMode(pinP2, INPUT_PULLDOWN); 
  pinMode(pinR1, OUTPUT); 
  pinMode(pinR2, OUTPUT);
  Serial.begin(115200);

}

void loop() {
  
  if (digitalRead(pinP1)==true){
    estadoP1=!estadoP1;
    digitalWrite(pinR1, estadoP1);
    Serial.println("Pulsador 1 accionado");
    delay(500);
  }
  if (digitalRead(pinP2)==true){
    estadoP2=!estadoP2;
    digitalWrite(pinR2, estadoP2);
    Serial.println("Pulsador 2 accionado");
    delay(500);
  }
  
  sensor_luz=analogRead(pinFR);
  if(sensor_luz<50){
    estadoP1=true;
    estadoP2=true;
    digitalWrite(pinR1, estadoP1);
    digitalWrite(pinR2, estadoP2);
    Serial.println("Luces encendidas");
  } else if(sensor_luz>1000){
    estadoP1=false;
    estadoP2=false;
    digitalWrite(pinR1, estadoP1);
    digitalWrite(pinR2, estadoP2);
    Serial.println("Luces apagadas");
  }

  sensor_corriente=analogRead(pinSC);

  voltajeSC=sensor_corriente*(1.1/4095);
  corrienteSC=voltajeSC*20;
  Serial.println(corrienteSC, 3);
  delay(10);
}
