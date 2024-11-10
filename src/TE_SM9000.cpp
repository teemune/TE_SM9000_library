#include "TE_SM9000.h"
#include <Arduino.h>
#include <Wire.h>

#define SM9000_T_OFFSET 16881
#define SM9000_T_SCALE 397.2

// Configure the sensor variant
SM9000_sensor::SM9000_sensor(float _Pmax, float _Pmin, int _OUT_min, int _OUT_max)
{
  Pmax = _Pmax;
  Pmin = _Pmin;
  OUT_min = _OUT_min;
  OUT_max = _OUT_max;

  for(int i = 0; i < 6; i++)
  {
	reading[i] = 0;
  }
}

// Read the pressure, temperature and status 
// no CRC
void SM9000_sensor::readData()
{
  Wire.beginTransmission(I2C_address);
  Wire.write(0x2E);
  Wire.endTransmission(false);
  Wire.requestFrom((uint8_t)I2C_address, (size_t)6, true);
  for(int i = 0; i < 6; i++)
  {
  	if(Wire.available()) {
  	  reading[i] = Wire.read();
  	}
  }
}

// Parse temperature from the data read by readData()
// no CRC
float SM9000_sensor::getTemp()
{
  float temperature = 0;
  int16_t SM9000_temperature_raw = 0;
  SM9000_temperature_raw += reading[0] + (reading[1] << 8);
  temperature = ((float)SM9000_temperature_raw + SM9000_T_OFFSET) / SM9000_T_SCALE;
  return temperature;
}

// Parse pressure from the data read by readData()
// no CRC
float SM9000_sensor::getPressure()
{
  float pressure = 0;
  int16_t SM9000_pressure_raw = 0;
  long countScale = OUT_max;
  countScale -= OUT_min;
  double pressureScale = Pmax - Pmin;
  SM9000_pressure_raw += reading[2] + (reading[3] << 8);
  pressure = (((float)SM9000_pressure_raw - (float)OUT_min) / (float)countScale) * (float)pressureScale;
  pressure += Pmin;
  return pressure;
}

// Parse status from the data read by readData() 
// no CRC
word SM9000_sensor::getStatus()
{
  word SM9000_status = 0;
  SM9000_status += reading[4] + (reading[5] << 8);
  return SM9000_status;
}

// Read the pressure, temperature and status 
// no CRC
void SM9000_sensor::sleep()
{
  Wire.beginTransmission(I2C_address);
  Wire.write(0x22);
  Wire.write(0x32);
  Wire.write(0x6C);
  Wire.endTransmission(true);
}

// Wake the sensor from sleep by toggling SCL
void SM9000_sensor::wake()
{
  Wire.beginTransmission(I2C_address);
  Wire.endTransmission(true);
}

void SM9000_sensor::reset()
{
  Wire.beginTransmission(I2C_address);
  Wire.write(0x22);
  Wire.write(0x69);
  Wire.write(0xB1);
  Wire.endTransmission(true);
}
