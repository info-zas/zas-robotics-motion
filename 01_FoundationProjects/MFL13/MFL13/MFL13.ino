#include <TinyGPS++.h>

TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);     // Serial Monitor (USB)
  Serial.println("GPS Module Test - Lat, Lon, Date, Time");
}

void loop() {
  while (Serial.available() > 0) {
    gps.encode(Serial.read());

    if (gps.location.isUpdated() && gps.date.isUpdated() && gps.time.isUpdated()) {
      Serial.print("Lat: "); Serial.print(gps.location.lat(), 6);
      Serial.print(", Lon: "); Serial.print(gps.location.lng(), 6);
      Serial.print(", Date: ");
      if (gps.date.isValid()) {
        Serial.print(gps.date.day()); Serial.print("/");
        Serial.print(gps.date.month()); Serial.print("/");
        Serial.print(gps.date.year());
      } else {
        Serial.print("Invalid");
      }
      Serial.print(", Time: ");
      if (gps.time.isValid()) {
        if (gps.time.hour() < 10) Serial.print("0");
        Serial.print(gps.time.hour()); Serial.print(":");
        if (gps.time.minute() < 10) Serial.print("0");
        Serial.print(gps.time.minute()); Serial.print(":");
        if (gps.time.second() < 10) Serial.print("0");
        Serial.print(gps.time.second());
      } else {
        Serial.print("Invalid");
      }
      Serial.println();
    }
  }
}
