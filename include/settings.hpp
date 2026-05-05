//Definiciones
//Pines para salida en ESP32
#define RELAY1 27
#define RELAY2 26
#define WIFILED 12  //LED indicador
#define MQTTLED 13  //LED indicador

//Versión del HARDWARE
#define HW "CIVICBOT V1"

//ZONA WIFI

boolean wifi_staticIP;          // Uso de IP Estática
char    wifi_ssid[30];          // Red WiFi
char    wifi_passw[30];         // Contraseña de Red WiFi
char    wifi_ip_static[15];     // IP Estático
char    wifi_gateway[15];       // Gateway
char    wifi_subnet[15];        // Subred
char    wifi_primaryDNS[15];    // DNS primario
char    wifi_secondaryDNS[15];  // DNS secundario

// Zona Configuración General
char    id[30];                 // ID del dispositivo
int     bootCount;              // Número de reinicios

//Zona de AP
boolean ap_accessPoint;        // Uso de Modo AP
char    ap_nameap[31];         // SSID AP
char    ap_passwordap[63];     // Password AP
int     ap_canalap;            // Canal AP
int     ap_hiddenap;           // Es visible o no el AP (0 - Visible 1 - Oculto)
int     ap_connetap;           // Número de conexiones en el AP

uint8_t ip[4];