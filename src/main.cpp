#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
//Archivos para fragmentar código
#include "settings.hpp"
#include "functions.hpp"
#include "settingsReset.hpp"
#include "settingsRead.hpp"
#include "settingsSave.hpp"
#include "esp32_wifi.hpp"

void setup(){
  Serial.begin(115200);
  setCpuFrequencyMhz(240);
  log("\nInfo: Iniciando Setup");
  //Configuración de pines
  settingPines();

  if (!SPIFFS.begin())
  {
    log(F("Error: Falló la inicialización del SPIFFS"));
    while(true);
  }
  //Lee la configuración WIFI
  settingsReadWifi();
  WiFi.disconnect(true);
  delay(1000);
  //Configuración del WIFI
  wifi_setup();

}
void loop() {
  yield();

  if (wifi_mode == WIFI_STA)
  {
    wifiLoop();
  }
  if (wifi_mode == WIFI_AP)
  {
    wifiAPLoop();
  }
  
}

// put function declarations here:
int myFunction(int, int);

