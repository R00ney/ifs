# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall
# LIFS is defined in path in bashrc for ifs library 
# -lm for math library

# the build target executable:
TARGET = sobel_kernels

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) $(TARGET).c -o $(TARGET) $(LIFS) -lm

clean:
	$(RM) $(TARGET)

	
#cc -g blur_conv.c -o blur_conv ${LIFS}
