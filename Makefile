TARGET = PSIDdumper
OBJS = main.o

CFLAGS = -G0 -Wall -O2
CXXFLAGS = $(CFLAGS)
ASFLAGS = $(CFLAGS)

LIBDIR =
LIBS = -lpspopenpsid

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = PSIDdumper
#PSP_EBOOT_PIC1 = PIC1.png
#PSP_EBOOT_ICON0 = ICON0.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
