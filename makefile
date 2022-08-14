CC=g++ -g -Wall -ansi -pedantic -std=c99 # define the compiler to use
TARGET=exec_prog # define the name of the executable
SOURCES=main.cpp
LFLAGS=-lm

#define list of objects
OBJSC=$(SOURCES:.c=.o)
OBJS=$(OBJSC:.cpp=.o)

# the target is obtained linking all .o files
all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)

purge: clean
	rm -f $(TARGET)

clean:
	rm -f *.o
