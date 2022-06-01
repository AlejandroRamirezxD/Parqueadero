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


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);

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
  Serial.print (WiFi.localIP());
  delay(100);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  server.handleClient();
}

void handle_OnConnect()
{
  server.send(200, "text/html", SendHTML());
}

String SendHTML ()
{
  String ptr = "<html lang=\"en\">\n";
  ptr += "<head>\n";
  ptr += "<meta charset=\"UTF-8\">\n";
  ptr += "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
  ptr += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
  ptr += "<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.0-beta1/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-0evHe/X+R7YkIZDRvuzKMRqM+OrBnVFBL6DOitfPri4tjfHxaWutUpFmBp4vmVor\" crossorigin=\"anonymous\">\n";
  ptr += "<title>Parqueo Nova 13</title>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>Parque Nova 13</h1>\n";
  ptr += "<table class=\"table\">\n";
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
  else {
    ptr += "<td>Libre</td>\n";
  }
  ptr += "</tr>\n";
  ptr += "<tr>\n";
  ptr += "<th scope=\"row\">2</th>\n";
  ptr += "<td>Ocupado</td>\n";
  ptr += "</tr>\n";
  ptr += "<tr>\n";
  ptr += "<th scope=\"row\">3</th>\n";
  ptr += "<td>Ocupado</td>\n";
  ptr += "</tr>\n";
  ptr += "<tr>\n";
  ptr += "<th scope=\"row\">4</th>\n";
  ptr += "<td>Ocupado</td>\n";
  ptr += "</tr>\n";
  ptr += "<tr>\n";
  ptr += "<th scope=\"row\">5</th>\n";
  ptr += "<td>Ocupado</td>\n";
  ptr += "</tr>\n";
  ptr += "<tr>\n";
  ptr += "<th scope=\"row\">6</th>\n";
  ptr += "<td>Ocupado</td>\n";
  ptr += "</tr>\n";
  ptr += "<tr>\n";
  ptr += "<th scope=\"row\">7</th>\n";
  ptr += "<td>Ocupado</td>\n";
  ptr += "</tr>\n";
  ptr += "<tr>\n";
  ptr += "<th scope=\"row\">8</th>\n";
  ptr += "<td>Ocupado</td>\n";
  ptr += "</tr>\n";
  ptr += "</tbody>\n";
  ptr += "</table>\n";
  ptr += "<script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.0-beta1/dist/js/bootstrap.bundle.min.js\" integrity=\"sha384-pprn3073KE6tl6bjs2QrFaJGz5/SUsLqktiwsUTF55Jfv3qYSDhgCecCxMW52nD2\" crossorigin=\"anonymous\"></script>\n";
  ptr += "</body>\n";
  ptr += "</html>";

  return ptr;
}
