#include <Servo.h>
#include <Adafruit_NeoPixel.h>

// Rotary encoder pins
#define outputA 2
#define outputB A3

// NeoPixel setup
#define LED_PIN 12         // Change if needed
#define NUM_LEDS 4

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

int counter = 0;       // Encoder position tracker
int angle = 0;         // Servo angle
int stepSize = 5;      // Servo angle increment per encoder tick
int aState;
int aLastState;

Servo servomotor;

void setup() {
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);

  Serial.begin(9600);
  aLastState = digitalRead(outputA);

  servomotor.attach(11); // Servo on pin 9
  servomotor.write(angle);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  aState = digitalRead(outputA);

  // If encoder has moved
  if (aState != aLastState) {
    if (digitalRead(outputB) != aState) {
      // Clockwise
      counter++;
      angle += stepSize;
      Serial.println("CW");
      setColor(125, 125, 0); // Red
    } else {
      // Counter-clockwise
      counter--;
      angle -= stepSize;
      Serial.println("CCW");
      setColor(0, 0, 255); // Blue
    }

    // Clamp angle
    angle = constrain(angle, 0, 180);
    servomotor.write(angle);

    Serial.print("Position: ");
    Serial.print(counter);
    Serial.print(" | Servo angle: ");
    Serial.println(angle);
  }

  aLastState = aState;
}

// Function to set NeoPixel color
void setColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}

