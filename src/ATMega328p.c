/**
 * Config of the ATMEGA328P microcontroller
 * 
 * author:  Jakub Gawryl
 * date:    17.07.2024
 * 
 * this is for educational process only - in real project avr-lib should be used instead!
 * 
 * Bit order:  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * 
 */

/**
 * 19.10.1 UDRn – USART I/O Data Register n
 */
#define     UDR0          *((volatile unsigned char*) 0xC6)

/**
 * 19.10.5 UBRRnL and UBRRnH – USART Baud Rate Registers
 */
#define     UBRR0H        *((volatile unsigned char*) 0xC5)
#define     UBRR0L        *((volatile unsigned char*) 0xC4)

/**
 * 19.10.2 UCSRnA – USART Control and Status Register n A
 * 
 * - bit 7    USART Receive Complete                        R
 * - bit 6    USART Transmit Complete                       R/W
 * - bit 5    USART Data Register Empty                     R
 * - bit 4    Frame Error                                   R
 * - bit 3    Data OverRun                                  R
 * - bit 2    USART Parity Error                            R
 * - bit 1    Double the USART Transmission Speed           R/W
 * - bit 0    Multi-processor Communication Mode            R/W
 */
#define     UCSR0A        *((volatile unsigned char*) 0xC0)

/**
 * 19.10.3 UCSR0B – USART Control and Status Register n B
 *
 * - bit 7    RX Complete Interrupt Enable 0                R/W
 * - bit 6    TX Complete Interrupt Enable 0                R/W
 * - bit 5    USART Data Register Empty Interrupt Enable 0  R/W
 * - bit 4    Receiver Enable 0                             R/W
 * - bit 3    Transmitter Enable 0                          R/W
 * - bit 2    Character Size 0 (UCSZ02)                     R/W
 * - bit 1    Receive Data Bit 8 0                          R
 * - bit 0    Transmit Data Bit 8 0                         R/W
 * 
 */
#define     UCSR0B        *((volatile unsigned char*) 0xC1)

/**
 * 19.10.4 UCSRnC – USART Control and Status Register n C
 * 
 * - bit 7:6  USART Mode Select
 *              0 0   Asynchronous USART
 *              0 1   Synchronous USART
 *              1 0   (Reserved)
 *              1 1   Master SPI (MSPIM)(1)
 * - bit 5:4  Parity Mode
 *              0 0   Disabled
 *              0 1   Reserved
 *              1 0   Enabled, even parity
 *              1 1   Enabled, odd parity
 * - bit 3    Stop Bit Select
 *              0   1-bit
 *              1   2-bit
 * - bit 2:1  Character Size - NOTE: The UCSZ01:0 bits combined with the UCSZ02 bit in UCSR0B
 *            sets the number of data bits (character size) | order: UCSZ02 UCSZ01 UCSZ00
 *              0 0 0   5-bit
 *              0 0 1   6-bit
 *              0 1 0   7-bit
 *              0 1 1   8-bit
 *              1 0 0   Reserved
 *              1 0 1   Reserved
 *              1 1 0   Reserved
 *              1 1 1   9-bit
 * - bit 0    Clock Polarity
 *              0   Rising XCKn edge [Output of TxD0 Pin] AND Falling XCKn edge [Input on RxD0 Pin]
 *              1   Falling XCKn edge [Output of TxD0 Pin] AND Rising XCKn edge [Input on RxD0 Pin]
 * 
 */
#define     UCSR0C        *((volatile unsigned char*) 0xC2)

/**
 * PORTD
 */
#define     DDRD          *((volatile unsigned char*) 0x2A)
#define     PORTD         *((volatile unsigned char*) 0x2B)