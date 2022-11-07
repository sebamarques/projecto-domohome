#include <Servo.h>

Servo servo;
int rojo = 11;
int echo = 8;
int trig =9;
int duracion;
int distancia;
int duracion1;
int distancia1;
int trig1 = 7;
int echo1 = 6;  
int valor = 0;
void setup(){
  
  Serial.begin(9600);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(rojo,OUTPUT);
  digitalWrite(trig,LOW);
  pinMode(echo1,INPUT);
  pinMode(trig1,OUTPUT);
  servo.attach(4);
}
  
  void loop(){
    if(Serial.available()>0){
    valor = Serial.read();
  
  if(valor == "1"){
    servo.write(90);
    Serial.println("aca prendio");
    }
  if(valor == "0"){
    Serial.println("aca no prendio");
    servo.write(0);}
    }
      
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    duracion = pulseIn(echo,HIGH);
    distancia = duracion/58.2;
    if (distancia <20 and distancia >0){
      servo.write(90);
      Serial.println("aca esta recibibiednp");
      Serial.println(distancia);
      delay(1000);
      
      }
     else{
      servo.write(0);
      }
    ultra1();
    }

  void ultra1(){
    digitalWrite(trig1,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1,LOW);
    duracion1 = pulseIn(echo1,HIGH);
    distancia1 = duracion1/58.2;
    if (distancia1 <5 and distancia1 >0){
      Serial.println("esta lleno");
      digitalWrite(rojo,HIGH);
      }
     else{
      digitalWrite(rojo,LOW);
     }
  }
