CC=g++
CFLAGS=-c -g -m32
LDFLAGS=-m32
SOURCES=$(wildcard *.cpp)
OBJNOSERV=$(SOURCES:.cpp=.o)
OBJECTS=$(SOURCES:.cpp=.o) Server.o
EXECUTABLE=PLS

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
		$(CC) $(CFLAGS) $< -o $@

clean:
		rm $(OBJNOSERV) $(EXECUTABLE)
