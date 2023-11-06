/*
 *   CÓDIGO:    Q0684
 *   AUTOR:     BrincandoComIdeias
 *   ACOMPANHE: https://www.youtube.com/brincandocomideias ; https://www.instagram.com/canalbrincandocomideias/
 *   APRENDA:   https://cursodearduino.net/ ; https://cursoderobotica.net
 *   COMPRE:    https://www.arducore.com.br/
 *   SKETCH:    Menu TFT Touch
 *   DATA:      21/09/2021
*/

// INCLUSÃO DE BIBLIOTECAS
#include <Adafruit_GFX.h>    
#include <Adafruit_TFTLCD.h> 
#include <TouchScreen.h>

// DEFINIÇÕES DE PINOS
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4


// DEFINIÇÕES
#define WHITE          0xFFFF
#define YELLOW         0xFFE0
#define RED            0xF800
#define BLUE           0x001F
#define BLACK          0x0000
#define CINZA          0x0008

#define LIGADO         0x07E0
#define DESLIGADO      0xF800

#define MINPRESSURE 10
#define MAXPRESSURE 1000


/*____CALIBRAR TFT LCD_____*/
#define YP A3
#define XM A2
#define YM 9
#define XP 8

#define TS_LEFT 110
#define TS_RT   920
#define TS_TOP  70
#define TS_BOT  883
/*______FIM DA CALIBRAÇÃO______*/

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); //300 É A SENSITIVIDADE
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

int X, Y;
long corBot[3] = {DESLIGADO, DESLIGADO, DESLIGADO};

TSPoint waitTouch() {
  TSPoint p;
  do {
    p = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
  } while ((p.z < MINPRESSURE ) || (p.z > MAXPRESSURE));
  
  p.x = map(p.x, TS_LEFT, TS_RT, 0, 240);
  p.y = map(p.y, TS_BOT, TS_TOP, 0, 320);
  
  return p;
}

void setup() {
  Serial.begin(9600);
  
  tft.reset();
  tft.begin(0x9341); // CÓDIGO DO DRIVER DO SEU DISPLAY
  tft.setRotation(1);
  tft.fillScreen(BLACK);

//  IntroScreen();   // DESENHA A TELA DE INTRO
  draw_Buttons(0); // DESENHA TODOS OS BOTOES
}

void loop() {
  TSPoint p = waitTouch();
  X = p.x; Y = p.y;

  //DetectButtons(); // DETECTA OS BOTOES

  delay(300);
}

// IMPLEMENTO DE FUNÇÕES

/*void DetectButtons() {

  if (X < 200 && X > 40) {

    if (Y > 220 && Y < 300) { // LOGICA PARA O BOTAO 1
      Serial.println ("Button 1");
      if (corBot[0] == LIGADO) corBot[0] = DESLIGADO;
      else corBot[0] = LIGADO;
      draw_Buttons(1);
    }


    if (Y > 120 && Y < 200) { // LOGICA PARA O BOTAO 2
      Serial.println ("Button 2");
      if (corBot[1] == LIGADO) corBot[1] = DESLIGADO;
      else corBot[1] = LIGADO;
      draw_Buttons(2);
    }

    if (Y > 20 && Y < 100) { // LOGICA PARA O BOTAO 3
      Serial.println ("Button 3");
      if (corBot[2] == LIGADO) corBot[2] = DESLIGADO;
      else corBot[2] = LIGADO;
      draw_Buttons(3);
    }

  }

}*/

/*void IntroScreen() {
  tft.setCursor (55, 80);
  tft.setTextSize (3);
  tft.setTextColor(WHITE);
  tft.println("MENU");
  tft.setCursor (30, 120);
  tft.println("COM ARDUINO");
  tft.setCursor (30, 180);
  tft.setTextSize (2);
  tft.setTextColor(BLUE);
  tft.println("Brincando");
  tft.setCursor (30, 200);
  tft.setTextColor(WHITE);
  tft.println("    com");
  tft.setCursor (30, 220);
  tft.setTextColor(RED);
  tft.println("       Ideias");
  delay(3500);

  tft.fillScreen(BLACK);
}*/

void draw_Buttons(int type) {
  
  tft.fillScreen(BLACK);
  tft.fillRoundRect(5,5,300,30,0,BLACK);
  tft.fillRoundRect(7,7,300,26,0,BLUE);
  tft.setCursor(18,13);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("Horarios - Saida Bairro");

  //HORARIO 1
  tft.fillRoundRect(7,40,300,35,0,WHITE);
  //tft.fillRoundRect(7,7,223,26,0,BLUE);
  tft.setCursor(260,44);
  tft.setTextColor(BLACK);
  tft.setTextSize(1);
  tft.print("Saida");
  tft.setCursor(250,55);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("6:15");
  tft.setCursor(12,54);
  tft.setTextColor(BLACK);
  tft.setTextSize(1);
  tft.print("BIERRENBACH, JD. DOIS CORAES");

  //HORARIO 2
  tft.fillRoundRect(7,80,300,35,0,WHITE);
  //tft.fillRoundRect(7,7,223,26,0,BLUE);
  tft.setCursor(260,84);
  tft.setTextColor(BLACK);
  tft.setTextSize(1);
  tft.print("Saida");
  tft.setCursor(250,95);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("7:45");
  tft.setCursor(12,94);
  tft.setTextColor(BLACK);
  tft.setTextSize(1);
  tft.print("JD. MORUMBI III E IV");

  //HORARIO 3
  tft.fillRoundRect(7,120,300,35,0,WHITE);
  //tft.fillRoundRect(7,7,223,26,0,BLUE);
  tft.setCursor(260,124);
  tft.setTextColor(BLACK);
  tft.setTextSize(1);
  tft.print("Saida");
  tft.setCursor(250,135);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("9:20");
  tft.setCursor(12,134);
  tft.setTextColor(BLACK);
  tft.setTextSize(1);
  tft.print("JD. MORUMBI III E IV");

  //HORARIO 4
  tft.fillRoundRect(7,160,300,35,0,WHITE);
  //tft.fillRoundRect(7,7,223,26,0,BLUE);
  tft.setCursor(260,164);
  tft.setTextColor(BLACK);
  tft.setTextSize(1);
  tft.print("Saida");
  tft.setCursor(240,175);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("10:50");
  tft.setCursor(12,174);
  tft.setTextColor(BLACK);
  tft.setTextSize(1);
  tft.print("JD. MORUMBI III E IV");

  //HORARIO 4
  tft.fillRoundRect(7,200,300,35,0,WHITE);
  //tft.fillRoundRect(7,7,223,26,0,BLUE);
  tft.setCursor(260,204);
  tft.setTextColor(BLACK);
  tft.setTextSize(1);
  tft.print("Saida");
  tft.setCursor(240,215);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("12:30");
  tft.setCursor(12,214);
  tft.setTextColor(BLACK);
  tft.setTextSize(1);
  tft.print("JD. MORUMBI III E IV");
  
  /*switch (type) {
    case 1:
      
      tft.fillRect  (40, 20 , 160, 80, corBot[0]);

      tft.setTextColor(BLACK);
      tft.setTextSize (1);
      tft.setCursor(50, 50);
      tft.print(" QUARTO");
      break;

    case 2:
      tft.fillRect  (40, 120, 160, 80, corBot[1]);

      tft.setTextColor(BLACK);
      tft.setTextSize (3);
      tft.setCursor(50, 150);
      tft.println("  SALA ");
      break;

    case 3:
      tft.fillRect  (40, 220, 160, 80, corBot[2]);

      tft.setTextColor(BLACK);
      tft.setTextSize (3);
      tft.setCursor(60, 250);
      tft.println("COZINHA");
      break;

    default:
      tft.fillRect  (40, 20 , 160, 80, corBot[0]);
      tft.fillRect  (40, 120, 160, 80, corBot[1]);
      tft.fillRect  (40, 220, 160, 80, corBot[2]);

      tft.setTextColor(BLACK);
      tft.setTextSize (3);

      tft.setCursor(50, 50);
      tft.println(" QUARTO");

      tft.setCursor(50, 150);
      tft.println("  SALA ");

      tft.setCursor(60, 250);
      tft.println("COZINHA");
  }*/

}
