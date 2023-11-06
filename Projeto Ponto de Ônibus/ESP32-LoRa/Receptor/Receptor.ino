#include "heltec.h"
#include <ArduinoJson.h>
#include "EspMQTTClient.h"
#include <Wire.h>

EspMQTTClient client(
  "Alemão", //nome da rede wi-fi
  "lucas124", //senha da rede wi-fi
  "mqtt.tago.io",  // MQTT Broker server ip
  "Default",   //username
  "30c7c8ca-c6a6-42ad-b631-eccf6c139071",   //Código Token
  "TestClient",      //Client name that uniquely identify your device
  1883
);

#define BAND    915E6  //Escolha a frequência

String packSize = "--";
String packet ;

char temP[100];

/* Protótipo da função */
void LoRaDataPrint();
void cbk(int packetSize);

/*
  Nome da função: LoRaDataPrint
  objetivo: imprime a temperatura e tamanho do pacote recebido no display.
*/
void LoRaDataPrint(){
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  //Heltec.display->setFont(ArialMT_Plain_10);
  //Heltec.display->drawString(0 , 1 , "Recebendo "+ packSize + " bytes");
  Heltec.display->setFont(ArialMT_Plain_16);
  //Heltec.display->drawString(0, 16, "Temperatura:");
  Heltec.display->drawString(0, 1, packet);
  //Heltec.display->drawString(78, 38, "°C");
  Heltec.display->display();
}

/*
  Nome da função: cbk
  recebe como parâmetos um inteiros (packetSize)
  objetivo: recebe a temperatura via LoRa e armazena na variável packet.
*/
void cbk(int packetSize) {
  packet ="";
  packSize = String(packetSize,DEC);
  for (int i = 0; i < packetSize; i++) {
    packet += (char) LoRa.read(); //Atribui um caractere por vez a váriavel packet 
  }
  Serial.println(packet);

  LoRaDataPrint();
}

/******************* função principal (setup) *********************/
void setup()
{
  pinMode(LED,OUTPUT); //inicializa o LED
  
  Serial.begin(115200);
  Heltec.begin(true /*Habilita o Display*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Habilita debug Serial*/, true /*Habilita o PABOOST*/, BAND /*Frequência BAND*/);
 
  //Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  //Heltec.display->setFont(ArialMT_Plain_10);
  //Heltec.display->clear();
  //Heltec.display->drawString(10, 5, "Iniciado com Sucesso!");
  //Heltec.display->drawString(10, 30, "Aguardando os dados...");
  //Heltec.display->display();
  //Serial.println("Iniciado com Sucesso!");
  //Serial.println("Aguardando os dados...");
  //delay(1000);
  
  LoRa.receive(); // Habilita o rádio LoRa para receber dados
}

//This function is called once everthing is connected (WI-FI and MQTT)
//WARRING: YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{}


/******************* função em loop (loop) *********************/
void loop()
{

  int packetSize = LoRa.parsePacket();
  if (packetSize) { //Verifica se há dados chegando via LoRa
    cbk(packetSize);
    digitalWrite(LED, HIGH);   // Liga o LED
    delay(500);                // Espera 500 milissegundos
    digitalWrite(LED, LOW);    // Desliiga o LED
    delay(500);                // Espera 500 milissegundos
    //Serial.print("Recebendo a temperatura: ");
    Serial.println(packet); //Imprime no monitor serial a temperatura
    //Serial.println("°C");
  }
  delay(10);

  //arquivo JSON
  StaticJsonDocument<300> temp;

  temp["variable"] = "TEMP";
  temp["value"] = packet;

  serializeJson(temp,temP);

  //envio de dados
  client.publish("info/temP", temP);
  delay(100);

  client.loop();

}