#include "../includes/game.h"

/// @brief Checks if a point is inside a wall in the map.
/// @param x The x-coordinate of the point.
/// @param y The y-coordinate of the point.
/// @param game A pointer to the game structure containing the map data.
/// @return True if the point is inside a wall, false otherwise.
bool	is_wall(float x, float y, t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / BLOCK);
	map_y = (int)(y / BLOCK);
	if (map_x < 0 || map_x >= game->map_width || map_y < 0
		|| map_y >= game->map_height)
		return (true);
	return (game->map[map_y][map_x] == '1');
}

/// @brief Initializes the player structure with default values.
/// @param player A pointer to the player structure to be initialized.
void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

/// @brief Handles key press events and updates the player's movement
//	and rotation flags.
/// @param keycode The key code of the pressed key.
/// @param player A pointer to the player structure.
/// @return Always returns 0.
int	key_press(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT || keycode == KEY_Q)
		player->left_rotate = true;
	if (keycode == RIGHT || keycode == KEY_E)
		player->right_rotate = true;
	return (0);
}

/// @brief Handles key release events and updates the player's movement
//	and rotation flags.
/// @param keycode The key code of the released key.
/// @param player A pointer to the player structure.
/// @return Always returns 0.
int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT || keycode == KEY_Q)
		player->left_rotate = false;
	if (keycode == RIGHT || keycode == KEY_E)
		player->right_rotate = false;
	return (0);
}

/// @brief Updates the player's position and angle based on the current
//	movement and rotation flags.
/// @param player A pointer to the player structure.
void	move_player(t_player *player, t_game *game)
{
	int		speed;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;
	float	new_x;
	float	new_y;

	speed = 3;
	angle_speed = 0.03;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	if (player->key_up)
	{
		new_x = player->x + cos_angle * speed;
		new_y = player->y + sin_angle * speed;
		if (!is_wall(new_x, new_y, game))
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
	if (player->key_down)
	{
		new_x = player->x - cos_angle * speed;
		new_y = player->y - sin_angle * speed;
		if (!is_wall(new_x, new_y, game))
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
	if (player->key_left)
	{
		new_x = player->x + sin_angle * speed;
		new_y = player->y - cos_angle * speed;
		if (!is_wall(new_x, new_y, game))
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
	if (player->key_right)
	{
		new_x = player->x - sin_angle * speed;
		new_y = player->y + cos_angle * speed;
		if (!is_wall(new_x, new_y, game))
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
}
