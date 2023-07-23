#include <Arduino.h>
#include <Wire.h>
#include <GyverBME280.h>                            // Подключение библиотеки
#include "tools.h"

#define I2C_ADDRESS 0x76

GyverBME280 bme;

struct bmx280_data
{
  float temperature;
  float humidity;
  float pressure;
  bool valid = false;
};


namespace BMX280
{
  bmx280_data getData()
  {
    bmx280_data data;

    bme.setMode(FORCED_MODE);                             // Перед инициализацией говорим датчику работать в принудительном режиме
    if (!bme.begin())
    {
      PRINTLN("Couldn't find BMx280");
      return data;
    }
    PRINT("Connecting BMx280... ");
    bme.oneMeasurement();
    while (bme.isMeasuring());

    data.temperature = bme.readTemperature();
    data.humidity = bme.readHumidity();
    data.pressure = bme.readPressure();
    data.valid = true;
    PRINTLN("DONE");
    return data;
  }
}