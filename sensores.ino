void solo()
{
  if (millis() - ultimaLeituraSolo < INTERVALO_LEITURA_SOLO)
  {
    return;
  }
      
  for (uint8_t i = 0; i < sizeof(SOIL_SENSOR_PINS); i++)
  {
    float ultimoValorSolo = FazLeituraUmidade(SOIL_SENSOR_PINS[i]);

    Serial.print("- Sensor #");
    Serial.print(i + 1);
    Serial.print(" - ");
    Serial.print(ultimoValorSolo);
    Serial.println("%");

    metricas[i] = ultimoValorSolo;
  }
  
  ultimaLeituraSolo = millis();
}

//Função: faz a leitura do nível de umidade
//Parâmetros: nenhum
//Retorno: umidade percentual (0-100)
//Observação: o ADC do NodeMCU permite até, no máximo, 3.3V. Dessa forma,
//            para 3.3V, obtem-se (empiricamente) 978 como leitura de ADC
// @from https://www.filipeflop.com/blog/planta-iot-com-esp8266-nodemcu/
float FazLeituraUmidade(int pino)
{
    int ValorADC;
    float UmidadePercentual;
 
     ValorADC = analogRead(pino);   //978 -> 3,3V
     
     //Serial.print("- Leitura ADC: ");
     //Serial.println(ValorADC);
 
     //Quanto maior o numero lido do ADC, menor a umidade.
     //Sendo assim, calcula-se a porcentagem de umidade por:
     //      
     //   Valor lido                 Umidade percentual
     //      _    0                           _ 100
     //      |                                |   
     //      |                                |   
     //      -   ValorADC                     - UmidadePercentual 
     //      |                                |   
     //      |                                |   
     //     _|_  978                         _|_ 0
     //
     //   (UmidadePercentual-0) / (100-0)  =  (ValorADC - 978) / (-978)
     //      Logo:
     //      UmidadePercentual = 100 * ((978-ValorADC) / 978)  
     UmidadePercentual = 100 * ((978-(float)ValorADC) / 978);
 
     return UmidadePercentual;
}
