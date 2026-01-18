#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// TB6612 motor pins
#define PWMA 5
#define AIN1 6
#define AIN2 4

int motorSpeed = 150;      // Speed (0–255)
String direction = "CW";

void setup() {
  // Motor pins
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  // Serial & OLED
  Serial.begin(9600);
  Wire.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  // Start motor clockwise
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, motorSpeed);

  direction = "CLOCKWISE";
}

void loop() {

  // -------- OLED Display --------
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("DC Motor Control");

  display.setCursor(0, 20);
  display.print("Direction: ");
  display.println(direction);

  display.setCursor(0, 40);
  display.print("Speed: ");
  display.println(motorSpeed);

  display.display();

  // -------- Serial Monitor --------
  Serial.print("Direction: ");
  Serial.print(direction);
  Serial.print(" | Speed: ");
  Serial.println(motorSpeed);

  delay(3000);   // Run for 3 seconds

  // Change direction
  if (direction == "CLOCKWISE") {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    direction = "ANTICLOCKWISE";
  } else {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    direction = "CLOCKWISE";
  }
}
