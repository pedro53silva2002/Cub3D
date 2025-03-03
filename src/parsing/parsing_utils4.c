#include "../../includes/game.h"

/// @brief Checks if the colors and sides are correct
/// @param colors The colors to use on the map
/// @param sides The textures of the sides
/// @return Returns 0 if some check fails. Returns 1 if everything alright
int	ft_has_sides_and_colors(int *colors, int *sides)
{
	int	i;

	i = -1;
	while (++i <= 1)
	{
		if (!colors[i] || colors[i] != 1)
			return (0);
	}
	i = -1;
	while (++i <= 3)
	{
		if (!sides[i] || sides[i] != 1)
			return (0);
	}
	return (1);
}

int	ft_strlens(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

int	ft_is_map(char *str)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	if (!str)
		return (0);
	while (str[++i] && str[i] != '\n')
	{
		if (str[i] != '1' && str[i] != '0'
			&& str[i] != ' ' && str[i] != 'W'
			&& str[i] != 'E' && str[i] != 'N'
			&& str[i] != 'S')
			return (0);
		if (str[i] == '1')
			check = 1;
	}
	if (!check)
		return (0);
	return (1);
}
