#ifndef BATTERY_H
#define BATTERY_H

#include <Arduino.h>
#include <driver/adc.h>
#include <esp_adc_cal.h>

class BatteryMonitor {
public:
    explicit BatteryMonitor(int samples, float minVoltage, float maxVoltage);
    void begin();
    float readVoltage();
    int getPercentage(float voltage);
private:
    int samples;
    float minVoltage;
    float maxVoltage;
    esp_adc_cal_characteristics_t *adc_chars;
};

#endif // BATTERY_H
