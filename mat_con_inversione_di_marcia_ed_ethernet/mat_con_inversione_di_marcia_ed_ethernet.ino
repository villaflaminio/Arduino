#define MotoreAvanti 40             // LED collegato al pin digitale 13  
#define LedMotoreAvanti 53
#define Motoreinversione 44              // LED collegato al pin digitale 13  
#define LedMotoreinversione 52
#define BUTTON 22 
 #define BUTTON2 24  
 #define BUTTON3 26
bool protezione1=LOW;
bool protezione2=LOW;
int val = 0;                  // si userà val per conservare lo stato del pin di input  
int vecchio_val = 0;          // si userà vecchio_val per conservare lo stato del pin di input al passo precedente  
int stato = 0;   
 
  int val2 = 0;                  // si userà val per conservare lo stato del pin di input  
int vecchio_val2 = 0;          // si userà vecchio_val per conservare lo stato del pin di input al passo precedente  
int stato2 = 0;

int val3 = 0;                  // si userà val per conservare lo stato del pin di input  
int vecchio_val3 = 0;          // si userà vecchio_val per conservare lo stato del pin di input al passo precedente  
int stato3 = 0;  

 int fisico1=0;
 int virtuale1=0;
 
#include <SPI.h>
#include <Ethernet.h>


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   // mac address
byte ip[] = { 192, 168, 1, 89};                      //ip ("192.168.1.89")
byte gateway[] = { 192, 168, 1, 254};                   // internet access router
byte subnet[] = { 255, 255, 255, 0 };                  //subnet mask
EthernetServer server(80);                             //server port     
String readString;

void setup() {
  protezione1=LOW;
 protezione2=LOW; 
  pinMode(MotoreAvanti, OUTPUT);       // imposta il pin digitale come output 
    pinMode(Motoreinversione, OUTPUT);       // imposta il pin digitale come output  
 pinMode(LedMotoreAvanti, OUTPUT);
 pinMode(LedMotoreinversione, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);     // imposta il pin digitale come input  
    pinMode(BUTTON2, INPUT_PULLUP);     // imposta il pin digitale come input  
    pinMode(BUTTON3, INPUT_PULLUP);     // imposta il pin digitale come input  
    digitalWrite(MotoreAvanti, LOW);   // accende il led  
        digitalWrite(Motoreinversione, LOW);   // accende il led 
       val2 =HIGH;
 // Apro la comunicazione seriale:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  //Imposto i pin come OUTPUT
 


  // Inizio la comunicazione Ethernet con il server:
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
   fisico();
  // Creo una connessione al client
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
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
     
           client.println("HTTP/1.1 200 OK"); //Invio nuova pagina
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");

           client.println("<HEAD>");
                  // client.print("<meta http-equiv=\"refresh\" content=\"5\">"); // refresh pagina

           client.println("<TITLE>Controllo MAT da remoto</TITLE>");

           client.println("</HEAD>");
           client.println("<BODY>");

        client.println("<body background= http://www.boorp.com/sfondi_gratis_desktop_pc/sfondi_gratis/sfondi_3d_computer_grafica/sfondi_3d_125.jpg>");

           client.println("<hr />");

           client.println("<H1> <I> <CENTER>Controllo MAT da remoto </CENTER> </I></H1>");
           client.println("<hr />");
           client.println("<hr />");

           client.println("<br />");  
        client.println(" <form method=get> <DIV STYLE=position:absolute;top:300px> <button type=submit style=width:150px;height:50px   name=avviomotore value=ON>avvia il motore </button></DIV></form></font>");            
        client.println(" <form method=get> <DIV STYLE=position:absolute;top:300px;left:300px;> <button type=submit style=width:150px;height:50px   name=StopMotore value=ON>STOP </button></DIV></form></font>");  
        client.println(" <form method=get> <DIV STYLE=position:absolute;top:300px;left:600px;> <button type=submit style=width:150px;height:50px   name=inversionemotore value=ON>inverti il motore </button></DIV></form></font>");  
        
client.println(" <form method=get> <DIV STYLE=position:top:600px;left:0px;>");

              client.println("<H3> Grazie a questa interfaccia grafica andremo a controllare un  MAT da remoto effettuando anche l'inversione di marcia. </H3>");
           client.println("<H3> in questa pagina web ci sono 3 pulsanti che servono ad avviare arrestare o invertire un M.A.T  </H3>");
           client.println("<H3> Per iniziare premere il pulsante _stop_ ,  questo e' un controllo di sicurezza, per assicurarci che il motore sia fermo.</H3>");
                      client.println("<hr />");

                      client.println("<br />");  
                      client.println("<br />");  
                      client.println("<br />");  
                      client.println("<br />");  
                      client.println("<br />");  
           client.println("<br />");  
           client.println("<br />");  
           client.println("<hr />");
           client.println("<hr />");

           client.println("<H3> <U> Le stesse funzionalita' della pagina web possono essere eseguite grazie a dei pulsanti fisici di arduino, Possiamo notare diverse protezioni nel programma: </U> </H3>");
           client.println("<H3> 1) E' impossibile effetturare l'inversione di marcia mentre il motore e' gia in funzione.</H3>");
           client.println("<H3> 2) E' impossibile avviare il motore quando e' in corso l'inversione di marcia. </H3>");
           client.println("<H3> 3) Per poter inveritire il motore bisogna prima premere il pulsante di stop.  </H3>");
           client.println("<H3> (gli stessi controlli di sicurezza vengono effettuati nel comando manuale)  </H3>");
           client.println("<H3>  vi sono ulteriori protezioni per evitare che i controlli virtuali e quelli fisici vadano in conflitto: </H3>");
           client.println("<H3> 1)E' impossibile avviare il motore virtualmentre se e' gia stato avviato manualmente.  </H3>");
           client.println("<H3> 2) E' impossibile invertire il motore fisicamente se e' gia stato avviato virtualmente.  </H3>");
           client.println("<H3> 3) Prima di poter azionare o invertire il motore e' obbligatorio fermarlo, fisicamente o virtualmente  </H3>");

           client.println("<H3>  </H3>");
           client.println("<H3>  </H3>");
           client.println("<H3>  </H3>");
           client.println("<H3>  </H3>");
           client.println("<H3>  </H3>");
           client.println("<H3>  </H3>");
           client.println("<H3>  </H3>");
           client.println("<H3>  </H3>");

           client.println("</BODY>");
           client.println("</HTML>");
     
 delay(1);
 

           //Controlli su Arduino: Se è stato premuto il pulsante sul webserver
           if ((readString.indexOf("avviomotore") >0) and (protezione1==HIGH)and(fisico1==1) )
           {
       client.println(  "<DIV STYLE=position:absolute;top:290px;left:205px;>  START<br> <img src= https://us.123rf.com/450wm/maxborovkov/maxborovkov0912/maxborovkov091200051/6015780-pulsante-verde-lucido-illustrazione-vettoriale.jpg?ver=6.jpg style=width:50px;height:50px>    </DIV>" );
protezione2=LOW;
stato=1;
stato2=0;
stato3=0;
virtuale1=0;

           }
           if (readString.indexOf("StopMotore") >0)
           {
                    client.println(  "<DIV STYLE=position:absolute;top:280px;left:460px;> STOP <br> <img src=https://openclipart.org/download/122749/glossy-red-button.svg.jpg style=width:60px;height:60px>    </DIV>" );
 protezione1= HIGH;
            protezione2= HIGH;
stato=0;
stato2=1;
stato3=0;
fisico1=1;

virtuale1=1;

           }
            if ((readString.indexOf("inversionemotore") >0) and (protezione2==HIGH)and(fisico1==1)) 
            {
    
       
                   client.println(  "<DIV STYLE=position:absolute;top:280px;left:780px;> inversione <br> <img src=https://publicdomainvectors.org/photos/glossy-light-orange-button.png style=width:50px;height:50px>    </DIV>" );
protezione1=LOW;
 stato=0;
stato2=0;
stato3=1;
virtuale1=0;

           }
           
         
            //Cancella la stringa una volta letta
            readString="";  
           
                    client.stop();

    }
   }
    }
  }
}
 
void fisico() {  
 
  val = digitalRead(BUTTON);  // legge il valore dell'input e lo conserva  
  
  // controlla se è accaduto qualcosa  
  if ((val == HIGH) && (vecchio_val == LOW) and (protezione2==HIGH) and(virtuale1 ==1) ){  
    stato = 1 - stato;  
    stato3=0;
    stato2=0;
    fisico1=0; 


                    protezione1= LOW;

  }   
  
  vecchio_val = val;            // ricordiamo il valore precedente di val  

 
  
  vecchio_val2 = val2; 

   val3 = digitalRead(BUTTON3);  // legge il valore dell'input e lo conserva  
  
  // controlla se è accaduto qualcosa  
  if ((val3 == HIGH) && (vecchio_val3 == LOW) and (protezione1==HIGH) and (virtuale1 ==1) ){  
              protezione2= LOW;

    stato3 = 1 - stato3;  
    stato2=0;
    stato=0;
fisico1=0;
  }   
  
  vecchio_val3 = val3; 

   val2 = digitalRead(BUTTON2);  // legge il valore dell'input e lo conserva  
  
  // controlla se è accaduto qualcosa  
  if ((val2 == HIGH) && (vecchio_val2 == LOW)){  
    stato2 = 1 - stato2;  
    stato=0;
    stato3=0;
                protezione1= HIGH;
            protezione2= HIGH;
fisico1=1;

virtuale1=1;

  }   
  if (stato2 == 1) {  
    digitalWrite(MotoreAvanti, LOW);   // accende il led 
         digitalWrite(Motoreinversione, LOW);   // accende il led 
         
    digitalWrite(LedMotoreAvanti, LOW);   // accende il led 

        digitalWrite(LedMotoreinversione, LOW);   // accende il led  
        
  }
  else if (stato == 1) { 

    digitalWrite(MotoreAvanti, HIGH);   // accende il led  
        digitalWrite(LedMotoreAvanti, HIGH);   // accende il led  


  }  
  
      
else  if (stato3 == 1)
{
  stato=0;
      digitalWrite(Motoreinversione, HIGH);   // accende il led  
            digitalWrite(LedMotoreinversione, HIGH);   // accende il led  


}

 
  


   
}
 



 

