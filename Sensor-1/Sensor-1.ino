/*
  Sensor-1:
  - Crea una pàgina web en el servidor d'un Punt d'Accés
  - ESP8266WiFi en node estació
  - Recull les dades del sendor AM2302 i les mostra a la pàgina web

  inclou:
  - WiFiStation.ino
  - SensorTemperaturaHumitat.ino
*/

#include "sensor.h"

void setup() {
  Serial.begin(115200);
  initWiFiStation();
  initSensorTemperaturaHumitat();
}

void loop() {
  WiFiStation();
}
