/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:20:17 by vafernan          #+#    #+#             */
/*   Updated: 2025/03/08 16:54:43 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			return (ft_perror("Error\nColors problem\n"), 0);
	}
	i = -1;
	while (++i <= 3)
	{
		if (!sides[i] || sides[i] != 1)
			return (ft_perror("Error\nSides problem\n"), 0);
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

void	ft_add_line(char *str, char ***map, int height)
{
	static int	i;
	
	//ft_printf("SECOND \t %d\n", i);
	(*map)[i] = ft_strdupn(str);
	i++;
	if (i == height)
		i = 0;
}

int	ft_find_player(char **tmp_map)
{
	int	i;
	int	j;
	int	result;

	i = -1;
	result = 0;
	while (tmp_map[++i])
	{
		j = -1;
		while (tmp_map[i][++j])
		{
			if (tmp_map[i][j] == 'N' || tmp_map[i][j] == 'S'
					|| tmp_map[i][j] == 'W' || tmp_map[i][j] == 'E')
				result += 1;
		}
	}
	return (result);
}

int	ft_is_color(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (ft_isdigit(str[i]))
			return (1);
	}
	return (0);
}
