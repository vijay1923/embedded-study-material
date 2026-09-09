# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Target executable name
TARGET = student_mgmt

# Object files
OBJS = main.o student.o

# Default rule
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Object file dependencies
main.o: main.c student.h
	$(CC) $(CFLAGS) -c main.c

student.o: student.c student.h
	$(CC) $(CFLAGS) -c student.c

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)
