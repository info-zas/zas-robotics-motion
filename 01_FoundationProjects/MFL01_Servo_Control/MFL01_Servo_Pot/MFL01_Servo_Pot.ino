#include <Servo.h>

Servo myServo;        // create servo object
int potPin = A0;      // potentiometer connected to A0
int potValue;         // variable to read potentiometer
int angle;            // servo angle

void setup() {
  myServo.attach(11); // servo signal pin
}

void loop() {
  potValue = analogRead(potPin);        // read potentiometer (0 to 1023)
  angle = map(potValue, 0, 1023, 0, 180); // map to servo angle (0 to 180)

  myServo.write(angle);  // move servo
  delay(15);             // small delay for smooth movement
}

