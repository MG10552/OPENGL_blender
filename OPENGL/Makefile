INCDIRS = -I/usr/openwin/include -I/usr/local/include
LIBDIRS = -L/usr/openwin/lib -L/usr/local/lib      

CC = gcc
CFLAGS = -g $(INCDIRS)
LIBS = -lX11 -lglut -lGL -lGLU -lGLEW -lm
OBJECTS=$(SOURCES:.cpp=.o)
SOURCES = $(wildcard  *.c)
EXECUTABLE = $(patsubst %.c,%, $(wildcard  *.c))

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -f $(EXECUTABLE)
