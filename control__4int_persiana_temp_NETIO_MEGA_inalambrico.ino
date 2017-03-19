#include <SPI.h>
#include <Ethernet.h>
#include <HTTPClient.h>
#include "nRF24L01.h"
#include "RF24.h"


#define BUFFER 25
byte mac[] = { 0x34, 0xC0, 0xA2, 0xB3, 0x00, 0xC5 };
byte ip[] = { 192, 168, 0, 150 }; // Aqui pon la ip que quieras darle a tu Arduino


RF24 radio(49,48); // CE - CS
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

EthernetServer servidorArduino(3200);

boolean estado_salida_luz_1_1=0;
boolean estado_salida_luz_1_2=0;
boolean estado_salida_luz_1_3=0;
boolean estado_salida_luz_1_4=0;

boolean estado_salida_luz_2_1=0;
boolean estado_salida_luz_2_2=0;
boolean estado_salida_luz_2_3=0;
boolean estado_salida_luz_2_4=0;

long int lectura_temp=0;
long int lectura_temp_1=0;
long int lectura_temp_2=0;
float temp_1=0;
float temp_2=0;

int contador=0;

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac, ip, dns);             
  servidorArduino.begin();             
  radio.begin();
  radio.setRetries(15,15);  
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]); 
  radio.startListening(); 

}

void loop()
{

while(radio.available())
{
  radio.read (&lectura_temp, sizeof(long int));
  if (lectura_temp >=1100 && lectura_temp <=2150)
  {
    lectura_temp_1=lectura_temp-1100;
  }
  if (lectura_temp >=2200 && lectura_temp <=3250)
  {
    lectura_temp_2=lectura_temp-2200;
  }


}

  
  
int index = 0;
char comando[BUFFER];
  EthernetClient clienteApp = servidorArduino.available();
  if (clienteApp) {
	if (clienteApp.connected()) {
          while (clienteApp.available()) {
          char caracter = clienteApp.read();
          if (caracter != '\n') {
            comando[index] = caracter;
            index++;
            if (index >= BUFFER) index = BUFFER -1;
            continue;
            }
            comando[index] = '\0';
            
            if (strstr(comando, "iniciandO")) {
            clienteApp.println("done");
            }
            
 //**********************************************************************************
 //****************************** MODULO INALAMBRICO 1 ***************************
 //********************************************************************************* 
 
            if (strstr(comando, "PULSADOR_LUZ_1_1")) {
             if (estado_salida_luz_1_1==0){   
              estado_salida_luz_1_1=1;
              radio.stopListening();
              delay(10);
              int ei=11;
              bool ok = radio.write( &ei, sizeof(int) );
              radio.startListening();       
              }
              else
              {
              estado_salida_luz_1_1=0;
              radio.stopListening();
              delay(10);
              int ei=10;
              bool ok = radio.write( &ei, sizeof(int) );
              radio.startListening();     
              }
              clienteApp.println("done");
              }           

            if (strstr(comando, "PULSADOR_LUZ_1_2")) {
             if (estado_salida_luz_1_2==0){   
              estado_salida_luz_1_2=1;
              radio.stopListening();
              delay(10);
              int ei=21;
              bool ok = radio.write( &ei, sizeof(int) );
              radio.startListening();       
              }
              else
              {
              estado_salida_luz_1_2=0;
              radio.stopListening();
              delay(10);
              int ei=20;
              bool ok = radio.write( &ei, sizeof(int) );
              radio.startListening();     
              }
              clienteApp.println("done");
              } 
 
             if (strstr(comando, "PULSADOR_LUZ_1_3")) {
             if (estado_salida_luz_1_3==0){   
              estado_salida_luz_1_3=1;
              radio.stopListening();
              delay(10);
              int ei=31;
              bool ok = radio.write( &ei, sizeof(int) );
              radio.startListening();       
              }
              else
              {
              estado_salida_luz_1_3=0;
              radio.stopListening();
              delay(10);
              int ei=30;
              bool ok = radio.write( &ei, sizeof(int) );
              radio.startListening();     
              }
              clienteApp.println("done");
              } 

            if (strstr(comando, "PULSADOR_LUZ_1_4")) {
             if (estado_salida_luz_1_4==0){   
              estado_salida_luz_1_4=1;
              radio.stopListening();
              delay(10);
              int ei=41;
              bool ok = radio.write( &ei, sizeof(int) );
              radio.startListening();       
              }
              else
              {
              estado_salida_luz_1_4=0;
              radio.stopListening();
              delay(10);
              int ei=40;
              bool ok = radio.write( &ei, sizeof(int) );
              radio.startListening();     
              }
              clienteApp.println("done");
              } 
              
            if (strstr(comando, "SUBIR_PER_1_ON")) {
             radio.stopListening();
             delay(10);
             int ei=51;
             bool ok = radio.write( &ei, sizeof(int) );
             radio.startListening();  
             clienteApp.println("done");       
            }
            
            if (strstr(comando, "SUBIR_PER_1_OFF")) {
            radio.stopListening();
            delay(10);
            int ei=50;
            bool ok = radio.write( &ei, sizeof(int) );
            radio.startListening();
            clienteApp.println("done");
            }
            
            if (strstr(comando, "BAJAR_PER_1_ON")) {
             radio.stopListening();
             delay(10);
             int ei=61;
             bool ok = radio.write( &ei, sizeof(int) );
             radio.startListening(); 
             clienteApp.println("done"); 
            }
            
           if (strstr(comando, "BAJAR_PER_1_OFF")) {
            radio.stopListening();
            delay(10);
            int ei=60;
            bool ok = radio.write( &ei, sizeof(int) );
            radio.startListening(); 
            clienteApp.println("done");
           }
   
          if (strstr(comando, "TEMP_1")) { 
          temp_1 = (3.3 * lectura_temp_1 * 100.0)/1024.0;
          clienteApp.println(temp_1);
         }
 //********************************************************************************* 
 //********************************************************************************* 
 //*********************************************************************************  
 
 
  //********************************************************************************
 //****************************** MODULO INALAMBRICO 2 *****************************
 //********************************************************************************* 
 
            if (strstr(comando, "PULSADOR_LUZ_2_1")) {
             if (estado_salida_luz_2_1==0){   
              estado_salida_luz_2_1=1;
              radio.stopListening();
              delay(10);
              int ei=71;
              bool ok = radio.write( &ei, sizeof(int) );
              radio.startListening();       
              }
              else
              {
              estado_salida_luz_2_1=0;
              radio.stopListening();
              delay(10);
              int ei=70;
              bool ok = radio.write( &ei, sizeof(int) );
              radio.startListening();     
              }
              clienteApp.println("done");
              }           

            if (strstr(comando, "PULSADOR_LUZ_2_2")) {
             if (estado_salida_luz_2_2==0){   
              estado_salida_luz_2_2=1;
              radio.stopListening();
              delay(10);
              int ei=81;
              bool ok = radio.write( &ei, sizeof(int) );
              radio.startListening();       
              }
              else
              {
              estado_salida_luz_2_2=0;
              radio.stopListening();
              delay(10);
              int ei=80;
              bool ok = radio.write( &ei, sizeof(int) );
              radio.startListening();     
              }
              clienteApp.println("done");
              } 
 
             if (strstr(comando, "PULSADOR_LUZ_2_3")) {
             if (estado_salida_luz_2_3==0){   
              estado_salida_luz_2_3=1;
              radio.stopListening();
              delay(10);
              int ei=91;
              bool ok = radio.write( &ei, sizeof(int) );
              radio.startListening();       
              }
              else
              {
              estado_salida_luz_2_3=0;
              radio.stopListening();
              delay(10);
              int ei=90;
              bool ok = radio.write( &ei, sizeof(int) );
              radio.startListening();     
              }
              clienteApp.println("done");
              } 

            if (strstr(comando, "PULSADOR_LUZ_2_4")) {
             if (estado_salida_luz_2_4==0){   
              estado_salida_luz_2_4=1;
              radio.stopListening();
              delay(10);
              int ei=101;
              bool ok = radio.write( &ei, sizeof(int) );
              radio.startListening();       
              }
              else
              {
              estado_salida_luz_2_4=0;
              radio.stopListening();
              delay(10);
              int ei=100;
              bool ok = radio.write( &ei, sizeof(int) );
              radio.startListening();     
              }
              clienteApp.println("done");
              } 
              
            if (strstr(comando, "SUBIR_PER_2_ON")) {
             radio.stopListening();
             delay(10);
             int ei=111;
             bool ok = radio.write( &ei, sizeof(int) );
             radio.startListening();  
             clienteApp.println("done");       
            }
            
            if (strstr(comando, "SUBIR_PER_2_OFF")) {
            radio.stopListening();
            delay(10);
            int ei=110;
            bool ok = radio.write( &ei, sizeof(int) );
            radio.startListening();
            clienteApp.println("done");
            }
            
            if (strstr(comando, "BAJAR_PER_2_ON")) {
             radio.stopListening();
             delay(10);
             int ei=121;
             bool ok = radio.write( &ei, sizeof(int) );
             radio.startListening(); 
             clienteApp.println("done"); 
            }
            
           if (strstr(comando, "BAJAR_PER_2_OFF")) {
            radio.stopListening();
            delay(10);
            int ei=120;
            bool ok = radio.write( &ei, sizeof(int) );
            radio.startListening(); 
            clienteApp.println("done");
           }
   
          if (strstr(comando, "TEMP_2")) { 
          temp_2 = (3.3 * lectura_temp_2 * 100.0)/1024.0;
          clienteApp.println(temp_2);
         }
 //********************************************************************************* 
 //********************************************************************************* 
 //********************************************************************************* 
        }       
      }
    }
}

