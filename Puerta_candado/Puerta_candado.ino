#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal_I2C.h> // Incluir la libreria LiquidCrystal_I2C
#include <Keypad.h>            // Incluir la libreria Keypad
#include <Servo.h>             // Incluir la libreria Servo
#include <EEPROM.h>           //incluir libreria EEPROM para guardar datos por si se apaga la placa
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
int estado=0;                  // 0=cerrado 1=abierto
Servo servo;                 // Crea el objeto servo 
const byte FILAS = 4;          // define numero de filas
const byte COLUMNAS = 4;       // define numero de columnas
char keys[FILAS][COLUMNAS] = {    // define la distribucion de teclas
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte pinesFilas[FILAS] = {9,8,7,6};         // pines correspondientes a las filas
byte pinesColumnas[COLUMNAS] = {5,4,3,2};  // pines correspondientes a las columnas
Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);  // crea objeto teclado
int value,pw,currentpw=1234;
int guardado =0;
char key;
char valor = 0;

void setup(){
  
  Serial.begin(9600);
  teclado.setHoldTime(1000);
  EEPROM.get(0,pw);
  if(pw!=currentpw &&pw>0){
    currentpw=pw;
    }
    display.clearDisplay();
    Serial.println(currentpw);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Otra direccion es la 0x3D
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
 servo.attach(11);        // Asocia el servo1 al pin 11
 servo.write(0);                // Gira el servo a 0 grados 
 limpia();
}
int password(void){
  int pass,i=0;
  String keyword;
  while(i<4){
    key= teclado.waitForKey();
    display.clearDisplay();
    display.print(key);
    display.display();
    if(key >='0'&& key<='9'){
     keyword+=key;
     i++; 
      }
      if(key=='D'){
        i=4;
        Serial.print("nashe");}
      }
    if(keyword.length()>0){
      pass = keyword.toInt();}
    else{
      pass =0;
      }
      return (pass);
}
void loop(){
  char keyop;
  if(Serial.available()>0){ 
    valor = Serial.read();
  
  if(valor == '1'){  
  display.clearDisplay();         // Borra la pantalla
  display.setTextSize(2);         // Tamaño de la fuente del texto 1 - 2 - 3 - 4 - 5
  display.setCursor(30,20);       // (X,Y) . (Horizontal, Vertical)
  display.print("Abierto");  // texto a mostrar / si es variable sin comillas
  display.display() ;       // Muestra el Texto en la pantalla
  servo.write(90);
  Serial.println(valor);
  estado = 1; // valor en 1 por si quiere cambiar la clave del teclado
  delay(1000);}
  if(valor == '0'){
  display.clearDisplay();         // Borra la pantalla
  display.setTextSize(2);         // Tamaño de la fuente del texto 1 - 2 - 3 - 4 - 5
  display.setCursor(30,20);       // (X,Y) . (Horizontal, Vertical)
  display.print("Cerrado");  // texto a mostrar / si es variable sin comillas
  display.display();  
    servo.write(0);
    Serial.println(valor);
    estado = 0; // cambiar valor por si quiere cambiar clave de candado
    delay(1000);}
  }
  key=teclado.getKey();

  if(key>='A' && key<='C'){
     keyop = key;
     Serial.println(keyop);
     display.print("Ingrese la contra");
     display.display();
     pw = password();
     if(pw == currentpw){
      abierto();
  }
  else{
    error();}
  }
  if((digitalRead(10)==0)&& (estado==1)){
        nueva_clave();}  
        
    
}

  void error(){   
      
  display.clearDisplay();         // Borra la pantalla
  display.setTextSize(2);         // Tamaño de la fuente del texto 1 - 2 - 3 - 4 - 5
  display.setCursor(30,20);       // (X,Y) . (Horizontal, Vertical)
  display.print("ERROR");  // texto a mostrar / si es variable sin comillas
  display.display();      
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.print("Ingrese nuevamente contra");
  display.display();
  limpia();
}
/////////////////////abierto o cerrado //////////////////////////////
void abierto(){  
   if(estado==0){ 
      estado=1;
  display.clearDisplay();         // Borra la pantalla
  display.setTextSize(2);         // Tamaño de la fuente del texto 1 - 2 - 3 - 4 - 5
  display.setCursor(30,20);       // (X,Y) . (Horizontal, Vertical)
  display.print("Abierto");  // texto a mostrar / si es variable sin comillas
  display.print(estado);
  display.display();      
      servo.write(90);                 // Gira el servo a 90 grados  abre la puerta
   }
   else{
    estado=0;
  display.clearDisplay();         // Borra la pantalla
  display.setTextSize(2);         // Tamaño de la fuente del texto 1 - 2 - 3 - 4 - 5
  display.setCursor(30,20);       // (X,Y) . (Horizontal, Vertical)
  display.print("Cerrado");  // texto a mostrar / si es variable sin comillas
  display.print(estado);
  display.display();      
    servo.write(0);                // Gira el servo a 0 grados  cierra la puerta
   } 
 limpia();
}

/////////////////////Nueva_Clave //////////////////////////////
void nueva_clave(){  
   display.clearDisplay();         // Borra la pantalla
  display.setTextSize(2);         // Tamaño de la fuente del texto 1 - 2 - 3 - 4 - 5
  display.setCursor(30,20);       // (X,Y) . (Horizontal, Vertical)
  display.print("Nueva Clave");  // texto a mostrar / si es variable sin comillas
  display.display();
  pw =password();
  EEPROM.put(0,pw);
  display.clearDisplay();
  display.print("contraseña cambiada");
  display.display();
  currentpw = pw;
  delay(2000);
  
}

///////////////////// limpia //////////////////////////////
void limpia(){  
  display.clearDisplay();              
}
  
