#include <UTFT.h>
#include <URTouch.h>

UTFT myGLCD(ILI9481, 38, 39, 40, 41);
URTouch myTouch( 6, 5, 4, 3, 2);
//UTFT  myGLCD(ILI9481, 50, 51, 52, 53);
extern uint8_t BigFont[];

int x, y;
char stCurrent[10] = "";
int stCurrentLen = 0;
char staux[10] = "";
int stauxLen = 0;
char password[10] = "0000";
char stLast[20] = "";

/*************************
**   Custom functions   **
*************************/

void drawButtons()
{
  myGLCD.clrScr();
  // Draw the upper row of buttons
  for (x = 0; x < 5; x++)
  {
    myGLCD.setColor(0, 0, 255);
    myGLCD.fillRoundRect (15 + (x * 93), 15, 93 + (x * 93), 93);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (15 + (x * 93), 15, 93 + (x * 93), 93);
    myGLCD.printNumI(x + 1, 47 + (x * 93), 47);
   
  }
  // Draw the center row of buttons
  for (x = 0; x < 5; x++)
  {
    myGLCD.setColor(0, 0, 255);
    myGLCD.fillRoundRect (15 + (x * 93), 108, 93 + (x * 93), 186);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (15 + (x * 93), 108, 93 + (x * 93), 186);
    if (x < 4)
      myGLCD.printNumI(x + 6, 47 + (x * 93), 142);
  }
  myGLCD.print("0", 419, 142);

  // Draw the lower row of buttons
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (15, 201, 155, 260);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (15, 201, 155, 260);
  myGLCD.print("Clear", 45, 222);
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (325, 201, 465, 260);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (325, 201, 465, 260);
  myGLCD.print("Enter", 355, 222);
  myGLCD.setBackColor (0, 0, 0);
}

void updateStr(int val)
{
  if (stCurrentLen < 10)
  {
    stCurrent[stCurrentLen] = val;
    stCurrent[stCurrentLen + 1] = '\0';
    stCurrentLen++;
    staux[stauxLen] = '*';
    staux[stauxLen + 1] = '\0';
    stauxLen++;
    myGLCD.setColor(0, 255, 0);
    myGLCD.print(staux, CENTER, 275);
  }
}


void abierto()
{
  myGLCD.clrScr();
  myGLCD.fillScr(VGA_WHITE);
  myGLCD.setBackColor(VGA_WHITE);
  myGLCD.setColor(VGA_GREEN);
  myGLCD.print("PUERTA ABIERTA", CENTER, 160);
  delay (5000);
}


// Draw a red frame while a button is touched
void waitForIt(int x1, int y1, int x2, int y2)
{
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
    myTouch.read();
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
}

/*************************
**  Required functions  **
*************************/

void setup()
{
  // Initial setup
  myGLCD.InitLCD();
  myGLCD.clrScr();

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);

  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 0, 255);
  drawButtons();
}

void loop()
{
  while (true)
  {
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();

      if ((y >= 15) && (y <= 93)) // Upper row
      {
        if ((x >= 15) && (x <= 93)) // Button: 1
        {
          waitForIt(15, 15, 93, 93);
          updateStr('1');
        }
        if ((x >= 108) && (x <= 186)) // Button: 2
        {
          waitForIt(108, 15, 186, 93);
          updateStr('2');
        }
        if ((x >= 201) && (x <= 279)) // Button: 3
        {
          waitForIt(201, 15, 279, 93);
          updateStr('3');
        }
        if ((x >= 294) && (x <= 372)) // Button: 4
        {
          waitForIt(294, 15, 372, 93);
          updateStr('4');
        }
        if ((x >= 387) && (x <= 465)) // Button: 5
        {
          waitForIt(387, 15, 465, 93);
          updateStr('5');
        }
      }

      if ((y >= 108) && (y <= 186)) // Center row
      {
        if ((x >= 15) && (x <= 93)) // Button: 6
        {
          waitForIt(15, 108, 93, 186);
          updateStr('6');
        }
        if ((x >= 108) && (x <= 186)) // Button: 7
        {
          waitForIt(108, 108, 186, 186);
          updateStr('7');
        }
        if ((x >= 201) && (x <= 279)) // Button: 8
        {
          waitForIt(201, 108, 279, 186);
          updateStr('8');
        }
        if ((x >= 294) && (x <= 372)) // Button: 9
        {
          waitForIt(294, 108, 372, 186);
          updateStr('9');
        }
        if ((x >= 387) && (x <= 465)) // Button: 0
        {
          waitForIt(387, 108, 465, 186);
          updateStr('0');
        }
      }



      if ((y >= 201) && (y <= 260)) // Last row
      {
        if ((x >= 15) && (x <= 155)) // Button: Clear
        {
          waitForIt(15, 201, 155, 260);
          myGLCD.setBackColor(0, 0, 0);
          myGLCD.setColor(0, 0, 0);
          myGLCD.print(staux, CENTER, 275);
          stCurrent[0] = '\0';
          stCurrentLen = 0;
          staux[0] = '\0';
          stauxLen = 0;
        }
        if ((x >= 325) && (x <= 465)) // Button: Enter
        {
          waitForIt(325, 201, 465, 260);
          if (strcmp(stCurrent, password) == 0)
          {
            myGLCD.setColor(0, 0, 255);
            myGLCD.print("Correcto", CENTER, 300);
            stCurrent[0] = '\0';
            stCurrentLen = 0;
            staux[0] = '\0';
            stauxLen = 0;
            abierto();
            myGLCD.setBackColor(0, 0, 255);
            myGLCD.setColor(255, 255, 255);
            drawButtons();
          }
          else
          {
            myGLCD.setColor(255, 0 , 0);
            myGLCD.print("Incorrecto", CENTER, 300);
            delay (1000);
            myGLCD.setBackColor(0, 0, 0);
            myGLCD.setColor(0, 0, 0);
            myGLCD.print(stCurrent, CENTER, 275);
            myGLCD.print("Incorrecto", CENTER, 300);
            stCurrent[0] = '\0';
            stCurrentLen = 0;
            staux[0] = '\0';
            stauxLen = 0;
          }
        }
      }
    }
  }
}
