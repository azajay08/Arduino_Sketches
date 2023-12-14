#include <Servo.h>

Servo servo;
int pos = 0;

void setup() {
  servo.attach(5);
  servo.write(pos);

  delay(100);
}

void loop() {
  if (pos == 0) {
    while (pos < 180) {
      servo.write(pos);
      pos++;
      delay(10);
    }
  }
  if (pos == 180) {
    while (pos > 0) {
      servo.write(pos);
      pos--;
      delay(10);
    }
  }

  // servo.write(pos);
  // delay(3000);
  // // movement++;

  // servo.write(pos);
  // delay(3000);
}
