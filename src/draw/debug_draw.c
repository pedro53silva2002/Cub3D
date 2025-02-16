#include "../../includes/game.h"

bool	debug_touch(float px, float py, t_game *game)
{
	//debug print
	printf("[DEBUG] Entering debug_touch\n");
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

void	debug_put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	//debug print
	printf("[DEBUG] Entering debug_put_pixel\n");
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

// void debug_draw_line(t_player *player, t_game *game, float start_x, int i)
// {
// 	//debug print
// 	printf("[DEBUG] Entering debug_draw_line\n");
// 	float cos_angle;
// 	float sin_angle;
// 	float ray_x;
// 	float ray_y;
// 	float dist;
// 	float height;
// 	int start_y;
// 	int end;

// 	cos_angle = cos(start_x);
// 	sin_angle = sin(start_x);
// 	ray_x = player->x;
// 	ray_y = player->y;

// 	// Raycasting loop
// 	while (!debug_touch(ray_x, ray_y, game))
// 	{
// 		//debug print
// 		printf("[DEBUG] ray_x: %f, ray_y: %f\n", ray_x, ray_y);
// 		debug_put_pixel(ray_x, ray_y, 0xFF0000, game); // Draw the ray path in red
// 		ray_x += cos_angle;
// 		ray_y += sin_angle;
// 	}

// 	// Debug print to check if the ray hit something
// 	printf("[DEBUG] Ray hit at ray_x: %f, ray_y: %f\n", ray_x, ray_y);

// 	// Calculate distance and height
// 	dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
// 	height = (BLOCK / dist) * (WIDTH / 2);
// 	start_y = (HEIGHT - height) / 2;
// 	end = start_y + height;

// 	// Debug print to check calculated values
// 	printf("[DEBUG] dist: %f, height: %f, start_y: %d, end: %d\n", dist, height, start_y, end);

// 	// Draw the wall slice as a simple vertical line
// 	while (start_y < end)
// 	{
// 		debug_put_pixel(i, start_y, 0xFFFFFF, game); // Draw the wall slice in white
// 		start_y++;
// 	}
// }
void debug_draw_line(t_player *player, t_game *game, float start_x, int i)
{
	//debug print
	printf("[DEBUG] Entering debug_draw_line\n");
	float cos_angle;
	float sin_angle;
	float ray_x;
	float ray_y;
	float dist;
	float height;
	int start_y;
	int end;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = player->x;
	ray_y = player->y;

	// Raycasting loop
	while (!debug_touch(ray_x, ray_y, game))
	{
		//debug print
		printf("[DEBUG] ray_x: %f, ray_y: %f\n", ray_x, ray_y);
		debug_put_pixel(ray_x, ray_y, 0xFF0000, game); // Draw the ray path in red
		ray_x += cos_angle;
		ray_y += sin_angle;

		// Check if ray_x and ray_y are within the map boundaries
		if (ray_x < 0 || ray_x >= WIDTH || ray_y < 0 || ray_y >= HEIGHT)
		{
			printf("[DEBUG] Ray out of bounds: ray_x: %f, ray_y: %f\n", ray_x, ray_y);
			break;
		}
	}

	// Debug print to check if the ray hit something
	printf("[DEBUG] Ray hit at ray_x: %f, ray_y: %f\n", ray_x, ray_y);

	// Calculate distance and height
	dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
	height = (BLOCK / dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;

	// Debug print to check calculated values
	printf("[DEBUG] dist: %f, height: %f, start_y: %d, end: %d\n", dist, height, start_y, end);

	// Draw the wall slice as a simple vertical line
	while (start_y < end)
	{
		debug_put_pixel(i, start_y, 0xFFFFFF, game); // Draw the wall slice in white
		start_y++;
	}
}

/// @brief Draws a square of a specified size and color at the given coordinates in the game's image.
/// @param x The x-coordinate of the top-left corner of the square.
/// @param y The y-coordinate of the top-left corner of the square.
/// @param size The size of the square (length of one side).
/// @param color The color of the square in hexadecimal format.
/// @param game A pointer to the game structure containing the image data.
void	debug_draw_square(int x, int y, int size, int color, t_game *game)
{
	//Debug print
	printf("[DEBUG] Entering debug_draw_square\n");
	int	i;

	i = 0;
	while (i < size)
	{
		debug_put_pixel(x + i, y, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		debug_put_pixel(x, y + i, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		debug_put_pixel(x + size, y + i, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		debug_put_pixel(x + i, y + size, color, game);
		i++;
	}
	//Debug print
	printf("[DEBUG] Finished debug_draw_square\n");
}

/// @brief Draws the map by iterating through the map array and drawing squares for each '1' character.
/// @param game A pointer to the game structure containing the map data.
void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		y;
	int		x;

	//Debug print
	printf("[DEBUG] Entering draw_map\n");
	map = game->map;
	color = 0x0000FF;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				debug_draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
			x++;
		}
		y++;
	}
}
