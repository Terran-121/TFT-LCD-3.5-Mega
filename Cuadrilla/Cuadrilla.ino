//*------Terran 121------*//
/*
 Creando una cuadrilla para tener referncia ala hora de dibujar
 controles,tablas, importar dibujos etc 
 facebook youtube: bytedataperu   
 */

#include <UTFT.h>

UTFT myGLCD(ILI9486, 38, 39, 40, 41);
extern uint8_t SmallFont[];
int Xsize;
int Ysize;

int XTsize;
int YTsize;

void setup() {
  Serial.begin(9600);
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.fillScr(VGA_BLACK);//Fondo
  myGLCD.setColor(VGA_WHITE);//Texto y Numero
  myGLCD.setBackColor(VGA_BLACK);//Fondo Texto

  Xsize = myGLCD.getDisplayXSize();
  Ysize = myGLCD.getDisplayYSize();
  Serial.println(Xsize);
  Serial.println(Ysize);
  XTsize = myGLCD.getFontXsize ();
  YTsize = myGLCD.getFontYsize ();

  for (int i = 20; i < Ysize ; i = i + 10) {
    myGLCD.setColor(VGA_GRAY);//Texto y Numero
    if (i % 20 == 0)// 
      myGLCD.setColor(VGA_WHITE);//Texto y Numero
    myGLCD.printNumI(i, 0, i - YTsize / 2);
    myGLCD.drawLine(20, i, Xsize - 10, i);
  }
  for (int i = 20; i < Xsize ; i = i + 10) {
    myGLCD.setColor(VGA_GRAY);//Texto y Numero
    if (i % 20 == 0)
      myGLCD.setColor(VGA_WHITE);//Texto y Numero
    myGLCD.print(String(i), i - YTsize / 2, 20, -90);//Giro texto -90º
    myGLCD.drawLine(i, 20, i, Ysize - 10);
  }

}

void loop() {
  // Ahora Si Tenemos Referencia para Dibujar
}
