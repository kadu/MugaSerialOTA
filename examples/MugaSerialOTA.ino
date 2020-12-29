// MugaSerialOTA.ino Funções para Upload local de Sketch
// 07/07/2020 05:07'
//
// Utilizando o código exemplo do canal do YouTube CANAL INTERNET E COISAS
// De 03/2020 - Andre Michelon
// andremichelon@internetecoisas.com.br
// https://internetecoisas.com.br
//
#ifdef ESP8266
  // Bibliotecas para ESP8266
  #include <ESP8266WiFi.h>
  #include <ESP8266mDNS.h>
  #include <FS.h>
#else
  // Bibliotecas para ESP32
  #include <WiFi.h>
  #include <ESPmDNS.h>
#endif

// Bibliotecas comuns
#include "Arduino.h"
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <LittleFS.h>

#include "MugaSerialOTA.h"  // Lib de atualização Serial OTA

const char*   SSID      = "";
const char*   PASSWORD  = "";


void setup() {
  // 
  Serial.begin(115200);  
  //
  WiFi.begin(SSID, PASSWORD);
  //  
  Serial.println("Conectando WiFi " + String(SSID));
  //
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  //
  Serial.println("Ok");
  //
  MugaSerialOTA::OTA("MeuEspSerial");
  //
}

void loop() {
  ArduinoOTA.handle();
}