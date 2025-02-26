#include "../includes/game.h"

/// @brief Generates a hardcoded map for the game.
/// @return A pointer to the generated map array.
char **get_map(char **argv)
{
	char **map;

	if (BypassParse)
	{
		map = malloc(sizeof(char *) * 11);
		map[0] = "111111111111111";
		map[1] = "100000000000001";
		map[2] = "100100000000001";
		map[3] = "100000000000001";
		map[4] = "100000000000001";
		map[5] = "100000010000001";
		map[6] = "100000000000001";
		map[7] = "100000000001101";
		map[8] = "100000000000001";
		map[9] = "111111111111111";
		map[10] = NULL;
	}
	if (!BypassParse)
	{
		map = ft_fill_design(argv);
	}
	return (map);
}

char *ft_get_wall_path(char **argv, char *side)
{
	int fd;
	char *str;
	char **lines;
	char *path;

	path = "";
	lines = NULL;
	fd = open(argv[1], O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		if (!ft_strncmp(str, side, 2))
		{
			lines = ft_split(str, ' ');
			path = ft_substr(lines[1], 0, ft_strclen(lines[1], '\n'));
			return (ft_free_map(lines), path);
		}
		str = get_next_line(fd);
	}
	return (NULL);
}

int	ft_get_color(char **argv, char side, int pricol)
{
	int fd;
	char *str;
	char *dummy;
	char **lines;
	char **rgb;
	int color;

	color = 0;
	lines = NULL;
	rgb = NULL;
	fd = open(argv[1], O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		if (str[0] == side)
		{
			dummy = ft_strsdup(str);
			//ft_printf("STR: %s\n", dummy);
			lines = ft_split(dummy, ' ');
			//ft_printf("LINE: %s\n", lines[1]);
			rgb = ft_split(lines[1], ',');
			/* ft_printf("RGB: %s\n", rgb[0]);
			ft_printf("RGB: %s\n", rgb[1]); */
			//ft_printf("RGB: %s\n", rgb[2]);
			color = ft_atoi(rgb[pricol]);
			//ft_printf("NBR after: %d\n", color);
			return (ft_free_map(lines), ft_free_map(rgb), color);
		}
		str = get_next_line(fd);
	}
	return (color);
}

/// @brief Initializes the game structure, including the player, map, and graphics.
/// @param game A pointer to the game structure to be initialized.
void init_game(t_game *game, char **argv)
{
	game->map = get_map(argv);
	init_player(&game->player, game->map);
	game->map_width = ft_max_width(game->map);	 // Set the map width
	game->map_height = ft_max_height(game->map); // Set the map height
	ft_printf("W: %d\tH: %d\n", game->map_width, game->map_height);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);

	// Set wall paths
	game->path_north = ft_get_wall_path(argv, "NO");
	game->path_south = ft_get_wall_path(argv, "SO");
	game->path_west = ft_get_wall_path(argv, "WE");
	game->path_east = ft_get_wall_path(argv, "EA");

	// Set ceiling and floor colors
	game->ceiling_r = ft_get_color(argv, 'C', 0);
	game->ceiling_g = ft_get_color(argv, 'C', 1);
	game->ceiling_b = ft_get_color(argv, 'C', 2);
	game->floor_r = ft_get_color(argv, 'F', 0);
	game->floor_g = ft_get_color(argv, 'F', 1);
	game->floor_b = ft_get_color(argv, 'F', 2);
	ft_printf("FIRST\n");
	/* game->ceiling_r = 200;
	game->ceiling_g = 200;
	game->ceiling_b = 200;
	game->floor_r = 50;
	game->floor_g = 100;
	game->floor_b = 50; */
	/* ft_printf("NORTH: %s\n", game->path_north);
	ft_printf("SOUTH: %s\n", game->path_south);
	ft_printf("WEST: %s\n", game->path_west);
	ft_printf("EAST: %s\n", game->path_east); */
	// Load textures
	game->texture_img[0] = mlx_xpm_file_to_image(game->mlx, game->path_north, &game->texture_width[0], &game->texture_height[0]);
	game->texture_data[0] = mlx_get_data_addr(game->texture_img[0], &game->texture_bpp[0], &game->texture_size_line[0], &game->texture_endian[0]);
	game->texture_img[1] = mlx_xpm_file_to_image(game->mlx, game->path_south, &game->texture_width[1], &game->texture_height[1]);
	game->texture_data[1] = mlx_get_data_addr(game->texture_img[1], &game->texture_bpp[1], &game->texture_size_line[1], &game->texture_endian[1]);
	game->texture_img[2] = mlx_xpm_file_to_image(game->mlx, game->path_west, &game->texture_width[2], &game->texture_height[2]);
	game->texture_data[2] = mlx_get_data_addr(game->texture_img[2], &game->texture_bpp[2], &game->texture_size_line[2], &game->texture_endian[2]);
	game->texture_img[3] = mlx_xpm_file_to_image(game->mlx, game->path_east, &game->texture_width[3], &game->texture_height[3]);
	game->texture_data[3] = mlx_get_data_addr(game->texture_img[3], &game->texture_bpp[3], &game->texture_size_line[3], &game->texture_endian[3]);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}