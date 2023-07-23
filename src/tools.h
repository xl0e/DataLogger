#include <Arduino.h>

#ifndef TOOLS_C
#define TOOLS_C

#define LED_PIN 3

#ifdef ENABLE_DEBUG
#define PRINT(...) Serial.print(__VA_ARGS__); Serial.flush();
#define PRINTLN(...) Serial.println(__VA_ARGS__); Serial.flush();
#else
#define PRINT(...) ;
#define PRINTLN(...) ;
#endif //ENABLE_DEBUG

void out(uint8_t pin)
{
  pinMode(pin, OUTPUT);
}

void high(uint8_t pin)
{
  digitalWrite(pin, HIGH);
}

void low(uint8_t pin)
{
  digitalWrite(pin, LOW);
}

void blink(uint32_t ms)
{
  high(LED_PIN);
  delay(ms);
  low(LED_PIN);
  delay(ms);
}

#endif // TOOLS_C