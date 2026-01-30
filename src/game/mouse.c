/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 09:05:30 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/30 11:25:40 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_view(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

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

int	handle_mouse(int x, int y, t_game *game)
{
	int		delta_x;
	int		delta_y;
	double	sensitivity_x;
	double	sensitivity_y;

	sensitivity_x = 0.002;
	sensitivity_y = 1.0;
	delta_x = x - (WIDTH / 2);
	if (delta_x != 0)
		rotate_view(game, delta_x * sensitivity_x);
	delta_y = y - (HEIGHT / 2);
	if (delta_y != 0)
	{
		game->player.pitch -= delta_y * sensitivity_y;
		if (game->player.pitch > HEIGHT)
			game->player.pitch = HEIGHT;
		if (game->player.pitch < -HEIGHT)
			game->player.pitch = -HEIGHT;
	}
	mlx_mouse_move(game->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}
