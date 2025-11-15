#include <Servo.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width in pixels
#define SCREEN_HEIGHT 64 // OLED display height in pixels

// Create an OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);



Servo myServo;        // Create servo object
int potPin = A0;      // Potentiometer connected to A0
int val;              // Variable to store potentiometer value

void setup() {
  Serial.begin(9600);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C is default I2C address
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  
  display.clearDisplay(); // Clear display buffer

  display.setTextSize(2);      // Text size
  display.setTextColor(SSD1306_WHITE); // Text color
  display.setCursor(0, 10);    // Start at top-left corner (x=0, y=10)
  display.println("Hello");
  
  display.display();           // Actually display everything you wrote

  
  myServo.attach(11);  // Servo signal pin connected to pin 3
}

void loop() {
  val = analogRead(potPin); 
  Serial.println(val);              // Read potentiometer value (0–1023)
  val = map(val, 0, 1023, 0, 180);        // Map to servo angle (0–180 degrees)
  myServo.write(val);                     // Rotate servo
  delay(15);                              // Short delay for smooth movement
}

