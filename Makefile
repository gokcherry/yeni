# Makefile

.PHONY: all compile connect run clean

all: compile connect run

compile:
	gcc -I ./include/ -o ./lib/BuzDeviGezegen.o   -c ./src/BuzDeviGezegen.c
	gcc -I ./include/ -o ./lib/CuceGezegen.o     -c ./src/CuceGezegen.c
	gcc -I ./include/ -o ./lib/GazDeviGezegen.o  -c ./src/GazDeviGezegen.c
	gcc -I ./include/ -o ./lib/KayacGezegen.o    -c ./src/KayacGezegen.c
	gcc -I ./include/ -o ./lib/Gezegen.o         -c ./src/Gezegen.c
	gcc -I ./include/ -o ./lib/Kisi.o            -c ./src/Kisi.c
	gcc -I ./include/ -o ./lib/Simulasyon.o      -c ./src/Simulasyon.c
	gcc -I ./include/ -o ./lib/UzayGemisi.o      -c ./src/UzayGemisi.c
	gcc -I ./include/ -o ./lib/Zaman.o           -c ./src/Zaman.c
	gcc -I ./include/ -o ./lib/DosyaOkuma.o      -c ./src/DosyaOkuma.c
	gcc -I ./include/ -o ./lib/Main.o            -c ./src/Main.c

connect:
	gcc -I ./include/ -o ./bin/program \
	  ./lib/BuzDeviGezegen.o \
	  ./lib/CuceGezegen.o \
	  ./lib/GazDeviGezegen.o \
	  ./lib/KayacGezegen.o \
	  ./lib/Gezegen.o \
	  ./lib/Kisi.o \
	  ./lib/Simulasyon.o \
	  ./lib/UzayGemisi.o \
	  ./lib/Zaman.o \
	  ./lib/DosyaOkuma.o \
	  ./lib/Main.o \
	  -lm

run:
	./bin/program

clean:
	rm -f ./lib/*.o ./bin/program
