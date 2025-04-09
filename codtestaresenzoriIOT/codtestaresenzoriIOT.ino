#include "DHT.h"
#include <Wire.h>
#include "MAX30105.h"




#define DHTPIN 26  // gpio26
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);


const int ecgPin = 36; // gpio36 / adc0
const int loMinus = 39;// gpio39
const int loPlus = 34;// gpio34

MAX30105 particleSensor;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
// leads off
 pinMode(loMinus, INPUT);
 pinMode(loPlus, INPUT);

 Serial.println(F("DHTxx test!"));
 dht.begin();
  
   // Initialize sensor
  if (particleSensor.begin() == false)
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }

  particleSensor.setup(); //Configure sensor. Use 6.4mA for LED drive

  
}

void readDht()
{
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
}

void readEcgSensor()
{
if((digitalRead(loMinus) == 1)||(digitalRead(loPlus) == 1))
 {
    Serial.println('!');
 }
else
{
// send the value of analog input 0:
    Serial.println(analogRead(ecgPin));
}
//Wait for a bit to keep serial data from saturating
delay(1);
}

void readPulsSensor()
{

 Serial.print(" R[");
  Serial.print(particleSensor.getRed());
  Serial.print("] IR[");
  Serial.print(particleSensor.getIR());
  Serial.print("] G[");
  Serial.print(particleSensor.getGreen());
  Serial.print("]");

  Serial.println();
}
void loop() {
  // put your main code here, to run repeatedly:
 
 //readEcgSensor(); // testare senzor ecg;
 //readDht();//   testare dht11
 readPulsSensor();

}
