#include <Arduino.h>
#include <Wire.h>
#include <GyverPower.h>

// #define ENABLE_DEBUG 1

#include "tools.h"
#include "sdcard.h"
#include "rtc.h"
#include "bmx280.h"

#define POWER_PIN 2
#define RX_PIN 0
#define TX_PIN 1

#define BLINK_DURATION 20

void logData()
{
  blink(BLINK_DURATION);
  PRINTLN("------------------------------------------");
  PRINTLN("Start log cycle...");
  bool createHeaders = false;
  File file = SD::createFile(createHeaders);
  if (!file)
  {
    return;
  }
  blink(BLINK_DURATION);

  date_time date = RTC::getTime();
  blink(BLINK_DURATION);

  bmx280_data bmx_data = BMX280::getData();
  if (!bmx_data.valid)
  {
    return;
  }
  blink(BLINK_DURATION);

  if (createHeaders)
  {
    file.println("Date;Pressure[Pa];Temperature[C];Humidity[%]");
  }
  file.print(date.date);
  file.print(" ");
  file.print(date.time);
  file.print(";");
  file.print(bmx_data.pressure, 0);
  file.print(";");
  file.print(bmx_data.temperature, 1);
  file.print(";");
  file.print(bmx_data.humidity, 1);
  file.println();
  file.flush();
  file.close();

  PRINTLN("Log cycle DONE");
  PRINTLN("------------------------------------------");
}

void setup()
{
#ifdef ENABLE_DEBUG
  Serial.begin(9600);
  while (!Serial)
    ;
#endif

  pinMode(POWER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  power.autoCalibrate();
  power.setSleepMode(POWERDOWN_SLEEP);
  power.bodInSleep(false);
  blink(BLINK_DURATION);
}

void loop()
{
#ifdef ENABLE_DEBUG
  uint16_t options = PWR_I2C | PWR_SPI | PWR_UART0 | PWR_TIMER0 | PWR_TIMER1;
#else
  uint16_t options = PWR_I2C | PWR_SPI | PWR_TIMER0 | PWR_TIMER1;
#endif
  //
  power.hardwareEnable(options);

  PRINTLN("Enable power...");
  high(POWER_PIN);
  delay(100);
  // RTC::rtc.setTime(00, 51, 11, 15, 4, 2023);
  logData();
  PRINTLN("Disabling power...");
  low(POWER_PIN);
  power.hardwareDisable(PWR_ADC);
  power.sleepDelay(10000);
}