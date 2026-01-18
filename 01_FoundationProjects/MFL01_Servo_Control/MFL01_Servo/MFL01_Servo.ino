#include <Servo.h>

Servo myServo;   // create servo object

void setup() {
  myServo.attach(11);   // connect servo to pin 11
}

void loop() {

  // Move from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle += 10) {
    myServo.write(angle);
    delay(500);   // wait 0.5 second
  }

  // Move from 180 back to 0 degrees
  for (int angle = 180; angle >= 0; angle -= 10) {
    myServo.write(angle);
    delay(500);   // wait 0.5 second
  }
}
