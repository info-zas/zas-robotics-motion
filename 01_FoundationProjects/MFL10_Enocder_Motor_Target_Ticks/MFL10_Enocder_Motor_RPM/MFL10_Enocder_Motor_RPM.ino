#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Encoder pins
#define INT_PIN 3
#define DIR_PIN 12

volatile long pulseCount = 0;

unsigned long lastTime = 0;
int rpm = 0;

const int PPR = 20;   // Pulses Per Revolution (CHANGE THIS)

void setup() {
  delay(1000);   // Power stabilization

  pinMode(INT_PIN, INPUT);
  pinMode(DIR_PIN, INPUT);

  Serial.begin(9600);
  Wire.begin();

  // OLED initialization
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("Encoder RPM");
  display.display();

  attachInterrupt(digitalPinToInterrupt(INT_PIN), countPulse, RISING);

  lastTime = millis();
}

void loop() {
  unsigned long currentTime = millis();

  // Calculate RPM every 1 second
  if (currentTime - lastTime >= 1000) {

    noInterrupts();
    long pulses = pulseCount;
    pulseCount = 0;
    interrupts();

    rpm = (pulses * 60) / PPR;

    // -------- Serial Monitor --------
    Serial.print("RPM: ");
    Serial.print(rpm);

    Serial.print(" | Direction: ");
    if (digitalRead(DIR_PIN) == HIGH)
      Serial.println("CW");
    else
      Serial.println("CCW");

    // -------- OLED Display --------
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Encoder RPM");

    display.setCursor(0, 20);
    display.print("RPM: ");
    display.println(rpm);

    display.setCursor(0, 40);
    display.print("DIR: ");
    if (digitalRead(DIR_PIN) == HIGH)
      display.println("CW");
    else
      display.println("CCW");

    display.display();

    lastTime = currentTime;
  }
}

// Interrupt Service Routine
void countPulse() {
  pulseCount++;
}
