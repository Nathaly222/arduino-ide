int Pin1= 2;
int Pin2 = 3;
int Pin3 = 4;
int Pin4 = 5;

int Pin_Sensor1 = 8; 
int Pin_sensor2 = 9;



void setup() {
 Serial.begin(9600);
 pinMode(Pin1, OUTPUT);
 pinMode(Pin2, OUTPUT);
 pinMode(Pin3, OUTPUT);
 pinMode(Pin4, OUTPUT);
 pinMode(Pin_Sensor1, INPUT);
 pinMode(Pin_Sensor2, INPUT);
}

void loop() {
  int value1 = 0;  // Variable temporal para recoger la señal del sensor izq
  int value2 = 0;  // Variable temporal para recoger la señal del sensor der
  value1 = digitalRead(Pin_Sensor1);
  value2 = digitalRead(Pin_Sensor2);   //lectura digital

  if(value1 == LOW && value2 == LOW)
  {
    Serial.println("Adelante");
    MotorAdelante();
  }
  if(value1 == HIGH && value2 == HIGH)
  {
    Serial.println("Detenido");
    MotorStop();
  }
  if(value1 == HIGH && value2 == LOW) // si el sensor izq detecta una zona oscura
  {
    Serial.println("Gira a la Izquierda");
    MotorIzquierda();
  }
  if(value1 == LOW && value2 == HIGH) 
  {
    Serial.println("Gira a la Derecha");
    MotorDerecha();
  }
  delay(20); // para poder leer el sensor 
}
  void MotorIzquierda ()
  {
    digitalWrite (Pin1, HIGH);  //Motor izquierdo atras 
    digitalWrite (Pin2, LOW);
    digitalWrite (Pin3, HIGH); // Motor derecho adelante
    digitalWrite (Pin4, LOW);
  }
  void MotorDerecha ()
  {
    digitalWrite (Pin1, LOW);   // motor izquierdo adelante
    digitalWrite (Pin2, HIGH);
    digitalWrite (Pin3, LOW);   //motor derecgo atras
    digitalWrite (Pin4, HIGH);
  }
  void MotorDerecha ()
  {
    digitalWrite (Pin1, LOW);  //motor izquierdo adelante
    digitalWrite (Pin2, HIGH);
    digitalWrite (Pin3, HIGH); // motor derecho adelante 
    digitalWrite (Pin4, LOW);
  }



