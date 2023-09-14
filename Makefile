# Compiler and flags
CC = clang
CFLAGS = -std=c99 -I./inc -Wall -Werror -Wextra -pedantic -g

# Source files
SRC_DIR = ./src
SRC_FILES = main.c player.c sdl_graphics.c textures.c upng.c \
		geometry.c map.c ray_direction.c raycasting.c \
		sprite.c wall.c init_window.c destroy_window.c
SRCS = $(addprefix $(SRC_DIR)/,$(SRC_FILES))

# Object files
OBJ_DIR = ./obj
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Output executable
OUT = maze

# Libraries
LIBS = -lSDL2 -lm

# Build rule for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

build: $(OBJS)
	$(CC) $(OBJS) -o $(OUT) $(LIBS)

run: build
	clear
	./$(OUT)

clean:
	rm -rf $(OBJ_DIR) $(OUT)
