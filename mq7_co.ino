
#include <Wire.h>
#include <AHT20.h> 
int UV_OUT = A2;
int pressurePin = 20;
AHT20 aht20;
#define RE 29
#define DE 30 
const byte temp_[] = {0x01, 0x03, 0x00, 0x13, 0x00, 0x01, 0x75, 0xcf};
const byte mois_[] = {0x01, 0x03, 0x00, 0x12, 0x00, 0x01, 0x24, 0x0F};
const byte econ[] = {0x01, 0x03, 0x00, 0x15, 0x00, 0x01, 0x95, 0xce};
const byte ph_[] = {0x01, 0x03, 0x00, 0x06, 0x00, 0x01, 0x64, 0x0b};
const byte nitro[] = {0x01, 0x03, 0x00, 0x1E, 0x00, 0x01, 0xE4, 0x0C};
const byte phos[] = {0x01, 0x03, 0x00, 0x1F, 0x00, 0x01, 0xB5, 0xCC};
const byte pota[] = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xC0};
void setup() {
  
  Serial.begin(9600);
}

void loop() {
  
  int pressureValue = analogRead(pressurePin);
  float sensorvalue = analogRead(A0) *1000.0/ 1023; //i used A0 while coding w arduino uno
  Serial.println (sensorvalue);
  delay (1000);
  int uv_Level = analogRead(UV_OUT);
  int en = analogRead(10);
  float temperature = aht20.getTemperature();
  float humidity = aht20.getHumidity();
  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.print(" C\t");
  Serial.print("Humidity: ");
  Serial.print(humidity, 2);
  Serial.print("% RH");


  float output_Voltage = 3.3 / en * uv_Level;

  float uvIntensity = mapfloat(output_Voltage, 0.99, 2.8, 0.0, 15.0);
  
  Serial.print(uvIntensity);
  delay(1000);
}
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}




