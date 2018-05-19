void enviaDados()
{
  char Fields[100];

  //verifica se está conectado no WiFi e se é o momento de enviar dados ao ThingSpeak
  if (!client.connected() && (millis() - ultimaConexaoGravacao > INTERVALO_ENVIO_THINGSPEAK))
  {    
    sprintf(
      Fields, 
      "field1=%d&field2=%d&field3=%d&field4=%d&field5=%d&field6=%d&field7=%d&field8=%d", 
      (int) metricas[0],
      (int) metricas[1],
      (int) metricas[2],
      (int) metricas[3],
      (int) metricas[4],
      (int) metricas[5],
      (int) metricas[6],
      (int) metricas[7]
    );

    Serial.print("- Enviando dados: ");
    Serial.println(Fields);

    post(Fields);
  }
}

void post(String StringDados)
{
  if (client.connect(EnderecoAPIThingSpeak, 80))
  {
    //faz a requisição HTTP ao ThingSpeak
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: " + EnderecoAPIThingSpeak + "\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + THINGSPEAK_WRITE + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(StringDados.length());
    client.print("\n\n");
    client.print(StringDados);

    ultimaConexaoGravacao = millis();
  }

  client.stop();
}

