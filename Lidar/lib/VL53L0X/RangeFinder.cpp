#include "RangeFinder.h"

// One instance per sensor
static Adafruit_VL53L0X lox1;
static Adafruit_VL53L0X lox2;

bool loxTestSetup(int XSHUT1_pin, int XSHUT2_pin, int retries) {
    Wire.begin();

    pinMode(XSHUT1_pin, OUTPUT);
    pinMode(XSHUT2_pin, OUTPUT);

    // Shutdown both sensors
    digitalWrite(XSHUT1_pin, LOW);
    digitalWrite(XSHUT2_pin, LOW);
    delay(10);

    bool lox1_initialized = false;
    bool lox2_initialized = false;

    // === SENSOR 1 ===
    digitalWrite(XSHUT1_pin, HIGH);
    delay(10);

    for (int i = 0; i < retries && !lox1_initialized; i++) {
        if (lox1.begin()) {
            lox1.setAddress(0x30);
            lox1_initialized = true;
            Serial.println("Sensor 1 initialized at 0x30");
        }
        delay(50);
    }

    // === SENSOR 2 ===
    digitalWrite(XSHUT2_pin, HIGH);
    delay(10);

    for (int i = 0; i < retries && !lox2_initialized; i++) {
        if (lox2.begin()) {
            lox2_initialized = true;
            Serial.println("Sensor 2 initialized at 0x29");
        }
        delay(50);
    }

    if (!lox1_initialized) Serial.println("Failed to initialize Sensor 1");
    if (!lox2_initialized) Serial.println("Failed to initialize Sensor 2");

    return lox1_initialized && lox2_initialized;
}


std::tuple<uint16_t, uint16_t> loxRead() {
    VL53L0X_RangingMeasurementData_t measure1;
    VL53L0X_RangingMeasurementData_t measure2;

    lox1.rangingTest(&measure1, false);
    lox2.rangingTest(&measure2, false);

    uint16_t distance1 = (measure1.RangeStatus != 4 && measure1.RangeMilliMeter != 8191) ? measure1.RangeMilliMeter : 0;
    uint16_t distance2 = (measure2.RangeStatus != 4 && measure2.RangeMilliMeter != 8191) ? measure2.RangeMilliMeter : 0;

    return std::make_tuple(distance1, distance2);
}


