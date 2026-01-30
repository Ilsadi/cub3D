/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 09:21:48 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/30 09:45:18 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_direction(t_game *game)
{
	double	angle;

	angle = game->player.angle;
	game->player.pitch = 0;
	game->player.is_sprinting = 0;
	game->ray.dir_x = cos(angle);
	game->ray.dir_y = sin(angle);
	game->ray.plane_x = -sin(angle) * 0.66;
	game->ray.plane_y = cos(angle) * 0.66;
}

int	is_wall(t_game *game, double x, double y)
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
