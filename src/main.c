#ifndef F_CPU
  #define F_CPU       16000000
#endif

#include <stdio.h>
#include <stddef.h>
#include "UART.c"

void main() {
  usartInit(57600);
  setUSARTString("Hello world!\r\n");
}