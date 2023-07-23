#include <Arduino.h>
#include <Wire.h>
#include <microDS3231.h>


#include "tools.h"

struct date_time {
  String date;
  String time;
};

namespace RTC
{
  MicroDS3231 rtc;
  
  date_time getTime()
  {
    date_time dt;

    dt.date = rtc.getDateString();
    dt.time = rtc.getTimeString();

    return dt;
  }

}