#include "LedControl.h"

LedControl lc = LedControl(12, 11, 10, 1);
byte heart[8] = {
  B00000000,
  B01100110,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000,
  B00000000
};

byte x[8] = {
  B00000000,
  B00000000,
  B01000100,
  B00101000,
  B00010000,
  B00101000,
  B01000100,
  B00000000
};

// byte b[8] = {
//   B00000000,
//   B01111100,
//   B01000010,
//   B01111100,
//   B01000010,
//   B01111100,
//   B00000000,
//   B00000000
// };

void setup() {
  /*
    The MAX72XX is in power-saving mode on startup,
    we have to do a wakeup call
  */
  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 5);
  /* and clear the display */
  lc.clearDisplay(0);
}

void loop() {
  displayDot();
  displayCol();
  displayRow();
  displayPic(heart);
  displayPic(x);
  // displayPic(b);
}

void displayDot() {
  lc.clearDisplay(0);
  delay(100);
  for (int row = 0; row < 8; row++)
  {
    for (int col = 0; col < 8; col++)
    {
      lc.setLed(0, row, col, true);
      delay(50);
    }
  }
}

void displayCol() {
  lc.clearDisplay(0);
  delay(100);
  byte data = B01100110;
  for (int col = 0; col < 8; col++) {
    lc.setColumn(0, col, data);
    delay(100);
  }
}

void displayRow() {
  lc.clearDisplay(0);
  delay(100);
  byte data = B10011001;
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, data);
    delay(100);
  }
}

void displayPic(byte pic[8]) {
  lc.clearDisplay(0);
  delay(100);

  // Number of times to move the image down
 int numMoves = 8; // 8 for the image onto the screen, 8 more to go off

  // Loop to move the image down
  // Moving image onto the screen
  for (int moveOn = 0; moveOn < numMoves; moveOn++) {
    int tempOn = moveOn;
    // if (move < 8) {
    for (int j = 0; j < moveOn; j++) {
      lc.setColumn(0, j, pic[7 - tempOn]);
      tempOn--;
    }
    delay(100);
    lc.clearDisplay(0);
  } 
  // Moving image off the screen
  for (int moveOff = 1; moveOff < numMoves; moveOff++) {
    int tempOff = moveOff;
    for (int j = 7; j > moveOff; j--) {
      lc.setColumn(0, j, pic[7 - tempOff]);
      tempOff++;
    }
    delay(100);
    lc.clearDisplay(0);
  }
  delay(10);
}


