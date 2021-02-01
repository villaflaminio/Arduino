// includo la libreria del tipo sensore DHT
#include "DHT.h"
// pin su cui è collegato il sensore ( A1)
#define DHTPIN 15 
 // tipo di sensore = DHT 22
#define DHTTYPE DHT22

// definisco su quali pin sono collegati i rele dei condizionatori 
#define CondizionatoreCaldo 12
#define CondizionatoreFreddo 11
// stringhe per la lettura della libreria
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
 dht.begin();
}

void loop() {

float h = dht.readHumidity(); // leggiamo il valore per l'umidita'
  // leggiamo il valore della temperature (in gradi celsius)
  float t = dht.readTemperature();
  
  // funzione che calcola l'indice di calore.
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C  ---  ");
  Serial.print("Umidita': ");
  Serial.print(h);
  Serial.print(" %\n");
// se la temperatura è minore di 15 gradi

if (( t <= 15))
 {
  
digitalWrite(CondizionatoreCaldo , HIGH);
}
// se la temperatura è compresa tra 16 e 20 gradi
if (( t>=16 and t<= 20  ) ) 
 {
 digitalWrite(CondizionatoreCaldo , LOW);
 digitalWrite(CondizionatoreFreddo , HIGH);


}
// se la temperatura è compresa tra 21 e40  gradi

if ( t>=21 and  t<= 40  ) 
 {
  
digitalWrite(CondizionatoreFreddo , HIGH);
}
}
