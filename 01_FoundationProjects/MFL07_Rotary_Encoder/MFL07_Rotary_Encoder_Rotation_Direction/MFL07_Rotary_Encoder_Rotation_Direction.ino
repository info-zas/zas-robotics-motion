#define CLK_PIN 2     // Encoder CLK (Output A)
#define DT_PIN  A3    // Encoder DT  (Output B)
#define SW_PIN  A2    // Encoder Switch (optional)

int counter = 0;
int clkState;
int lastClkState;

void setup() {
  pinMode(CLK_PIN, INPUT);
  pinMode(DT_PIN, INPUT);
  pinMode(SW_PIN, INPUT_PULLUP);   // Switch uses pull-up

  Serial.begin(9600);

  // Read initial state of CLK
  lastClkState = digitalRead(CLK_PIN);
}

void loop() {
  clkState = digitalRead(CLK_PIN);

  // Detect change in CLK
  if (clkState != lastClkState) {

    // Check DT to determine direction
    if (digitalRead(DT_PIN) != clkState) {
      counter++;
      Serial.println("CW");
    } else {
      counter--;
      Serial.println("CCW");
    }

    Serial.print("Position: ");
    Serial.println(counter);
  }

  lastClkState = clkState;
}

