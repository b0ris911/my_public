###############################################################################
# Makefile for the project kitchen_v2
###############################################################################

## General Flags
PROJECT = kitchen_v2
MCU = atmega328p
TARGET = kitchen_v2.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -Os -std=gnu99 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=kitchen_v2.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = kitchen_v2.o alg.o din_ind.o eep_328.o hcsr.o ISR_timers.o kn1x.o kn2x.o led.o maintimer16.o messages.o ds18b20.o OWIcrc.o OWIIntFunc.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) kitchen_v2.hex kitchen_v2.eep kitchen_v2.lss size

## Compile
kitchen_v2.o: ../kitchen_v2.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

alg.o: ../alg.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

din_ind.o: ../din_ind.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

eep_328.o: ../eep_328.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

hcsr.o: ../hcsr.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ISR_timers.o: ../ISR_timers.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

kn1x.o: ../kn1x.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

kn2x.o: ../kn2x.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

led.o: ../led.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

maintimer16.o: ../maintimer16.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

messages.o: ../messages.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ds18b20.o: ../ds18b20.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

OWIcrc.o: ../OWIcrc.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

OWIIntFunc.o: ../OWIIntFunc.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) kitchen_v2.elf dep/* kitchen_v2.hex kitchen_v2.eep kitchen_v2.lss kitchen_v2.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

