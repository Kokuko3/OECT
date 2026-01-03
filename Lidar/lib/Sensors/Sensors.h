#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_AS5600.h>
#include <Adafruit_VL53L0X.h>
#include <tuple>

// Encoder Setup and Read Functions
bool encoderSetup(int retries);
std::tuple<uint16_t, float, float> readEncoder();

// Range Finder Setup and Read Functions
bool loxTestSetup(int XSHUT1_pin, int XSHUT2_pin, int retries);
std::tuple<uint16_t, uint16_t> loxRead();