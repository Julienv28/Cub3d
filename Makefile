NAME        = cub3D

SRC_DIR     = ./srcs
INC_DIR     = ./include
LIB_DIR     = ./libft
MLX_DIR     = ./mlx
MLX_LIB     = 	$(MLX_DIR)/libmlx_$(UNAME).a

LIB			= 	$(LIB_DIR)/libft.a

#=== SOURCES ===
SRC         =	$(SRC_DIR)/main.c \
				$(SRC_DIR)/init.c \
				$(SRC_DIR)/check.c \
				$(SRC_DIR)/utils.c \
				$(SRC_DIR)/init_mlx.c \
				$(SRC_DIR)/exit_prog/exit_error.c \
				$(SRC_DIR)/draw_map.c \
				$(SRC_DIR)/parsing/parsing_color_and_textures.c \
				$(SRC_DIR)/parsing/parsing_map.c \
				$(SRC_DIR)/parsing/playr_parse.c \
				$(SRC_DIR)/movement/handle_keypress.c \
				$(SRC_DIR)/RayCasting/cast.c \
				$(SRC_DIR)/RayCasting/draw_columns.c \
				$(SRC_DIR)/RayCasting/utils.c \
				$(SRC_DIR)/RayCasting/get_dist_from_player.c

OBJ         = 	${SRC:.c=.o}

# Détection du système d'exploitation
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
    INCLUDES    = -I/usr/include -I$(MLX_DIR)
    MLXFLAGS    = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
else ifeq ($(UNAME), Darwin) # macOS
    INCLUDES    = -I/opt/X11/include -I/opt/X11/include/X11 -I$(MLX_DIR)
    MLXFLAGS    = -L$(MLX_DIR) -lmlx -L/opt/X11/lib -lX11 -lXext -lm
else
    $(error Unsupported OS: $(UNAME))
endif

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIB_DIR) $(INCLUDES) 
MFLAGS      = $(MLXFLAGS)

all: $(NAME) $(LIB)

$(LIB):
	make -C $(LIB_DIR)

# Compiler MinilibX (attention à la version)
$(NAME): $(OBJ) $(LIB)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(MFLAGS) -L$(LIB_DIR) -lft -lm -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	rm -f $(OBJ)
	make clean -C $(MLX_DIR)
	make clean -C $(LIB_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
