/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:43:13 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/28 10:14:24 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_direction(t_game *game)
{
	double	angle;

	angle = game->player.angle;
	game->ray.dir_x = cos(angle);
	game->ray.dir_y = sin(angle);
	game->ray.plane_x = -sin(angle) * 0.66;
	game->ray.plane_y = cos(angle) * 0.66;
}

static void	move_forward_backward(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	if (game->player.move_forward)
	{
		new_x = game->player.x + game->ray.dir_x * move_speed;
		new_y = game->player.y + game->ray.dir_y * move_speed;
		game->player.x = new_x;
		game->player.y = new_y;
	}
	if (game->player.move_backward)
	{
		new_x = game->player.x - game->ray.dir_x * move_speed;
		new_y = game->player.y - game->ray.dir_y * move_speed;
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

static void	move_strafe(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	if (game->player.move_left)
	{
		new_x = game->player.x - game->ray.plane_x * move_speed;
		new_y = game->player.y - game->ray.plane_y * move_speed;
		game->player.x = new_x;
		game->player.y = new_y;
	}
	if (game->player.move_right)
	{
		new_x = game->player.x + game->ray.plane_x * move_speed;
		new_y = game->player.y + game->ray.plane_y * move_speed;
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

static void	rotate_player(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	if (game->player.rotate_left)
	{
		old_dir_x = game->ray.dir_x;
		game->ray.dir_x = game->ray.dir_x * cos(-rot_speed)
			- game->ray.dir_y * sin(-rot_speed);
		game->ray.dir_y = old_dir_x * sin(-rot_speed)
			+ game->ray.dir_y * cos(-rot_speed);
		old_plane_x = game->ray.plane_x;
		game->ray.plane_x = game->ray.plane_x * cos(-rot_speed)
			- game->ray.plane_y * sin(-rot_speed);
		game->ray.plane_y = old_plane_x * sin(-rot_speed)
			+ game->ray.plane_y * cos(-rot_speed);
	}
	if (game->player.rotate_right)
	{
		old_dir_x = game->ray.dir_x;
		game->ray.dir_x = game->ray.dir_x * cos(rot_speed)
			- game->ray.dir_y * sin(rot_speed);
		game->ray.dir_y = old_dir_x * sin(rot_speed)
			+ game->ray.dir_y * cos(rot_speed);
		old_plane_x = game->ray.plane_x;
		game->ray.plane_x = game->ray.plane_x * cos(rot_speed)
			- game->ray.plane_y * sin(rot_speed);
		game->ray.plane_y = old_plane_x * sin(rot_speed)
			+ game->ray.plane_y * cos(rot_speed);
	}
}

void	update_player(t_game *game)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.05;
	rot_speed = 0.03;
	move_forward_backward(game, move_speed);
	move_strafe(game, move_speed);
	rotate_player(game, rot_speed);
}
