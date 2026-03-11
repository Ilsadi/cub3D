/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 09:23:50 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/11 14:12:19 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	in_mini_circle(int px, int py)
{
	int	dx;
	int	dy;

	dx = px - MINI_RAD;
	dy = py - MINI_RAD;
	return (dx * dx + dy * dy <= MINI_RAD * MINI_RAD);
}

void	mini_pixel(t_game *game, int sx, int sy, int color)
{
	if (sx < MINI_OFFSET || sy < MINI_OFFSET)
		return ;
	if (sx >= MINI_OFFSET + MINI_SIZE
		|| sy >= MINI_OFFSET + MINI_SIZE)
		return ;
	if (!in_mini_circle(sx - MINI_OFFSET, sy - MINI_OFFSET))
		return ;
	if (sx >= 0 && sx < WIDTH && sy >= 0 && sy < HEIGHT)
		put_pixel(&game->img, sx, sy, color);
}

static int	mini_is_wall(char c)
{
	return (c == '1' || c == 'D' || c == '2');
}

int	mini_is_visible(t_game *game, double dx, double dy)
{
	double	pos[2];
	double	d[2];
	int		steps;

	pos[0] = game->player.x;
	pos[1] = game->player.y;
	d[0] = dx - pos[0];
	d[1] = dy - pos[1];
	if (fabs(d[0]) > fabs(d[1]))
		steps = (int)(fabs(d[0]) * 10);
	else
		steps = (int)(fabs(d[1]) * 10);
	d[0] /= steps;
	d[1] /= steps;
	while (steps-- > 0)
	{
		if ((int)pos[1] >= 0 && (int)pos[1] < game->map.height
			&& (int)pos[0] >= 0 && (int)pos[0] < game->map.width
			&& mini_is_wall(game->map.grid[(int)pos[1]][(int)pos[0]]))
			return (0);
		pos[0] += d[0];
		pos[1] += d[1];
	}
	return (1);
}

int	get_tile_color(t_game *game, int x, int y)
{
	char	c;

	c = game->map.grid[y][x];
	if (c == '1')
		return (MINI_WALL);
	if (c == 'D')
		return (MINI_DOOR_C);
	if (c == '2')
		return (0x6A4C93);
	if (c != ' ')
		return (MINI_FLOOR);
	return (MINI_BG);
}
