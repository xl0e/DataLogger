#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>

#include "tools.h"

namespace RTC
{
  RTC_DS3231 rtc;
  
  DateTime getTime()
  {
    DateTime date;
    PRINT("Connecting RTC... ");
    Wire.setTimeout(100);
    if (!rtc.begin())
    {
      PRINTLN("Couldn't find RTC");
      return date;
    }
    rtc.disable32K();
    date = rtc.now();
    if (!date.isValid())
    {
      PRINTLN("Error creating date");
      return date;
    }
    PRINTLN("DONE");
    return date;
  }

}