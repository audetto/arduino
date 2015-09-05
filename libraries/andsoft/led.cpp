#include "led.h"

namespace AndSoft
{

  LED::LED(const uint8_t pin, const uint8_t high)
    : myPIN(pin)
    , myHIGH(high)
    , myPeriods(NULL)
    , mySize(0)
    , myIsFirstHigh(false)
    , myActive(false)
  {
  }

  void LED::setup()
  {
    pinMode(myPIN, OUTPUT);
  }

  void LED::loop()
  {
    if (myActive)
    {
      const unsigned long now = millis();
      if (now >= myNextWakeupTime)
      {
	++myPosition;
	if (myPosition == mySize)
	{
	  myPosition = 0;
	  myDigital = myIsFirstHigh ? myHIGH : 0;
	}
	else
	{
	  myDigital = myDigital ? 0 : myHIGH;
	}
	analogWrite(myPIN, myDigital);
	myNextWakeupTime += myPeriods[myPosition];
      }
    }
  }

  void LED::on()
  {
    myActive = false;
    analogWrite(myPIN, myHIGH);
  }

  void LED::off()
  {
    myActive = false;
    analogWrite(myPIN, 0);
  }

  void LED::setHigh(const uint8_t high)
  {
    myHIGH = high;
  }

  void LED::flash(unsigned long const * periods, const int size, const boolean isFirstHigh)
  {
    if (myActive && periods == myPeriods && size == mySize && myIsFirstHigh == isFirstHigh)
    {
      // nothing to do
      return;
    }

    myActive = size > 1;
    myDigital = isFirstHigh ? myHIGH : 0;
    analogWrite(myPIN, myDigital);

    if (myActive)
    {
      myPeriods = periods;
      mySize = size;
      myIsFirstHigh = isFirstHigh;

      const unsigned long now = millis();
      myPosition = 0;

      myNextWakeupTime = now + myPeriods[myPosition];
    }
  }


}
