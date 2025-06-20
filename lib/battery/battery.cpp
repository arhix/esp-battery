#include "battery.h"

BatteryMonitor::BatteryMonitor(int samples, float minVoltage, float maxVoltage)
    : samples(samples), minVoltage(minVoltage), maxVoltage(maxVoltage), adc_chars(nullptr) {}

void BatteryMonitor::begin() {
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
    adc_chars = (esp_adc_cal_characteristics_t*)calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, adc_chars);
}

float BatteryMonitor::readVoltage() {
    uint32_t adc_reading = 0;
    for (int i = 0; i < samples; i++) {
        adc_reading += adc1_get_raw((adc1_channel_t)ADC1_CHANNEL_0);
    }
    adc_reading /= samples;
    uint32_t vOut_mV = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
    float vOut_V = (float)vOut_mV / 1000.0;
    float batteryVoltage = vOut_V * 2.0; // 1:1 divider
    return batteryVoltage;
}

int BatteryMonitor::getPercentage(float voltage) {
    int batteryPercent = round((voltage - minVoltage) * 100.0 / (maxVoltage - minVoltage));
    batteryPercent = constrain(batteryPercent, 0, 100);
    return batteryPercent;
}
