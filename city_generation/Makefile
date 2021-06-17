CC = gcc
CFLAGS = -Wall -Wextra
LDLIBS = -g

all: $(EXEC)

main: roads_gen.o name_gen.o main.o 
main.o: main.c  roads_gen.h name_gen.h 
city_gen.o:  roads_gen.c roads_gen.h name_gen.c name_gen.h

.PHONY: clean

clean:
	${RM} *.o

mrproper: clean
	${RM} .exe
