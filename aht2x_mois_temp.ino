
#include <Wire.h>
#include <AHT20.h> // this library is meant to use the fixed register address for the sensor on its own and so i didnt have to use it explicitly
AHT20 aht20;

void setup()
{
  Serial.begin(115200);
  // Wire.begin();
  Wire.begin();

}

void loop()
{
  if (aht20.available() == true)
  {
    float temperature = aht20.getTemperature();
    float humidity = aht20.getHumidity();

    //Print the results
    Serial.print("Temperature: ");
    Serial.print(temperature, 2);
    Serial.print(" C\t");
    Serial.print("Humidity: ");
    Serial.print(humidity, 2);
    Serial.print("% RH");

    Serial.println();
  }

  delay(1000);

  
}