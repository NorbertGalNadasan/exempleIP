/*
  MAX30105 Breakout: Output all the raw Red/IR/Green readings
  By: Nathan Seidle @ SparkFun Electronics
  Date: October 2nd, 2016
  https://github.com/sparkfun/MAX30105_Breakout

  Outputs all Red/IR/Green values.

  Hardware Connections (Breakoutboard to Arduino):
  -5V = 5V (3.3V is allowed)
  -GND = GND
  -SDA = A4 (or SDA)
  -SCL = A5 (or SCL)
  -INT = Not connected

  The MAX30105 Breakout can handle 5V or 3.3V I2C logic. We recommend powering the board with 5V
  but it will also run at 3.3V.

  This code is released under the [MIT License](http://opensource.org/licenses/MIT).
*/

#include <Wire.h>
#include "MAX30105.h"
#include "Adafruit_Si7021.h"

bool enableHeater = false;

MAX30105 particleSensor;
Adafruit_Si7021 tempSensor = Adafruit_Si7021();

const int lightPin = 36; //GpIO 36 // adc0
int lightValue = 0;

const int pirPin =  39;
int pirValue=0;


#define debug Serial //Uncomment this line if you're using an Uno or ESP
//#define debug SerialUSB //Uncomment this line if you're using a SAMD21

void setup()
{
  
  debug.begin(9600);
  pinMode(pirPin, INPUT); // pinul pentru pir

  // Initialize hearth reate sensor
  if (particleSensor.begin() == false)
  {
    debug.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }

  particleSensor.setup(); //Configure sensor. Use 6.4mA for LED drive

 // init tempSensor
  if (!tempSensor.begin()) {
    debug.println("Did not find Si7021 sensor!");
    while (true)
      ;
  }

  debug.print(tempSensor.getRevision());
  debug.print(")");
  debug.print(" Serial #"); debug.print(tempSensor.sernum_a, HEX); debug.println(tempSensor.sernum_b, HEX);
  
  
}

void loop()
{
  debug.print(" R[");
  debug.print(particleSensor.getRed());
  debug.print("] IR[");
  debug.print(particleSensor.getIR());
  debug.print("] G[");
  debug.print(particleSensor.getGreen());
  debug.print("]");
  debug.println();
  debug.print("Humidity:    ");
  debug.print(tempSensor.readHumidity(), 2);
  debug.print("\tTemperature: ");
  debug.println(tempSensor.readTemperature(), 2);
  debug.println(analogRead(lightPin)); // afisare valoare senzor lumina
  pirValue = digitalRead(pirPin);
  if (pirValue == HIGH)
  {
    debug.println("Miscare detectata");
  }

  delay(1000);
 
  debug.println();
}
