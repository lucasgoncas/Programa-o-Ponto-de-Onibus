
/*
 *   Q0467
 *   AUTOR:   BrincandoComIdeias
 *   LINK:    https://www.youtube.com/brincandocomideias ; https://cursodearduino.net/
 *   COMPRE:  https://www.arducore.com.br/
 *   SKETCH:  DfPlayer Mini
 *   DATA:    13/05/2019
*/

// INCLUSÃO DE BIBLIOTECAS
//#include "heltec.h"
//#include <SoftwareSerial.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Wire.h>

// DEFINIÇÕES DE PINOS
#define pinRx 10
#define pinTx 11

// DEFINIÇÕES
#define volumeMP3 30

#define DEBUG
// INSTANCIANDO OBJETOS
SoftwareSerial playerMP3Serial(pinRx, pinTx);

DFRobotDFPlayerMini playerMP3;

// DECLARAÇÃO DE FUNÇÕES
  

// DECLARAÇÃO DE VARIÁVEIS	


void setup() {
	Serial.begin(9600);
	playerMP3Serial.begin(9600);

  Serial.println();
  Serial.println(F("Iniciando DFPlayer ... (Espere 3~5 segundos)"));

  if (!playerMP3.begin(playerMP3Serial)) {  // COMUNICAÇÃO REALIZADA VIA SOFTWARE SERIAL
    Serial.println(F("Falha ao iniciar:"));
    Serial.println(F("1.Confira as conexões!"));
    Serial.println(F("2.Confira o cartão SD!"));
    while(true){
      delay(0);
    }
  }

  Serial.println(F("DFPlayer ligado!"));

  playerMP3.volume(volumeMP3);
  
  playerMP3.playFolder(1, 3);

	#ifdef DEBUG
		Serial.println("Fim Setup");
	#endif	
  
  
}

void loop() {
  
  //if( bot1.pressed() ){
    /*playerMP3.playFolder(1, 1);
    Serial.println("Tocando pasta 01, musica 001");
    delay(1000);*/
  //}
  /*if( bot2.pressed() ){
    playerMP3.playFolder(1, 2);
    Serial.println("Tocando pasta 01, musica 002");
    delay(1000);
  }
  if( bot3.pressed() ){
    playerMP3.playFolder(1, 3);
    Serial.println("Tocando pasta 01, musica 003");
    delay(1000);
  }
  if( digitalRead(pinLDR) == HIGH ){
    playerMP3.playFolder(2, 1);
    Serial.println("Tocando pasta 02, musica 001");
    delay(1000);
  }
  if( digitalRead(pinSensor) == LOW){
    playerMP3.playFolder(2, 1);
    Serial.println("Tocando pasta 02, musica 001");
    delay(1000);
  }
  if( bot4.pressed() ){
    playerMP3.playFolder(2, 2);
    Serial.println("Tocando pasta 02, musica 002");
    delay(1000);
  }*/
  
}

// IMPLEMENTO DE FUNÇÕES
