/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:43:13 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/30 09:46:48 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_sign(double value)
{
	if (value > 0)
		return (1.0);
	return (-1.0);
}

static void	move_forward_backward(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;
	double	margin;
	double	sign_x;
	double	sign_y;

	margin = 0.2;
	sign_x = get_sign(game->ray.dir_x);
	sign_y = get_sign(game->ray.dir_y);
	if (game->player.move_forward)
	{
		new_x = game->player.x + game->ray.dir_x * move_speed;
		new_y = game->player.y + game->ray.dir_y * move_speed;
		if (!is_wall(game, new_x + margin * sign_x, game->player.y))
			game->player.x = new_x;
		if (!is_wall(game, game->player.x, new_y + margin * sign_y))
			game->player.y = new_y;
	}
	if (game->player.move_backward)
	{
		new_x = game->player.x - game->ray.dir_x * move_speed;
		new_y = game->player.y - game->ray.dir_y * move_speed;
		if (!is_wall(game, new_x - margin * sign_x, game->player.y))
			game->player.x = new_x;
		if (!is_wall(game, game->player.x, new_y - margin * sign_y))
			game->player.y = new_y;
	}
}

static void	move_strafe(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;
	double	margin;
	double	sign_x;
	double	sign_y;

	margin = 0.2;
	sign_x = get_sign(game->ray.plane_x);
	sign_y = get_sign(game->ray.plane_y);
	if (game->player.move_left)
	{
		new_x = game->player.x - game->ray.plane_x * move_speed;
		new_y = game->player.y - game->ray.plane_y * move_speed;
		if (!is_wall(game, new_x - margin * sign_x, game->player.y))
			game->player.x = new_x;
		if (!is_wall(game, game->player.x, new_y - margin * sign_y))
			game->player.y = new_y;
	}
	if (game->player.move_right)
	{
		new_x = game->player.x + game->ray.plane_x * move_speed;
		new_y = game->player.y + game->ray.plane_y * move_speed;
		if (!is_wall(game, new_x + margin * sign_x, game->player.y))
			game->player.x = new_x;
		if (!is_wall(game, game->player.x, new_y + margin * sign_y))
			game->player.y = new_y;
	}
}

static void	rotate_player(t_game *game, double rot_speed)
{
	double	old_dir;
	double	old_plane;
	double	cos_rot;
	double	sin_rot;

	if (game->player.rotate_left || game->player.rotate_right)
	{
		if (game->player.rotate_left)
			rot_speed = -rot_speed;
		cos_rot = cos(rot_speed);
		sin_rot = sin(rot_speed);
		old_dir = game->ray.dir_x;
		game->ray.dir_x = game->ray.dir_x * cos_rot - game->ray.dir_y * sin_rot;
		game->ray.dir_y = old_dir * sin_rot + game->ray.dir_y * cos_rot;
		old_plane = game->ray.plane_x;
		game->ray.plane_x = game->ray.plane_x * cos_rot
			- game->ray.plane_y * sin_rot;
		game->ray.plane_y = old_plane * sin_rot + game->ray.plane_y * cos_rot;
	}
}

void	update_player(t_game *game)
{
	double	current_speed;

	if (game->player.is_sprinting)
		current_speed = SPRINT_SPEED;
	else
		current_speed = MOVE_SPEED;
	move_forward_backward(game, current_speed);
	move_strafe(game, current_speed);
	rotate_player(game, ROT_SPEED);
}
