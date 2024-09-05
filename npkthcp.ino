#include <AltSoftSerial.h>

#define RE 6
#define DE 7

const byte temp[] = {0x01, 0x03, 0x00, 0x13, 0x00, 0x01, 0x75, 0xcf};
const byte mois[] = {0x01, 0x03, 0x00, 0x12, 0x00, 0x01, 0x24, 0x0F};
const byte econ[] = {0x01, 0x03, 0x00, 0x15, 0x00, 0x01, 0x95, 0xce};
const byte ph[] = {0x01, 0x03, 0x00, 0x06, 0x00, 0x01, 0x64, 0x0b};
const byte nitro[] = {0x01, 0x03, 0x00, 0x1E, 0x00, 0x01, 0xE4, 0x0C};
const byte phos[] = {0x01, 0x03, 0x00, 0x1F, 0x00, 0x01, 0xB5, 0xCC};
const byte pota[] = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xC0};

byte values[7];
AltSoftSerial mod;

void setup() {
  Serial.begin(9600);
  mod.begin(9600);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  delay(3000);
}

void loop() {
  float soil_mois_hex = readSensor(mois); 
  float soil_mois = soil_mois_hex / 1.8; 
  soil_mois = mapToRange(soil_mois, 0, 1023, 0, 100); 
  delay(1000);
  float soil_temp = readSensor(temp) / 10.0;
  delay(1000);
  float soil_ec = readSensor(econ);
  delay(1000);
  float soil_ph = readSensor(ph);
  soil_ph = mapToRange(soil_ph, 0, 1023, 2, 14); 
  delay(1000);
  float soil_nitro = readSensor(nitro);
  delay(1000);
  float soil_phos = readSensor(phos);
  delay(1000);
  float soil_pota = readSensor(pota);
  delay(1000);

  Serial.print("Moisture: "); 
  Serial.print(soil_mois, 2); 
  Serial.println(" %"); 
  delay(1000);
  Serial.print("Temperature: "); 
  Serial.print(soil_temp, 2); 
  Serial.println(" C");
  delay(1000);
  Serial.print("EC: "); 
  Serial.print(soil_ec, 2); 
  Serial.println(" us/cm");
  delay(1000);
  Serial.print("pH: "); 
  Serial.print(soil_ph, 2); 
  Serial.println(" pH");
  delay(1000);
  Serial.print("Nitrogen: "); 
  Serial.print(soil_nitro, 2); 
  Serial.println(" mg/kg");
  delay(1000);
  Serial.print("Phosphorous: "); 
  Serial.print(soil_phos, 2); 
  Serial.println(" mg/kg");
  delay(1000);
  Serial.print("Potassium: "); 
  Serial.print(soil_pota, 2); 
  Serial.println(" mg/kg");
  Serial.println();
  delay(3000);
}

float readSensor(const byte* command) {
  mod.flushInput();
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(1);
  for (uint8_t i = 0; i < 8; i++) {
    mod.write(command[i]);
  }
  mod.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  delay(200);
  for (byte i = 0; i < 7; i++) {
    values[i] = mod.read();
  }
  return combineBytes();
}

float combineBytes() {
  int16_t combinedValue = (values[3] << 8) | values[4];
  return combinedValue;
}

float mapToRange(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


   /*Arduino Uno
    +-----------+
    |    GND    |-------------------------------[GND]
    |    5V     |-------------------------------[5V]
    |           |
    |    D2     |------[AltSoftSerial TX]-------[Sensors]
    |    D3     |------[AltSoftSerial RX]-------[Sensors]
    |    D6     |-------------------------------[RS-485 DE]
    |    D7     |-------------------------------[RS-485 RE]
    |    D8     |-------------------------------[RS-485 RO]
    |    D9     |-------------------------------[RS-485 DI]
    +-----------+
    
    RS-485 Module
    +---------------------+
    |          GND        |-------------------------------[GND]
    |          VCC        |-------------------------------[5V]
    |          DE         |-------------------------------[Arduino D6]
    |          RE         |-------------------------------[Arduino D7]
    |          RO         |-------------------------------[Arduino D8]
    |          DI         |-------------------------------[Arduino D9]
    +---------------------+
    
    Sensors
    +---------------------+
    |          VCC        |-------------------------------[5V]
    |          GND        |-------------------------------[GND]
    |         Data        |-------------------------------[Arduino Digital Pins]
    +---------------------+
*/
