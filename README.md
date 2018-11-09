# STM32duino-TM1637
ARDUINO STM32 TM1637 7 segment module


##Example
```arduino
#include "STM32_TM1637.h"
#define numb_clock  PB14
#define numb_data PB15

STM32_TM1637 numb(numb_clock,numb_data);

void setup()
{
}

void loop()
{
  numb.show(6543);
}
```
