#include "_config.h"
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>

#define INTERVALO_ENVIO_THINGSPEAK 60000 // intervalo entre envios de dados ao ThingSpeak (em ms)
#define INTERVALO_LEITURA_SOLO 10000 // intervalo entre leitura de dados do sensor de solo (em ms)
#define INTERVALO_LEITURA_TEMPERATURA 20000 // intervalo entre leitura de dados do sensor de solo (em ms)
#define INTERVALO_RESTART 3600000 // reboot a cada 1h (em ms)
#define TEMP_SENSOR_PIN D0 // porta do sensor de temperatura
#define TEMP_SENSOR_TYPE DHT11 // tipo do sensor de temperatura

const String EnderecoAPIThingSpeak = "api.thingspeak.com"; // endereço do thingspeak
const uint8_t SOIL_SENSOR_PINS[] = { D1, D2, D4, D5, D6, D7 }; // portas dos sensores de umidade

long ultimaLeituraSolo = 0;
long ultimaLeituraTemperatura = 0;
long ultimaConexaoGravacao = 0;
long ultimaConexaoLeitura = 0;
float metricas[10];

WiFiClient client;
DHT dht_internal(TEMP_SENSOR_PIN, TEMP_SENSOR_TYPE);

void setup() 
{
  Serial.begin(9600);
  Serial.println();

  for (uint8_t i = 0; i < sizeof(SOIL_SENSOR_PINS); i++)
  {
    pinMode(SOIL_SENSOR_PINS[i], INPUT);
  }

  connectWifi();
  dht_internal.begin();
}

void loop() {
  ArduinoOTA.handle();

  solo();
  temperatura();
  enviaDados();

  // necessário senão o OTA pira
  delay(1000);

  // restartando a cada 1h ou quando o link cai
  if (client.status() == WL_DISCONNECTED || millis() >= INTERVALO_RESTART) 
  {
    ESP.restart();
  }
}
