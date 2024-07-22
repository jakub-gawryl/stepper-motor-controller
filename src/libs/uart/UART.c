#include <avr/io.h>
#include <avr/interrupt.h>

void setBaud(unsigned long baud) {
  unsigned int ubrr = (F_CPU / 16 / baud) - 1;
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)(ubrr);
}

void usartInit(unsigned long baud) {
  // Set baud rate
  setBaud(baud);

  // Set frame format: 8-bit data, 2 stop bit
  UCSR0C = ( 1 << USBS0) | ( 3 << UCSZ00 );

  // Enable USART Receiver and Transmitter
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

  // RX Complete Interrupt Enable
  UCSR0B |= (1 << RXCIE0);
}

void setUSARTChar(unsigned char c) {
  // Wait for buffer to be empty - ready to be written
  while (!(UCSR0A & (1 << UDRE0)));

  UDR0 = c;
}

void setUSARTString(unsigned char* msgPtr) {
  while (*msgPtr != 0x00) {
    setUSARTChar(*msgPtr);
    msgPtr++;
  }
}