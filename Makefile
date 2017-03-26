SOURCES = atasgps.cpp main.cpp

default: all

all:
	g++ -std=c++11 $(SOURCES) -o atasservice -lgps

clean:
	-rm -f atasservice
