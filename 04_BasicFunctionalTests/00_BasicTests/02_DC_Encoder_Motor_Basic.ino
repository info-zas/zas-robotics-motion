// Motor driver pins
const int PWMA = 5;   // PWM control for speed
const int AIN1 = 6;   // Direction pin 1
const int AIN2 = 4;   // Direction pin 2

// Extra motor direction control (if needed)
const int DIR = 12;   // External direction pin (from your encoder/motor setup)

void setup() {
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(DIR, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Clockwise rotation
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(DIR, HIGH);         // Direction pin HIGH = CW (you can invert if needed)
  analogWrite(PWMA, 200);          // Speed (0-255)

  Serial.println("Motor running clockwise...");
  delay(3000);

  // Stop
  analogWrite(PWMA, 0);
  Serial.println("Motor stopped.");
  delay(1000);

  // Anticlockwise rotation
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(DIR, LOW);          // Direction pin LOW = CCW
  analogWrite(PWMA, 200);

  Serial.println("Motor running anticlockwise...");
  delay(3000);

  // Stop
  analogWrite(PWMA, 0);
  Serial.println("Motor stopped.");
  delay(1000);
}

