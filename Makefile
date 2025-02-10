SRCS            = 

SRCS_BONUS      = 

OBJS            = $(SRCS:.c=.o)

OBJS_BONUS            = $(SRCS_BONUS:.c=.o)

CC              = cc

RM              = rm -f

CFLAGS          =  -g -Wall -Wextra -Werror

LIBFT			= ./Libft/libft.a

LIBMLX			= ./minilibx-linux/libmlx_Linux.a

NAME            = cub3D

NAME_BONUS      = cub3D_bonus

all:            $(NAME)

bonus:            $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(LIBFT):	
	$(MAKE) -C ./Libft

$(LIBMLX):	
	$(MAKE) -C ./mlx_linux	

$(NAME):        $(OBJS) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) $(OBJS) $(LIBFT) $(LIBMLX)

$(NAME_BONUS):        $(OBJS_BONUS) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBFT) $(LIBMLX)	

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean:         clean
	$(RM) $(NAME) $(NAME_BONUS)

re:             fclean $(NAME) $(NAME_BONUS)

.PHONY:         all clean fclean re