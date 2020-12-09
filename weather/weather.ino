#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space<br>#include < ESP8266WiFi.h>
#include  <BlynkSimpleEsp8266.h>
#include "Seeed_BME280.h"
#include <Wire.h>
BME280 bme280;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "3df5f636c7dc464a457a32e382c4796xx";// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SSID";
char pass[] = "PASS WORD";
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  Serial.begin(9600);
  if(!bme280.init()){
  Serial.println("Device error!");
  }
}

void loop()
{
  Blynk.run();
  
  //get and print temperatures
  float temp = bme280.getTemperature();
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.println("C");//The unit for  Celsius because original arduino don't support speical symbols
  Blynk.virtualWrite(0, temp); // virtual pin 0
  Blynk.virtualWrite(4, temp); // virtual pin 4
  //get and print atmospheric pressure data
  float pressure = bme280.getPressure(); // pressure in Pa
  float p = pressure/100.0 ; // pressure in hPa
  Serial.print("Pressure: ");
  Serial.print(p);
  Serial.println("hPa");
  Blynk.virtualWrite(1, p); // virtual pin 1
  //get and print altitude data
  float altitude = bme280.calcAltitude(pressure);
  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println("m");
  Blynk.virtualWrite(2, altitude); // virtual pin 2  //get and print humidity data
  float humidity = bme280.getHumidity();
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  Blynk.virtualWrite(3, humidity); // virtual pin 3
  ESP.deepSleep(5 * 60 * 1000000); // deepSleep time is defined in microseconds.
}
