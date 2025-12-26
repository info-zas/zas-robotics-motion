#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Adafruit_NeoPixel.h>
#define NEOPIXEL_PIN 12
#define NUM_PIXELS 4
Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Motor driver pins
const int AIN1 = 6;
const int AIN2 = 4;
const int PWMA = 5;

// Ultrasonic pins
const int trigPin = 7;
const int echoPin = 11;

// MQ135 sensor pin
const int mq135Pin = A1;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  pixels.begin();  
  pixels.show();   // Turn off initially

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);

  // OLED INIT
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("DC Motor + Ultrasonic");
  display.println("System Starting...");
  display.display();
  delay(1500);
}

void loop() {

  float distance = getDistance();
  int mq135Value = analogRead(mq135Pin);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | MQ135: ");
  Serial.print(mq135Value);

  // 🔵 NEOPIXEL LOGIC (simple)
  if (distance > 10) {
    setColor(0, 255, 0);   // GREEN
  } else {
    setColor(255, 0, 0);   // RED
  }

  // Motor logic
  if (mq135Value > 215) {
    ccw();
    Serial.println(" | Status: HIGH POLLUTION - Motor CCW");
  } else if (distance < 10) {
    cw();
    Serial.println(" | Status: OBSTACLE - Motor CW");
  } else {
    stopMotor();
    Serial.println(" | Status: STOPPED");
  }

  delay(100);

  // OLED Update
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Dist: ");
  display.print(distance);
  display.println(" cm");

  display.setCursor(0, 16);
  display.print("Pollution: ");
  display.println(mq135Value);
  display.display();
}

float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.0343 / 2.0;
  return distance;
}

// 🔵 Set all neopixels to a colour
void setColor(int r, int g, int b) {
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  pixels.show();
}

// TB6612 functions
void cw() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 255);
}

void ccw() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, 255);
}

void stopMotor() {
  analogWrite(PWMA, 0);
}

