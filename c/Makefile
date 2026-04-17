CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic
TARGET = stats
SRC = stats.c

.PHONY: all run test clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	printf '5\n1 3 2 3 4\n' | ./$(TARGET)

clean:
	rm -f $(TARGET)
