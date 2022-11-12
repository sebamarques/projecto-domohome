#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <Firebase_ESP_Client.h>
#include <DS3232RTC.h>      
#include <TimeLib.h>
#include <string.h>
#include <Servo.h>
Servo servo;
WiFiServer server(80);
#define data_url  "https://dispensador-ca5ae-default-rtdb.firebaseio.com/"
#define data_secret  "WMMaxSwOmvYGvCls8DfwfKx3XyyjAFuEhcI6ZYGJ"

//creamos la  base de datos en el programa
FirebaseData fbdo;

FirebaseAuth auth;

FirebaseConfig config;
unsigned long datamillis=0;
int count = 0;

void setup(){
  Serial.begin(115200);
  WiFiManager wf;
  setTime(14,30,10,12,11,2022);
  //descomentar linea para resetear configuracion de wifi
  //wf.resetSettings();
  servo.attach(2);
  wf.autoConnect("miwifi","contraseña");
  
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
String Hora1;
String Minuto1;
void loop(){
 
if(Firebase.RTDB.getString(&fbdo,"DIA/Hora")){
  Hora = fbdo.stringData();
  }
 
if(Firebase.RTDB.getString(&fbdo,"DIA/Minuto")){
  Minuto = fbdo.stringData();
  }
  
if(Firebase.RTDB.getString(&fbdo,"NOCHE/Hora")){
  Hora1= fbdo.stringData();
  }
  
if(Firebase.RTDB.getString(&fbdo,"NOCHE/Minuto")){
  Minuto1 = fbdo.stringData();
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
    delay(8000);
    servo.write(0);}
    if(Hora1 == nH1 && Minuto1 == nM1){
    Serial.println("prendido");
    servo.write(90);
    delay(8000);
    servo.write(0);}

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
  client.println("</body>");
  
  client.println("</html>"); //Terminamos el HTML
 
  delay(1);
  Serial.println("Cliente desconectado"); //Imprimimos que terminó el proceso con el cliente desconectado
  Serial.println("");
}

  
