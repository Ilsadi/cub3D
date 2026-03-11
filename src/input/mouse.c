/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 09:05:30 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/11 16:25:05 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_vectors_from_angle(t_game *game)
{
	game->ray.dir_x = cos(game->player.angle);
	game->ray.dir_y = sin(game->player.angle);
	game->ray.plane_x = -game->ray.dir_y * 0.66;
	game->ray.plane_y = game->ray.dir_x * 0.66;
}

int	handle_mouse(int x, int y, t_game *game)
{
	int	diff_x;
	int	diff_y;

	diff_x = x - (WIDTH / 2);
	diff_y = y - (HEIGHT / 2);
	if (diff_x != 0)
	{
		game->player.angle += diff_x * MOUSE_SENSITIVITY;
		if (game->player.angle < 0)
			game->player.angle += 2 * M_PI;
		if (game->player.angle > 2 * M_PI)
			game->player.angle -= 2 * M_PI;
		update_vectors_from_angle(game);
	}
	if (diff_y != 0)
	{
		game->player.pitch -= diff_y;
		if (game->player.pitch > HEIGHT)
			game->player.pitch = HEIGHT;
		if (game->player.pitch < -HEIGHT)
			game->player.pitch = -HEIGHT;
	}
	mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}
