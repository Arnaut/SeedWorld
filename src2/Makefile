CC= gcc

CFLAGS= -g -Wall -Wextra -Werror -std=c99 -O3 `pkg-config --cflags sdl SDL_image` `pkg-config --cflags gtk+-3.0`
LDLIBS= -pthread -lpthread -lm `pkg-config --libs sdl SDL_image` `pkg-config --libs gtk+-3.0`


SRC = main.c gen.c Perlin.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

main: main.o gen.o Perlin.o


-include ${DEP}ls


# remove object files and executable when user executes "make clean"
clean:
	rm *.o -f
	rm *.d -f
