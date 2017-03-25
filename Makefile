SOURCES = atasgps.cpp main.cpp

default: all

all:
	g++ $(SOURCES) -o atasservice -lgps

clean:
	-rm -f atasservice
