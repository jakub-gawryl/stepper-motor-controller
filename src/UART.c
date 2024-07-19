#include "ATMega328p.c"

#ifndef F_CPU
  #define F_CPU       16000000
#endif

void setBaud(unsigned long baud) {
  unsigned int ubrr = (F_CPU / 16 / baud) - 1;
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)(ubrr);
}

void usartInit(unsigned long baud) {
  // Set baud rate
  setBaud(baud);

  // Set parity bits (1 0   Enabled, even parity)
  UCSR0C |= (1 << 5);
  UCSR0C &= ~(1 << 4);

  // Set char size (8-bit)
  UCSR0C |= (1 << 2) | (1 << 1);

  // Enable USART
  UCSR0B |= (1 << 3);
  UCSR0B |= (1 << 4);
}

void setUSARTChar(unsigned char c) {
  // Wait for buffer be empty - ready to be written
  // TODO - maybe do it in async way?
  // can this slow stepper motor down?
  while ( !(UCSR0A & (1 << 5)));

  UDR0 = c;
}

void setUSARTString(unsigned char* msgPtr) {
  while (*msgPtr != 0x00) {
    setUSARTChar(*msgPtr);
    msgPtr++;
  }
}