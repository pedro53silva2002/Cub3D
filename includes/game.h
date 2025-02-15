#ifndef GAME_H
#define GAME_H

//Defines fo window creation
# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64
//Variables for debbuging
# define DEBUG 1
# define BypassParse 1
//end of it

//Defines for keypress
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define KEY_E 101
# define KEY_Q 113

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
	void *mlx;
	void *win;
	void *img;
	char *data;
	int bpp;
	int size_line;
	int endian;
	t_player player;
	void *texture_img[4];
	char *texture_data[4];
	int texture_width[4];
	int texture_height[4];
	int texture_bpp[4];
	int texture_size_line[4];
	int texture_endian[4];
	char **map;
	int map_width;
	int map_height;
	// RGB values for ceiling and floor colors
	int ceiling_r;
	int ceiling_g;
	int ceiling_b;
	int floor_r;
	int floor_g;
	int floor_b;

} t_game;

// Function declarations
//Draw
void	put_pixel(int x, int y, int color, t_game *game);
void	put_texture_pixel(int x, int y, int tex_x, int tex_y, t_game *game, int texture_index);
void	clear_image(t_game *game);
float	distance(float x, float y);
float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game);
bool	touch(float px, float py, t_game *game);
int		draw_loop(t_game *game);
int		determine_texture_index(t_game *game, int map_x, int map_y);
void	draw_line(t_player *player, t_game *game, float start_x, int i);
//Draw_debug
void	draw_square(int x, int y, int size, int color, t_game *game);
void	draw_map(t_game *game);

//Parsing
int		ft_check_path(char **tmp_map, int height);
int		ft_valid_file(char **argv);
int		ft_check_assets(char **argv);
int		ft_valid_map(char **argv);
int		ft_check(int argc, char **argv);
//Parsing_utils
int		ft_check_borders_horizontal(char **tmp_map, int height);
int		ft_check_borders_vertical(char **tmp_map, int height);
char	**ft_fill_design(char **argv);
int		ft_rowlen(char *file);
int		ft_checkfile(char *file);
//Parsing_utils2
int		ft_has_sides_and_colors(int *colors, int *sides);
int		ft_check_img(char *str);
void	ft_see_assets(int **colors, int **sides, char *str);
int		ft_check_colors(char *str);
int		ft_find_path(char **map, int x, int y);
//Parsing_utils3
int		ft_check_borders(char **tmp_map, int height);
int		ft_has_hole(char **map, int x, int y, int height);
int		ft_check_holes(char **map, int height);
int		ft_get_coor(char **tmp_map, char c);
int		ft_check_unkchr(char **map);

//Frees
void	ft_free_map(char **map);
void	ft_free_file(char *str, int fd);

//Main
char	**get_map(void);
void	init_game(t_game *game);
int		close_window(t_game *game);
int		handle_key(int key, t_game *game);
int		main(int argc, char **argv);

//Player
bool	is_wall(float x, float y, t_game *game);
void	init_player(t_player *player);
int		key_press(int keycode, t_player *player);
int		key_release(int keycode, t_player *player);
void 	move_player(t_player *player, t_game *game);

//Utils
char	*ft_strdupn(const char *str1);
int		ft_max_width(char **map);
#endif
