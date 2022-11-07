#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal_I2C.h> // Incluir la libreria LiquidCrystal_I2C
#include <Keypad.h>            // Incluir la libreria Keypad
#include <Servo.h>             // Incluir la libreria Servo
#include <EEPROM.h>           //incluir libreria EEPROM para guardar datos por si se apaga la placa
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
int direccion = 0; // variable iterable para guardar clave en memoria EEPROM
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
char TECLA;                        // almacena la tecla presionada
char CLAVE[5];                     // almacena en un array 4 digitos ingresados
char CLAVE_MAESTRA[5] = "0000";    // almacena en un array la contraseña inicial
byte INDICE = 0;                   // indice del array

int guardado =0;
byte value;
char valor = 0;
int hola;
void setup(){
  
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Otra direccion es la 0x3D
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
 servo.attach(11);        // Asocia el servo1 al pin 11
 servo.write(0);                // Gira el servo a 0 grados 
 limpia();
}
void loop(){
 
  
  if(Serial.available()>0){
    valor = Serial.read();
  
  if(valor == '1'){  
  display.clearDisplay();         // Borra la pantalla
  display.setTextSize(2);         // Tamaño de la fuente del texto 1 - 2 - 3 - 4 - 5
  display.setCursor(30,20);       // (X,Y) . (Horizontal, Vertical)
  display.print("Abierto");  // texto a mostrar / si es variable sin comillas
  display.display();              // Muestra el Texto en la pantalla
  servo.write(90);
  estado = 1; // valor en 1 por si quiere cambiar la clave del teclado
  delay(1000);}
  if(valor == '0'){
  display.clearDisplay();         // Borra la pantalla
  display.setTextSize(2);         // Tamaño de la fuente del texto 1 - 2 - 3 - 4 - 5
  display.setCursor(30,20);       // (X,Y) . (Horizontal, Vertical)
  display.print("Cerrado");  // texto a mostrar / si es variable sin comillas
  display.display();      
    servo.write(0);
    estado = 0; // cambiar valor por si quiere cambiar clave de candado
    delay(1000);}
  }
  
  TECLA = teclado.getKey();   // obtiene tecla presionada y asigna a variable
  if (TECLA)                  // comprueba que se haya presionado una tecla
  {
    EEPROM.put(guardado,TECLA);// guardamos en memoria EEPROM las teclas para que no se borre la configuracion
    
    hola = EEPROM.get(guardado,TECLA);
    guardado += sizeof(int);
    Serial.println(hola);
    CLAVE[INDICE] = TECLA;    // almacena en array la tecla presionada
    INDICE++;                 // incrementa indice en uno   
  display.clearDisplay();        // Borra la pantalla
  display.setTextSize(2);        // Tamaño de la fuente del texto 1 - 2 - 3 - 4 - 5
  display.setCursor(30,20);       // (X,Y) . (Horizontal, Vertical)
  display.print(TECLA);  // texto a mostrar / si es variable sin comillas
  display.display();      
     }

  if(INDICE == 4)             // si ya se almacenaron los 4 digitos
  { 
    if(!strcmp(CLAVE, CLAVE_MAESTRA)){    // compara clave ingresada con clave maestra
        abierto();              }
    else {
        error();
    }
    INDICE = 0;
  }
  if(estado==1 && (analogRead(A3)==1)){    // si esta abierta y se pulsa boton de Nueva Clave
         nueva_clave();  }

}

  void error(){   
      
  display.clearDisplay();         // Borra la pantalla
  display.setTextSize(2);         // Tamaño de la fuente del texto 1 - 2 - 3 - 4 - 5
  display.setCursor(30,20);       // (X,Y) . (Horizontal, Vertical)
  display.print("ERROR");  // texto a mostrar / si es variable sin comillas
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
  display.display();      
      servo.write(90);                 // Gira el servo a 90 grados  abre la puerta
   }
   else{
    estado=0;
  display.clearDisplay();         // Borra la pantalla
  display.setTextSize(2);         // Tamaño de la fuente del texto 1 - 2 - 3 - 4 - 5
  display.setCursor(30,20);       // (X,Y) . (Horizontal, Vertical)
  display.print("Cerrado");  // texto a mostrar / si es variable sin comillas
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
  INDICE=0;
  while (INDICE<=3) {
   TECLA = teclado.getKey();   // obtiene tecla presionada y asigna a variable TECLA
   
   if (TECLA)                 // comprueba que se haya presionado una tecla
    {
      EEPROM.put(direccion,TECLA);
      
      CLAVE_MAESTRA[INDICE] = TECLA;    // almacena en array la tecla presionada
      CLAVE[INDICE] = TECLA;
      INDICE++;                 // incrementa indice en uno
      display.print(TECLA);        // envia a lcd la tecla presionada
    }   
  }
 estado=0;
  
  display.clearDisplay();         // Borra la pantalla
  display.setTextSize(2);         // Tamaño de la fuente del texto 1 - 2 - 3 - 4 - 5
  display.setCursor(30,20);       // (X,Y) . (Horizontal, Vertical)
  display.print("Clave Cambiada");  // texto a mostrar / si es variable sin comillas
  
  display.display();        
  
  delay(2000);
  
  limpia();
}

///////////////////// limpia //////////////////////////////
void limpia(){  
  display.clearDisplay();              
}
  
