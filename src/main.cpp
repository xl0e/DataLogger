#include <Arduino.h>
#include <GyverPower.h>

// #define ENABLE_DEBUG 1

#include "tools.h"
#include "sdcard.h"
#include "rtc.h"
#include "bmx280.h"

#define POWER_PIN PD2
#define RX_PIN PD0
#define TX_PIN PD1

#define BLINK_DURATION 25

void logData()
{
  PRINTLN("------------------------------------------");
  PRINTLN("Start log cycle...");

  File file = SD::createFile();
  if (!file)
  {
    return;
  }
  blink(BLINK_DURATION);

  DateTime date = RTC::getTime();
  if (!date.isValid())
  {
    return;
  }
  blink(BLINK_DURATION);

  BMX280::logData(&file, &date);

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
  out(LED_PIN);
  out(POWER_PIN);
  out(CS_PIN);
  power.autoCalibrate();
  blink(1000);
}

void loop()
{
#ifdef ENABLE_DEBUG
  uint16_t options = PWR_I2C | PWR_SPI | PWR_UART0 | PWR_TIMER0 | PWR_TIMER1;
#else
  uint16_t options = PWR_I2C | PWR_SPI | PWR_TIMER0 | PWR_TIMER1;
#endif
  power.hardwareEnable(options);
  PRINTLN("Enable power...");
  high(POWER_PIN);
  PRINTLN("Blink...");
  blink(BLINK_DURATION);
  logData();
  PRINTLN("Disabling power...");
  low(POWER_PIN);
  power.hardwareDisable(PWR_ALL);
  power.sleepDelay(60000);
}