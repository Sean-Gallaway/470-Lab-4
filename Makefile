# Compiler and flags  -Wextra -std=c99
CC = gcc
CFLAGS = -Wall

# Source files
SRCS = SeanLibFS.c SeanTestfile.c

# Object files (automatically generated from source files)
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = Lab4

# Default target (run when you type 'make')
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .c files into .o files
%.o: %.c libFS.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets (not actual files)
# .PHONY: all clean
