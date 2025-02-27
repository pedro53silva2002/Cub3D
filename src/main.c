#include "../includes/game.h"

void	free_map(char **map)
{
	int i = 0;

	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

/// @brief Closes the game window and exits the program.
/// @param game A pointer to the game structure containing the window data.
/// @return Always returns 0.
int	close_window(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->texture_img[i])
			mlx_destroy_image(game->mlx, game->texture_img[i]);
		i++;
	}
	free(game->path_north);
	free(game->path_south);
	free(game->path_west);
	free(game->path_east);
	free_map(game->map);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
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
	t_game	game;

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
