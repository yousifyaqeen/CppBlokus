CXX = clang++
CXXFLAGS =  -Wall -g -O2 -std=c++11 -Wno-deprecated-declarations
LDFLAGS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

TARGETS = blokus

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
