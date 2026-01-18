#include <Wire.h>
#include <MPU6050.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize MPU6050
  mpu.initialize();

  // Initialize OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  if (mpu.testConnection()) {
    display.println("MPU6050 Connected");
    Serial.println("MPU6050 connected successfully!");
  } else {
    display.println("MPU6050 Failed");
    Serial.println("MPU6050 connection failed!");
  }

  display.display();
  delay(2000);
}

void loop() {
  int16_t ax, ay, az;

  // Read accelerometer values
  mpu.getAcceleration(&ax, &ay, &az);

  // -------- Serial Monitor Output --------
  Serial.print("AX: ");
  Serial.print(ax);
  Serial.print(" | AY: ");
  Serial.print(ay);
  Serial.print(" | AZ: ");
  Serial.println(az);

  // -------- OLED Display Output --------
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);

  display.print("AX: ");
  display.println(ax);

  display.print("AY: ");
  display.println(ay);

  display.print("AZ: ");
  display.println(az);

  display.display();

  delay(500);
}
