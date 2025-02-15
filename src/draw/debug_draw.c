#include "../../includes/game.h"

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
