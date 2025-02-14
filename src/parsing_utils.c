#include "../includes/game.h"

/// @brief Checks horizontal walls
/// @param tmp_map The map
/// @param height The map's height
/// @return Returns the length of the row
int ft_check_borders_horizontal(char **tmp_map, int height)
{
	size_t i;

	i = 0;
	while (tmp_map[0][i] && (tmp_map[0][i] == '1' || tmp_map[0][i] == ' ' || tmp_map[0][i] == '	'))
	{
		i++;
	}
	//ft_printf("Line1: %d\tLine2: %d\n", ft_strlen(tmp_map[0]), ft_strlen(tmp_map[1]));
	if (tmp_map[0][i])
		return (ft_printf("Border not closed (top).\n"), 0);
	i = 0;
	while (tmp_map[height - 1][i] && (tmp_map[height - 1][i] == '1' || tmp_map[height - 1][i] == ' ' || tmp_map[height - 1][i] == '	'))
	{
		i++;
	}
	if (tmp_map[height - 1][i])
		return (ft_printf("Border not closed (bottom).\n"), 0);
	return (1);
}

/// @brief Checks vertical walls
/// @param tmp_map The map
/// @param height The map's height
/// @return Returns the length of the row
int ft_check_borders_vertical(char **tmp_map, int height)
{
	size_t i;

	i = 0;
	while (tmp_map[i] && (tmp_map[i][0] == '1' 
		|| tmp_map[i][0] == ' ' || tmp_map[i][0] == '	'))
		i++;
	if (tmp_map[i] && tmp_map[i][0])
		return (ft_printf("Border not closed (left).\n"), 0);
	i = 0;
	while (i < (size_t)height)
	{
		if (!tmp_map[i] || (tmp_map[i] && (tmp_map[i][ft_strlen(tmp_map[i]) - 1] == '1' || tmp_map[i][ft_strlen(tmp_map[i]) - 1] == ' ' || tmp_map[i][ft_strlen(tmp_map[i]) - 1] == '	')))
			i++;
		else
			break ;
	}
	if (tmp_map[i] && tmp_map[i][ft_strlen(tmp_map[i]) - 1])
		return (ft_printf("Border not closed (right).\n"), 0);
	return (1);
}

/// @brief Puts the map in a variable
/// @param argv The arguments. -_-
/// @return Returns the map
char **ft_fill_design(char **argv)
{
	int fd;
	int i;
	char *str;
	char **map;

	// ft_printf("LEN: %d\n", ft_rowlen(argv[1]));
	map = malloc(sizeof(char *) * (ft_rowlen(argv[1]) + 1));
	i = 0;
	fd = open(argv[1], O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		if ((str[0] == '1' || str[0] == '0' || str[0] == ' '))
		{
			map[i] = ft_strdupn(str);
			i++;
		}
		free(str);
		str = get_next_line(fd);
	}
	map[i] = NULL;
	return (map);
}

/// @brief Sees the length of a row
/// @param file The path of the file
/// @return Returns the length of the row
int ft_rowlen(char *file)
{
	int fd;
	int i;
	char *str;

	i = 0;
	fd = open(file, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		// ft_printf("Some: %s", str);
		if ((str[0] == '1' || str[0] == '0' || str[0] == ' ' || str[0] == '	') /* && ft_strchr(str, '1') */)
			i++;
		free(str);
		str = get_next_line(fd);
	}
	return (i);
}

/// @brief Checks if the file ends with .cub
/// @param file The path to the file.
/// @return Returns 0 if doesn't end with curb else returns 1.
int ft_checkfile(char *file)
{
	char *str;
	char *filecpy;
	int len;

	str = ".cub";
	len = ft_strlen(file);
	filecpy = ft_substr(file, len - 4, 4);
	if (ft_strncmp(str, filecpy, 4) != 0)
	{
		free(filecpy);
		return (0);
	}
	free(filecpy);
	return (1);
}
