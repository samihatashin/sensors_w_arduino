#include "DFRobot_OxygenSensor.h"

DFRobot_OxygenSensor oxygen;

void setup(void) {
  Serial.begin(9600);
  Wire.begin();
  while (!oxygen.begin(0x73)) {
    Serial.println("I2C device number error");
    delay(1000);
  }
  Serial.println("I2C connect success!");
}

void loop(void) {
  float oxygenData = oxygen.getOxygenData(10);  //took average of 10 readings
  Serial.print("Oxygen concentration is ");
  Serial.print(oxygenData);
  Serial.println(" %vol");
  delay(1000);
}
