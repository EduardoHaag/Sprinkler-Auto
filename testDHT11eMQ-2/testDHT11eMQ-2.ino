#include "DHT.h"

#define MQ2pin (D5)

#define DHTPIN A1  

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float sensorValue;

void setup()
{
  Serial.begin(9600); 
  Serial.println("Gas sensor warming up!");
  delay(20000); 
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

void loop()
{
  sensorValue = analogRead(A2); 
  
  Serial.println("Sensor Value: ");
  Serial.println(sensorValue);
  
  if(sensorValue > 300)
  {
    Serial.print("Smoke detected!");
  }
  Serial.println("");

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));

  delay(2000);
}
