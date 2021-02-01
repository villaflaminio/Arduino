

#include <SPI.h>                    //Include la libreria SPI
#include <Ethernet.h>               //Include la libreria ETHERNET
#include <Mudbus.h>                 //Include la libreria MUDBUS

//////////////// Registri dello Slave Sensore Colore Arduino [IP: 192.168.1.80] ///////////////////

Mudbus Mb;
//  La libreria Mudbus supporta le funzioni Modbus 1, 3, 5 , 6.
//  Il primo registro parte dall'indirizzo 0, conformemente alle specifiche Modbus.
//Function codes 1(read coils), 3(read registers), 5(write coil), 6(write register)
//signed int Mb.R[0 to 125] and bool Mb.C[0 to 128] 

//***************************************************************************************************
//****** DEFINIZIONE DEI PIN DI ARDUINO UTILIZZATI **************************************************
//***************************************************************************************************
////
int pinUscita1 = 8;  //Definisce il pin (8) corrispondente all'uscita digitale 1 di Arduino.
////
const int s0 = 2;
const int s1 = 3;
const int s2 = 5;
const int s3 = 6;
const int out = 7;


int red = 6749;
int green = 0;
int blue = 0;

//***************************************************************************************************
//****** DICHIARAZIONE DELLE VARIBILI UTILIZZATE ****************************************************
//***************************************************************************************************


void setup()
{
  uint8_t mac[]     = { 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x01 };
  uint8_t ip[]      = { 192, 168,   1,  80 };
  uint8_t gateway[] = { 192, 168,   1,   1 };
  uint8_t subnet[]  = { 255, 255, 255,   0 };
  Ethernet.begin(mac, ip, gateway, subnet);

  delay(500);  //Tempo di ritardo per apertura del terminale


  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
  
  Serial.begin(9600);
}


void loop()
{

  
  Mb.Run();   //  Aggiornamento modbus TCP

  //--------- Registri Colore ---------------------

 Mb.R[0] = red;   // il valore red sarà trasmesso al PLC Master sul reg. 0.
 Mb.R[1] = green; // il valore green sarà trasmesso al PLC Master sul reg. 1.
 Mb.R[2] = blue;  // il valore blue sarà trasmesso al PLC Master sul reg. 2.

}
