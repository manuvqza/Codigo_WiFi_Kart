#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

WiFiServer server(80);
WiFiClient cliente;

const char *ssid="servidor_ESP32GPG";
const char *pass="claveGPG"; //minimo 8 caracteres

IPAddress ip(192, 168, 1, 200); //Definiendo una IP estática para el Servidor
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP); //Modo Access Point
  WiFi.softAP(ssid, pass);
  WiFi.softAPConfig(ip, gateway, subnet);

  Serial.print("Inciando Access Point como: ");
  Serial.println(ssid);
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
  Serial.println("Servidor iniciado");

}

void loop() {
  cliente = server.available();
  if(cliente){
    delay(100);
    while(cliente.available()){
      Serial.write(cliente.read());
      Serial.println("...");
    }
    Serial.println();
  }
}