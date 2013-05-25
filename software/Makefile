# Name: Makefile
# Author: Severin Haas
# Copyright: Coffee-Licence (based on the beerware-licence)
# License: 
#    As long as you retain this notice you can do whatever you want
#    with this stuff. If we meet some day, and you think
#    this stuff is worth it, you can buy me a coffee in return.


DEVICE     = atmega328p
CLOCK      = 16000000
PROGRAMMER = -P usb -c usbasp
OBJECTS    = main.o usart.o ds18s20.o cmd_line.o pd_controller.o eeprom.o
#FUSES      = -U hfuse:w:0xd9:m -U lfuse:w:0x24:m
STANDARD   = -std=gnu99


# Tune the lines below only if you know what you are doing:

AVRDUDE = avrdude -p $(DEVICE) $(PROGRAMMER) 
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) $(STANDARD)

# symbolic targets:
all:	main.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i

#fuse:
#	$(AVRDUDE) $(FUSES)

clean:
	rm -f main.hex main.elf $(OBJECTS)

# file targets:
main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm:	main.elf
	avr-objdump -d main.elf

cpp:
	$(COMPILE) -E main.c
