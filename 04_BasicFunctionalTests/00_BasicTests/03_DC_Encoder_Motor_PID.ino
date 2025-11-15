// -------------------- Motor Driver Pins --------------------
const int PWMA = 5;   // PWM control for speed
const int AIN1 = 6;   // Direction pin 1
const int AIN2 = 4;   // Direction pin 2
const int DIR  = 12;  // Optional direction pin (for external use)

// -------------------- Encoder Pin --------------------
const int ENCA = 3;   // Encoder A connected to interrupt pin (D3)

// -------------------- Global Variables --------------------
volatile long encoderCount = 0;   // Updated in ISR
long targetCount = 5000;          // Target position (pulses)

// PID constants (tune these)
float Kp = 0.6;
float Ki = 0.0005;
float Kd = 0.2;

float error = 0, prevError = 0;
float integral = 0, derivative = 0;
unsigned long prevTime = 0;

// -------------------- Setup --------------------
void setup() {
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(DIR, OUTPUT);

  pinMode(ENCA, INPUT_PULLUP);   // Encoder input with internal pullup
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);

  Serial.begin(9600);
  Serial.println("Single-Channel Encoder PID Position Control Starting...");
}

// -------------------- Main Loop --------------------
void loop() {
  unsigned long currentTime = millis();
  float dt = (currentTime - prevTime) / 1000.0;

  if (dt >= 0.01) {  // Run control loop every ~10ms
    // Compute error
    error = targetCount - encoderCount;
    integral += error * dt;
    derivative = (error - prevError) / dt;

    // PID output
    float output = Kp * error + Ki * integral + Kd * derivative;
    output = constrain(output, -255, 255);  // Limit PWM range

    // Apply motor direction and speed
    if (output > 0) {
      // Clockwise
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(DIR, HIGH);
      analogWrite(PWMA, (int)output);
    } else {
      // Counterclockwise
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      digitalWrite(DIR, LOW);
      analogWrite(PWMA, (int)(-output));
    }

    // Debug output
    Serial.print("Target: ");
    Serial.print(targetCount);
    Serial.print(" | Count: ");
    Serial.print(encoderCount);
    Serial.print(" | Error: ");
    Serial.print(error);
    Serial.print(" | PWM: ");
    Serial.println(output);

    // Stop when close enough
    if (abs(error) < 10) {
      analogWrite(PWMA, 0);
      Serial.println("Target reached!");
      delay(2000);  // Wait 2s before reversing direction
      targetCount = (targetCount == 5000) ? 0 : 5000;  // Alternate target
    }

    prevError = error;
    prevTime = currentTime;
  }
}

// -------------------- Interrupt Service Routine --------------------
void readEncoder() {
  encoderCount++;   // Increment on each rising edge
}
