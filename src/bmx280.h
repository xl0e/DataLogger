#include <Arduino.h>
#include <Wire.h>
#include "SdFat.h"
#include <BMx280TwoWire.h>
#include <RTClib.h>
#include "tools.h"

#define I2C_ADDRESS 0x76

BMx280TwoWire bmx280(&Wire, I2C_ADDRESS);

namespace BMX280
{
  void logData(File *file, DateTime *now)
  {
    PRINT("Connecting BMx280... ");
    if (!bmx280.begin())
    {
      PRINTLN("Couldn't find BMx280");
      return;
    }
    PRINTLN("DONE");

    //reset sensor to default parameters.
    bmx280.resetToDefaults();

    //by default sensing is disabled and must be enabled by setting a non-zero
    //oversampling setting.
    //set an oversampling setting for pressure and temperature measurements.
    bmx280.writeOversamplingPressure(BMx280MI::OSRS_P_x16);
    bmx280.writeOversamplingTemperature(BMx280MI::OSRS_T_x16);
    bmx280.writeOversamplingHumidity(BMx280MI::OSRS_H_x16);

    //if sensor is a BME280, set an oversampling setting for humidity measurements.
    if (bmx280.isBME280())
      bmx280.writeOversamplingHumidity(BMx280MI::OSRS_H_x16);

    //start a measurement
    if (!bmx280.measure())
    {
      PRINTLN("Could not start measurement, is a measurement already running?");
      return;
    }

    //wait for the measurement to finish.
    uint16_t wait = 0;
    do
    {
      if (wait++ > 100) {
        return;
      }
      delay(10);
    } while (!bmx280.hasValue());

    //important: measurement data is read from the sensor in function hasValue() only.
    //make sure to call get*() functions only after hasValue() has returned true.

    char format[] = "YYYY-MM-DD hh:mm:ss";
    now->toString(format);
    PRINT("Time: ");
    PRINTLN(format);
    PRINT("Pressure: ");
    PRINTLN(bmx280.getPressure());
    PRINT("Pressure (64 bit): ");
    PRINTLN(bmx280.getPressure64());
    PRINT("Temperature: ");
    PRINTLN(bmx280.getTemperature());


    file->print(format);
    file->print(";");
    file->print(bmx280.getPressure());
    file->print(";");
    file->print(bmx280.getPressure64());
    file->print(";");
    file->print(bmx280.getTemperature());

    if (bmx280.isBME280())
    {
      PRINT("Humidity: ");
      PRINTLN(bmx280.getHumidity());
      file->print(";");
      file->print(bmx280.getTemperature());
    }
    file->println();
    file->flush();

    file->close();
  }
}