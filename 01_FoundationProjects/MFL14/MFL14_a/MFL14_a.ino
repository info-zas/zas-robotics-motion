#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Ultrasonic pins
const int trigPin = 7;
const int echoPin = 11;

// MQ135 sensor pin
const int mq135Pin = A1;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(mq135Pin,INPUT);

  Serial.begin(9600);
    // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
}

void loop() {
  float distance = getDistance();
  int mq135Value = analogRead(mq135Pin);

  // Print both distance and MQ135 values
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | ");
  Serial.print("MQ135: ");
  Serial.println(mq135Value);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_WHITE);
  display.print("Dist: ");
  display.print(distance);
  display.println(" cm");

  display.setCursor(0, 16);
  display.print("Pollution: ");
  display.println(mq135Value);
  display.display();
  delay(300);
}

float getDistance() {
  // Send trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo time
  long duration = pulseIn(echoPin, HIGH);

  // Convert to cm
  float distance = duration * 0.0343 / 2.0;
  return distance;
}

