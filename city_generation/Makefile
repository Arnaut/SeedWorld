CC = gcc
CFLAGS = -Wall -Wextra
LDLIBS = -g

all: $(EXEC)

main: city_gen.o main.o
main.o: main.c city_gen.h
city_gen.o: city_gen.c city_gen.h

.PHONY: clean

clean:
	${RM} *.o

mrproper: clean
	${RM} .exe
