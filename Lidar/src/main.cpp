#include <Arduino.h>
#include "RangeFinder.h"

int XSHUT1_pin = 3;
int XSHUT2_pin = 2;
int retries = 10;

void setup() {
  Serial.begin(115200);
  loxTestSetup(XSHUT1_pin, XSHUT2_pin, retries);
}

void loop() {
  std::tuple<uint16_t, uint16_t> distances;
  distances = loxRead();
  Serial.print("Distance Sensor 1: ");
  Serial.print(std::get<0>(distances));
  Serial.println(" mm");
  Serial.print("Distance Sensor 2: ");
  Serial.print(std::get<1>(distances));
  Serial.println(" mm");
  delay(30);
}