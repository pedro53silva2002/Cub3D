#ifndef GAME_H
#define GAME_H

//Defines fo window creation
# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64
# define DEBUG 0

//Defines for keypress
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

# define PI 3.14159265359

#include "minilibx-linux/mlx.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct s_player
{
	float x;
	float y;
	float angle;

	bool key_up;
	bool key_down;
	bool key_left;
	bool key_right;

	bool left_rotate;
	bool right_rotate;
}   t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;

	char		*data;
	int			bpp;
	int			size_line;
	int 		endian;
	t_player	player;

	void		*texture_img;
	char		*texture_data;
	int			texture_width;
	int			texture_height;
	int			texture_bpp;
	int			texture_size_line;
	int			texture_endian;
	
	char		**map;
} t_game;

void init_player(t_player *player);
int key_release(int keycode, t_player *player);
int key_press(int keycode, t_player *player);
void move_player(t_player *player);
int	ft_check(int argc, char **argv);
void	ft_free_map(char	**map);
char	*ft_strdupn(const char *str1);
int	ft_max_width(char **map);
int ft_check_borders_horizontal(char **tmp_map, int height);
int ft_check_borders_vertical(char **tmp_map, int height);
char **ft_fill_design(char **argv);
int ft_rowlen(char *file);
int ft_checkfile(char *file);
void	ft_free_file(char *str, int fd);
int ft_has_sides_and_colors(int *colors, int *sides);
int	ft_check_img(char *str);
void ft_see_assets(int **colors, int **sides, char *str);
int ft_check_colors(char *str);
int ft_find_path(char **map, int x, int y);
int ft_check_borders(char **tmp_map, int height);
int ft_has_hole(char **map, int x, int y, int height);
int ft_check_holes(char **map, int height);
int ft_get_coor(char **tmp_map, char c);
int ft_check_unkchr(char **map);

#endif
