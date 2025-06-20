#include <Arduino.h>
#include <driver/adc.h>
#include <esp_adc_cal.h>

static esp_adc_cal_characteristics_t *adc_chars;

const int BATTERY_SAMPLES = 64;

void setup() {
  Serial.begin(115200);
  delay(100);

  // ESP32 ADC calibration setup
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
  adc_chars = (esp_adc_cal_characteristics_t*)calloc(1, sizeof(esp_adc_cal_characteristics_t));
  esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, adc_chars);
}

float readBatteryVoltageADC() {
  uint32_t adc_reading = 0;
  for (int i = 0; i < BATTERY_SAMPLES; i++) {
    adc_reading += adc1_get_raw((adc1_channel_t)ADC1_CHANNEL_0);
  }
  adc_reading /= BATTERY_SAMPLES;
  uint32_t vOut_mV = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
  float vOut_V = (float)vOut_mV / 1000.0;
  float batteryVoltage = vOut_V * 2.0; // 1:1 divider
  return batteryVoltage;
}

void printBatteryStatus(float voltage) {
  int batteryPercent = map(voltage * 100, 300, 420, 0, 100); // Scale 3.0V-4.2V to 0-100%
  batteryPercent = constrain(batteryPercent, 0, 100); // Ensure it stays within 0-100%
  Serial.print("Battery Voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V | Battery Percentage: ");
  Serial.print(batteryPercent);
  Serial.println("%");
}

void loop() {
  float Vbattf = readBatteryVoltageADC();
  printBatteryStatus(Vbattf);
  delay(1000);
}