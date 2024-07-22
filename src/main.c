#include <avr/io.h>
#include <avr/interrupt.h>
#include "libs/uart/UART.c"
#include "libs/twi/TWI.c"

/**
 * MCP 23017 for drive 3 MOTORS
 * 
 * Set BANK = 0
 * 
 * Bit order:
 * | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * 
 * ***** PORT A *****
 *    bit  MOTOR   A4988_PIN
 *    0    Y       MS1
 *    1    Y       MS2
 *    2    Y       MS3
 *    3    Y       !ENABLE
 *    4    Y       DIRECTION
 *    5    Z       !ENABLE
 *    6    Z       DIRECTION
 *    7    -       N/C
 * 
 * ***** PORT B *****
 *    bit  MOTOR   A2988_PIN
 *    0    Z       MS3
 *    1    Z       MS2
 *    2    Z       MS1
 *    3    X       DIRECTION
 *    4    X       !ENABLE
 *    5    X       MS3
 *    6    X       MS2
 *    7    X       MS1
 * 
 */

#define TEP_CONFIG_X        0b00000000
#define TWI_WRITE_ADDRESS   0b01001110
#define TWI_READ_ADDRESS    0b01001111

unsigned long MOTOR_X = 0b00010000;

ISR(USART_RX_vect) {
  volatile unsigned char dummy;
  dummy = UDR0;

  if  (dummy == 'd') {
    MOTOR_X ^= (1 << 3);
    twiSend(TWI_WRITE_ADDRESS, 0x15, MOTOR_X);   // PORT B
  }

  if  (dummy == '1') {
    MOTOR_X &= ~(1 << 5) & ~(1 << 6) & ~(1 << 7);
    twiSend(TWI_WRITE_ADDRESS, 0x15, MOTOR_X);
  }
  if  (dummy == '2') {
    MOTOR_X |= (1 << 7);
    MOTOR_X &= ~(1 << 5) & ~(1 << 6);
    twiSend(TWI_WRITE_ADDRESS, 0x15, MOTOR_X);
  }

  if  (dummy == '3') {
    MOTOR_X |= (1 << 6);
    MOTOR_X &= ~(1 << 5) & ~(1 << 7);
    twiSend(TWI_WRITE_ADDRESS, 0x15, MOTOR_X);
  }
  if  (dummy == '4') {
    MOTOR_X |= (1 << 6) | (1 << 7) ;
    MOTOR_X &= ~(1 << 5);
    twiSend(TWI_WRITE_ADDRESS, 0x15, MOTOR_X);
  }
  if  (dummy == '5') {
    MOTOR_X |=  (1 << 7) | (1 << 6) | (1 << 5);
    twiSend(TWI_WRITE_ADDRESS, 0x15, MOTOR_X);
  }

  if  (dummy == 's') {
    MOTOR_X ^= (1 << 4);
    twiSend(TWI_WRITE_ADDRESS, 0x15, MOTOR_X);
  }

  // PORTC ^= (1 << PC3); // ON pin 3
  
  cli();
}

int main() {
  usartInit(9600);
  setUSARTString("\r\nHello world!\r\n");

  volatile unsigned long i = 0;
  // Init i2c
  twiInit(400000);  // 400 kHz

  // Set pins as outputs
  twiSend(TWI_WRITE_ADDRESS, 0x00, 0x00);   // PORT A
  twiSend(TWI_WRITE_ADDRESS, 0x01, 0x00);   // PORT B

  // Enable global interruption handling
  sei();

  // Set port C as output
  DDRC |= (1 << PC2) | (1 << PC3);
  PORTC |= (1 << PC2); // OFF pin 2
  PORTC |= (1 << PC3); // OFF pin 3

  while (1) {
    while (i < 1000) { i++; }
    PORTC &= ~(1 << PC2); // ON pin 2
    PORTC |= (1 << PC2); // OFF pin 2
    // Set all pins from PORT A to high
    //twiSend(TWI_WRITE_ADDRESS, 0x15, (0xFF & (1 << 7)));

    i = 0;

    //while (i < 500) { i++; }
    //PORTC |= (1 << PC2); // OFF pin 2
    // Set all pins from PORT A to high
    // twiSend(TWI_WRITE_ADDRESS, 0x15, 0x00);
    // setUSARTChar('P');
    i = 0;
  }

  return 0;
}