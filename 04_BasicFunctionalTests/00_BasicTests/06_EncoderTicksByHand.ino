#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

// -------------------- OLED Configuration --------------------
#define OLED_RESET -1
Adafruit_SH1106 display(OLED_RESET);

// -------------------- Pins --------------------
const int ENCA = 3;   // Encoder A (interrupt-capable)
const int DIR  = 12;  // Direction pin (external input or controlled)

// -------------------- Encoder Tracking --------------------
volatile long encoderTicks = 0;
volatile int lastDirection = 1;  // 1 = CW, -1 = CCW

void readEncoder() {
  if (digitalRead(DIR)) {
    encoderTicks++;
    lastDirection = 1;
  } else {
    encoderTicks--;
    lastDirection = -1;
  }
}

void setup() {
  pinMode(ENCA, INPUT_PULLUP);
  pinMode(DIR, INPUT);

  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);

  // OLED setup
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Ready...");
  display.display();
  delay(1000);
}

void loop() {
  // Copy volatile vars safely
  noInterrupts();
  long ticks = encoderTicks;
  int dir = lastDirection;
  interrupts();

  // Display values
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Ticks:");
  display.setCursor(0, 20);
  display.println(ticks);

  display.setCursor(0, 45);
  display.print("Dir: ");
  display.println(dir == 1 ? "CW" : "CCW");

  display.display();
  delay(200);
}
