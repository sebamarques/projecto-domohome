#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <Firebase_ESP_Client.h>
#include <DS3232RTC.h>      
#include <TimeLib.h>
#include <string.h>

WiFiServer server(80);
#define data_url  "https://persiana-97f05-default-rtdb.firebaseio.com/"
#define data_secret  "SACZnduTWg7Rcrt88TUGKqAuSRLPJLSBaERJg6YN"

//creamos la  base de datos en el programa
FirebaseData fbdo;

FirebaseAuth auth;

FirebaseConfig config;
unsigned long datamillis=0;
int count = 0;
int in1 = 4;
int in2 = 5;
void setup(){
  Serial.begin(115200);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  WiFiManager wf;
  setTime(14,17,8,6,9,2022);
  //descomentar linea para resetear configuracion de wifi
  //wf.resetSettings();
  wf.autoConnect("miwifi","contraseña");
  //
  IPAddress ip(192,168,1,22);     
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
String Hora1;
String Minuto1;

void loop(){
  
if(Firebase.RTDB.getString(&fbdo,"DIA/Hora")){
  Hora = fbdo.stringData();
  Serial.println("esta es el dia");
  Serial.println(Hora);
  delay(1000);
  }
 
if(Firebase.RTDB.getString(&fbdo,"DIA/Minuto")){
  Minuto = fbdo.stringData();
  Serial.println(Minuto);
  
  delay(1000);
  }
  
if(Firebase.RTDB.getString(&fbdo,"NOCHE/Hora")){
  Hora1 = fbdo.stringData();
  Serial.println("esto es la noche");
  Serial.println(Hora1);
  delay(1000);
  }
if(Firebase.RTDB.getString(&fbdo,"NOCHE/Minuto")){
  Minuto1 = fbdo.stringData();
  Serial.println(Minuto1);
  delay(1000);
  }
  int nH = hour();
  int nM = minute();
  String nH1 = String(nH);
  String nM1 = String(nM);
  
  /*Serial.print(nH1);
  Serial.print(":");
  Serial.println(nM1);*/
  if(Hora == nH1 && Minuto == nM1){
   digitalWrite(in1,LOW);
   digitalWrite(in2,HIGH);
   delay(7000);
   digitalWrite(in2,LOW);

}

  if(Hora1 == nH1 && Minuto1 == nM1){
    digitalWrite(in2,LOW);
    digitalWrite(in1,HIGH);
    delay(7000);
    digitalWrite(in1,LOW);
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
 
  if (request.indexOf("/arriba") != -1) {
   digitalWrite(in1,LOW);
   digitalWrite(in2,HIGH);
  } 
  if (request.indexOf("/bajar")!=-1){
    digitalWrite(in1,HIGH);
   digitalWrite(in2,LOW);
    }
  if(request.indexOf("/parar")!=-1){
    digitalWrite(in1,LOW);
   digitalWrite(in2,LOW);
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
  
