#include <SPI.h>
#include <SdFat.h>

#include "tools.h"

#define FILE_NAME "log.txt"
#define CS_PIN 10

SdFat sd;

namespace SD
{

  bool begin()
  {
    return sd.begin(CS_PIN, SPI_FULL_SPEED);
  }

  File createFile(bool &createHeaders)
  {
    File logFile;
    PRINT("Connecting SD card... ");

    if (!begin())
    {
      PRINT("SD initialization failed!");
      return logFile;
    }

    PRINTLN("DONE");

    PRINT("Creating log file... ");

    if (!sd.exists(FILE_NAME))
    {
      createHeaders = true;
    }
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