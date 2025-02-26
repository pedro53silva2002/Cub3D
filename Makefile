NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_DIR = ./includes/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
LFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft
SRC =	src/main.c \
		src/init.c \
		src/player/player.c \
		src/player/player_move.c \
		src/frees.c \
		src/utils.c \
		src/parsing/parsing.c \
		src/parsing/parsing_utils.c \
		src/parsing/parsing_utils2.c \
		src/parsing/parsing_utils3.c \
		src/draw/draw.c \
		src/draw/draw_utils.c \
		src/draw/draw_line.c \
		src/draw/cast_ray.c \
		src/draw/determine_texture.c \
		src/draw/debug/debug_draw.c \
		src/draw/debug/debug_draw_utils.c \
		src/draw/debug/debug_draw_utils2.c
OBJ_DIR = obj
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@make -s -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS) $(LIBFT_FLAGS)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/player
	mkdir -p $(OBJ_DIR)/parsing
	mkdir -p $(OBJ_DIR)/draw
	mkdir -p $(OBJ_DIR)/draw/debug
$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@make clean -s -C $(MLX_DIR)
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all


valgrind: 
	/usr/bin/valgrind --leak-check=full -s --show-leak-kinds=all ./$(NAME) ./maps/good/hard_good.cub

download:
	@wget https://cdn.intra.42.fr/document/document/27195/minilibx-linux.tgz
	@tar -xzf minilibx-linux.tgz -C includes
	@rm minilibx-linux.tgz

.PHONY: all clean fclean re download