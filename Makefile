# NAME = game
# CC = cc -Wall -Wextra -Werror
# OBJ = $(SRC:.c=.o)
# MLX_DIR = ./includes/minilibx-linux
# LFLAGS = -L./includes/minilibx-linux -lmlx -lXext -lX11 -lm -lz
# INCLUDES = includes/minilibx-linux/libmlx.a
# SRC = src/main.c src/player.c

# all: $(NAME)

# $(NAME): $(OBJ)
# 	@make -s -C $(MLX_DIR)
# 	$(CC) $(SRC) -o $(NAME) $(INCLUDES) $(LFLAGS)

# fclean:
# 	rm -f $(OBJ)
# 	rm -f $(NAME)
# 	@make clean -s -C includes/minilibx-linux

# re: fclean all

# download:
# 	@wget https://cdn.intra.42.fr/document/document/27195/minilibx-linux.tgz
# 	@tar -xzf minilibx-linux.tgz -C includes
# 	@rm minilibx-linux.tgz

# .PHONY: all clean fclean re bonus




# NAME = game
# CC = cc
# CFLAGS = -Wall -Wextra -Werror
# MLX_DIR = ./includes/minilibx-linux
# MLX = $(MLX_DIR)/libmlx.a
# LFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
# SRC = src/main.c src/player.c
# OBJ = $(SRC:.c=.o)

# all: $(NAME)

# $(NAME): $(OBJ)
# 	@make -s -C $(MLX_DIR)
# 	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	@make clean -s -C $(MLX_DIR)
# 	@rm -f $(OBJ)
# 	@rm -f $(NAME)

# fclean: clean
# 	@rm -f $(NAME)
# 	@rm -f $(OBJ)

# re: fclean all

# download:
# 	@wget https://cdn.intra.42.fr/document/document/27195/minilibx-linux.tgz
# 	@tar -xzf minilibx-linux.tgz -C includes
# 	@rm minilibx-linux.tgz

# .PHONY: all clean fclean re download


#Good before libft
# NAME = game
# CC = cc
# CFLAGS = -Wall -Wextra -Werror
# MLX_DIR = ./includes/minilibx-linux
# MLX = $(MLX_DIR)/libmlx.a
# LFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
# SRC = src/main.c src/player.c
# OBJ_DIR = obj
# OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

# all: $(NAME)

# $(NAME): $(OBJ)
# 	@make -s -C $(MLX_DIR)
# 	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)

# $(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(OBJ_DIR):
# 	mkdir -p $(OBJ_DIR)

# clean:
# 	@make clean -s -C $(MLX_DIR)
# 	@rm -rf $(OBJ_DIR)
# 	@rm -f $(NAME)

# fclean: clean
# 	@rm -f $(NAME)

# re: fclean all

# download:
# 	@wget https://cdn.intra.42.fr/document/document/27195/minilibx-linux.tgz
# 	@tar -xzf minilibx-linux.tgz -C includes
# 	@rm minilibx-linux.tgz

# .PHONY: all clean fclean re download

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = ./includes/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
LFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft
SRC =	src/main.c \
		src/player.c
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

download:
	@wget https://cdn.intra.42.fr/document/document/27195/minilibx-linux.tgz
	@tar -xzf minilibx-linux.tgz -C includes
	@rm minilibx-linux.tgz

.PHONY: all clean fclean re download