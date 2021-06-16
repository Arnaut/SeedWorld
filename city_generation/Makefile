CC = gcc
CFLAGS = -Wall -Wextra
LDLIBS = -g

all: $(EXEC)

main: roads_gen.o name_gen.o house.o mat_to_img.o pixel_operation.o main.o 
main.o: main.c  roads_gen.h name_gen.h house.h mat_to_img.h pixel_operation.h
city_gen.o:  roads_gen.c roads_gen.h name_gen.c name_gen.h house.c house.h mat_to_img.c mat_to_img.h pixel_operation.c pixel_operation.h

.PHONY: clean

clean:
	${RM} *.o

mrproper: clean
	${RM} .exe
