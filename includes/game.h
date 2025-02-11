#ifndef GAME_H
#define GAME_H

//Variables for debbuging
# define DEBUG 0
# define BypassParse 1
//end of it

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64

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

// typedef struct s_game
// {
// 	void		*mlx;
// 	void		*win;
// 	void		*img;

// 	char		*data;
// 	int			bpp;
// 	int			size_line;
// 	int 		endian;
// 	t_player	player;

// 	void		*texture_img;
// 	char		*texture_data;
// 	int			texture_width;
// 	int			texture_height;
// 	int			texture_bpp;
// 	int			texture_size_line;
// 	int			texture_endian;
	
// 	char		**map;
// } t_game;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int 		bpp;
	int			size_line;
	int			endian;
	void		*texture_img[4];
	char		*texture_data[4];
	int			texture_width[4];
	int			texture_height[4];
	int			texture_bpp[4];
	int			texture_size_line[4];
	int			texture_endian[4];
	t_player	player;
	char		**map;
} t_game;

//main.c:
char	**get_map(void);
void	init_game(t_game *game);
int		close_window(t_game *game);
int		handle_key(int key, t_game *game);

//player.c:
void	init_player(t_player *player);
int		key_release(int keycode, t_player *player);
int		key_press(int keycode, t_player *player);
void	move_player(t_player *player);

//draw.c:
void	put_pixel(int x, int y, int color, t_game *game);
//void	put_texture_pixel(int x, int y, int tex_x, int tex_y, t_game *game);
void put_texture_pixel(int x, int y, int tex_x, int tex_y, t_game *game, int texture_index);
void	clear_image(t_game *game);
void	draw_square(int x, int y, int size, int color, t_game *game);
void	draw_map(t_game *game);
float	distance(float x, float y);
float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game);
bool	touch(float px, float py, t_game *game);
void	draw_line(t_player *player, t_game *game, float start_x, int i);
int		draw_loop(t_game *game);
#endif
