CC	= g++
CFLAGS 	= -std=c++11 -DRASPBERRY_PI -DBCM2835_NO_DELAY_COMPATIBILITY
LIBS	= -lgps -lbcm2835
LIBDIR 	= lib

BUILDDIR := build
BINDIR := bin
SRCDIR	:= src
LIBDIR  := lib

INCLUDE = -I $(LIBDIR)

default: all

ini.o: $(LIBDIR)/inih/ini.c
	$(CC) $(CFLAGS) -c $(LIBDIR)/inih/ini.c $(INCLUDE) -o $(BUILDDIR)/ini.o

inireader.o: $(LIBDIR)/inih/INIReader.cpp
	$(CC) $(CFLAGS) -c $(LIBDIR)/inih/INIReader.cpp $(INCLUDE) -o $(BUILDDIR)/INIReader.o

raspi.o: $(LIBDIR)/raspi/raspi.cpp
	$(CC) $(CFLAGS) -c $(LIBDIR)/raspi/raspi.cpp $(INCLUDE) -o $(BUILDDIR)/raspi.o 	

radio.o: $(LIBDIR)/lmic/radio.c
	$(CC) $(CFLAGS) -c $(LIBDIR)/lmic/radio.c $(INCLUDE) -o $(BUILDDIR)/radio.o

oslmic.o:$(LIBDIR)/lmic/oslmic.c
	$(CC) $(CFLAGS) -c $(LIBDIR)/lmic/oslmic.c $(INCLUDE) -o $(BUILDDIR)/oslmic.o

lmic.o: $(LIBDIR)/lmic/lmic.c
	$(CC) $(CFLAGS) -c $(LIBDIR)/lmic/lmic.c $(INCLUDE) -o $(BUILDDIR)/lmic.o

hal.o: $(LIBDIR)/hal/hal.cpp
	$(CC) $(CFLAGS) -c $(LIBDIR)/hal/hal.cpp $(INCLUDE) -o $(BUILDDIR)/hal.o

aes.o: $(LIBDIR)/aes/lmic.c
	$(CC) $(CFLAGS) -c $(LIBDIR)/aes/lmic.c $(INCLUDE) -o $(BUILDDIR)/aes.o

atasgps.o: atasgps.cpp
	$(CC) $(CFLAGS) -c $(INCLUDE) $< -o  $(BUILDDIR)/atasgps.o

ataslora.o: ataslora.cpp
	$(CC) $(CFLAGS) -c $(INCLUDE) $< -o  $(BUILDDIR)/ataslora.o

atasbutton.o: atasbutton.cpp
	$(CC) $(CFLAGS) -c $(INCLUDE) $< -o  $(BUILDDIR)/atasbutton.o

atassound.o: atassound.cpp
	$(CC) $(CFLAGS) -c $(INCLUDE) $< -o  $(BUILDDIR)/atassound.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c $(INCLUDE) $< -o $(BUILDDIR)/main.o

base: ataslora.o atasgps.o atassound.o atasbutton.o main.o 
	$(CC) $(CFLAGS) $(BUILDDIR)/*.o $(LIBS) -o $(BINDIR)/atas-node

all: atassound.o atasbutton.o ataslora.o atasgps.o main.o raspi.o radio.o oslmic.o lmic.o hal.o aes.o ini.o inireader.o
	$(CC) $(CFLAGS) $(BUILDDIR)/*.o $(LIBS) -o $(BINDIR)/atas-node

clean:
	-rm -rf $(BUILDDIR)/*.o atas-node
