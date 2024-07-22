# Settings

PROGRAMMER_ID		:= usbasp
AVRDUDE_CMD			:= avrdude -v -c /etc/avrdude.conf -p ${CHIP} -c ${PROGRAMMER_ID}
CHIP						:= atmega328p
CPU_SPEED 			:= 8000000UL

# Default command

default: build

# Main commands

build:
	@avr-gcc -Os -mmcu=atmega328p src/main.c -o output -D F_CPU=${CPU_SPEED} && \
	avr-objcopy -O ihex -R .eeprom output output.hex && \
	echo "Building DONE 👍"

write:
	${AVRDUDE_CMD} -U flash:w:output.hex:i

rfuse:
	${AVRDUDE_CMD} -U lfuse:r:-:h

# Set fuses to use external 16MHz oscilator
set_ext_osc_fuses:
	${AVRDUDE_CMD} -U lfuse:w:0xFF:m -U hfuse:w:0xD9:m -U efuse:w:0xFF:m
 
# Set fuses to use internal 8MHz oscilator (no divider)
set_int_osc_fuses:
	${AVRDUDE_CMD} -U lfuse:w:0xE2:m -U hfuse:w:0xD9:m -U efuse:w:0xFF:m


# Other commands
dump:
	avr-gcc -S -Os -mmcu=atmega328p src/main.c -o dump.asm

serial:
	sudo minicom -b 57600 -o -D /dev/ttyACM0