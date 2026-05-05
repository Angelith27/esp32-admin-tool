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
#include "esp32_mqtt.hpp"

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
  settingsReadRelays();

  setOnOffSingle(RELAY1,Relay01_status);
  setOnOffSingle(RELAY2,Relay02_status);

  //Lee la configuración WIFI
  settingsReadWifi();
  WiFi.disconnect(true);
  delay(1000);
  //Configuración del WIFI
  wifi_setup();
  // Lee la Configuración MQTT
  settingsReadMQTT();
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
  //MQTT
  if ((WiFi.status() == WL_CONNECTED) && (wifi_mode == WIFI_STA)){
    if(mqtt_server != 0)
    {
      mqttLoop();
      if (mqttclient.connected())
      {
        if (millis() - lastMsg > mqtt_time)
        {
          lastMsg = millis();
          mqtt_publish();
        }
      }      
    }
  }
}

