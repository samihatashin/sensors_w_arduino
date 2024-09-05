// #include <Wire.h>

// int BH1750address = 0x23;
// byte buff[2];

// void setup()
// {
//   Wire.begin();
//   Serial.begin(9600);
//   Serial.println("BH1750 Light Intensity Sensor");
//   delay(2000);
// }

// void loop()
// {
//   uint16_t value = 0;
//   BH1750_Init(BH1750address);
//   delay(200);
//   if (2 == BH1750_Read(BH1750address))
//   {
//     value = ((buff[0] << 8) | buff[1]) / 1.2;
//     Serial.print("Intensity in LUX: ");
//     Serial.println(value);
//   }
//   delay(1500);
// }

// int BH1750_Read(int address)
// {
//   int i = 0;
//   Wire.beginTransmission(address);
//   Wire.requestFrom(address, 2);
//   while (Wire.available())
//   {
//     buff[i] = Wire.read();
//     i++;
//   }
//   Wire.endTransmission();  
//   return i;
// }

// void BH1750_Init(int address)
// {
//   Wire.beginTransmission(address);
//   Wire.write(0x10);
//   Wire.endTransmission();
// }



#include <Wire.h>
#include <BH1750.h>

// Create an instance of the BH1750 class with a specified I2C address
BH1750 lightMeter(0x23);  // Use 0x5C if the ADDR pin is connected to VCC

void setup() {
  Serial.begin(9600);    // Initialize serial communication at 9600 baud rate
  Wire.begin();          // Initialize I2C communication
  
  // Initialize the BH1750 sensor with a specified I2C address
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23)) {
    Serial.println("BH1750 Test");
  } else {
    Serial.println("Error initializing BH1750");
  }
}

void loop() {
  uint16_t lux = lightMeter.readLightLevel();  // Read light level in lux
  Serial.print(lux);
  delay(1000);    // Wait for 1 second before repeating the loop
}
