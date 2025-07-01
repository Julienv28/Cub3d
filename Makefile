NAME        = cub3D

#=== Directories ===
SRC_DIR     = ./srcs
INC_DIR     = ./includes
LIB_DIR     = ./libft
MLX_DIR     = ./mlx
OBJ_DIR		= ./obj

#=== External Libraries ===
MLX_LIB     = 	$(MLX_DIR)/libmlx_$(UNAME).a
LIB			= 	$(LIB_DIR)/libft.a

#=== SOURCES ===
SRCS         =	$(SRC_DIR)/main.c \
				$(SRC_DIR)/init.c \
				$(SRC_DIR)/check.c \
				$(SRC_DIR)/load_map.c \
				$(SRC_DIR)/check_map.c \
				$(SRC_DIR)/utils.c \
				$(SRC_DIR)/init_mlx.c \
				$(SRC_DIR)/draw_minimap.c \
				$(SRC_DIR)/exit_prog/exit_error.c \
				$(SRC_DIR)/draw_map.c \
				$(SRC_DIR)/parsing/parsing_color_and_textures.c \
				$(SRC_DIR)/parsing/parsing_map.c \
				$(SRC_DIR)/parsing/playr_parse.c \
				$(SRC_DIR)/parsing/parse_line_textures.c \
				$(SRC_DIR)/movement/handle_keypress.c \
				$(SRC_DIR)/movement/handle_mouse_bonus.c \
				$(SRC_DIR)/RayCasting/cast.c \
				$(SRC_DIR)/RayCasting/draw_columns.c \
				$(SRC_DIR)/RayCasting/draw_columns_utils.c \
				$(SRC_DIR)/RayCasting/utils.c \
				$(SRC_DIR)/RayCasting/get_dist_from_player.c \
				$(SRC_DIR)/RayCasting/run_dda.c \
				$(SRC_DIR)/RayCasting/init_ray_data.c

#=== Object Files ===
OBJ         = 	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#=== Compiler & Flags ===
# Détection du système d'exploitation
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
    INCLUDES    = -I/usr/includes -I$(MLX_DIR)
    MLXFLAGS    = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
else ifeq ($(UNAME), Darwin) # macOS
    INCLUDES    = -I/opt/X11/includes -I/opt/X11/includes/X11 -I$(MLX_DIR)
    MLXFLAGS    = -L$(MLX_DIR) -lmlx -L/opt/X11/lib -lX11 -lXext -lm
else
    $(error Unsupported OS: $(UNAME))
endif

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIB_DIR) $(INCLUDES) 
LDFLAGS      = $(MLXFLAGS) -L$(LIB_DIR) -lft -lm

#=== Compilation Rules ===
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

#=== Build Targets ===

all: $(NAME)

$(LIB):
	make -C $(LIB_DIR)

# Compiler MinilibX (attention à la version)
$(NAME): $(OBJ) $(LIB)
	@echo "\033[0;33m\n==> Linking $(NAME)...\033[0m"
	@make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "\033[1;32m==> $(NAME) built successfully.\033[0m"

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

#=== Cleaning rules===
clean:
	@echo "\033[0;31m==> Cleaning object files...\033[0m"
	@rm -rf $(OBJ_DIR)
	@make clean -C $(MLX_DIR)
	@make clean -C $(LIB_DIR)
	@echo "\033[1;32m==> Clean complete.\033[0m"

fclean: clean
	@echo "\033[0;31m==> Removing executable $(NAME)...\033[0m"
	@rm -f $(NAME)
	@make -s -C $(LIB_DIR) fclean
	@echo "\033[1;32m==> Full clean complete.\033[0m"

re: fclean all

.PHONY: all clean fclean re
