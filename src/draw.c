#include "../includes/game.h"

/// @brief Puts a pixel of a color at the coordinates in the game's image.
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

/// @brief Puts a texture pixel at the given coordinates in the game's image.
/// @param x The x-coordinate of the pixel in the game's image.
/// @param y The y-coordinate of the pixel in the game's image.
/// @param tex_x The x-coordinate of the pixel in the texture.
/// @param tex_y The y-coordinate of the pixel in the texture.
/// @param game A ptr to the game struct containing the image and texture data.
void	put_texture_pixel(int x, int y, int tex_x, int tex_y, t_game *game, int texture_index)
{
	int		color;
	char	*texture_data;
	int		texture_bpp;
	int		texture_size_line;

	texture_data = game->texture_data[texture_index];
	texture_bpp = game->texture_bpp[texture_index];
	texture_size_line = game->texture_size_line[texture_index];
	color = *(int *)(texture_data + (tex_y * texture_size_line + tex_x * (texture_bpp / 8)));
	put_pixel(x, y, color, game);
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

/// @brief Draws a square of a specifc size and color at coords
/// in the game's image.
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

/// @brief Draws the map by iterating through the map array and drawing squares
/// for each '1' character.
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

/// @brief Calculates the distance between two points using Pythagorean theorem
/// @param x The x-coordinate of the point.
/// @param y The y-coordinate of the point.
/// @return The distance between the point and the origin.
float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

/// @brief Calculates the fixed distance between two points,
/// adjusted for the player's viewing angle.
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

/// @brief Draws a line representing a ray from the player's position
/// to the first wall it hits.
/// @param player A pointer to the player structure containing the player's
/// position and angle.
/// @param game A pointer to the game structure containing the map and image data.
/// @param start_x The starting x-coordinate of the ray.
/// @param i The index of the current ray being drawn.
/* Messy, I think it is drawing the textures based on player position and not map position */
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
// 	int		tex_x;
// 	int		tex_y;
// 	float	step;
// 	float	tex_pos;
// 	int		texture_index;

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
// 		// Determine the texture index based on the direction of the ray
// 		if (fabs(ray_x - floor(ray_x)) < fabs(ray_y - floor(ray_y)))
// 		{
// 			tex_x = (int)(ray_x * game->texture_width[0]) % game->texture_width[0];
// 			if (cos_angle > 0)
// 				texture_index = 0; // North texture
// 			else
// 				texture_index = 1; // South texture
// 		}
// 		else
// 		{
// 			tex_x = (int)(ray_y * game->texture_width[0]) % game->texture_width[0];
// 			if (sin_angle > 0)
// 				texture_index = 2; // East texture
// 			else
// 				texture_index = 3; // West texture
// 		}
// 		step = 1 * game->texture_height[texture_index] / height;
// 		tex_pos = (start_y - HEIGHT / 2 + height / 2) * step;
// 		while (start_y < end)
// 		{
// 			tex_y = (int)tex_pos & (game->texture_height[texture_index] - 1);
// 			tex_pos += step;
// 			put_texture_pixel(i, start_y, tex_x, tex_y, game, texture_index);
// 			start_y++;
// 		}
// 	}
// }

/* Not bad... */
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
	int		tex_y = 0; // Initialize to a default value
	int		texture_index = -1; // Initialize to an invalid value
	float	wall_x;
	int		map_x;
	int		map_y;

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

	// Debug: Log ray position
	//printf("Ray hit at: (%f, %f)\n", ray_x, ray_y);

	if (!DEBUG)
	{
		dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
		height = (BLOCK / dist) * (WIDTH / 2);
		start_y = (HEIGHT - height) / 2;
		end = start_y + height;

		// Debug: Log distance and height
		//printf("Distance: %f, Height: %f\n", dist, height);

		// Determine the map position of the wall
		map_x = (int)(ray_x / BLOCK);
		map_y = (int)(ray_y / BLOCK);

		// Debug: Log map position
		//printf("Map position: (%d, %d)\n", map_x, map_y);

		// Ensure map_x and map_y are within bounds
		if (map_x < 0 || map_x >= game->map_width || map_y < 0 || map_y >= game->map_height)
		{
			printf("Out of bounds: (%d, %d)\n", map_x, map_y);
			return;
		}

		// Determine the texture index based on the wall's position in the map
		if (game->map[map_y][map_x] == '1')
		{
			if (map_y > 0 && game->map[map_y - 1][map_x] == '0')
				texture_index = 0; // Top wall (red)
			else if (map_y < game->map_height - 1 && game->map[map_y + 1][map_x] == '0')
				texture_index = 1; // Bottom wall (blue)
			else if (map_x > 0 && game->map[map_y][map_x - 1] == '0')
				texture_index = 2; // Left wall (yellow)
			else if (map_x < game->map_width - 1 && game->map[map_y][map_x + 1] == '0')
				texture_index = 3; // Right wall (green)
			else
			{
				// Determine the texture index based on the direction of the ray
				if (fabs(ray_x - floor(ray_x)) < fabs(ray_y - floor(ray_y)))
				{
					wall_x = ray_y;
					if (cos_angle > 0)
						texture_index = 0; // North texture
					else
						texture_index = 1; // South texture
				}
				else
				{
					wall_x = ray_x;
					if (sin_angle > 0)
						texture_index = 2; // East texture
					else
						texture_index = 3; // West texture
				}
			}
		}

		// Debug: Log texture index
		//printf("Texture index: %d\n", texture_index);

		if (texture_index < 0 || texture_index >= 4)
		{
			printf("Invalid texture index: %d\n", texture_index);
			return;
		}

		wall_x = (fabs(ray_x - floor(ray_x)) < fabs(ray_y - floor(ray_y))) ? ray_y : ray_x;
		wall_x -= floor(wall_x);
		tex_x = (int)(wall_x * game->texture_width[texture_index]);
		if ((fabs(ray_x - floor(ray_x)) < fabs(ray_y - floor(ray_y)) && cos_angle > 0) ||
			(fabs(ray_x - floor(ray_x)) >= fabs(ray_y - floor(ray_y)) && sin_angle < 0))
		{
			tex_x = game->texture_width[texture_index] - tex_x - 1;
		}

		// Debug: Log texture coordinates
		//printf("Texture coordinates: (%d, %d)\n", tex_x, tex_y);

		while (start_y < end)
		{
			int d = (start_y * 256 - HEIGHT * 128 + height * 128);
			tex_y = ((d * game->texture_height[texture_index]) / height) / 256;

			// Clamp tex_y to valid range
			if (tex_y < 0)
				tex_y = 0;
			else if (tex_y >= game->texture_height[texture_index])
				tex_y = game->texture_height[texture_index] - 1;

			// Ensure tex_x is within bounds
			if (tex_x < 0 || tex_x >= game->texture_width[texture_index])
			{
				printf("Texture coordinates out of bounds: (%d, %d)\n", tex_x, tex_y);
				return;
			}

			int color = *(int *)(game->texture_data[texture_index] + (tex_y * game->texture_size_line[texture_index] + tex_x * (game->texture_bpp[texture_index] / 8)));
			put_pixel(i, start_y, color, game);
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
