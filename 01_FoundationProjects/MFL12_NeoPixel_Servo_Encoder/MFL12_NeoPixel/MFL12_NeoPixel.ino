#include <Adafruit_NeoPixel.h>

#define PIN 12
#define NUMPIXELS 4

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();            // Initialize NeoPixel strip
  pixels.setBrightness(100); // Set brightness (0–255)
  pixels.show();             // Turn off all LEDs initially
}

void loop() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 255)); // Cyan color
  }

  pixels.show();             // Update LEDs
  delay(100);                // Small delay
}

