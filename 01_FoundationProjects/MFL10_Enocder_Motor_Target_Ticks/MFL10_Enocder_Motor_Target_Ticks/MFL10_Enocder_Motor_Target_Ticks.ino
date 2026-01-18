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

// TB6612 pins
#define PWMA 5
#define AIN1 6
#define AIN2 4

volatile long position = 0;
long targetPosition = 200;   // Target ticks

int motorSpeed = 150;

void setup() {
  delay(1000);

  pinMode(INT_PIN, INPUT);
  pinMode(DIR_PIN, INPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  Serial.begin(9600);
  Wire.begin();

  // OLED init
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  // Start motor clockwise
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, motorSpeed);

  attachInterrupt(digitalPinToInterrupt(INT_PIN), countPulse, RISING);

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  Serial.println("Motor Started");
}

void loop() {

  // -------- Serial Monitor --------
  Serial.print("Position: ");
  Serial.print(position);
  Serial.print(" / Target: ");
  Serial.println(targetPosition);

  // -------- OLED Display --------
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Encoder Position");

  display.setCursor(0, 20);
  display.print("Pos: ");
  display.println(position);

  display.setCursor(0, 35);
  display.print("Target: ");
  display.println(targetPosition);

  // Stop motor when target reached
  if (position >= targetPosition) {
    analogWrite(PWMA, 0);   // Stop motor

    display.setCursor(0, 50);
    display.println("Target Reached");
    display.display();

    Serial.println("Target Reached - Motor Stopped");
    while (1);   // Stop program
  }

  display.display();
  delay(200);
}

// Interrupt Service Routine
void countPulse() {
  if (digitalRead(DIR_PIN) == HIGH) {
    position--;    // CW
  } else {
    position++;    // CCW
  }
}

