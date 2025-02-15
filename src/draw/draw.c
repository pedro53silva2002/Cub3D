#include "../../includes/game.h"

/// @brief Puts a pixel of a specified color at the given coordinates in the game's image.
/// @param x The x-coordinate of the pixel.
/// @param y The y-coordinate of the pixel.
/// @param color The color of the pixel in hexadecimal format.
/// @param game A pointer to the game structure containing the image data.
void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	put_texture_pixel(int x, int y, int tex_x, int tex_y, t_game *game, int texture_index)
{
	int	color;
	int	tex_index;
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return;
	tex_index = tex_y * game->texture_size_line[texture_index] + tex_x * game->texture_bpp[texture_index] / 8;
	color = *(int *)(game->texture_data[texture_index] + tex_index);
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

/// @brief Calculates the distance between two points using the Pythagorean theorem.
/// @param x The x-coordinate of the point.
/// @param y The y-coordinate of the point.
/// @return The distance between the point and the origin.
float distance(float x, float y)
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

int	determine_texture_index(t_game *game, int map_x, int map_y)
{
	// Check the top neighbor
	if (map_y > 0 && game->map[map_y - 1][map_x] == '0')
		return (0); // north
	// Check the bottom neighbor
	else if (map_y < game->map_height - 1 && game->map[map_y + 1][map_x] == '0')
		return (1); // south
	// Check the left neighbor
	else if (map_x > 0 && game->map[map_y][map_x - 1] == '0')
		return (2); // west (left)
	// Check the right neighbor
	else if (map_x < game->map_width - 1 && game->map[map_y][map_x + 1] == '0')
		return (3); // east (right)
	// Default: if the wall is completely surrounded (should not happen with proper maps)
	return (0);
}

/// @brief Main drawing loop that updates the game screen.
/// @param game A pointer to the game structure.
/// @return Always returns 0.
int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	// Get a pointer to the player structure
	player = &game->player;
	move_player(player, game);
	clear_image(game);
	if (DEBUG)
	{
		draw_square(player->x, player->y, 10, 0x00FF00, game);
		draw_map(game);
	}
	// Calculate the angle increment for each ray
	fraction = PI / 3 / WIDTH;
	// Calculate the starting angle for the first ray
	start_x = player->angle - PI / 6;
	// Loop through each vertical stripe on the screen
	i = 0;
	while (i < WIDTH)
	{
		// Cast a ray and draw the corresponding vertical stripe
		draw_line(player, game, start_x, i);
		// Increment the angle for the next ray
		start_x += fraction;
		// Move to the next vertical stripe
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
