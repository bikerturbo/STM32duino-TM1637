
#include "STM32_TM1637.h"

STM32_TM1637::STM32_TM1637( int clock, int data)
{
  numb_clock = clock;
  numb_data  = data;
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);
  start();
  writeValue(0x8c);
  stop();
  // clear display
  write(0x00, 0x00, 0x00, 0x00);
}




bool STM32_TM1637::writeValue(uint8_t value)
{
  for(uint8_t i = 0; i < 8; i++)
  {
    digitalWrite(numb_clock, LOW);
    delayMicroseconds(5);
    digitalWrite(numb_data, (value & (1 << i)) >> i);
    delayMicroseconds(5);
    digitalWrite(numb_clock, HIGH);
    delayMicroseconds(5);
  }
  // wait for ACK
  digitalWrite(numb_clock,LOW);
  delayMicroseconds(5);
  pinMode(numb_data,INPUT);
  digitalWrite(numb_clock,HIGH);
  delayMicroseconds(5);
  bool ack = digitalRead(numb_data) == 0;
  pinMode(numb_data,OUTPUT);
  return ack;
}


void STM32_TM1637::start(void)
{
  digitalWrite(numb_clock,HIGH);//send start signal to TM1637
  digitalWrite(numb_data,HIGH);
  delayMicroseconds(5);
  digitalWrite(numb_data,LOW);
  digitalWrite(numb_clock,LOW);
  delayMicroseconds(5);
}

void STM32_TM1637::stop(void)
{
  digitalWrite(numb_clock,LOW);
  digitalWrite(numb_data,LOW);
  delayMicroseconds(5);

  digitalWrite(numb_clock,HIGH);
  digitalWrite(numb_data,HIGH);
  delayMicroseconds(5);
}


void STM32_TM1637::write(uint8_t first, uint8_t second, uint8_t third, uint8_t fourth)
{
  start();
  writeValue(0x40);
  stop();

  start();
  writeValue(0xc0);
  writeValue(first);
  writeValue(second);
  writeValue(third);
  writeValue(fourth);
  stop();
}



void STM32_TM1637::show(int numb_in)
{
  uint8_t digits[] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f };
  int numb = numb_in;
  byte num4 = (numb / 1) % 10;
  byte num3 = (numb / 10) % 10;
  byte num2 = (numb / 100) % 10;
  byte num1 = (numb / 1000) % 10;
  write(digits[num1], digits[num2] , digits[num3], digits[num4]);
}
