#include "../../includes/game.h"

/// @brief Casts a ray from the player's position at a given angle until a wall is hit.
/// @param player Pointer to the player structure.
/// @param game Pointer to the game structure.
/// @param ray_angle The angle at which to cast the ray.
/// @param hit_x Pointer to store the x-coordinate where the ray hit a wall.
/// @param hit_y Pointer to store the y-coordinate where the ray hit a wall.
void cast_ray(t_player *player, t_game *game, float ray_angle, float *hit_x, float *hit_y)
{
	float cos_angle = cos(ray_angle);
	float sin_angle = sin(ray_angle);
	float rayX = player->x;
	float rayY = player->y;

	// Increment the ray until it touches a wall.
	while (!touch(rayX, rayY, game))
	{
		rayX += cos_angle;
		rayY += sin_angle;
	}
	*hit_x = rayX;
	*hit_y = rayY;
}

/// @brief Calculates the vertical dimensions of the wall slice.
/// @param game Pointer to the game structure.
/// @param player Pointer to the player structure.
/// @param hit_x The x-coordinate where the ray hit a wall.
/// @param hit_y The y-coordinate where the ray hit a wall.
/// @param start_y Pointer to store the starting y-coordinate of the wall slice.
/// @param end_y Pointer to store the ending y-coordinate of the wall slice.
/// @param perp_dist Pointer to store the perpendicular distance to the wall.
/// @param line_height Pointer to store the calculated height of the wall slice.
void calculate_wall_slice_dimensions(t_game *game, t_player *player, float hit_x, float hit_y,
									 int *start_y, int *end_y, float *perp_dist, float *line_height)
{
	// Calculate the perpendicular distance (avoids fish-eye effect)
	*perp_dist = fixed_dist(player->x, player->y, hit_x, hit_y, game);

	// Determine the height of the wall slice.
	*line_height = (BLOCK / (*perp_dist)) * (WIDTH / 2);

	// Calculate the starting and ending y positions for drawing the stripe.
	*start_y = (HEIGHT - *line_height) / 2;
	*end_y = *start_y + *line_height;
}

/// @brief Calculates the x-coordinate on the texture (the column to sample).
/// @param game Pointer to the game structure.
/// @param texture_index Index of the texture to use.
/// @param hit_x The x-coordinate where the ray hit a wall.
/// @param hit_y The y-coordinate where the ray hit a wall.
/// @return The x-coordinate (column) in the texture.
// int calculate_texture_x(t_game *game, int texture_index, float hit_x, float hit_y)
// {
// 	(void)game; // Mark game as unused if not needed

// 	if (texture_index == 0 || texture_index == 1) // North or South walls
// 		return (int)hit_x % BLOCK;
// 	else // East or West walls
// 		return (int)hit_y % BLOCK;
// }
int calculate_texture_x(t_game *game, int texture_index, float hit_x, float hit_y)
{
	(void)game; // Mark game as unused if not needed

	float wall_x;
	if (texture_index == 0 || texture_index == 1) // North/South walls
		wall_x = fmod(hit_x, BLOCK) / BLOCK; // Normalize hit_x to [0,1]
	else // East/West walls
		wall_x = fmod(hit_y, BLOCK) / BLOCK;

	return (int)(wall_x * game->texture_width[texture_index]); // Scale to texture width
}

/// @brief Draws a vertical stripe of the wall on the screen.
/// @param game Pointer to the game structure.
/// @param texture_index Index of the texture to sample.
/// @param tex_x The x-coordinate on the texture (column to sample).
/// @param start_y The starting y-coordinate on the screen for the wall slice.
/// @param end_y The ending y-coordinate on the screen for the wall slice.
/// @param screen_x The x-coordinate on the screen where this stripe is drawn.
/// @param line_height The height of the wall slice.
void draw_vertical_stripe(t_game *game, int texture_index, int tex_x,
						  int start_y, int end_y, int screen_x, float line_height)
{
	(void)line_height;
	for (int y = start_y; y < end_y; y++)
	{
		// Map the entire texture over the drawn stripe.
		int tex_y = ((y - start_y) * game->texture_height[texture_index]) / (end_y - start_y);

		// Optional: Clamp tex_y to be safe (usually not needed with this mapping).
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= game->texture_height[texture_index])
			tex_y = game->texture_height[texture_index] - 1;

		int color = *(int *)(game->texture_data[texture_index] +
							 (tex_y * game->texture_size_line[texture_index] +
							  tex_x * (game->texture_bpp[texture_index] / 8)));
		put_pixel(screen_x, y, color, game);
	}
}

/// @brief Casts a ray and draws the corresponding vertical wall stripe on the screen.
/// @param player Pointer to the player structure.
/// @param game Pointer to the game structure.
/// @param ray_angle The angle at which the ray is cast.
/// @param screen_x The x-coordinate on the screen where this stripe is drawn.
// void draw_line(t_player *player, t_game *game, float ray_angle, int screen_x)
// {
// 	float hit_x, hit_y;

// 	// 1. Cast the ray to get the hit coordinates.
// 	cast_ray(player, game, ray_angle, &hit_x, &hit_y);

// 	// 2. Calculate the dimensions of the wall slice (line height and vertical drawing range).
// 	int start_y, end_y;
// 	float perp_dist, line_height;
// 	calculate_wall_slice_dimensions(game, player, hit_x, hit_y, &start_y, &end_y, &perp_dist, &line_height);

// 	// 3. Determine which map cell was hit.
// 	int map_x = (int)(hit_x / BLOCK);
// 	int map_y = (int)(hit_y / BLOCK);

// 	// 4. Choose the correct texture based on the wall's surrounding.
// 	int texture_index = determine_texture_index(game, map_x, map_y);

// 	// 5. Calculate the x coordinate on the texture.
// 	int tex_x = calculate_texture_x(game, texture_index, hit_x, hit_y);

// 	// Draw the ceiling
// 	int ceiling_color = (game->ceiling_r << 16) | (game->ceiling_g << 8) | game->ceiling_b;
// 	for (int y = 0; y < start_y; y++)
// 	{
// 		put_pixel(screen_x, y, ceiling_color, game);
// 	}

// 	// Draw the vertical stripe on the screen using the calculated texture coordinates.
// 	draw_vertical_stripe(game, texture_index, tex_x, start_y, end_y, screen_x, line_height);

// 	// Draw the floor
// 	int floor_color = (game->floor_r << 16) | (game->floor_g << 8) | game->floor_b;
// 	for (int y = end_y; y < HEIGHT; y++)
// 	{
// 		put_pixel(screen_x, y, floor_color, game);
// 	}
// }

void draw_line(t_player *player, t_game *game, float ray_angle, int screen_x)
{
	float hit_x, hit_y;

	// 1. Cast the ray to get the hit coordinates.
	cast_ray(player, game, ray_angle, &hit_x, &hit_y);

	// 2. Calculate the dimensions of the wall slice (line height and vertical drawing range).
	int start_y, end_y;
	float perp_dist, line_height;
	calculate_wall_slice_dimensions(game, player, hit_x, hit_y, &start_y, &end_y, &perp_dist, &line_height);

	// 3. Determine which map cell was hit.
	int map_x = (int)(hit_x / BLOCK);
	int map_y = (int)(hit_y / BLOCK);

	// 4. Choose the correct texture based on the wall's surrounding and ray angle.
	// int texture_index = determine_texture_index(game, map_x, map_y, ray_angle);
	int texture_index = determine_texture_index(game, map_x, map_y);

	// 5. Calculate the x coordinate on the texture.
	int tex_x = calculate_texture_x(game, texture_index, hit_x, hit_y);

	// Draw the ceiling
	int ceiling_color = (game->ceiling_r << 16) | (game->ceiling_g << 8) | game->ceiling_b;
	for (int y = 0; y < start_y; y++)
	{
		put_pixel(screen_x, y, ceiling_color, game);
	}

	// Draw the vertical stripe on the screen using the calculated texture coordinates.
	draw_vertical_stripe(game, texture_index, tex_x, start_y, end_y, screen_x, line_height);

	// Draw the floor
	int floor_color = (game->floor_r << 16) | (game->floor_g << 8) | game->floor_b;
	for (int y = end_y; y < HEIGHT; y++)
	{
		put_pixel(screen_x, y, floor_color, game);
	}
}

