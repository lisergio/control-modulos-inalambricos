//RECEPTOR INALAMBRICO , 2 SALIDAS PULSADOR PARA PERSIANA, 4 INTERRUPTORES LUCES Y SENSOR DE TEMPERATURA

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(15,16);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

int subir_persiana_1=4;
int bajar_persiana_1=5;
int salida_luz_1=6;
int salida_luz_2=7;
int salida_luz_3=8;
int salida_luz_4=9;
int lectura_sensor_temperatura=0;
int sensor_temperatura=A0;
int contador=0;

long int entrada=0;

void setup(){
  radio.begin();
  pinMode(subir_persiana_1,OUTPUT);
  pinMode(bajar_persiana_1,OUTPUT);
  pinMode(salida_luz_1,OUTPUT);
  pinMode(salida_luz_2,OUTPUT);
  pinMode(salida_luz_3,OUTPUT);
  pinMode(salida_luz_4,OUTPUT);
  radio.setRetries(15,15);  
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]); 
  radio.startListening(); 
  }
  
void loop()
{
  entrada=0;
    while (radio.available() )
    {
            
// LA IDENTIFICACION PARA LOS INTERRUPTORES : PRIMERO EL NUMERO DE INTERUPTOR O PULSADOR 1,2,3...11,12,13.. ETC, SEGUIDO DE 1 PARA ENCENDER O 0 PARA APAGAR... 11, 10,101,100 111,110...

      radio.read( &entrada, sizeof(long int) ); 
      if (entrada==71)
      {
         digitalWrite(salida_luz_1,HIGH);
      }
      
      else if (entrada==70)
      {
         digitalWrite(salida_luz_1,LOW);
      }
            
      else if(entrada==81)
      {
        digitalWrite (salida_luz_2,HIGH);
      }
      
      else if(entrada==80)
      {
        digitalWrite (salida_luz_2,LOW);
      } 
      
      else if (entrada==91)
      {
        digitalWrite (salida_luz_3,HIGH);  
      }
      
      else if (entrada==90)
      {
        digitalWrite (salida_luz_3,LOW);        
      }      

      else if (entrada==101)
      {
        digitalWrite (salida_luz_4,HIGH); 
      }
      
      else if (entrada==100)
      {
        digitalWrite (salida_luz_4,LOW);        
      }

      else if (entrada==111)
      {
        digitalWrite (subir_persiana_1,HIGH); 
      }
      
      else if (entrada==110)
      {
        digitalWrite (subir_persiana_1,LOW);        
      }  
      else if (entrada==121)
      {
        digitalWrite (bajar_persiana_1,HIGH);  
      }
      
      else if (entrada==120)
      {
        digitalWrite (bajar_persiana_1,LOW);       
      }       
    }
delay(1);
contador++;
if (contador >=2500)
{
radio.stopListening();
lectura_sensor_temperatura=analogRead(sensor_temperatura);
lectura_sensor_temperatura=lectura_sensor_temperatura+2200;
bool ok = radio.write( &lectura_sensor_temperatura, sizeof(int) );
radio.startListening();
contador=0;
}

}
