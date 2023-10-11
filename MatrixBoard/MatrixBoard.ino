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
  B01000010,
  B00100100,
  B00011000,
  B00100100,
  B01000010,
  B00000000,
  B00000000
};

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
  int numMoves = 16; // 8 for the image onto the screen, 8 more to go off

  // Loop to move the image down
  for (int move = 0; move < numMoves; move++) {
    int temp = move % 8;
    // Moving image onto the screen
    if (move < 8) {
      for (int j = 0; j < move; j++) {
        lc.setColumn(0, j, pic[7 - temp]);
        temp--;
      }
      delay(100);
    } // Moving image off the screen
    else if (move > 8) {
      int pos = temp;
      for (int j = 7; j > temp; j--) {
        lc.setColumn(0, j, pic[7 - pos]);
        pos++;
      }
      delay(100);
    }
    
    lc.clearDisplay(0); // Clear the display after each shift
  }
  delay(10);
}
