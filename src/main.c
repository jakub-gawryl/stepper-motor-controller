// define type of microprocessor
#define __AVR_ATmega328P__

// TODO - Change to 16000000UL and set fuse bits after connect 16MHz crystal!
#ifndef F_CPU
  #define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.c"

unsigned char ELO = 'A';

ISR(USART_RX_vect) {
  volatile unsigned char dummy;
  dummy = UDR0;
  PORTC ^= (1 << PC3); // ON pin 3
  cli();
}

int main() {
  usartInit(9600);
  setUSARTString("Hello world!\r\n");

  // Set port C as output
  DDRC = 0xFF;
  PORTC = 0xFF; // set all C ports to OFF

  volatile unsigned long i = 0;

  // Enable global interruption handling
  sei();

  while (1) {
    while (i < 100000) { i++; }
    PORTC &= ~(1 << PC2); // ON pin 2

    i = 0;

    while (i < 100000) { i++; }
    PORTC |= (1 << PC2); // OFF pin 2
    setUSARTChar('X');
    i = 0;
  }

  return 0;
}