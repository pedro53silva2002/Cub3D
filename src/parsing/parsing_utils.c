/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:20:04 by vafernan          #+#    #+#             */
/*   Updated: 2025/03/08 16:53:33 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

/// @brief Checks horizontal walls
/// @param tmp_map The map
/// @param height The map's height
/// @return Returns the length of the row
int	ft_check_borders_horizontal(char **tmp_map, int height)
{
	size_t	i;

	i = 0;
	if (!tmp_map[0] || !tmp_map[height - 1])
		return (0);
	while (tmp_map[0][i] && (tmp_map[0][i] == '1'
		|| tmp_map[0][i] == ' '
		|| tmp_map[0][i] == '	'))
	{
		i++;
	}
	if (tmp_map[0][i])
		return (0);
	i = 0;
	while (tmp_map[height - 1][i]
		&& (tmp_map[height - 1][i] == '1'
		|| tmp_map[height - 1][i] == ' '
		|| tmp_map[height - 1][i] == '	'))
	{
		i++;
	}
	if (tmp_map[height - 1][i])
		return (0);
	return (1);
}

/// @brief Checks vertical walls
/// @param tmp_map The map
/// @param height The map's height
/// @return Returns the length of the row
int	ft_check_borders_vertical(char **tmp_map, int height)
{
	size_t	i;

	i = 0;
	while (tmp_map[i] && (tmp_map[i][0] == '1'
		|| tmp_map[i][0] == ' ' || tmp_map[i][0] == '	'))
		i++;
	if (tmp_map[i] && tmp_map[i][0])
		return (0);
	i = 0;
	while (i < (size_t)height)
	{
		if (!tmp_map[i] || (tmp_map[i]
				&& (tmp_map[i][ft_strlen(tmp_map[i]) - 1] == '1'
				|| tmp_map[i][ft_strlen(tmp_map[i]) - 1] == ' '
			|| tmp_map[i][ft_strlen(tmp_map[i]) - 1] == '	')))
			i++;
		else
			break ;
	}
	if (tmp_map[i] && tmp_map[i][ft_strlen(tmp_map[i]) - 1])
		return (0);
	return (1);
}

/// @brief Puts the map in a variable
/// @param argv The arguments. -_-
/// @return Returns the map
char	**ft_fill_design(char **argv)
{
	int		fd;
	int		i;
	char	*str;
	char	**map;
	int		assets;

	map = malloc(sizeof(char *) * (ft_rowlen(argv[1]) + 1));
	assets = 0;
	fd = open(argv[1], O_RDONLY);
	str = get_next_line(fd);
	//ft_printf("Height: %d\n", ft_rowlen(argv[1]));
	while (str)
	{
		i = 0;
		//ft_printf("FIRST\n");
		while (str[i] == ' ')
			i++;
		if (assets == 6 && str[i] != '\n')
			ft_add_line(str, &map, ft_rowlen(argv[1]));	
		if ((str[i] == 'N' || str[i] == 'S' || str[i] == 'W' || str[i] == 'E' || str[i] == 'C' || str[i] == 'F'))
			assets++;
		free(str);
		str = get_next_line(fd);
	}
	map[ft_rowlen(argv[1])] = NULL;
	return (map);
}

/// @brief Sees the length of a row
/// @param file The path of the file
/// @return Returns the length of the row
int	ft_rowlen(char *file)
{
	int		fd;
	int		i;
	int		j;
	int		assets;
	char	*str;

	j = 0;
	assets = 0;
	fd = open(file, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		i = 0;
		while (str[i] == ' ')
			i++;
		if (assets == 6 && str[i] != '\n')
		{
			j++;	
			//ft_printf("STR: %s\t%d\n", str, j);
		}
		if ((str[i] == 'N' || str[i] == 'S' || str[i] == 'W' || str[i] == 'E' || str[i] == 'C' || str[i] == 'F'))
		{
			assets++;
			//ft_printf("ASSETS: %s\t%d\n", str, assets);	
		}
		free(str);
		str = get_next_line(fd);
	}
	return (j);
}

/// @brief Checks if the file ends with .cub
/// @param file The path to the file.
/// @return Returns 0 if doesn't end with curb else returns 1.
int	ft_checkfile(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4)
		return (0);
	if (ft_strncmp(file + len - 4, ".cub", 4) != 0)
		return (0);
	if (len > 4 && (file[len - 5] == '/' || file[len - 5] == ' '
			|| file[len - 5] == '\t'))
		return (0);
	return (1);
}
