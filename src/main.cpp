#include <Arduino.h>
#include "battery.h"

BatteryMonitor battery(64, 3.0, 4.2);

void setup() {
  Serial.begin(115200);
  delay(100);
  battery.begin();
}

void printBatteryStatus() {
  float voltage = battery.readVoltage();
  int batteryPercent = battery.getPercentage(voltage);
  Serial.print("Battery Voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V | Battery Percentage: ");
  Serial.print(batteryPercent);
  Serial.println("%");
}

void loop() {
  printBatteryStatus();
  delay(1000);
}