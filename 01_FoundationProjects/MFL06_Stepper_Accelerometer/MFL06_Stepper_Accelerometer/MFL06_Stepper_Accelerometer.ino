#include <Wire.h>
#include <MPU6050.h>
#include <Stepper.h>

MPU6050 mpu;

// Stepper motor settings (28BYJ-48)
const int stepsPerRevolution = 2048;

// IN1, IN3, IN2, IN4 pin sequence
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 7);

int16_t ax, ay, az;
int threshold = 2000;   // Dead zone to avoid jitter

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize MPU6050
  mpu.initialize();

  // Initialize Stepper
  myStepper.setSpeed(10); // RPM

  Serial.println("MPU6050 + Stepper Control Ready");
}

void loop() {
  // Read accelerometer values
  mpu.getAcceleration(&ax, &ay, &az);

  // Print X value
  Serial.print("AX: ");
  Serial.println(ax);

  // -------- Motion Control --------
  if (ax > threshold) {
    Serial.println("Clockwise Rotation");
    myStepper.step(100);   // Small step clockwise
  }
  else if (ax < -threshold) {
    Serial.println("Anti-Clockwise Rotation");
    myStepper.step(-100);  // Small step anticlockwise
  }
  else {
    Serial.println("Motor Stop");
  }

  delay(200);
}

