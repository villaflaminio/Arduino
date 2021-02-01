//==============================//
// dichiaro i pin dei pulsanti
int pulsanteingresso = 5;
int pulsantebagno = 6;
int pulsantecucinasoggiorno = 7;
int pulsantecamera = 8;
//==============================//
//dichiaro i pin dei rele
int Releingresso = 10;
int Relebagno = 11;
int Relecucinasoggiorno = 12;
int Relecamera = 13;
//==============================//
// variabili che memorizzano lo stato dei pulsanti
bool Statopulsanteingresso = LOW;
bool Statopulsantebagno = LOW;
bool Statopulsantecucinasoggiorno = LOW;
bool Statopulsantecamera = LOW;
//================================//
// variabili della memoria pulsante
bool Memoriapulsanteingresso = LOW;
bool Memoriapulsantebagno = LOW;
bool Memoriapulsantecucinasoggiorno = LOW;
bool Memoriapulsantecamera = LOW;
//================================//
// stati d'appoggio
bool Stato1 = LOW;
bool Stato2 = LOW;
bool Stato3 = LOW;
bool Stato4 = LOW;

void setup() {
  // dichiaro i pulsanti in INPUT_PULLUP
  pinMode(pulsanteingresso, INPUT_PULLUP);
  pinMode(pulsantebagno, INPUT_PULLUP);
  pinMode(pulsantecucinasoggiorno, INPUT_PULLUP);
  pinMode(pulsantecamera, INPUT_PULLUP);
  // dichiaro i relè in OUTPUT
  pinMode(Releingresso, OUTPUT);
  pinMode(Relebagno, OUTPUT);
  pinMode(Relecucinasoggiorno, OUTPUT);
  pinMode(Relecamera, OUTPUT);
}

void loop()
{
  ingresso();
  bagno();
  cucinasoggiorno();
  camera();
}
// dichiaro dei singoli void per i vari pulsanti.
void ingresso() {
  Statopulsanteingresso = digitalRead(pulsanteingresso); // analizzo la lettura del pulsante e la associo ad una variabile
  if ((Statopulsanteingresso == HIGH) and (Memoriapulsanteingresso == LOW)) // confronto
  {
    Stato1 = 1 - Stato1;   // stoato di appoggio per stato rele
    delay(20);
  }

  Statopulsanteingresso = Memoriapulsanteingresso; //confronto

  if (Stato1 == LOW) // verifico che sia spento
  {
    digitalWrite(Releingresso, LOW);   // se premuto accende il rele
    // ( i relè funzionano al contrario dei led aperto-chiuso)
    delay(50);
  }
  else
  {
    digitalWrite(Releingresso, HIGH);  // altrimenti spegne il rele
    delay(50);
  }
}
void bagno () {
  Statopulsantebagno = digitalRead(pulsantebagno);
  if ((Statopulsantebagno == HIGH) and (Memoriapulsantebagno == LOW))
  {
    Stato2 = 1 - Stato2;
    delay(20);
  }

  Statopulsantebagno = Memoriapulsantebagno;

  if (Stato2 == LOW)
  {
    digitalWrite(Relebagno, LOW);   // se premuto accende il led
    delay(50);
  }
  else
  {
    digitalWrite(Relebagno, HIGH);
    delay(50);
  }
}
void cucinasoggiorno () {
  Statopulsantecucinasoggiorno = digitalRead(pulsantecucinasoggiorno);
  if ((Statopulsantecucinasoggiorno == HIGH) and (Memoriapulsantecucinasoggiorno == LOW))
  {
    Stato3 = 1 - Stato3;
    delay(20);
  }

  Statopulsantecucinasoggiorno = Memoriapulsantecucinasoggiorno;

  if (Stato3 == LOW)
  {
    digitalWrite(Relecucinasoggiorno, LOW);   // se premuto accende il led
    delay(50);
  }
  else
  {
    digitalWrite(Relecucinasoggiorno, HIGH);
    delay(50);
  }
}
void camera () {
  Statopulsantecamera = digitalRead(pulsantecamera);
  if ((Statopulsantecamera == HIGH) and (Memoriapulsantecamera == LOW))
  {
    Stato4 = 1 - Stato4;
    delay(20);
  }

  Statopulsantecamera = Memoriapulsantecamera;

  if (Stato4 == LOW)
  {
    digitalWrite(Relecamera, LOW);   // se premuto accende il led
    delay(50);
  }
  else
  {
    digitalWrite(Relecamera, HIGH);
    delay(50);
  }
}

