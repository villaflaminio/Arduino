
//----------------librerie-------------//


#include <SPI.h>
#include <Ethernet.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22 // DHT 22 
#include <String.h> //gestione stringhe
#include <Wire.h>

DHT dht(DHTPIN, DHTTYPE);
float Temperatura;
float Umidita;

//---------------------------------//
float vout = 0.0;
float vin = 0.0;
float R1 = 100000.0; //  valore esatto resistenza R1 (100K)
float R2 = 10000.0; //  valore esatto resistenza R2 (10K)
int valpannello = 0;




//----------pin output------------//
int Verde = 32;
int Rosso = 34;
int luciesterne = 36;
int luce1 = 38;
int luce2 = 40;
int luce3 = 42;
int luce4 = 44;
int luce5 = 46;
int luce6 = 48;
int luce7 = 50;
int luce8 = 52;
int sensoreporta = 30;
int pinchiave = 28;
int allarme = 26;

int pannellosolare = A0;
int pinsensoreluminosita = A1;
int sensoregas = A2;
//


/////////////////////////

//-------variabili d'appoggio--------//
bool statoall = LOW;
bool allarmeon = LOW;
int statoporta = 0;
int val1 = 0;
int stato1 = 0;
int luminosita = 0;
int sensorValue = 0;
int chiave = 0;
///////////////////////////////
//-----------------configurazioni web-------------------------------------//
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   // mac address
byte ip[] = { 192, 168, 1, 89};                      //ip ("192.168.1.89")
byte gateway[] = { 192, 168, 1, 1};                   // internet access router
byte subnet[] = { 255, 255, 255, 0 };                  //subnet mask
EthernetServer server(80);     
String readString;
String Stringa_01;
/////////////////


void setup()
{
  Serial.begin(9600);

  // comunicazione seriale
  while (!Serial) {
    ;
  }
  //------------Imposto i pin come OUTPUT---------------//
  pinMode( pinsensoreluminosita, INPUT);
  pinMode( sensoregas, INPUT);
  pinMode(sensoreporta, INPUT_PULLUP);
  pinMode(  pinchiave, INPUT_PULLUP);
  pinMode(pannellosolare, INPUT);

  //  pinMode(LED,OUTPUT);

  pinMode(luce1, OUTPUT);
  pinMode(luce2, OUTPUT);
  pinMode(luce3, OUTPUT);
  pinMode(luce4, OUTPUT);
  pinMode(luce5, OUTPUT);
 pinMode(luce6, OUTPUT);
  pinMode(luce7, OUTPUT);
  pinMode(luce8, OUTPUT);

  pinMode(luciesterne, OUTPUT);
  pinMode(Rosso, OUTPUT);
  pinMode(Verde, OUTPUT);
  pinMode(allarme, OUTPUT);
  // string
  Stringa_01 = "";
  dht.begin();

  // Inizio la comunicazione Ethernet con il server:
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop()

{

  float h = dht.readHumidity(); // leggiamo il valore per l'umidita'
  float t = dht.readTemperature();  // leggiamo il valore della temperature (in gradi celsius)
  Temperatura = t;
  Umidita = h;
  luminosita = analogRead(pinsensoreluminosita);
  valpannello = analogRead(pannellosolare);

  vout = (valpannello * 5.0) / 1024.0;
  // inserire al posto di 5.0V l`uscita in volt tra i Pin 5V e GND del vostro Arduino

  vin = vout / (R2 / (R1 + R2));
  if (vin < 0.09) {
    vin = 0.0;
  }
  chiave = digitalRead(pinchiave);
  if (chiave == HIGH)
  {
    allarmeon = LOW;
  }
  else
  {
    allarmeon = HIGH;

  }
  //---------------------------------------//
  if (allarmeon == LOW)
  {
    digitalWrite(Verde, HIGH);
    digitalWrite(Rosso, LOW);
    digitalWrite(allarme, HIGH);
delay(500);
    digitalWrite(allarme, LOW);
  }
  else
  {
    digitalWrite(Verde, LOW);
    digitalWrite(Rosso, HIGH);
    digitalWrite(allarme, LOW);


  }

  statoporta = digitalRead(sensoreporta);

  if ((statoporta == 1) and (allarmeon == 1))
  {
    digitalWrite(allarme, HIGH);
  }
  else
  {
    digitalWrite(allarme, LOW);
  }

  if (luminosita < 500)
  {
    digitalWrite(luciesterne, LOW);
  }
  else
  {
    digitalWrite(luciesterne, HIGH);
  }

  // Creo una connessione al client
  EthernetClient client = server.available();
  if (client)
    while (client.connected())
    {
      if (client.available()) {
        char c = client.read();

        //Leggo i caratteri da HTTP
        if (readString.length() < 100) {
          //Inserisco i caratteri nella stringa
          readString += c;
          //Serial.print(c);
        }

        //Se la richiesta HTTP è andata a buon fine
        if (c == '\n') {
          Serial.println(readString); //scrivi sul monitor seriale per debugging

          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connnection: close");
          client.println();
          client.println("<!DOCTYPE HTML>");
          
          client.println("<body background= https://img-new.cgtrader.com/items/862599/e780918d7a/free-4k-wood-texures-3d-model-rigged.jpg>");

          client.println("<head>");


          client.println("<title>Camera 2</title>");
          client.println("<meta name=\"description\" content=\"Arduino Controllo casa\"/>");


          client.print("<meta http-equiv=\"refresh\" content=\"");
          client.println("; url=/\">");


          client.println("<meta name=\"apple-mobile-web-app-capable\" content=\"yes\">");
          client.println("<meta name=\"apple-mobile-web-app-status-bar-style\" content=\"default\">");
          client.println("<meta name=\"viewport\" content=\"width=device-width, user-scalable=no\">");


          client.println("<style type=\"text/css\">");
          client.println("");


          client.println("html { height:100%; }");

          client.println("body{");

          //client.println("background: #f5f6f6; /* Old browsers */");
          //client.println("background: -moz-linear-gradient(top,#3b5998 0%,#8b9dc3 21%,  #dfe3ee 49%,  #f7f7f7 80%,#FF9900  100%); /* FF3.6-15 */");
          //client.println("background: -webkit-linear-gradient(top, #3b5998 0%,#8b9dc3 21%,  #dfe3ee 49%,  #f7f7f7 80%,#FF9900  100%); /* Chrome10-25,Safari5.1-6 */");
          //client.println("background: linear-gradient(to bottom, #A13F00   0%,#A13F00  21%,  #A13F00 49%,  #A13F00 80%,#A13F00  100%); /* W3C, IE10+, FF16+, Chrome26+, Opera12+, Safari7+ */");
          // client.println("filter: progid:DXImageTransform.Microsoft.gradient( startColorstr='#f5f6f6', endColorstr='#f5f6f6',GradientType=0 ); /* IE6-9 */");
          client.println("margin:50px 0px; padding:0px;");
          client.println("text-align:center;");
          client.println("}");
          client.println("h1");
          client.println("{");
          client.println("text-align: center;");
          client.println("font-family:Times New Roman;");
          client.println("}");
          client.println("h3");
          client.println("{");
          client.println("text-align: center;");
          client.println("font-family:Arial,  Helvetica, sans-serif;");
          client.println("}");
          client.println("a");
          client.println("{");
          client.println("text-decoration:none;");
          client.println("width:180px;");
          client.println("height:180px;");
          client.println("border-color:Black;");
          client.println("border-top:2px solid;");
          client.println("border-bottom:2px solid;");
          client.println("border-right:2px solid;");
          client.println("border-left:2px solid;");
          client.println("border-radius:10px 10px 10px;");
          client.println("-o-border-radius:10px 10px 10px;");
          client.println("-webkit-border-radius:20px 20px 20px;");
          client.println("font-family:Arial, Helvetica, sans-serif;");
          client.println("-moz-border-radius:10px 10px 10px;");
          client.println("background-color:#008080;");
          client.println("padding10px;");
          client.println("text-align:center;");
          client.println("}");
          client.println("a:link {color:white;}      /* unvisited link */");
          client.println("a:visited {color:white;}  /* visited link */");
          client.println("a:hover {color:yellow;}  /* mouse over link */");
          client.println("a:active {color:white;}  /* selected link */");
          client.println("</style>");
          client.println("</head>");


          client.println("<body>");

          client.println("<TITLE>Controllo casa Domotica</TITLE>");

          client.println("</HEAD>");
          client.println("<BODY>");
          client.println("<hr />");
          client.println("<br />");
          client.println("<font color=WHITE> <font face=”Lucida Handwriting”></font> <H1>Controllo casa Domotica</H1>");
          client.println("<br />");
          client.println("<a href='?buttonluce1on'> --Luce Salotto ON-- </a>");
          client.println("&#160");
          client.println("&#160");
          client.println("<a href='?buttonluce1off'> --Luce Salotto OFF-- </a><br />");

          client.println("<br />");
          client.println("<br />");

          client.println("<a href='?buttonLuce2on'> --Luce Cucina ON-- </a>");
          client.println("&#160");
          client.println("&#160");
          client.println("<a href='?buttonLuce2off'> --Luce Cucina OFF-- </a><br />");


          client.println("<br />");
          client.println("<br />");

          client.println("<a href='?buttonLuce3on'> --Luce corridoio ON-- </a>");
          client.println("&#160");
          client.println("&#160");
          client.println("<a href='?buttonLuce3off'> --Luce corridoio OFF-- </a><br />");

          client.println("<br />");
          client.println("<br />");

          client.println("<a href='?buttonLuce4on'> --Luce stanza1 ON-- </a>");
          client.println("&#160");
          client.println("&#160");
          client.println("<a href='?buttonLuce4off'> --Luce stanza1 OFF-- </a><br />");

          client.println("<br />");
          client.println("<br />");

          client.println("<a href='?buttonLuce5on'> --Luce bagno1 ON-- </a>");
          client.println("&#160");
          client.println("&#160");
          client.println("<a href='?buttonLuce5off'> --Luce bagno1 OFF-- </a><br />");
          client.println("<br />");
          client.println("<br />");
          client.println("<a href='?buttonLuce6on'> --Luce stanzino ON-- </a>");
          client.println("&#160");
          client.println("&#160");
          client.println("<a href='?buttonLuce6off'> --Luce stanzino OFF-- </a><br />");
          client.println("<br />");
          client.println("<br />");
          client.println("<a href='?buttonLuce7on'> --Luce letto2 ON-- </a>");
          client.println("&#160");
          client.println("&#160");
          client.println("<a href='?buttonLuce7off'> --Luce letto2 OFF-- </a><br />");
          client.println("<br />");
          client.println("<br />");
          client.println("<a href='?buttonLuce8on'> --Luce bagno2 ON-- </a>");
          client.println("&#160");
          client.println("&#160");
          client.println("<a href='?buttonLuce8off'> --Luce bagno2 OFF-- </a><br />");
          client.println("<br />");
          client.println("<br />");
          client.println("<a href='?buttonLucegon'> --Tutte le luci ON-- </a>");
          client.println("&#160");
          client.println("&#160");
          client.println("<a href='?buttonLucegoff'> --Tutte le luci OFF-- </a><br />");
          client.println("<br />");
          client.println("<br />");
          client.println("<a href='?allarmeonon'> --ALLARME ON-- </a>");
          client.println("&#160");
          client.println("&#160");
          client.println("<a href='?allarmeonoff'> --ALLARME OFF-- </a><br />");
          client.println("<br />");
          client.println("<br />");

client.println("<DIV STYLE=position:absolute;top:140px><form method=get name=Servo ><input type=text maxlength=2 size=10 style=width:80px;height:30px; name=Servo <br>");
        client.println("<button type=submit style=width:100px;height:100px; >CONFERMA </button></form></DIV>");

        
          //--------temperatura

          client.println(  "<DIV STYLE=position:absolute;top:250px;left:205px;>  <br> <img src= https://static5.depositphotos.com/1006634/532/v/950/depositphotos_5323796-stock-illustration-thermometer-in-hot-and-cold.jpg style=width:70px;height:70px>    </DIV>" );
          client.println("<p><font color=red> <font size=3> <DIV STYLE=position:absolute;top:230px;left:205px> Temperatura Ambiente: ");
          client.print(Temperatura);
          client.println("*C<br/></p></DIV></font> </font>");

          //-------------------------UMIDITà---------

          client.println(  "<DIV STYLE=position:absolute;top:400px;left:205px;>  <br> <img src= https://previews.123rf.com/images/maxborovkov/maxborovkov0803/maxborovkov080300023/2667053-Luminose-gocce-d-acqua-Illustrazione-vettoriale--Archivio-Fotografico.jpg style=width:70px;height:70px>    </DIV>" );
          //client.println("<font color=blue> <font size=3> <DIV STYLE=position:absolute;top:100;left:105px> Umidita' Ambiente: ");
          client.print(Umidita);
          client.println("%<br/></p></DIV></font> </font>");


          //--------------------LUMINOSITà---------
          client.println(  "<DIV STYLE=position:absolute;top:580px;left:205px;>  <br> <img src= http://www.news24web.it/wp-content/uploads/2014/05/Meteo-sole.jpg?x71225 style=width:70px;height:70px>   </DIV>" );

          client.println("<font color=yellow> <font size=3> <DIV STYLE=position:absolute;top:570px;left:205px>Luminosita' Ambiente: ");

          client.print(luminosita);

          //---------------------GAS

          sensorValue = analogRead(sensoregas);
          sensorValue = map(sensorValue, 0, 1023, 0, 100);
          client.println(  "<DIV STYLE=position:absolute;top:180px;left:0px;>  <br> <img src= http://www.atalayar.com/sites/default/files/gas%20natural.JPG style=width:70px;height:70px>    </DIV>" );

          client.println("<font color=green> <font size=3> <DIV STYLE=position:absolute;top:160px;left:0px>Gas Ambiente: ");
          client.print(sensorValue);
          //--------------------- fotovoltaico
          client.println(" %\n <br/></p></DIV></font> </font>");
          client.println("<font color=white> <font size=3> <DIV STYLE=position:absolute;top:280px;left:600px> Tensione prodotta:  ");
          client.print(vin);
          client.println(" V\n <br/></p></DIV></font> </font>");


          client.println("<meta http-equiv=refresh content=10;url=192.168.1.120>");

          client.println("%<br/></p></DIV></font> </font>");

          client.println("</BODY>");
          client.println("</HTML>");

          delay(1);

          //Controlli su Arduino: Se è stato premuto il pulsante sul webserver
          if (readString.indexOf("?buttonLuce1on") > 0) {
            digitalWrite(luce1, HIGH);

          }
          if (readString.indexOf("?buttonLuce1off") > 0) {
            digitalWrite(luce1, LOW);

          }
          if (readString.indexOf("?buttonLuce2on") > 0) {
            digitalWrite(luce2, HIGH);

          }
          if (readString.indexOf("?buttonLuce2off") > 0) {
            digitalWrite(luce2, LOW);
          }

          if (readString.indexOf("?buttonLuce3on") > 0) {
            digitalWrite(luce3, HIGH);

          }
          if (readString.indexOf("?buttonLuce3off") > 0) {
            digitalWrite(luce3, LOW);

          }
          if (readString.indexOf("?buttonLuce4on") > 0) {
            digitalWrite(luce4, HIGH);

          }
          if (readString.indexOf("?buttonLuce4off") > 0) {
            digitalWrite(luce4, LOW);


          }
          if (readString.indexOf("?buttonLuce5on") > 0) {
            digitalWrite(luce5, HIGH);


          }
          if (readString.indexOf("?buttonLuce5off") > 0) {
            digitalWrite(luce5, LOW);

          }
          if (readString.indexOf("?buttonLuce6on") > 0) {
            digitalWrite(luce6, HIGH);


          }
          if (readString.indexOf("?buttonLuce6off") > 0) {
            digitalWrite(luce6, LOW);

          }
          if (readString.indexOf("?buttonLuce7on") > 0) {
            digitalWrite(luce7, HIGH);


          }
          if (readString.indexOf("?buttonLuce7off") > 0) {
            digitalWrite(luce7, LOW);

          }
          if (readString.indexOf("?buttonLuce8on") > 0) {
            digitalWrite(luce8, HIGH);


          }
          if (readString.indexOf("?buttonLuce8off") > 0) {
            digitalWrite(luce8, LOW);

          }

          if (readString.indexOf("?buttonLucegon") > 0) {
            digitalWrite(luce1, HIGH);
            digitalWrite(luce2, HIGH);
            digitalWrite(luce3, HIGH);
            digitalWrite(luce4, HIGH);
            digitalWrite(luce5, HIGH);
            digitalWrite(luce6, HIGH);
            digitalWrite(luce7, HIGH);
            digitalWrite(luce8, HIGH);
          }
          if (readString.indexOf("?buttonLucegoff") > 0) {
            digitalWrite(luce1, LOW);
            digitalWrite(luce2, LOW);
            digitalWrite(luce3, LOW);
            digitalWrite(luce4, LOW);
            digitalWrite(luce5, LOW);
            digitalWrite(luce6, LOW);
            digitalWrite(luce7, LOW);
            digitalWrite(luce8, LOW);

          }
          if (readString.indexOf("?allarmeonon") > 0) {

            client.println(" <DIV STYLE=position:absolute;top:100px;left:700px> <H1> <U> <font color=red> ATTENZIONE ALLARME ATTIVO </U> </font> </H1>");
            allarmeon = HIGH;

          }
          if (readString.indexOf("?allarmeonoff") > 0) {

            client.println("<DIV STYLE=position:absolute;top:100px;left:700px> <H1> <U> <font color=blue> ALLARME DISATTIVATO    </U> </font> </H1>");
            allarmeon = LOW;
          }
if(readString.indexOf("Servo=00")>0) {
               client.println("<font color=white> <font size=3>frjtrydjdtyjtyjtyjtyjjjjjjjjjjjjjjjjjjjjjjjjjjjj: ");

       
       
      }
      

          //Cancella la stringa una volta letta
          readString = "";
          Stringa_01 = "";

          client.stop();
        }

      }
    }
}





