#include <Servo.h>
//esta configurado
//nombre hc 06
// 9600 baudios
// contraseña 1234
// 

Servo servomotor;
char estado = 0;
int in1 = 8;
int in2 = 9;

void setup(){
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  
}
void loop(){
  if(Serial.available()>0){
    estado = Serial.read();}
    if(estado == '0'){
      digitalWrite(13,LOW);
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      }
      
  if(estado == '1'){
    Serial.println("premdo");
    digitalWrite(13,HIGH);
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    }
    
    if(estado == '2'){
    Serial.println("apago");
    digitalWrite(13,LOW);
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    }
  }
  
