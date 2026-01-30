/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 09:21:48 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/30 17:25:06 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || y < 0)
		return (1);
	map_x = (int)x;
	map_y = (int)y;
	if (map_x >= game->map.width || map_y >= game->map.height)
		return (1);
	if (game->map.grid[map_y][map_x] == '1')
		return (1);
	if (game->map.grid[map_y][map_x] == '2')
		return (1);
	return (0);
}

void	init_player_direction(t_game *game)
{
	game->ray.dir_x = cos(game->player.angle);
	game->ray.dir_y = sin(game->player.angle);
	game->ray.plane_x = -game->ray.dir_y * 0.66;
	game->ray.plane_y = game->ray.dir_x * 0.66;
}
