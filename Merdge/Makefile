CC= gcc

CFLAGS= -B/usr/lib/x86_64-linux-gnu -g -Wall -Wextra -Werror -std=c99 -O3 `pkg-config --cflags sdl SDL_image` `pkg-config --cflags gtk+-3.0`
LDLIBS= -pthread -lpthread `pkg-config --libs sdl SDL_image` `pkg-config --libs gtk+-3.0`

EXE = SeedWorld

SRC = gen.c interface.c Perlin.c pixel_operations.c
OBJ = ${SRC:.c=.o}

all: $(EXE)
$(EXE): $(OBJ)
	$(CC) $^ -o $@ $(LDLIBS)
	
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@


# remove object files and executable when user executes "make clean"
clean:
	rm -rf $(OBJ) $(EXE)

