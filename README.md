# Battery Level Monitor for XIAO ESP32S3
Measure battery voltage and estimate charge percentage using a voltage divider and the ESP32S3's ADC.

## Features
- Reads battery voltage via a 1:1 voltage divider (e.g., two 10kΩ resistors)
- Uses ESP32 ADC calibration for accurate readings
- Prints battery voltage and estimated percentage to the serial monitor
- Configurable sample averaging for stable readings

## Hardware Setup
- **Board:** Seeed Studio XIAO ESP32S3
- **Voltage Divider:** Two equal-value resistors (e.g., 10kΩ + 10kΩ) between battery positive and ground. Divider midpoint to A0
- **Battery:** 3.7V LiPo (typical range: 3.0V - 4.2V)

## Example Output
```
Battery Voltage: 3.85 V | Battery Percentage: 70%
```

## Documentation
- [Seeed XIAO ESP32S3 Getting Started](https://wiki.seeedstudio.com/xiao_esp32s3_getting_started/)
- [Seeed Battery Voltage Measurement](https://wiki.seeedstudio.com/check_battery_voltage/)

## License
MIT
