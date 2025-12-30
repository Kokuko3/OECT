#pragma once

#include <Arduino.h>
#include <Adafruit_VL53L0X.h>
#include <Wire.h>
#include <tuple>

// Public API
bool loxTestSetup(int XSHUT1_pin, int XSHUT2_pin, int retries);
std::tuple<uint16_t, uint16_t> loxRead();