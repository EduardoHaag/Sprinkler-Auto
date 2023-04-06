#include "DHT.h"

#define MQ2pin (D6)

#define DHTPIN A5  

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float sensorValue;  //variable to store sensor value

void setup()
{
  Serial.begin(9600); // sets the serial port to 9600
  Serial.println("Gas sensor warming up!");
  delay(20000); // allow the MQ-6 to warm up
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

void loop()
{
  sensorValue = analogRead(A4); // read analog input pin 0
  
  Serial.println("Sensor Value: ");
  Serial.println(sensorValue);
  
  if(sensorValue > 300)
  {
    Serial.print("Smoke detected!");
  }
  
  Serial.println("");

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  delay(2000); // wait 2s for next reading
}
