/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 09:23:50 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/30 11:53:07 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINI_SCALE)
	{
		j = 0;
		while (j < MINI_SCALE)
		{
			put_pixel(&game->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static int	is_visible(t_game *game, double dest_x, double dest_y)
{
	double	pos_x;
	double	pos_y;
	double	dx;
	double	dy;
	int		steps;

	pos_x = game->player.x;
	pos_y = game->player.y;
	dx = dest_x - pos_x;
	dy = dest_y - pos_y;
	if (fabs(dx) > fabs(dy))
		steps = (int)(fabs(dx) * 10);
	else
		steps = (int)(fabs(dy) * 10);
	dx /= steps;
	dy /= steps;
	while (steps-- > 0)
	{
		if (game->map.grid[(int)pos_y][(int)pos_x] == '1')
			return (0);
		pos_x += dx;
		pos_y += dy;
	}
	return (1);
}

static void	handle_tile(t_game *game, int x, int y)
{
	int		color;
	double	dist;
	char	c;

	dist = sqrt(pow(game->player.x - x, 2) + pow(game->player.y - y, 2));
	c = game->map.grid[y][x];
	if (c == '1')
		color = MINI_WALL;
	else if (c != ' ')
		color = MINI_FLOOR;
	else
		color = MINI_BG;
	if (dist < 3.9)
	{
		if (!is_visible(game, x + 0.5, y + 0.5))
			color = MINI_BG;
		else
			color = apply_shading(color, dist / 1.3);
	}
	else
		color = MINI_BG;
	draw_square(game, MINI_OFFSET + x * MINI_SCALE,
		MINI_OFFSET + y * MINI_SCALE, color);
}

static void	draw_player_icon(t_game *game)
{
	int		p[2];
	int		i;
	int		j;
	double	d[2];

	p[0] = MINI_OFFSET + (int)(game->player.x * MINI_SCALE);
	p[1] = MINI_OFFSET + (int)(game->player.y * MINI_SCALE);
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j++ <= 2)
			put_pixel(&game->img, p[0] + j, p[1] + i, MINI_PLAYER);
		i++;
	}
	d[0] = game->ray.dir_x;
	d[1] = game->ray.dir_y;
	i = 0;
	while (i++ < 10)
		put_pixel(&game->img, p[0] + (int)(d[0] * i),
			p[1] + (int)(d[1] * i), MINI_PLAYER);
}

void	render_minimap(t_game *game)
{
	int	x;
	int	y;
	int	w;
	int	h;

	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
			handle_tile(game, x, y);
	}
	draw_player_icon(game);
	w = game->map.width * MINI_SCALE;
	h = game->map.height * MINI_SCALE;
	x = -2;
	while (++x < w + 2)
	{
		put_pixel(&game->img, MINI_OFFSET + x, MINI_OFFSET - 2, MINI_BORDER);
		put_pixel(&game->img, MINI_OFFSET + x, MINI_OFFSET + h + 1,
			MINI_BORDER);
	}
	y = -2;
	while (++y < h + 2)
	{
		put_pixel(&game->img, MINI_OFFSET - 2, MINI_OFFSET + y, MINI_BORDER);
		put_pixel(&game->img, MINI_OFFSET + w + 1, MINI_OFFSET + y,
			MINI_BORDER);
	}
}
