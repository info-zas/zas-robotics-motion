#include <Servo.h>

// Rotary encoder pins
#define CLK_PIN 2     // CLK
#define DT_PIN  A3    // DT
#define SW_PIN  A2    // SW (optional, not used here)

int counter = 0;        // Encoder position
int angle = 0;          // Servo angle
int stepSize = 5;       // Angle change per encoder step
int clkState;
int lastClkState;

Servo servomotor;

void setup() {
  pinMode(CLK_PIN, INPUT);
  pinMode(DT_PIN, INPUT);
  pinMode(SW_PIN, INPUT_PULLUP);   // For future use

  Serial.begin(9600);

  // Read initial CLK state
  lastClkState = digitalRead(CLK_PIN);

  // Attach servo to pin 11
  servomotor.attach(11);
  servomotor.write(angle);
}

void loop() {
  clkState = digitalRead(CLK_PIN);

  // Detect encoder movement
  if (clkState != lastClkState) {

    // Clockwise rotation
    if (digitalRead(DT_PIN) != clkState) {
      counter++;
      angle += stepSize;
      Serial.println("CW");
    }
    // Counter-clockwise rotation
    else {
      counter--;
      angle -= stepSize;
      Serial.println("CCW");
    }

    // Limit servo angle between 0 and 180
    if (angle > 180) angle = 180;
    if (angle < 0) angle = 0;

    // Move servo
    servomotor.write(angle);

    Serial.print("Position: ");
    Serial.print(counter);
    Serial.print(" | Servo angle: ");
    Serial.println(angle);
  }

  lastClkState = clkState;
}

