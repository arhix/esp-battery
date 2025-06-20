#include <unity.h>
#include <battery.h>

constexpr int BATTERY_SAMPLES = 64;
constexpr float BATTERY_MIN_VOLTAGE = 3.0;
constexpr float BATTERY_MAX_VOLTAGE = 4.2;

BatteryMonitor battery(BATTERY_SAMPLES, BATTERY_MIN_VOLTAGE, BATTERY_MAX_VOLTAGE);

void test_battery_percentage(void) {
    // 4.2V should be 100%
    TEST_ASSERT_EQUAL(100, battery.getPercentage(4.2));
    // 3.0V should be 0%
    TEST_ASSERT_EQUAL(0, battery.getPercentage(3.0));
    // 3.6V should be about 50%
    int percent = battery.getPercentage(3.6);
    TEST_ASSERT_TRUE(percent > 40 && percent < 60);
    // 3.85V should be about 70%
    percent = battery.getPercentage(3.85);
    TEST_ASSERT_TRUE(percent > 65 && percent < 75);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_battery_percentage);
    UNITY_END();
}

void loop() {}
