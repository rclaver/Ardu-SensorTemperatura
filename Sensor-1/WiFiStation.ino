/**
 Crea una pàgina web en el Punt d'Accés
 ESP8266WiFi en node estació
 Recull les dades del sendor AM2302 i les mostra a la pàgina web
*/
#include <ESP8266WiFi.h>

t_sensor dades_sensor;

// Configura la red WiFi
const char* ssid = "SSID";
const char* password = "passwd";

WiFiServer server(80);

String html = "<!DOCTYPE HTML><html>"
  "<head>"
  "<title>Arduino ESP8266 Web Server</title>"
  "<meta http-equiv='refresh' content='2'>"
  "<meta name='viewport' content='width=device-width,initial-scale=1'>"
  "<link rel='icon' href='data:,'>"
  "<style>"
  "html {font-family:Arial;display:inline-block;text-align:center;}"
  "body {margin:0;}"
  "p {font-size:1.1rem;}"
  ".titol {overflow:hidden;background-color:#25C098;color:white;font-size:1rem;}"
  ".content {padding:20px;}"
  ".card {background-color:white;box-shadow:2px 2px 12px 1px rgba(140,140,140,.5);}"
  ".cards {max-width:600px;margin:0 auto;display:grid;grid-gap:2rem;grid-template-rows:repeat(auto-fit,minmax(100px,1fr));}"
  ".dades {font-size:1.2rem;}"
  "</style>"
  "</head>"
  "<body>"
  "<div class='titol'><h1>Arduino ESP8266 Web Server</h1></div>"
  "<div class='content'><div class='cards'>"
  "<div class='card'>"
  "<p>&#127777; TEMPERATURA</p>"
  "<p><span class='dades'><span id='temp'>%TEMPERATURA%</span>&deg;C</span></p>"
  "</div>"
  "<div class='card'>"
  "<p>&#8779; HUMITAT</p>"
  "<p><span class='dades'><span id='humi'>%HUMITAT%</span>&percnt;</span></p>"
  "</div></div></div></body></html>";

void initWiFiStation() {
  delay(3000);
  Serial.print("\nConectant a "); Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectat a la xarxa WiFi");
  Serial.print("Adreça IP del servidor: "); Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Servidor iniciat");
}

void WiFiStation() {
  WiFiClient client = server.accept();
  if (!client) {
    delay(1000);
    dades_sensor = SensorTemperaturaHumitat(1);
    return;
  }

  Serial.println("connectant nou client ...");
  while(!client.available()) {delay(1);}

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  String paginaWeb = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + html;
  paginaWeb.replace("%TEMPERATURA%", String(dades_sensor.temperatura));
  paginaWeb.replace("%HUMITAT%", String(dades_sensor.humitat));

  client.print(paginaWeb);
  delay(1000);
}
