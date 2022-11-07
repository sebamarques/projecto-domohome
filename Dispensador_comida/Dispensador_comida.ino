#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <Firebase_ESP_Client.h>
#include <DS3232RTC.h>      
#include <TimeLib.h>
#include <string.h>
#include <Servo.h>
Servo servo;
int echo = 7;
int trig =8;
int duracion;
int distancia;
WiFiServer server(80);
#define data_url  "lednodemcu-c09c6-default-rtdb.firebaseio.com"
#define data_secret  "PoutAh31PLV2r7cEfY5ROUFc5CRkbktl0gGQy6Qf"

//creamos la  base de datos en el programa
FirebaseData fbdo;

FirebaseAuth auth;

FirebaseConfig config;
unsigned long datamillis=0;
int count = 0;

void setup(){
  Serial.begin(115200);
  WiFiManager wf;
  setTime(14,17,8,6,9,2022);
  //descomentar linea para resetear configuracion de wifi
  //wf.resetSettings();
  servo.attach(2);
  wf.autoConnect("miwifi","contraseña");
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  IPAddress ip(192,168,1,21);     
  IPAddress gateway(192,168,1,1);   
  IPAddress subnet(255,255,255,0); 
  config.database_url = data_url;
  config.signer.tokens.legacy_token = data_secret;
Firebase.reconnectWiFi(true);
Firebase.begin(&config,&auth); 
WiFi.config(ip, gateway, subnet);
server.begin();
  Serial.println("Servidor iniciado");

  Serial.print("Usa esta URL para comunicar al ESP: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
}
String Hora;
String Minuto;

void loop(){
 ultra();
if(Firebase.RTDB.getString(&fbdo,"Hora")){
  Hora = fbdo.stringData();
  }
 
if(Firebase.RTDB.getString(&fbdo,"Minuto")){
  Minuto = fbdo.stringData();
  }
  int nH = hour();
  int nM = minute();
  String nH1 = String(nH);
  String nM1 = String(nM);
  Serial.print(nH1);
  Serial.print(":");
  Serial.println(nM1);
  if(Hora == nH1 && Minuto == nM1){
    Serial.println("prendido");
    servo.write(90);
    delay(10000);
    servo.write(0);
    
    
}

WiFiClient client = server.available();
  if (!client) {
    return;}
  while(!client.available()){  //Esperamos a que el ciente mande una solicitud
    delay(1);
  }
  String request = client.readStringUntil('\r');
  Serial.println(request); //Imprimimos la solicitud
  client.flush(); //Descartamos los datos que se han escrito en el cliente y no se han leído
 
  if (request.indexOf("/alimentar") != -1) {
    servo.write(90);
    delay(10000);
    servo.write(0);
  } 
  
 
  
  client.println("HTTP/1.1 200 OK"); // La respuesta empieza con una linea de estado  
  client.println("Content-Type: text/html"); //Empieza el cuerpo de la respuesta indicando que el contenido será un documento html
  client.println(""); // Ponemos un espacio
  client.println("<!DOCTYPE HTML>"); //Indicamos el inicio del Documento HTML
  client.println("<html lang=\"en\">");
  client.println("<head>");
  client.println("<meta charset=\"UTF-8\">");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"); //Para que se adapte en móviles
  client.println("<title>Servidor Web ESP8266</title>");
  client.println("<p>HOLAAAAA</p>");
  client.println("</body>");
  
  client.println("</html>"); //Terminamos el HTML
 
  delay(1);
  Serial.println("Cliente desconectado"); //Imprimimos que terminó el proceso con el cliente desconectado
  Serial.println("");
}

void ultra(){
      
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    duracion = pulseIn(echo,HIGH);
    distancia = duracion/58.2;
    if (distancia <10 and distancia >0){
      servo.write(90);
      Serial.println("aca esta recibibiednp");
      Serial.println(distancia);
      delay(1000);
      
      }
  }
