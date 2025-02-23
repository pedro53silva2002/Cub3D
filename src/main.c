#include "../includes/game.h"

/// @brief Generates a hardcoded map for the game.
/// @return A pointer to the generated map array.
char	**get_map(char **argv)
{
	char	**map;

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

/// @brief Initializes the game structure, including the player, map, and graphics.
/// @param game A pointer to the game structure to be initialized.
void	init_game(t_game *game, char **argv)
{
	game->map = get_map(argv);
	init_player(&game->player, game->map);
	game->map_width = 15; // Set the map width
	game->map_height = 10; // Set the map height
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);

	// Set ceiling and floor colors
	game->ceiling_r = 0;
	game->ceiling_g = 200;
	game->ceiling_b = 200;
	game->floor_r = 50;
	game->floor_g = 100;
	game->floor_b = 50;

	// Load textures
	game->texture_img[0] = mlx_xpm_file_to_image(game->mlx, "./textures/n.xpm", &game->texture_width[0], &game->texture_height[0]);
	game->texture_data[0] = mlx_get_data_addr(game->texture_img[0], &game->texture_bpp[0], &game->texture_size_line[0], &game->texture_endian[0]);
	game->texture_img[1] = mlx_xpm_file_to_image(game->mlx, "./textures/s.xpm", &game->texture_width[1], &game->texture_height[1]);
	game->texture_data[1] = mlx_get_data_addr(game->texture_img[1], &game->texture_bpp[1], &game->texture_size_line[1], &game->texture_endian[1]);
	game->texture_img[2] = mlx_xpm_file_to_image(game->mlx, "./textures/e.xpm", &game->texture_width[2], &game->texture_height[2]);
	game->texture_data[2] = mlx_get_data_addr(game->texture_img[2], &game->texture_bpp[2], &game->texture_size_line[2], &game->texture_endian[2]);
	game->texture_img[3] = mlx_xpm_file_to_image(game->mlx, "./textures/w.xpm", &game->texture_width[3], &game->texture_height[3]);
	game->texture_data[3] = mlx_get_data_addr(game->texture_img[3], &game->texture_bpp[3], &game->texture_size_line[3], &game->texture_endian[3]);

	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

/// @brief Closes the game window and exits the program.
/// @param game A pointer to the game structure containing the window data.
/// @return Always returns 0.
int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

/// @brief Handles key press events, specifically the ESC key to close the game.
/// @param key The key code of the pressed key.
/// @param game A pointer to the game structure.
/// @return Always returns 0.
int	handle_key(int key, t_game *game)
{
	if (key == 65307)
		close_window(game);
	return (0);
}

/// @brief The main function that initializes the game and starts the main loop.
/// @return Always returns 0.
int	main(int argc, char **argv)
{
	t_game game;

	if (!ft_check(argc, argv))
		return (0);
	ft_printf("It passed!\n");
	init_game(&game, argv);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}