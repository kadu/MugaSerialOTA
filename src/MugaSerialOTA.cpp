// MugaSerialOTA.cpp Funções para Upload local de Sketch
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
//
// Bibliotecas comuns
#include "Arduino.h"
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <LittleFS.h>
//
namespace MugaSerialOTA{

void OTA(String NomeDoDevice)
{
  LittleFS.begin();
  // Define funções de callback do processo
  // Início
  ArduinoOTA.onStart([](){
    String s;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      // Atualizar sketch
      s = "Sketch";
    } else { // U_SPIFFS
      // Atualizar SPIFFS
      s = "SPIFFS";
      // SPIFFS deve ser finalizada
      LittleFS.end();
    }
    Serial.println("Iniciando OTA - " + s);
  });
  // Fim
  ArduinoOTA.onEnd([](){
    Serial.println("\nOTA Concluído.");
  });
  // Progresso
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.print(progress * 100 / total);
    Serial.print(" ");
  });
  // Falha
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.print("Erro " + String(error) + " ");
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Falha de autorização");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Falha de inicialização");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Falha de conexão");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Falha de recebimento");
    } else if (error == OTA_END_ERROR) {
      Serial.println("Falha de finalização");
    } else {
      Serial.println("Falha desconhecida");
    }
  });
  // Inicializa OTA
  ArduinoOTA.setHostname(NomeDoDevice.c_str());
  ArduinoOTA.begin();
  //
  return; 
}


} // end do namespace


