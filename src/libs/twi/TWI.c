/**
 * TWI (aka i²c)
 */

#include <string.h>
#include <avr/io.h>

#define START           0x08
#define REPEATED_START  0x10
#define MT_SLA_ACK      0x18
#define MT_SLA_NACK     0x20
#define MT_DATA_ACK     0x28
#define MT_DATA_NACK    0x30
#define MR_SLA_ACK      0x40
#define MR_SLA_NACK     0x48
#define MR_DATA_ACK     0x50
#define MR_DATA_NACK    0x58
#define LOST_ARBTRTN    0x38

// TODO
int twiError(unsigned char msg[]) {
  setUSARTString("TWI ERROR\r\n");

  return 0;
}

void twiInit(unsigned long speed) {
  // Set period of SCL to TWBR register
  TWBR = ((F_CPU / speed) - 16) / 2;
}

int twiSend(unsigned char address, unsigned char reg, unsigned char value) {
  // start conndition
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);

  // Wait for TWINT flag set. This indicates that the START condition has been transmitted
  while (!(TWCR & (1 << TWINT)));
  if ((TWSR & 0xF8) != START) {
    return twiError(0x00);
  }

  // set the receiver address
  TWDR = address;

  // Send address
  TWCR = (1 << TWINT) | (1 << TWEN);

  // Wait for ACK
  while (!(TWCR & (1 << TWINT)));
  if ((TWSR & 0xF8) != MT_SLA_ACK) {
    return twiError(0x00);
  }



  // Send data
  // 1st byte - register
  TWDR = reg;
  TWCR = (1 << TWINT) | (1 << TWEN);

  // wait for ACK
  while (!(TWCR & (1 << TWINT)));

  // ** sec byte - value to set to reg
  TWDR = value;
  TWCR = (1 << TWINT) | (1 << TWEN);

  // wait for ACK
  while (!(TWCR & (1 << TWINT)));
  if ((TWSR & 0xF8)!= MT_DATA_ACK) {
    return twiError(0x00);
  }

  // Transmit STOP
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

  return 0;
}


void waitToSet(unsigned char ackSignal) {

}