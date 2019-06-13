include ../Makefile.common
#include Makefile.feather-52840
include Makefile.feather-52832

SERIALPORT = $(shell ../find-serial-port $(USBVID) $(USBPID) || echo 'cant-find-serial-port')

APP = nrf52

all: $(BUILDDIR)/$(APP).ino.zip

flash: $(BUILDDIR)/$(APP).ino.zip $(SERIALPORT)
	adafruit-nrfutil dfu serial --package $(BUILDDIR)/$(APP).ino.zip -p $(SERIALPORT) -b 115200 -sb -t 1200

console:
	screen $(SERIALPORT) 115200

# Deps
nrf52.ino: i2c_ring_buffer.cpp state_machine.cpp log.h ../common/i2c_message.h

i2c_ring_buffer.cpp: i2c_ring_buffer.h

state_machine.cpp: state_machine.h
