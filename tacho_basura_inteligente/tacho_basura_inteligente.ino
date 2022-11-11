#include <Servo.h>

Servo servo;
int rojo = 9;
int echo = 4;
int trig =3;
int duracion;
int distancia;  
int echo1 = 6;
int trig1 =5;
int duracion1;
int distancia1;  
char valor;
void setup(){
  Serial.begin(9600);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo1,INPUT);
  pinMode(trig1,OUTPUT);
  pinMode(rojo,OUTPUT);
  servo.attach(8);
}
  
   
  void loop(){
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    duracion = pulseIn(echo,HIGH);
    distancia = duracion/58.2;
    if (distancia <10 and distancia >0){
      servo.write(90);
      Serial.println("aca esta recibibiednp");
      Serial.println(distancia);
      
      }
      else{
        servo.write(0);}
   
    digitalWrite(trig1,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1,LOW);
    duracion1 = pulseIn(echo1,HIGH);
    distancia1 = duracion1/58.2;
    if (distancia1 <5 and distancia1 >0){
      digitalWrite(rojo,HIGH);
      }
     else{
      digitalWrite(rojo,LOW);
      }

      if(Serial.available()>0){
    valor = Serial.read();
  
  if(valor == '1'){
    servo.write(90);
    Serial.println("aca prendio");
    }
  if(valor == '0'){
    Serial.println("aca no prendio");
    servo.write(0);}
    }
  }
  

  
