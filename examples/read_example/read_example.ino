// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include <TE_SM9000.h>

// Example settings for SM9233-BCE-S-250-000
SM9000_sensor T9233(250, 0, -26215, 26214);

void setup() {
  Wire.begin();
  Serial.begin(57600);
}

void loop() {
  //T9233.reset();
  T9233.wake();
  delay(2000);

  T9233.readData();

  Serial.print("SM9000: ");
  Serial.print("Pressure: ");
  Serial.print(T9233.getPressure());
  Serial.print(" Temperature: ");
  Serial.println(T9233.getTemp());

  T9233.sleep();

  delay(500);
}
