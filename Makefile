CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c99
SRCS = $(wildcard src/*.c src/araclar/*.c src/modeller/*.c src/simulasyon/*.c)
TARGET = uzay_simulasyon.exe

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(TARGET)
