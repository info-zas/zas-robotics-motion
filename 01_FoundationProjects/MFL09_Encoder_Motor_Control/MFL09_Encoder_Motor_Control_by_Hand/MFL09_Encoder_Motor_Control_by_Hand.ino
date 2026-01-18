#define INT_PIN 3
#define DIR_PIN 12

volatile long cwTicks = 0;
volatile long ccwTicks = 0;

void setup() {
  pinMode(INT_PIN, INPUT);
  pinMode(DIR_PIN, INPUT);

  Serial.begin(9600);

  // Interrupt on INT pin
  attachInterrupt(digitalPinToInterrupt(INT_PIN), countPulse, RISING);
}

void loop() {
  Serial.print("CW Ticks: ");
  Serial.print(cwTicks);

  Serial.print(" | CCW Ticks: ");
  Serial.println(ccwTicks);

  delay(500);
}

// Interrupt Service Routine
void countPulse() {
  if (digitalRead(DIR_PIN) == HIGH) {
    cwTicks++;     // Clockwise tick
  } else {
    ccwTicks++;    // Counter-clockwise tick
  }
}
