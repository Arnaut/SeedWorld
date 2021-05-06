CC= gcc

CFLAGS= -B/usr/lib/x86_64-linux-gnu -g -Wall -Wextra -Werror -std=c99 -O3 `pkg-config --cflags sdl SDL_image` `pkg-config --cflags gtk+-3.0`
LDLIBS= -pthread -lpthread `pkg-config --libs sdl SDL_image` `pkg-config --libs gtk+-3.0`


SRC = interface.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

interface: interface.o

-include ${DEP}ls


# remove object files and executable when user executes "make clean"
clean:
	rm *.o -f
	rm *.d -f	
