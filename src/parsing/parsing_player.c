/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:13:07 by ilsadi            #+#    #+#             */
/*   Updated: 2026/03/08 19:15:04 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	get_start_angle(char c)
{
	if (c == 'N')
		return (3 * M_PI / 2);
	if (c == 'S')
		return (M_PI / 2);
	if (c == 'E')
		return (0);
	return (M_PI);
}

int	find_player(t_game *game)
{
	int		x;
	int		y;
	int		count;
	char	c;

	count = 0;
	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < (int)ft_strlen(game->map.grid[y]))
		{
			c = game->map.grid[y][x];
			if (c == 'N' || c == 'S'
				|| c == 'E' || c == 'W')
			{
				count++;
				game->player.x = x + 0.5f;
				game->player.y = y + 0.5f;
				game->player.angle = get_start_angle(c);
				game->map.grid[y][x] = '0';
			}
		}
	}
	return (count == 1);
}
