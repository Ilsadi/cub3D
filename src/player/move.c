/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:43:13 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/10 14:03:49 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_player(t_game *game, double rot_speed)
{
	if (game->keys.left)
	{
		game->player.angle -= rot_speed;
		if (game->player.angle < 0)
			game->player.angle += 2 * M_PI;
	}
	if (game->keys.right)
	{
		game->player.angle += rot_speed;
		if (game->player.angle > 2 * M_PI)
			game->player.angle -= 2 * M_PI;
	}
	game->ray.dir_x = cos(game->player.angle);
	game->ray.dir_y = sin(game->player.angle);
	game->ray.plane_x = -game->ray.dir_y * 0.66;
	game->ray.plane_y = game->ray.dir_x * 0.66;
}

static void	calc_move(t_game *game, double spd, double *nx,
	double *ny)
{
	*nx = game->player.x;
	*ny = game->player.y;
	if (game->keys.w)
	{
		*nx += game->ray.dir_x * spd;
		*ny += game->ray.dir_y * spd;
	}
	if (game->keys.s)
	{
		*nx -= game->ray.dir_x * spd;
		*ny -= game->ray.dir_y * spd;
	}
	if (game->keys.a)
	{
		*nx += game->ray.dir_y * spd;
		*ny -= game->ray.dir_x * spd;
	}
	if (game->keys.d)
	{
		*nx -= game->ray.dir_y * spd;
		*ny += game->ray.dir_x * spd;
	}
}

static void	move_player(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	calc_move(game, move_speed, &new_x, &new_y);
	if (!is_wall(game, new_x, game->player.y))
		game->player.x = new_x;
	if (!is_wall(game, game->player.x, new_y))
		game->player.y = new_y;
}

void	update_player(t_game *game)
{
	double	speed;

	if (game->keys.shift && game->hud.food > 0)
		speed = SPRINT_SPEED;
	else
		speed = MOVE_SPEED;
	rotate_player(game, ROT_SPEED);
	move_player(game, speed);
}
