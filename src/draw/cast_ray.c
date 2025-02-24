#include "../../includes/game.h"

void	init_ray(t_game *game, float ray_angle)
{
	game->ray.cos_angle = cos(ray_angle);
	game->ray.sin_angle = sin(ray_angle);
	game->ray.ray_x = game->player.x;
	game->ray.ray_y = game->player.y;
	game->ray.delta_x = game->ray.cos_angle;
	game->ray.delta_y = game->ray.sin_angle;
}

void	perform_ray_casting(t_game *game)
{
	while (1)
	{
		game->ray.ray_x += game->ray.delta_x;
		game->ray.ray_y += game->ray.delta_y;
		if (game->ray.ray_x < 0 || game->ray.ray_x >= game->map_width * BLOCK
			|| game->ray.ray_y < 0
			|| game->ray.ray_y >= game->map_height * BLOCK)
		{
			game->hit_info.hit_x = game->ray.ray_x;
			game->hit_info.hit_y = game->ray.ray_y;
			return ;
		}
		if (touch(game->ray.ray_x, game->ray.ray_y, game))
			break ;
	}
	game->hit_info.hit_x = game->ray.ray_x;
	game->hit_info.hit_y = game->ray.ray_y;
}

void	determine_hit_side(t_game *game)
{
	game->ray.cell_x = fmod(game->ray.ray_x, BLOCK);
	game->ray.cell_y = fmod(game->ray.ray_y, BLOCK);
	if (fabs(game->ray.cell_x - BLOCK / 2) > fabs(game->ray.cell_y - BLOCK / 2))
	{
		if (game->ray.delta_x > 0)
			game->hit_info.hit_side = HIT_WEST;
		else
			game->hit_info.hit_side = HIT_EAST;
	}
	else
	{
		if (game->ray.delta_y > 0)
			game->hit_info.hit_side = HIT_NORTH;
		else
			game->hit_info.hit_side = HIT_SOUTH;
	}
}

void	cast_ray(t_game *game, float ray_angle)
{
	init_ray(game, ray_angle);
	game->hit_info.hit_side = HIT_NONE;
	perform_ray_casting(game);
	determine_hit_side(game);
}
