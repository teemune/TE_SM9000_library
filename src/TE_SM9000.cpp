#include "TE_SM9000.h"
#include <Arduino.h>
#include <Wire.h>

#define SM9000_T_OFFSET 16881
#define SM9000_T_SCALE 397.2

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
void SM9000_sensor::readData()
{
  Wire.beginTransmission(I2C_address);
  Wire.write(0x2E);
  Wire.write(0xD9);
  Wire.requestFrom(I2C_address, 6, true);
  Wire.endTransmission();
  for(int i = 0; i < 6; i++)
  {
	if(Wire.available()) {
	  reading[i] = Wire.read();
	}
  }
}
float SM9000_sensor::getTemp()
{
  int SM9000_temperature_raw = 0;
  SM9000_temperature_raw += reading[0] + (reading[1] << 8);
  temperature = ((float)SM9000_temperature_raw + SM9000_T_OFFSET) / SM9000_T_SCALE;
  return temperature;
}
float SM9000_sensor::getPressure()
{
  int SM9000_pressure_raw = 0;
  SM9000_pressure_raw += reading[2] + (reading[3] << 8);
  pressure = Pmin + ((float)(SM9000_pressure_raw - OUT_min) / (float)((long)OUT_max - (long)OUT_min))*(Pmax - Pmin);
  return pressure;
}