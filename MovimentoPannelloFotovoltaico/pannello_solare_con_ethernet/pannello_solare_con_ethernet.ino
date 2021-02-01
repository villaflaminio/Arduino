

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// Imposta l'indirizzo del display a 0x27 con 16 caratteri per 2 linee
LiquidCrystal_I2C lcd(0x27,16,2);  

#include <Wire.h>                      
                                                                                     
#include <Ethernet.h> //libreria ethernet
#include <SPI.h> //collabora con la libreria ethernet
#include <String.h> //gestione stringhe


#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22 // DHT 22

#include <Servo.h> // include la Libreria Servo.h
Servo myservo; // crea l’oggetto di tipo Servo, myservo sarà l’oggetto su cui opererai


DHT dht(DHTPIN, DHTTYPE);

int pannellosolare = 3;
float vout = 0.0;
float vin = 0.0;
float R1 = 100000.0; //  valore esatto resistenza R1 (100K) 
float R2 = 10000.0; //  valore esatto resistenza R2 (10K) 
int valpannello = 0;


//byte mac[] = {0x90, 0xA2, 0xDA, 0x11, 0x00, 0xAD};

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   // mac address
byte ip[] = { 192, 168, 1, 89};                      //ip ("192.168.1.89")
byte gateway[] = { 192, 168, 1, 1};                   // internet access router
byte subnet[] = { 255, 255, 255, 0};                  //subnet mask
EthernetServer server(29949);     
float Temperatura;
float Umidita;
float GradiServo;
char StatoSensore = 65;
char ON = 65;
char OFF = 78;


int analogInPin = A0; // sensore cropuscolare
int sensorValue = 0;

// memoria angoli
bool MemSensore_1 = false;
bool MemSensore_2 =  true;
bool Mem_0 = false;
bool Mem_15 = false;
bool Mem_25 = false;
bool Mem_30 = false;
bool Mem_35 = false;
bool Mem_45 = false;
bool Mem_60 = false;
bool Mem_75 = false;

String Stringa_01; 

void setup()
{
 lcd.init();// inizializza il display
  lcd.backlight();//accende la retroilluminazione
     pinMode( analogInPin, INPUT);

     pinMode(pannellosolare, INPUT);

  
  dht.begin();
  myservo.attach(9); // pin servo
 
  Ethernet.begin(mac, ip, gateway, subnet); 

  Stringa_01=""; 
}

void loop() {


disp(); // scrittura su display
  
  EthernetClient client = server.available(); //attendo l'arrivo di un client
  
  float h = dht.readHumidity(); // leggiamo il valore per l'umidita'
  // leggiamo il valore della temperature (in gradi celsius)
  float t = dht.readTemperature();
  
  // funzione che calcola l'indice di calore.
  float hic = dht.computeHeatIndex(t, h, false);

  Temperatura=t;
  Umidita=h;
  
  sensorValue = analogRead(analogInPin);            
 
  Serial.print("sensor = " );
  Serial.println(sensorValue);      
 
   sensorValue = map(sensorValue, 0, 500, 0, 180);  // "Mappa" i valori di una lettura analogica (che vanno quindi da 0 a 1023) a valori che vanno da 0 a 180.
   delay(200);

if (MemSensore_1 == false){
   
  if (( sensorValue <= 30)){
  myservo.write(0);
  Mem_0=true;
  Mem_15=false;
  Mem_30=false;
  Mem_45=false;
  Mem_60=false;
  Mem_75=false;
  GradiServo=0;
}

  if ((sensorValue>=30 and  sensorValue<= 25)){
  myservo.write(25);
   Mem_25=true;
   Mem_35=false;
   Mem_0=false;
   Mem_15=false;
   Mem_30=false;
   Mem_45=false;
   Mem_60=false;
   Mem_75=false;
   GradiServo=25;
   
  
}
   if ((sensorValue>=25 and  sensorValue<= 35)){
  myservo.write(35);
   Mem_25=false;
   Mem_35=true;
   Mem_0=false;
   Mem_15=false;
   Mem_30=false;
   Mem_45=false;
   Mem_60=false;
   Mem_75=false;
   GradiServo=35;
}
 if ((sensorValue>=35 and  sensorValue<= 45)){
  myservo.write(45);
   Mem_25=false;
   Mem_35=false;
   Mem_0=false;
   Mem_15=false;
   Mem_30=false;
   Mem_45=true;
   Mem_60=false;
   Mem_75=false;
   GradiServo=45;
}
 if ((sensorValue>=45 and  sensorValue<= 60)){
  myservo.write(60);
   Mem_25=false;
   Mem_35=false;
   Mem_0=false;
   Mem_15=false;
   Mem_30=false;
   Mem_45=false;
   Mem_60=true;
   Mem_75=false;
   GradiServo=60;
}
 
 if ((sensorValue>=75)){
  myservo.write(100);
   Mem_25=false;
   Mem_35=false;
   Mem_0=false;
   Mem_15=false;
   Mem_30=false;
   Mem_45=false;
   Mem_60=false;
   Mem_75=true;
   GradiServo=75;
 }


} 
  

  if (client) { 
    while(client.connected()) {
      if(client.available()) {
        char c = client.read(); //..leggere i caratteri che invia
        Stringa_01.concat(c); //concatena i caratteri del client

        

  if (c == '\n') { 
       
       if(Stringa_01.indexOf("Servo=00")>0) {
       myservo.write(0);
       Mem_0=true;
       Mem_15=false;
       Mem_30=false;
       Mem_45=false;
       Mem_60=false;
       Mem_75=false;
       GradiServo=0;
       
       
      }
      
  if (c == '\n') { 
       if(Stringa_01.indexOf("Servo=01")>0) {
       myservo.write(15);
       Mem_15=true;
       Mem_0=false;
       Mem_30=false;
       Mem_45=false;
       Mem_60=false;
       Mem_75=false;
       GradiServo=15;
       
      }
         
  if (c == '\n') { 
       if(Stringa_01.indexOf("Servo=02")>0) {
       myservo.write(30);
       Mem_30=true;
       Mem_0=false;
       Mem_15=false;
       Mem_45=false;
       Mem_60=false;
       Mem_75=false;
       GradiServo=30;
      }
         
  if (c == '\n') {
       if(Stringa_01.indexOf("Servo=03")>0) {
       myservo.write(45);
       Mem_45=true;
       Mem_0=false;
       Mem_15=false;
       Mem_30=false;
       Mem_60=false;
       Mem_75=false;
       GradiServo=45;
      }
         
  if (c == '\n') { 
       if(Stringa_01.indexOf("Servo=04")>0) {
       myservo.write(60);
       Mem_60=true;
       Mem_0=false;
       Mem_15=false;
       Mem_30=false;
       Mem_45=false;
       GradiServo=60;
       
      }
  if (c == '\n') { 
       if(Stringa_01.indexOf("Servo=05")>0) {
       myservo.write(75);
       Mem_75=true;
       Mem_0=false;
       Mem_15=false;
       Mem_30=false;
       Mem_45=false;
       Mem_60=false;
       GradiServo=75;
       
      }
         
         
  if (c == '\n') { 
       if(Stringa_01.indexOf("ComandoSensore=ON")>0) {
       MemSensore_1=false;
       MemSensore_2=true;
       StatoSensore=ON;
      }
        
  if (c == '\n') { 
       if(Stringa_01.indexOf("ComandoSensore=OFF")>0) {
       MemSensore_1=true;
       MemSensore_2=false;
       StatoSensore=OFF;
      
       }
       }
       }
       }
       }     
       }
       }     
       }
         
        client.println("HTTP/1.1 200 OK"); 
        client.println("Content-Type: text/html"); 
        client.println(); 
        client.println("<html>"); 
        client.println("<h1> <tt> <center> <font color=white> <font size=14> Controllo remoto pannello solare</h1> </font></font> </font></center></h1>");
        client.println("<body style=background-color:996600>");
        client.println("<body background= http://cdn.wallpapersafari.com/22/38/ayXxK3.jpg");
        
                //  client.print("<meta http-equiv=\"refresh\" content=\"5\">"); // refresh pagina

        client.println("<hr />");
        
       
        client.println("<font color=white> <font size=4> <DIV STYLE=position:absolute;top:100px> <b><u> Inserire l'angolo desiderato  e confermare </DIV></font></font>  <b/></u> <br>");
     
        
        
        client.println("<DIV STYLE=position:absolute;top:140px><form method=get name=Servo ><input type=text maxlength=2 size=10 style=width:80px;height:30px; name=Servo <br>");
        client.println("<button type=submit style=width:100px;height:100px; >CONFERMA </button></form></DIV>");

        
        client.println("<font color=white> <font size=4> <DIV STYLE=position:absolute;top:250px> <b><u> Abilitazione e disabilitazione dell  fotoresistore </u> </font></font> <br> </DIV></b>");
       
        client.println("<form method=get> <DIV STYLE=position:absolute;top:300px> <button type=submit style=width:150px;height:50px; name=ComandoSensore value=ON >Abilita Sensore </button></DIV></form>");            
        client.println("<form method=get> <DIV STYLE=position:absolute;top:300px;left:200px> <button type=submit style=width:150px;height:50px; name=ComandoSensore value=OFF >Disabilita Sensore</button></DIV></form>");      
        
        
        client.println("<font color=white><u> <font size=3> <DIV STYLE=position:absolute;top:300px;left:600px> Angolo attuale del pannello solare</u>: ");
        client.print(GradiServo); 
        client.println("*<br/></p></DIV></font> </font>");

        client.println("<font color=white> <font size=3> <DIV STYLE=position:absolute;top:370px;left:100px> Sensore di umidita': ");
        client.print(StatoSensore); 
        client.println("<br/></p></DIV></font> </font>");
       
        client.println("<font color=red> <font size=4><DIV STYLE=position:absolute;top:100px;left:600px> <b><u> Lettura temperatura e umidita</u>' </font></font></DIV> </b>  <br>");
        client.println("<head><title>Controllo Remoto Macchina del caffe'</title> <link rel='shortcut icon' type='image/x-icon' href='http://i44.servimg.com/u/f44/16/84/89/65/23570310.png' /></head>");
        client.println("<p><font color=white> <font size=3> <DIV STYLE=position:absolute;top:150px;left:600px> Temperatura Ambiente: ");
        client.print(Temperatura); 
        client.println("*C<br/></p></DIV></font> </font>");
        client.println("<font color=white> <font size=3> <DIV STYLE=position:absolute;top:180px;left:600px> Umidita' Ambiente: ");
        client.print(Umidita);
        client.println(" %\n <br/></p></DIV></font> </font>");
        client.println("<font color=white> <font size=3> <DIV STYLE=position:absolute;top:280px;left:600px> Tensione prodotta:  ");
        client.print(vin);
        client.println(" V\n <br/></p></DIV></font> </font>");
        
        
        client.println("<meta http-equiv=refresh content=10;url=192.168.1.120>");

          
        client.println("</html>"); //fine codice html
        client.stop(); //stop richieste dal client
        Stringa_01="";
        }
      }
    }
  }
}



void disp()
{
 float h = dht.readHumidity(); // leggiamo il valore per l'umidita'
  // leggiamo il valore della temperature (in gradi celsius)
  float t = dht.readTemperature();
  
  // funzione che calcola l'indice di calore.
  float hic = dht.computeHeatIndex(t, h, false);

  Temperatura=t;
  Umidita=h;
  
  valpannello = analogRead(pannellosolare);
   
   vout = (valpannello * 5.0) / 1024.0; 
   // inserire al posto di 5.0V l`uscita in volt tra i Pin 5V e GND del vostro Arduino
   
   vin = vout / (R2/(R1+R2)); 
   if (vin<0.09) {
   vin=0.0;
   }
     lcd.setCursor(0, 0);
     lcd.print("TENSIONEPRODOTTA");
     lcd.setCursor(0, 1);
     lcd.print("V");
     lcd.print(vin);
  
}
