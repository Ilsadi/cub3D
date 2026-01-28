/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:43:13 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/28 15:47:35 by amacaull         ###   ########.fr       */
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

static int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game->map.width
		|| map_y < 0 || map_y >= game->map.height)
		return (1);
	if (game->map.grid[map_y][map_x] == '1')
		return (1);
	return (0);
}

static void	move_forward_backward(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;
	double	margin;

	margin = 0.2;
	if (game->player.move_forward)
	{
		new_x = game->player.x + game->ray.dir_x * move_speed;
		new_y = game->player.y + game->ray.dir_y * move_speed;
		if (!is_wall(game, new_x + margin * (game->ray.dir_x > 0 ? 1 : -1),
				game->player.y))
			game->player.x = new_x;
		if (!is_wall(game, game->player.x,
				new_y + margin * (game->ray.dir_y > 0 ? 1 : -1)))
			game->player.y = new_y;
	}
	if (game->player.move_backward)
	{
		new_x = game->player.x - game->ray.dir_x * move_speed;
		new_y = game->player.y - game->ray.dir_y * move_speed;
		if (!is_wall(game, new_x - margin * (game->ray.dir_x > 0 ? 1 : -1),
				game->player.y))
			game->player.x = new_x;
		if (!is_wall(game, game->player.x,
				new_y - margin * (game->ray.dir_y > 0 ? 1 : -1)))
			game->player.y = new_y;
	}
}

static void	move_strafe(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;
	double	margin;

	margin = 0.2;
	if (game->player.move_left)
	{
		new_x = game->player.x - game->ray.plane_x * move_speed;
		new_y = game->player.y - game->ray.plane_y * move_speed;
		if (!is_wall(game, new_x - margin * (game->ray.plane_x > 0 ? 1 : -1),
				game->player.y))
			game->player.x = new_x;
		if (!is_wall(game, game->player.x,
				new_y - margin * (game->ray.plane_y > 0 ? 1 : -1)))
			game->player.y = new_y;
	}
	if (game->player.move_right)
	{
		new_x = game->player.x + game->ray.plane_x * move_speed;
		new_y = game->player.y + game->ray.plane_y * move_speed;
		if (!is_wall(game, new_x + margin * (game->ray.plane_x > 0 ? 1 : -1),
				game->player.y))
			game->player.x = new_x;
		if (!is_wall(game, game->player.x,
				new_y + margin * (game->ray.plane_y > 0 ? 1 : -1)))
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
