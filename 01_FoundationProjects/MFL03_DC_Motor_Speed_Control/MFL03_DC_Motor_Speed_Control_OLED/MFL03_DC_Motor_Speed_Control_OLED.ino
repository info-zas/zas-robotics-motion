#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int speedValue = 255;   // Motor speed (0–255)

void setup() {
  pinMode(5, OUTPUT);  // PWM speed control
  pinMode(6, OUTPUT);  // Direction pin 1
  pinMode(4, OUTPUT);  // Direction pin 2

  // Initialize OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  analogWrite(5, speedValue);

  forward();
  showStatus("FORWARD", speedValue);
  delay(1000);

  backward();
  showStatus("BACKWARD", speedValue);
  delay(1000);
}

// Function to move motor forward
void forward() {
  digitalWrite(6, HIGH);
  digitalWrite(4, LOW);
}

// Function to move motor backward
void backward() {
  digitalWrite(6, LOW);
  digitalWrite(4, HIGH);
}

// Function to display direction and speed
void showStatus(String direction, int speedVal) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("DIR:");
  display.setCursor(0, 20);
  display.print(direction);

  display.setTextSize(1);
  display.setCursor(0, 45);
  display.print("Speed: ");
  display.print(speedVal);

  display.display();
}
