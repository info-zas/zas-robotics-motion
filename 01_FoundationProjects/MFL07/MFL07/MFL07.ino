// Rotary Encoder pin connections
#define CLK_PIN 2     // Clock pin
#define DT_PIN  A3    // Data pin
#define SW_PIN  A2    // Switch pin

void setup() {
  pinMode(CLK_PIN, INPUT);
  pinMode(DT_PIN, INPUT);
  pinMode(SW_PIN, INPUT_PULLUP);  // Use internal pull-up for switch

  Serial.begin(9600);
  Serial.println("Rotary Encoder Test");
}

void loop() {
  int clkState = digitalRead(CLK_PIN);
  int dtState  = digitalRead(DT_PIN);
  int swState  = digitalRead(SW_PIN);

  Serial.print("CLK: ");
  Serial.print(clkState);

  Serial.print("  DT: ");
  Serial.print(dtState);

  Serial.print("  SW: ");
  Serial.println(swState);

     // Slow down Serial output
}

