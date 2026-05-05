#include "LedBlink.hpp"

//Sensar temperatura CPU
#ifdef __cplusplus
extern "C"
{
#endif
    uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

//Muestra una salida serial
void log(String s){
    Serial.println(s);
}

String platform(){
#ifdef ARDUINO_ESP32_DEV
    return "ESP32";
#endif
}

IPAddress CharToIP(const char *str){
    int ip[4];
    sscanf(str, "%hhu.%hhu.%hhu.%hhu", &ip[0], &ip[1], &ip[2], &ip[3]);
    return IPAddress(ip[0], ip[1], ip[2], ip[3]);
}

String ipStr(const IPAddress &ip){
    String sFn = "";
    for (byte bFn = 0; bFn < 3; bFn++)
    {
        sFn += String((ip >> (8 * bFn)) & 0xFF) + ".";
    }
    sFn += String((ip >> 8 * 3) & 0xFF);
    return sFn;
}

String hexStr(const unsigned long &h, const byte &l = 8){
    String s;
    s = String(h, HEX);
    s.toUpperCase();
    s = ("00000000" + s).substring(s.length() + 8 - l);
    return s;
}

String idUnique(){
    // Retorna los últimos 4 Bytes del MAC rotados
    char idunique[15];
    uint64_t chipid = ESP.getEfuseMac();
    uint16_t chip = (uint16_t)(chipid >> 32);
    snprintf(idunique, 15, "%04X", chip);
    return idunique;
}

String deviceID(){
    return String(platform()) + hexStr(ESP.getEfuseMac()) + String(idUnique());
}
void settingPines(){
    pinMode(WIFILED, OUTPUT);
    pinMode(MQTTLED, OUTPUT);
    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);
    digitalWrite(RELAY1, LOW);
    digitalWrite(RELAY2, LOW);
    digitalWrite(MQTTLED, LOW);
    digitalWrite(WIFILED, LOW);

}
//LED MQTT Transmisión
void mqttTX(){ 
    for (int i = 0; i < 2; i++){
        setOnSingle(MQTTLED);
        delay(50);
        setOffSingle(MQTTLED);
        delay(10);
    }  
}
//LED MQTT Recepción
void mqttRX(){
    for (int i = 0; i < 1; i++){
        blinkRandomSingle(5,50,MQTTLED);
        delay(5);
    }
}

int getRSSIasQuality(int RSSI){
    int quality = 0;
    if(RSSI <= -100){
        quality = 0;
    } else if(RSSI >= -50){
        quality = 100;
    } else{
       quality = 2 * (RSSI + 100); 
    }
    return quality;
}

float TempCPUValue (){
    return temp_cpu = (temprature_sens_read() - 32) / 1.8;
}