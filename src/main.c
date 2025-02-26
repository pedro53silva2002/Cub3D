#include "../includes/game.h"

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
