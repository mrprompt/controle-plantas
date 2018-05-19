void temperatura()
{
  if (millis() - ultimaLeituraTemperatura < INTERVALO_LEITURA_TEMPERATURA) {
    return;
  }

  float data[2];
  
  fazLeituraTemperatura(data);

  ultimaLeituraTemperatura = millis();

  metricas[6] = data[0];
  metricas[7] = data[1];
}

void fazLeituraTemperatura(float *data)
{  
  float UmidadeInterna;
  float TemperaturaInterna;
    
  UmidadeInterna = dht_internal.readHumidity();
  TemperaturaInterna = dht_internal.readTemperature();

  if (isnan(UmidadeInterna) || isnan(TemperaturaInterna)) {
    UmidadeInterna = 0;
    TemperaturaInterna = 0;
  }

  Serial.print("- Temperatura: ");
  Serial.print(TemperaturaInterna);
  Serial.println("ºC");
  
  Serial.print("- Umidade: ");
  Serial.print(UmidadeInterna);
  Serial.println("%");

  data[0] = TemperaturaInterna;
  data[1] = UmidadeInterna;
}


