#include "Arduino.h"

class STM32_TM1637
{
  public:
  STM32_TM1637( int clock, int data);
  void show(int numb_in);
  
  private:
  int numb_clock;
  int numb_data;
  bool writeValue(uint8_t value);
  void start(void);
  void stop(void);
  void write(uint8_t first, uint8_t second, uint8_t third, uint8_t fourth);
  
  
};
