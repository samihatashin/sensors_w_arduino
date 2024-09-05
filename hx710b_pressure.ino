int pressurePin = 20; // i coded this on mega

void setup() {

  Serial.begin(9600);
}

void loop() {

  int pressureValue = analogRead(pressurePin);


  Serial.print("Pressure: ");
  Serial.print(pressureValue);
  Serial.println(" Pa");


  delay(1000);
}