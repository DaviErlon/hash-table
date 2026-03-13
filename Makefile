CC = gcc
TARGET = main
SRC = *.c

all:
	$(CC) -Wall -Wextra -std=c11 -O2 $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
