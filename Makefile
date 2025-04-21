CC = gcc
CFLAGS = -Wall -Wextra -g

SRC := $(wildcard src/*.c)

TARGET = out/executable

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) $(TEST_TARGET)

