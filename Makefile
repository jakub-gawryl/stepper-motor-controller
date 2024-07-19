CHIP := atmega328p
PROGRAMMER_ID := usbasp
AVRDUDE_CCMD := avrdude -v -c /etc/avrdude.conf -p ${CHIP} -c ${PROGRAMMER_ID}

default: build

dump:
	avr-gcc -S -Os -mmcu=atmega328p src/main.c -o dump.asm

build:
	avr-gcc -Os -mmcu=atmega328p src/main.c -o output && \
	avr-objcopy -O ihex -R .eeprom output output.hex

serial:
	sudo minicom -b 57600 -o -D /dev/ttyACM0

write:
	${AVRDUDE_CCMD} -U flash:w:output.hex:i

rfuse:
	${AVRDUDE_CCMD} -U lfuse:r:-:h

# Set fuses to use external 16MHz oscilator
set_ext_osc_fuses:
	${AVRDUDE_CCMD} -U lfuse:w:0xFF:m -U hfuse:w:0xD9:m -U efuse:w:0xFF:m
 
# Set fuses to use internal 8MHz oscilator (no divider)
set_int_osc_fuses:
	${AVRDUDE_CCMD} -U lfuse:w:0xE2:m -U hfuse:w:0xD9:m -U efuse:w:0xFF:m