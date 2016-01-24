CC=g++
CFLAGS=-c -Wall -O2
LDFLAGS=-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
SOURCES=kaboom.cpp wrog_lewy.cpp ladowaniezawartosci.cpp interfejs.cpp kamera.cpp gracz.cpp wrog.cpp animation.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=game

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o game
