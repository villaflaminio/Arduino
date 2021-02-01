#include <IRremote.h>
// definisco librerie e variabili per controllare lo stato in tempo reale
#define ACCESO 0
#define SPENTO 1

byte stato_rele_alzatapp = 0; // conserva lo stato rele alza tapparella
byte stato_rele_abbassatapp = 0; // conserva lo stato rele abbassa tapparella
byte on[]={0,0,0,0,0,0,0}; // conservo gli stati
byte buttonstate = 0;
byte lastbuttonstate = 0; 

const byte RECV_PIN = 2; //pin ricevitore IR
const byte pinReleLuci[]={0,13,12,11,10,9,}; // pin rele' luci
const byte pinReleTapp[]={0,8,7}; //pin rele' tapparella
const byte BUTTON = 3; //pulsante all'ingresso

unsigned long lastmillis = millis();
unsigned long lastmillis1 = millis();
unsigned long last = millis();
unsigned long attesa = 10000;
unsigned long attesa1 = 10000;

IRrecv irrecv(RECV_PIN);
decode_results results;

void GestioneLuce(int nluce)
{ 
  on[nluce] =  or on[nluce];
  // dichiaro un tipo stringa lavorando sugli array
  digitalWrite(pinReleLuci[nluce], on[nluce] ? HIGH : LOW); //accende o spegne
  Serial.print("stato luce ");
  Serial.print(nluce);
  Serial.println(":    ");
  Serial.println(on[nluce]);
} 

void setup() {
  //per evitare di far andare troppo veloce ed impazzire il programma
  //metto un tempo minimo di attesa
  delay(1000);
   // spengo tutti i relè insieme prima di iniziare ad eseguire il loop
   
  for(int i=0; i<=6; i++) 
  {
    // inserisco in un array [i] i singoli rele
    pinMode(pinReleLuci[i], OUTPUT);
    digitalWrite(pinReleLuci[i], SPENTO);
    on[i]=SPENTO;
  }
  // spegno tutti i rele delle tapparelle prima del loop
  for(int x=0; x<=2; x++)
  { pinMode(pinReleTapp[x], OUTPUT);
    digitalWrite(pinReleTapp[x], SPENTO);
  }    
  // dichiaro il pulsante come input pullup( o 5v o 0)
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
  irrecv.enableIRIn(); // avvio la ricezione IR
}

void stampaON() {
  // stampo affiancati i valori rilevati dai singoli pulsanti 
  // e di conseguenza i relè attivati.
  Serial.print ("on1:   ");
    Serial.println (on[1]);
    Serial.print ("on2:  ");
    Serial.println (on[2]);
    Serial.print ("on3:   ");
    Serial.println (on[3]);
    Serial.print ("on4:  ");
    Serial.println (on[4]);
    Serial.print ("on5:   ");
    Serial.println (on[5]);
    Serial.print ("on6:  ");
    Serial.println (on[6]);
}

void loop() {
  if(irrecv.decode(&results)) {
    // controllo se vengono premuti pulsanti
    switch(results.value) {
      case 50167935: // tasto 1 (luci)

      // sfrutto millis per evitare di bloccare il programma
        if (millis() - last > 250) {
  //aziono il primo rele del primo array 
          GestioneLuce(1); 
        } 
        last = millis();
      break; 
  
    case 50151615: // tasto 2 (luci)
        if (millis() - last > 250) {
          GestioneLuce(2);
        } 
        last = millis();
    break;
    
    case 50184255: // tasto 3 (luci)
        if (millis() - last > 250) {
          GestioneLuce(3);
        } 
        last = millis();
    break;
    
    case 50143455: // tasto 4 (luci)
        if (millis() - last > 250) {
          GestioneLuce(4);
        } 
        last = millis();
    break; 
    
    case 50176095: // tasto 5 (luci)
        if (millis() - last > 250) {
          GestioneLuce(5);
        } 
        last = millis();
    break; 
    
    case 50159775: // tasto 6 (luci)
        if (millis() - last > 250) {
          GestioneLuce(6);
        } 
        last = millis();
    break; 
    
    case 50157735: // tasto alza tapparella
      stato_rele_alzatapp = LOW;
      stato_rele_abbassatapp = HIGH;
      digitalWrite(pinReleTapp[1], stato_rele_alzatapp); // accende il rele' di salita
      digitalWrite(pinReleTapp[2], stato_rele_abbassatapp); //mi assicuro che sia spento il rele' di abbassamento
      lastmillis = millis();
      Serial.print("la tapp si alza:   ");
      Serial.println(millis());
    break;
    
    case 50165895: // tasto abbassa tapparella
      stato_rele_abbassatapp = LOW;
      stato_rele_alzatapp = HIGH;
      digitalWrite(pinReleTapp[2], stato_rele_abbassatapp); 
      digitalWrite(pinReleTapp[1], stato_rele_alzatapp);
      lastmillis1 = millis();
      Serial.print("la tapp si abbassa:    ");
      Serial.println(millis());
    break;

    case 50137335: // tasto blocca tapparella
      digitalWrite (pinReleTapp[1], SPENTO);
      digitalWrite (pinReleTapp[2], SPENTO);
      Serial.println("la tapparella si blocca");
    break;
  
    case 50153655: // tasto rosso spegne tutte le luci
        if (millis() - last > 250) {
        for(int i=0; i<=6; i++) {  
        on[i] = SPENTO;
        digitalWrite (pinReleLuci[i], SPENTO); } 
        Serial.println("spengo tutto");
        } 
        last = millis();
    break;
    
    } 
    // fine dello  switch
    
  irrecv.resume(); // ricevo il valore
  }  
  // fine parte 1
  buttonstate = digitalRead(BUTTON); // immagazzino il valore di button
  if (buttonstate != lastbuttonstate) 
  { 
    //se lo stato button è diverso dal precedente
    buttonstate = lastbuttonstate;
    delay(250);
    if (on[1] == 0 or on[2] == 0 or on[3] == 0 or on[4] == 0 or on[5] == 0 or on[6] == 0) { //se una delle due variabili ha valore 0
    for (int i=0; i<=6; i++) {
    digitalWrite (pinReleLuci[i], SPENTO);  // spegne tutti i rele luci
    on[i] = SPENTO; }
    stampaON();
  }
  else 
  {
    for (int i=0; i<=6; i++) {
    digitalWrite (pinReleLuci[i], ACCESO); // accendo tutti i rele'   
    on[i] = ACCESO; }
    stampaON();
  }
  
 } 
 //end if di controllo buttonstate
  
  if ((millis() - lastmillis) >= attesa) 
  {
    lastmillis = millis();
    if (stato_rele_alzatapp == LOW)
    {
      stato_rele_alzatapp = HIGH;
      digitalWrite(pinReleTapp[1], stato_rele_alzatapp);
      Serial.print("la tapparella ha smesso di alzarsi   ");
      Serial.println(millis());
    }
  }
  
  if ((millis() - lastmillis1) >= attesa1)
  {
    lastmillis1 = millis();
    if (stato_rele_abbassatapp == LOW) 
    {
      stato_rele_abbassatapp = HIGH;
      digitalWrite(pinReleTapp[2], stato_rele_abbassatapp);
      Serial.print("la tapparella ha smesso di abbassarsi    ");
      Serial.println(millis());
    }
  }
}  // chiudo il loop
