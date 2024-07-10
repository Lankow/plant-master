#ifndef MOCK_ARDUINO_H
#define MOCK_ARDUINO_H

#include <cstdint>

typedef uint8_t uint8_t;
typedef uint16_t uint16_t;
typedef uint32_t uint32_t;

void pinMode(uint8_t pin, uint8_t mode)
{
}

void digitalWrite(uint8_t pin, uint8_t value)
{
}

int analogRead(uint8_t pin)
{
    return 0;
}

unsigned long millis()
{
    return 0;
}

#endif // MOCK_ARDUINO_H
