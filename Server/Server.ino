//librerias
#include <WiFi.h>
#include <SPIFFS.h>
#include <WebServer.h>

/* Put your SSID & Password */
const char* ssid = "Starbucks_free_wifi";  // Enter SSID here
const char* password = "12345678";  //Enter Password here



/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

// Variable to store the HTTP request
String header;


// Auxiliar variables to store the current output state
#define RXD2 16
#define TXD2 17

// Del display
#define e 18
#define d 19
#define c 21
#define g 14
#define f 27
#define a 26
#define b 25


// Variables
//parque libre = 0 y ocupado = 1
struct Estados{
  unsigned char par0 = 0;
  unsigned char par1 = 0;
  unsigned char par2 = 0;
  unsigned char par3 = 0;
  unsigned char par4 = 0;
  unsigned char par5 = 0;
  unsigned char par6 = 0;
  unsigned char par7 = 0;
}estado_parqueo;

unsigned char letra;

char contador = 0;

unsigned char steps = 0;
unsigned char steps2 = 0;
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  server.on("/", handle_OnConnect); // Directamente desde e.g. 
  
  server.begin();
  Serial.println("HTTP server started");
  delay(100);

  pinMode(a, OUTPUT);  //A
  pinMode(b, OUTPUT);  //B
  pinMode(c, OUTPUT);  //C
  pinMode(d, OUTPUT);  //D
  pinMode(e, OUTPUT);  //E
  pinMode(f, OUTPUT);  //F
  pinMode(g, OUTPUT);  //G
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0){
    estado_parqueo.par0 = Serial.read();
    //lo combierte a su valor en decimal
    estado_parqueo.par0 -= 48;
    //Serial.write(estado_parqueo.par0);
  }
  server.handleClient();

  if (Serial.available()){
    String CadenaEntrante = Serial.readStringUntil(',');
    //Serial.println(CadenaEntrante);

    String Parqueo00 = CadenaEntrante.substring(0,1);
    String Parqueo01 = CadenaEntrante.substring(1,2);
    String Parqueo02 = CadenaEntrante.substring(2,3);
    String Parqueo03 = CadenaEntrante.substring(3,4);
     estado_parqueo.par4 = CeroA1(Parqueo00.toInt());
estado_parqueo.par5 = CeroA1(Parqueo00.toInt());
estado_parqueo.par6 = CeroA1(Parqueo00.toInt());
     estado_parqueo.par7 = CeroA1(Parqueo00.toInt());
//     switch (steps2){
//      case 0:
//        estado_parqueo.par4 = CeroA1(Parqueo00.toInt());
//        steps2= 1;
//        break;
//  
//      case 1:
//        estado_parqueo.par5 = CeroA1(Parqueo01.toInt());
//        steps2 = 2;
//        break;
//  
//      case 2:
//        estado_parqueo.par6= CeroA1(Parqueo02.toInt());
//        steps2 = 3;
//        break;
//  
//      case 3:
//        estado_parqueo.par7 = CeroA1(Parqueo03.toInt());
//        steps2 = 0;
//        break;
//    }

  }

  if (Serial2.available()){
    String CadenaEntrante = Serial2.readStringUntil(',');
    Serial.println(CadenaEntrante);
    //Serial.println(CadenaEntrante);

    
    String Parqueo0 = CadenaEntrante.substring(0,1);
    String Parqueo1 = CadenaEntrante.substring(1,2);
    String Parqueo2 = CadenaEntrante.substring(2,3);
    String Parqueo3 = CadenaEntrante.substring(3,4);

    estado_parqueo.par0 = CeroA1(Parqueo0.toInt());
    estado_parqueo.par1 = CeroA1(Parqueo0.toInt());
    estado_parqueo.par2 = CeroA1(Parqueo0.toInt());
    estado_parqueo.par3 = CeroA1(Parqueo0.toInt());

//    switch (steps){
//      case 0:
//        estado_parqueo.par0 = CeroA1(Parqueo0.toInt());
//        steps = 1;
//        break;
//  
//      case 1:
//        estado_parqueo.par1 = CeroA1(Parqueo1.toInt());
//        steps = 2;
//        break;
//  
//      case 2:
//        estado_parqueo.par2= CeroA1(Parqueo2.toInt());
//        steps = 3;
//        break;
//  
//      case 3:
//        estado_parqueo.par3 = CeroA1(Parqueo3.toInt());
//        steps = 0;
//        break;
//    }
  }
  counter7 ();
  display7SEG (contador);
  
}

void display7SEG (int digit){
  switch (digit){
    case 0:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
      break;

    case 1:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;

    case 2:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;

    case 3:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;

    case 4:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;

    case 5:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;

    case 6:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;

    case 7:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;

    case 8:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;

    case 9:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
  }
}

void counter7 (){
  contador = estado_parqueo.par0 + estado_parqueo.par1 + estado_parqueo.par2 + 
  estado_parqueo.par4 + estado_parqueo.par5 + estado_parqueo.par6 + estado_parqueo.par7;
}

void handle_OnConnect()
{
  server.send(200, "text/html", SendHTML());
}

String SendHTML()
{
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<html lang=\"en\">\n";
  ptr += "<head>\n";
  ptr += "<script>function autoRefresh(){window.location=window.location.href}setInterval(\"autoRefresh()\",1000);</script>";
  ptr += "<meta charset=\"UTF-8\">\n";
  ptr += "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
  ptr += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
  ptr += "<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.0-beta1/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-0evHe/X+R7YkIZDRvuzKMRqM+OrBnVFBL6DOitfPri4tjfHxaWutUpFmBp4vmVor\" crossorigin=\"anonymous\">\n";
  ptr += "<title>Parqueo Nova 13</title>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<table border=\"0\">\n";
  ptr += "<tr>\n";
  ptr += "<th>\n";
  ptr += "<img src=\"https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Ftse1.mm.bing.net%2Fth%3Fid%3DOIP.bCrarp7bXtFJM64wWQntsgHaFk%26pid%3DApi&f=1\" class=\"img-thumbnail\" alt=\"Nova 13\">\n";
  ptr += "</th>\n";
  ptr += "<th>\n";
  ptr += "<h1 class=\"display-1\">Nova 13</h1>\n";
  ptr += "<figcaption class=\"blockquote-footer\">\n";
  ptr += "El parqueo de tus sueños\n";
  ptr += "</figcaption>\n";
  ptr += "</th>\n";
  ptr += "</tr>\n";
  ptr += "</table>\n";
  ptr += "<table class=\"table table-dark table-striped\">\n";
  ptr += "<thead>\n";
  ptr += "<tr>\n";
  ptr += "<th scope=\"col\">#</th>\n";
  ptr += "<th scope=\"col\">Estado</th>\n";
  ptr += "</tr>\n";
  ptr += "</thead>\n";
  ptr += "<tbody>\n";
  ptr += "<tr>\n";
  ptr += "<th scope=\"row\">1</th>\n";
    if (estado_parqueo.par0){
      ptr += "<td>Ocupado</td>\n";
    }
    else{
      ptr += "<td>Libre</td>\n";
    }
  ptr += "</tr>\n";
  
  ptr += "<tr>\n";
  ptr += "<th scope=\"row\">2</th>\n";
    if (estado_parqueo.par1){
      ptr += "<td>Ocupado</td>\n";
    }
    else{
      ptr += "<td>Libre</td>\n";
    }
  ptr += "</tr>\n";
  
  ptr += "<tr>\n";
  ptr += "<th scope=\"row\">3</th>\n";
    if (estado_parqueo.par2){
      ptr += "<td>Ocupado</td>\n";
    }
    else{
      ptr += "<td>Libre</td>\n";
    }
  ptr += "</tr>\n";

  ptr += "<tr>\n";
  ptr += "<th scope=\"row\">4</th>\n";
    if (estado_parqueo.par3){
      ptr += "<td>Ocupado</td>\n";
    }
    else{
      ptr += "<td>Libre</td>\n";
    }
  ptr += "</tr>\n";

  ptr += "<tr>\n";
  ptr += "<th scope=\"row\">5</th>\n";
    if (estado_parqueo.par4){
      ptr += "<td>Ocupado</td>\n";
    }
    else{
      ptr += "<td>Libre</td>\n";
    }
  ptr += "</tr>\n";

  ptr += "<tr>\n";
  ptr += "<th scope=\"row\">6</th>\n";
    if (estado_parqueo.par5){
      ptr += "<td>Ocupado</td>\n";
    }
    else{
      ptr += "<td>Libre</td>\n";
    }
  ptr += "</tr>\n";

  ptr += "<tr>\n";
  ptr += "<th scope=\"row\">7</th>\n";
    if (estado_parqueo.par6){
      ptr += "<td>Ocupado</td>\n";
    }
    else{
      ptr += "<td>Libre</td>\n";
    }
  ptr += "</tr>\n";

  ptr += "<tr>\n";
  ptr += "<th scope=\"row\">8</th>\n";
    if (estado_parqueo.par7){
      ptr += "<td>Ocupado</td>\n";
    }
    else{
      ptr += "<td>Libre</td>\n";
    }
  ptr += "</tr>\n";
  
  ptr += "</tbody>\n";
  ptr += "</table>\n";
  ptr += "<figcaption class=\"blockquote-footer\">\n";
  ptr += "By: Nico and Psaidon\n";
  ptr += "</figcaption>\n";
  ptr += "<script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.0-beta1/dist/js/bootstrap.bundle.min.js\" integrity=\"sha384-pprn3073KE6tl6bjs2QrFaJGz5/SUsLqktiwsUTF55Jfv3qYSDhgCecCxMW52nD2\" crossorigin=\"anonymous\"></script>\n";
  ptr += "</body>\n";
  ptr += "</html>";
  return ptr;
}
int CeroA1( int val){
  switch(val){
    case 0:
      return 1;
      break;
    case 1:
      return 0;
      break;
  }
}
