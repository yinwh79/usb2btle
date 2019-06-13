include ../Makefile.common
include Makefile.feather-m4
#include Makefile.trinket-m0

SERIALPORT = $(shell ../find-serial-port $(USBVID) $(USBPID) || echo cant-find-serial-port)

APP = samd

all: $(BUILDDIR)/$(APP).ino.bin

flash: $(BUILDDIR)/$(APP).ino.bin $(SERIALPORT)
	$(PKGDIR)/arduino/tools/bossac/1.8.0-48-gb176eee/bossac -R -e -w -v -o$(IMGOFFSET) -p$(SERIALPORT) $<

console:
	screen $(SERIALPORT) 115200
