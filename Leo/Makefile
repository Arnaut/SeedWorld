CC= gcc

CFLAGS= -g -Wall -Wextra -Werror -std=c99 -O3 `pkg-config --cflags sdl SDL_image` `pkg-config --cflags gtk+-3.0`
LDLIBS= -pthread -lpthread `pkg-config --libs sdl SDL_image` `pkg-config --libs gtk+-3.0`

user_interface: interface.o
	$(CC) -g -o interface.o -lm $(LDLIBS)

interface.o: interface.c
	$(CC)	$(CFLAGS)	-c interface.c

# remove object files and executable when user executes "make clean"
clean:
	rm *.o -f
