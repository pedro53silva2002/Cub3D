#include "../../includes/game.h"

void	rotate_player(t_game *game)
{
	float	angle_speed;

	angle_speed = 0.07;
	if (game->player.left_rotate)
		game->player.angle -= angle_speed;
	if (game->player.right_rotate)
		game->player.angle += angle_speed;
	if (game->player.angle > 2 * PI)
		game->player.angle = 0;
	if (game->player.angle < 0)
		game->player.angle = 2 * PI;
}

void	move_forward_backward(t_game *game, float cos_angle, float sin_angle,
	int speed)
{
	float	new_x;
	float	new_y;

	if (game->player.key_up)
	{
		new_x = game->player.x + cos_angle * speed;
		new_y = game->player.y + sin_angle * speed;
		if (!is_wall(new_x, new_y, game))
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	if (game->player.key_down)
	{
		new_x = game->player.x - cos_angle * speed;
		new_y = game->player.y - sin_angle * speed;
		if (!is_wall(new_x, new_y, game))
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
}

void	move_left_right(t_game *game, float cos_angle, float sin_angle,
	int speed)
{
	float	new_x;
	float	new_y;

	if (game->player.key_left)
	{
		new_x = game->player.x + sin_angle * speed;
		new_y = game->player.y - cos_angle * speed;
		if (!is_wall(new_x, new_y, game))
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	if (game->player.key_right)
	{
		new_x = game->player.x - sin_angle * speed;
		new_y = game->player.y + cos_angle * speed;
		if (!is_wall(new_x, new_y, game))
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
}

void	move_player(t_game *game)
{
	int		speed;
	float	cos_angle;
	float	sin_angle;

	speed = 6;
	rotate_player(game);
	cos_angle = cos(game->player.angle);
	sin_angle = sin(game->player.angle);
	move_forward_backward(game, cos_angle, sin_angle, speed);
	move_left_right(game, cos_angle, sin_angle, speed);
}

/// @brief Gets the direction the playes is gonna be watching.
/// @param map The map of the game
/// @return Returns the direction of the player
char	ft_get_dir(char **map)
{
	int		i;
	int		j;
	char	dir;

	i = -1;
	dir = 'o';
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'S' || map[i][j] == 'N'
					|| map[i][j] == 'E' || map[i][j] == 'W')
				dir = map[i][j];
		}
	}
	return (dir);
}
