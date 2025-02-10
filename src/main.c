#include "../includes/game.h"

/// @brief Puts a pixel of a specified color at the given coordinates in the game's image.
/// @param x The x-coordinate of the pixel.
/// @param y The y-coordinate of the pixel.
/// @param color The color of the pixel in hexadecimal format.
/// @param game A pointer to the game structure containing the image data.
void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	put_texture_pixel(int x, int y, int tex_x, int tex_y, t_game *game)
{
	int	color;
	int	tex_index;
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	tex_index = tex_y * game->texture_size_line + tex_x * game->texture_bpp / 8;
	color = *(int *)(game->texture_data + tex_index);
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

/// @brief Clears the game's image by setting all pixels to black.
/// @param game A pointer to the game structure containing the image data. 
void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}

/// @brief Draws a square of a specified size and color at the given coordinates in the game's image.
/// @param x The x-coordinate of the top-left corner of the square.
/// @param y The y-coordinate of the top-left corner of the square.
/// @param size The size of the square (length of one side).
/// @param color The color of the square in hexadecimal format.
/// @param game A pointer to the game structure containing the image data.
void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;

	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x, y + i, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + size, y + i, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y + size, color, game);
		i++;
	}
}

/// @brief Draws the map by iterating through the map array and drawing squares for each '1' character.
/// @param game A pointer to the game structure containing the map data.
void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		y;
	int		x;

	map = game->map;
	color = 0x0000FF;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
			x++;
		}
		y++;
	}
}

/// @brief Calculates the distance between two points using the Pythagorean theorem.
/// @param x The x-coordinate of the point.
/// @param y The y-coordinate of the point.
/// @return The distance between the point and the origin.
float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

/// @brief Calculates the fixed distance between two points, adjusted for the player's viewing angle.
/// @param x1 The x-coordinate of the first point.
/// @param y1 The y-coordinate of the first point.
/// @param x2 The x-coordinate of the second point.
/// @param y2 The y-coordinate of the second point.
/// @param game A pointer to the game structure containing the player's angle.
/// @return The fixed distance between the two points.
float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

/// @brief Checks if a point touches a wall in the map.
/// @param px The x-coordinate of the point.
/// @param py The y-coordinate of the point.
/// @param game A pointer to the game structure containing the map data.
/// @return True if the point touches a wall, false otherwise.
bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

/// @brief Generates a hardcoded map for the game.
/// @return A pointer to the generated map array.
char	**get_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 11);
	map[0] = "111111111111111";
	map[1] = "100000000000001";
	map[2] = "100000000000001";
	map[3] = "100000100000001";
	map[4] = "100000000000001";
	map[5] = "100000010000001";
	map[6] = "100001000000001";
	map[7] = "100000000000001";
	map[8] = "100000000000001";
	map[9] = "111111111111111";
	map[10] = NULL;
	return (map);
}

/// @brief Initializes the game structure, including the player, map, and graphics.
/// @param game A pointer to the game structure to be initialized.
void	init_game(t_game *game)
{
	init_player(&game->player);
	game->map = get_map();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);

	game->texture_img = mlx_xpm_file_to_image(game->mlx, "./textures/redbrick.xpm", &game->texture_width, &game->texture_height);
	game->texture_data = mlx_get_data_addr(game->texture_img, &game->texture_bpp, &game->texture_size_line, &game->texture_endian);

	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

/// @brief Draws a line representing a ray from the player's position to the first wall it hits.
/// @param player A pointer to the player structure containing the player's position and angle.
/// @param game A pointer to the game structure containing the map and image data.
/// @param start_x The starting x-coordinate of the ray.
/// @param i The index of the current ray being drawn.
// void	draw_line(t_player *player, t_game *game, float start_x, int i)
// {
// 	float	cos_angle;
// 	float	sin_angle;
// 	float	ray_x;
// 	float	ray_y;
// 	float	dist;
// 	float	height;
// 	int		start_y;
// 	int		end;

// 	cos_angle = cos(start_x);
// 	sin_angle = sin(start_x);
// 	ray_x = player->x;
// 	ray_y = player->y;
// 	while (!touch(ray_x, ray_y, game))
// 	{
// 		if (DEBUG)
// 			put_pixel(ray_x, ray_y, 0xFF0000, game);
// 		ray_x += cos_angle;
// 		ray_y += sin_angle;
// 	}
// 	if (!DEBUG)
// 	{
// 		dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
// 		height = (BLOCK / dist) * (WIDTH / 2);
// 		start_y = (HEIGHT - height) / 2;
// 		end = start_y + height;
// 		while (start_y < end)
// 		{
// 			put_pixel(i, start_y, 255, game);
// 			start_y++;
// 		}
// 	}
// }

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
    float	cos_angle;
    float	sin_angle;
    float	ray_x;
    float	ray_y;
    float	dist;
    float	height;
    int		start_y;
    int		end;
    int		tex_x;
    int		tex_y;
    float	step;
    float	tex_pos;

    cos_angle = cos(start_x);
    sin_angle = sin(start_x);
    ray_x = player->x;
    ray_y = player->y;
    while (!touch(ray_x, ray_y, game))
    {
        if (DEBUG)
            put_pixel(ray_x, ray_y, 0xFF0000, game);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
    if (!DEBUG)
    {
        dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
        height = (BLOCK / dist) * (WIDTH / 2);
        start_y = (HEIGHT - height) / 2;
        end = start_y + height;

        // Calculate tex_x based on the intersection point
        if (fabs(ray_x - floor(ray_x)) < fabs(ray_y - floor(ray_y)))
            tex_x = (int)(ray_x * game->texture_width) % game->texture_width;
        else
            tex_x = (int)(ray_y * game->texture_width) % game->texture_width;

        step = 1.0 * game->texture_height / height;
        tex_pos = (start_y - HEIGHT / 2 + height / 2) * step;
        while (start_y < end)
        {
            tex_y = (int)tex_pos & (game->texture_height - 1);
            tex_pos += step;
            put_texture_pixel(i, start_y, tex_x, tex_y, game);
            start_y++;
        }
    }
}

/// @brief Main drawing loop that updates the game state and renders the scene.
/// @param game A pointer to the game structure containing the game state and image data.
/// @return Always returns 0.
int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	player = &game->player;
	move_player(player);
	clear_image(game);
	if (DEBUG)
	{
		draw_square(player->x, player->y, 10, 0x00FF00, game);
		draw_map(game);
	}
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

/// @brief Closes the game window and exits the program.
/// @param game A pointer to the game structure containing the window data.
/// @return Always returns 0.
int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

/// @brief Handles key press events, specifically the ESC key to close the game.
/// @param key The key code of the pressed key.
/// @param game A pointer to the game structure.
/// @return Always returns 0.
int	handle_key(int key, t_game *game)
{
	if (key == 65307)
		close_window(game);
	return (0);
}

/// @brief The main function that initializes the game and starts the main loop.
/// @return Always returns 0.
int	main(void)
{
	t_game	game;

	init_game(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	//mlx_key_hook(game.win, handle_key, &game); //Bugs the movement
	mlx_loop(game.mlx);
	return (0);
}
