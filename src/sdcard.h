#include <Arduino.h>
#include <SPI.h>
#include "SdFat.h"

#include "tools.h"

#define FILE_NAME "log.txt"
#define CS_PIN 10



namespace SD
{
  SdFat sd;

  File createFile()
  {
    File logFile;
    PRINT("Connecting SD card... ");
    high(CS_PIN);
    if (!sd.begin(CS_PIN, SPI_HALF_SPEED))
    {
      sd.initErrorPrint("SD Error:");
      return logFile;
    }
    PRINTLN("DONE");

    PRINT("Creating log file... ");
    logFile = sd.open(FILE_NAME, FILE_WRITE);
    if (!logFile)
    {
      PRINTLN("Error creating log file");
      return logFile;
    }
    PRINTLN("DONE");
    return logFile;
  }
}