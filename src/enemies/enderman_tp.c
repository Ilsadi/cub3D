/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enderman_tp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 13:35:13 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/08 18:56:04 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_tp_pos(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map.width
		|| y >= game->map.height)
		return (0);
	if (game->map.grid[y][x] != '0'
		&& game->map.grid[y][x] != 'M'
		&& game->map.grid[y][x] != 'K')
		return (0);
	return (1);
}

static int	has_clear_path(t_game *game, t_enderman *e,
	double tx, double ty)
{
	double	cx;
	double	cy;
	double	dist;
	int		steps;
	int		i;

	dist = sqrt(pow(tx - e->x, 2) + pow(ty - e->y, 2));
	steps = (int)(dist * 4);
	if (steps < 1)
		steps = 1;
	i = 0;
	while (i <= steps)
	{
		cx = e->x + (tx - e->x) * i / steps;
		cy = e->y + (ty - e->y) * i / steps;
		if (game->map.grid[(int)cy][(int)cx] == '1'
			|| game->map.grid[(int)cy][(int)cx] == 'D')
			return (0);
		i++;
	}
	return (1);
}

static int	try_tp_pos(t_game *game, t_enderman *e,
	int *pos, int range)
{
	double	dist;

	if (!is_valid_tp_pos(game, pos[0], pos[1]))
		return (0);
	dist = sqrt(pow(pos[0] - e->x, 2)
			+ pow(pos[1] - e->y, 2));
	if (dist > range || dist <= 0.5)
		return (0);
	if (!has_clear_path(game, e,
			pos[0] + 0.5, pos[1] + 0.5))
		return (0);
	e->x = pos[0] + 0.5;
	e->y = pos[1] + 0.5;
	return (1);
}

void	teleport_enderman(t_game *game, t_enderman *ender)
{
	int	range;
	int	attempts;
	int	pos[2];

	if (ender->is_angry)
		range = ENDER_RANGE_ANGRY;
	else
		range = ENDER_RANGE_NORMAL;
	attempts = 50;
	while (attempts-- > 0)
	{
		pos[0] = (int)ender->x
			+ (rand() % (range * 2 + 1)) - range;
		pos[1] = (int)ender->y
			+ (rand() % (range * 2 + 1)) - range;
		if (try_tp_pos(game, ender, pos, range))
			return ;
	}
}
