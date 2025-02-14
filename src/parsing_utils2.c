#include "../includes/game.h"

/// @brief Checks if the colors and sides are correct
/// @param colors The colors to use on the map
/// @param sides The textures of the sides
/// @return Returns 0 if some check fails. Returns 1 if everything alright
int	ft_has_sides_and_colors(int *colors, int *sides)
{
	int	i;

	(void)colors;
	// ft_printf("NO: %d\tSO: %d\tWE: %d\tEA: %d\nF: %d\tC: %d\n", sides[0],sides[1],sides[2],sides[3], colors[0],colors[1]);
	i = -1;
	while (++i <= 1)
	{
		if (!colors[i] || colors[i] != 1)
			return (0);
	}
	i = -1;
	while (++i <= 3)
	{
		// ft_printf("Value: %d\n", sides[1]);
		if (!sides[i] || sides[i] != 1)
			return (0);
	}
	return (1);
}

/// @brief Checks if the images is correct
/// @param str The line with the image path
/// @return Returns 0 if some check fails. Returns 1 if everything alright
int	ft_check_img(char *str)
{
	char	**img;
	char	*xpm;

	img = ft_split(str, ' ');
	xpm = ft_substr(str, ft_strlen(str) - 5, 4);
	//ft_printf("FIRST\n");
	if (!ft_strncmp(img[1], ".xpm", 4))
		return (ft_free_map(img), free(xpm), 0);
	//ft_printf("Value: %s\t Bool: %d\n", img[1], ft_strcmp(img[1], ".xpm"));
	if (ft_strcmp(xpm, ".xpm"))
		return (ft_free_map(img), free(xpm), 0);
	//ft_printf("THIRD\n");
	return (ft_free_map(img), free(xpm), 1);
}

/// @brief Checks colors, sides and the image path
/// @param colors The colors to use on the map
/// @param sides The textures of the sides
/// @param str The line with the image path
/// @return Returns 0 if some check fails. Returns 1 if everything alright
void	ft_see_assets(int **colors, int **sides, char *str)
{
	if (!ft_strncmp(str, "NO", 2) && ft_check_img(str))
		sides[0][0] += 1;
	if (!ft_strncmp(str, "SO", 2) && ft_check_img(str))
		sides[0][1] += 1;
	if (!ft_strncmp(str, "WE", 2) && ft_check_img(str))
		sides[0][2] += 1;
	if (!ft_strncmp(str, "EA", 2) && ft_check_img(str))
		sides[0][3] += 1;
	if (!ft_strncmp(str, "F", 1))
		colors[0][0] += 1;
	if (!ft_strncmp(str, "C", 1))
		colors[0][1] += 1;
}

/// @brief Checks if the colors are correct
/// @param str The line with the colors path
/// @return Returns 0 if some check fails. Returns 1 if everything alright
int	ft_check_colors(char *str)
{
	char	**first_split;
	char	**second_split;
	int		i;

	i = -1;
	first_split = ft_split(str, ' ');
	second_split = ft_split(first_split[1], ',');
	if (!ft_strncmp(str, "F", 1) || !ft_strncmp(str, "C", 1))
	{
		while (second_split[++i])
		{
			if (ft_atoi(second_split[i]) > 255 || ft_atoi(second_split[i]) < 0)
			{
				if (second_split)
					ft_free_map(second_split);
				return (ft_free_map(first_split), 0);
			}
		}
	}
	if (first_split)
		ft_free_map(first_split);
	if (second_split)
		ft_free_map(second_split);
	return (1);
}

/// @brief Checks if the player has a good path (while the game doesn't have a end it doesn't do much)
/// @param map The map
/// @param x X coordinates
/// @param y Y coordinates
/// @return Returns 0 if it doesn't found nothing wrong and returns 1 if it founds something wrong
int	ft_find_path(char **map, int x, int y)
{
	static int	change;

	// ft_printf("POINT: %d\tCoor: %d/%d\n", change, x, y);
	if (change)
		return (1);
	if (!map[y][x])
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'F')
		return (0);
	map[y][x] = 'F';
	change = ft_find_path(map, x - 1, y);
	change = ft_find_path(map, x, y - 1);
	change = ft_find_path(map, x + 1, y);
	change = ft_find_path(map, x, y + 1);
	return (change);
}
