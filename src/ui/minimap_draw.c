/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 16:45:30 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/11 14:15:17 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_mini_bg(t_game *game)
{
	int	px;
	int	py;

	py = -1;
	while (++py < MINI_SIZE)
	{
		px = -1;
		while (++px < MINI_SIZE)
		{
			if (in_mini_circle(px, py))
				put_pixel(&game->img, MINI_OFFSET + px,
					MINI_OFFSET + py, MINI_BG);
		}
	}
}

static void	draw_tile_pixels(t_game *game, int sx,
	int sy, int color)
{
	int	px;
	int	py;
	int	tile_sz;

	tile_sz = (int)MINI_PPT + 1;
	py = -1;
	while (++py < tile_sz)
	{
		px = -1;
		while (++px < tile_sz)
			mini_pixel(game, sx + px, sy + py, color);
	}
}

static int	tile_vis_color(t_game *game, int tx, int ty)
{
	double	dist;
	int		color;

	if (tx < 0 || tx >= game->map.width
		|| ty < 0 || ty >= game->map.height)
		return (MINI_BG);
	dist = sqrt(pow(game->player.x - tx - 0.5, 2)
			+ pow(game->player.y - ty - 0.5, 2));
	if (dist >= VIS_RANGE
		|| !mini_is_visible(game, tx + 0.5, ty + 0.5))
		return (MINI_BG);
	color = get_tile_color(game, tx, ty);
	return (apply_shading(color, dist / 1.3));
}

void	draw_mini_tiles(t_game *game)
{
	int	tx;
	int	ty;
	int	cx;
	int	cy;
	int	range;

	cx = MINI_OFFSET + MINI_RAD;
	cy = MINI_OFFSET + MINI_RAD;
	range = (int)MINI_VIEW + 1;
	ty = (int)game->player.y - range - 1;
	while (++ty <= (int)game->player.y + range)
	{
		tx = (int)game->player.x - range - 1;
		while (++tx <= (int)game->player.x + range)
		{
			draw_tile_pixels(game,
				cx + (int)((tx - game->player.x)
					* MINI_PPT),
				cy + (int)((ty - game->player.y)
					* MINI_PPT),
				tile_vis_color(game, tx, ty));
		}
	}
}

void	draw_mini_dot(t_game *game, double wx,
	double wy, int color)
{
	int	sx;
	int	sy;
	int	i;
	int	j;

	sx = MINI_OFFSET + MINI_RAD
		+ (int)((wx - game->player.x) * MINI_PPT);
	sy = MINI_OFFSET + MINI_RAD
		+ (int)((wy - game->player.y) * MINI_PPT);
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			mini_pixel(game, sx + j, sy + i, color);
			j++;
		}
		i++;
	}
}
