# Uzay Simulasyonu Derleyici

# Derleyici ve bayraklar
default: all

CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c99

# Kaynaklar ve hedef
SRCS = src/Main.c \
       src/araclar/DosyaOkuma.c \
       src/modeller/Kisi.c \
       src/modeller/CuceGezegen.c \
       src/modeller/GazDeviGezegen.c \
       src/modeller/Gezegen.c \
       src/modeller/Zaman.c \
       src/modeller/KayacGezegen.c \
       src/modeller/UzayGemisi.c \
       src/modeller/BuzDeviGezegen.c \
       src/simulasyon/Simulasyon.c

# Platforma göre .exe uzantısı ve temizleme komutları
ifeq ($(OS),Windows_NT)
    EXE_EXT = .exe
    RM = del /Q
    SEP = .\\
else
    EXE_EXT =
    RM = rm -f
    SEP = ./
endif

TARGET = uzay_simulasyon$(EXE_EXT)

# Default hedef: derle ve çalıştır (eğer parametre yoksa sadece derle)
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	$(RM) $(TARGET) *.o src\araclar\*.o src\modeller\*.o src\simulasyon\*.o

run: $(TARGET)
	$(SEP)$(TARGET) giris.txt 365

.PHONY: default all clean run