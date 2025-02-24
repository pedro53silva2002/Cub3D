#include "../includes/game.h"

/// @brief Checks the path has a cornered path
/// @param tmp_map The map
/// @param height The map's height
/// @return Returns 0 if some check fails. Returns 1 if everything alright
int ft_check_path(char **tmp_map, int height)
{
	int x;
	int y;

	x = ft_get_coor(tmp_map, 'x');
	y = ft_get_coor(tmp_map, 'y');
	// ft_printf("Value: %d\n", ft_find_path(tmp_map,x ,y));
	if (!x && !y)
		return (ft_perror("Player not found."), 0);
	if (!ft_check_unkchr(tmp_map))
		return (ft_perror("Found an unknow character in the map."), 0);
	if (!ft_check_holes(tmp_map, height))
		return (ft_perror("Found a hole in your map."), 0);
	if (ft_find_path(tmp_map, x, y))
		return (ft_perror("Theres a missing wall."), 0);
	return (1);
}

/// @brief Checks if the path is valid
/// @param argv The arguments. -_-
/// @return Returns 0 if map's not valid else returns 1.
int ft_valid_file(char **argv)
{
	int fd;

	if (!ft_strncmp(argv[1], ".cub", 4))
		return (ft_perror("Must be something.cub"), 0);
	if (!ft_checkfile(argv[1]))
		return (ft_perror("The map must be .cub"), 0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_perror("Map not found"), 0);
	return (1);
}

/// @brief Checks if the assets likes images and colors of floor and ceiling exist and are correct
/// @param argv The arguments. -_-
/// @return Returns 0 if some check fails. Returns 1 if everything alright.
int ft_check_assets(char **argv)
{
	int fd;
	char *str;
	int *colors;
	int *sides;

	colors = malloc(sizeof(int) * 2);
	sides = malloc(sizeof(int) * 4);
	colors = ft_memset(colors, 0, sizeof(int) * 2);
	sides = ft_memset(sides, 0, sizeof(int) * 4);
	fd = open(argv[1], O_RDONLY);
	str = get_next_line(fd);
	while (str && (str[0] != '1' && str[0] != '0' && str[0] != ' '))
	{
		if (! (str))
			return (ft_free_file(str, fd), free(colors), free(sides), 0);
		ft_see_assets(&colors, &sides, str);
		free(str);
		str = get_next_line(fd);
	}
	if (str)
		ft_free_file(str, fd);
	close(fd);
	if (!ft_has_sides_and_colors(colors, sides))
		return (free(colors), free(sides), 0);
	return (free(colors), free(sides), 1);
}

/// @brief Sees if the map is valid
/// @param argv The arguments. -_-
/// @return Returns 0 if some checks fail. Returns 1 if everything alright.
int ft_valid_map(char **argv)
{
	char **tmp_map;
	int height;
	int width;

	tmp_map = ft_fill_design(argv);
	height = ft_rowlen(argv[1]);
	width = ft_max_width(tmp_map);
	//ft_printf("HEIGHT: %d\tWIDTH: %d\n", height, width);
	/* int i = -1;
	while (tmp_map[++i])
	{
		ft_printf("%s\n", tmp_map[i]);
	} */
	/* if (!ft_check_borders(tmp_map, height))
		return (ft_free_map(tmp_map), 0); */
	if (!ft_check_path(tmp_map, height))
		return (ft_free_map(tmp_map), 0);
	/* int i = -1;
	while (tmp_map[++i])
	{
		ft_printf("%s\n", tmp_map[i]);
	} */
	return (ft_free_map(tmp_map), 1);
}

/// @brief Calls all the checks functions to see if everything is ready for the game to start.
/// @param argc The number of arguments.
/// @param argv The arguments. -_-
/// @return Returns 0 if some checks fail. Returns 1 if everything alright.
int ft_check(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
		return (ft_perror("I need the executable and the map"), 0);
	if (!ft_valid_file(argv))
		return (0);
	if (!ft_check_assets(argv))
		return (ft_perror("Problems with assets"), 0);
	if (!ft_valid_map(argv))
		return (0);
	return (1);
}