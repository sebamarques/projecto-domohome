#include <Servo.h>

Servo servo;
int rojo = 11;
int verde = 10;
int echo = 8;
int trig =9;
int duracion;
int distancia;


void setup(){
  Serial.begin(9600);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(rojo,OUTPUT);
  pinMode(verde,OUTPUT);
  digitalWrite(trig,LOW);
  servo.attach(4);
}
  
  void loop(){
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    duracion = pulseIn(echo,HIGH);
    distancia = duracion/58.2;
    if (distancia <20 and distancia >0){
      digitalWrite(verde,HIGH);
      digitalWrite(rojo,LOW);
      servo.write(90);
      }
     else{
      servo.write(0);
      digitalWrite(rojo,HIGH);
      digitalWrite(verde,LOW);}
     Serial.println(distancia);
     delay(1000);
     
    }

  
