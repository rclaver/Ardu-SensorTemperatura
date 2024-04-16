/*
  Control del sensor de temperatura i humitat AM2302
*/

#include <AM2302-Sensor.h>

// Defineix el pin al que està connectat el sensor AM2302
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_SAM_DUE)
#define DHT22_PIN  2
#elif defined(ESP8266) || defined(ESP32)
#define DHT22_PIN  4 // GPIO4 (etiquetat com a D2 en algunes plaques ESP8266)
#else
#error "Pot funcionar, però no està verificat en aquesta placa"
#endif

AM2302::AM2302_Sensor am2302{DHT22_PIN};

void initSensorTemperaturaHumitat() {
  delay(1000);
  Serial.println(F("\nIniciant el sensor de temperatura i humitat AM2302"));
  // check for sensor
  if (!am2302.begin()) {
    while (true) {
      Serial.println("Error => Verifica la connexió del sensor.");
      delay(10000);
    }
  }
}

t_sensor SensorTemperaturaHumitat(int terminal) {
  t_sensor dades_sensor;
  if (terminal==1) {Serial.print("\nfunction SensorTemperaturaHumitat()");}
  auto status = am2302.read();
  if (status == 0) {
    dades_sensor.temperatura = am2302.get_Temperature();
    if (terminal==1) {Serial.printf("\nTemperatura: %.2fºC", dades_sensor.temperatura);}
    delay(2000);
    dades_sensor.humitat = am2302.get_Humidity();
    if (terminal==1) {Serial.printf("\nHumitat:     %.2f%%", dades_sensor.humitat);}
  }else{
    if (terminal==1) {Serial.printf("\nestat de la lectura del sensor: %d", status);}
  }
  if (terminal==1) Serial.println();
  return dades_sensor;
}
