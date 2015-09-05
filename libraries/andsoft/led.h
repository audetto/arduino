#pragma once

#include "Arduino.h"

namespace AndSoft
{

  class LED
  {
  public:
    LED(const uint8_t pin, const uint8_t high = 255);

    void setup();

    void loop();

    void on();

    void off();

    void flash(unsigned long const * periods, const int size, const bool isFirstHigh);

    void setHigh(const uint8_t high);

  private:

    const uint8_t myPIN;
    uint8_t myHIGH;

    unsigned long const * myPeriods;
    int mySize;
    uint8_t myIsFirstHigh;

    bool myActive;
    int myPosition;
    uint8_t myDigital;
    unsigned long myNextWakeupTime;
  };

}

// Local Variables:
// mode: c++
// End:
