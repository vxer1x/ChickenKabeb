# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Wunused-variable
LDFLAGS = -Llib -lraylib -lSDL2 -Llib -pthread -lgdi32 -lwinmm -lSDL2_net

# Source files and output
MAIN_FILE = src/main.c
OUT = bin/main.exe

ENTITY_SRC = src/entity/player.c src/entity/tile.c src/entity/entity.c src/entity/gun.c src/entity/enimy.c
LEVEL_SRC = src/level/level.c src/level/menu.c
GFX_SRC = src/gfx/texture.c src/gfx/camera.c
UTIL_SRC = src/util/aabb.c src/util/game.c src/util/network.c

SRC =  $(MAIN_FILE)  $(ENTITY_SRC)  $(LEVEL_SRC)  $(GFX_SRC) $(UTIL_SRC)

# Paths
INCLUDE_DIR = ./include
LIB_DIR = ./lib

# Build target
all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -L$(LIB_DIR) $(SRC) -o $(OUT) $(LDFLAGS)

# Clean target
clean:
	rm -f $(OUT)
