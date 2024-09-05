// float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
// {
//   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
// }

int UV_OUT = A2; //this was also done on mega

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int uv_Level = analogRead(UV_OUT);
  int en = analogRead(10);


  float output_Voltage = 3.3 / en * uv_Level;

  float uvIntensity = mapfloat(output_Voltage, 0.99, 2.8, 0.0, 15.0);

  Serial.print(uvIntensity);
  delay(1000);
}
// float mapfloat(long x, long in_min, long in_max, long out_min, long out_max)
// {
//   return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
// }

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
