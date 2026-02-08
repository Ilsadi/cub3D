/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 09:23:50 by amacaull          #+#    #+#             */
/*   Updated: 2026/02/08 11:19:00 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	in_mini_circle(int px, int py)
{
	int	dx;
	int	dy;

	dx = px - MINI_RAD;
	dy = py - MINI_RAD;
	return (dx * dx + dy * dy <= MINI_RAD * MINI_RAD);
}

static void	mini_pixel(t_game *game, int sx, int sy, int color)
{
	if (sx < MINI_OFFSET || sy < MINI_OFFSET)
		return ;
	if (sx >= MINI_OFFSET + MINI_SIZE || sy >= MINI_OFFSET + MINI_SIZE)
		return ;
	if (!in_mini_circle(sx - MINI_OFFSET, sy - MINI_OFFSET))
		return ;
	if (sx >= 0 && sx < WIDTH && sy >= 0 && sy < HEIGHT)
		put_pixel(&game->img, sx, sy, color);
}

static int	is_blocking_tile(char c)
{
	return (c == '1' || c == 'D' || c == '2');
}

static int	is_visible(t_game *game, double dest_x, double dest_y)
{
	double	pos[2];
	double	d[2];
	int		steps;

	pos[0] = game->player.x;
	pos[1] = game->player.y;
	d[0] = dest_x - pos[0];
	d[1] = dest_y - pos[1];
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
			&& is_blocking_tile(game->map.grid[(int)pos[1]][(int)pos[0]]))
			return (0);
		pos[0] += d[0];
		pos[1] += d[1];
	}
	return (1);
}

static int	get_tile_color(t_game *game, int x, int y)
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

static void	fill_mini_bg(t_game *game)
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

static void	draw_tile_pixels(t_game *game, int sx, int sy, int color)
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

	if (tx < 0 || tx >= game->map.width || ty < 0 || ty >= game->map.height)
		return (MINI_BG);
	dist = sqrt(pow(game->player.x - tx - 0.5, 2)
			+ pow(game->player.y - ty - 0.5, 2));
	if (dist >= VIS_RANGE || !is_visible(game, tx + 0.5, ty + 0.5))
		return (MINI_BG);
	color = get_tile_color(game, tx, ty);
	return (apply_shading(color, dist / 1.3));
}

static void	draw_mini_tiles(t_game *game)
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
				cx + (int)((tx - game->player.x) * MINI_PPT),
				cy + (int)((ty - game->player.y) * MINI_PPT),
				tile_vis_color(game, tx, ty));
		}
	}
}

static void	draw_mini_dot(t_game *game, double wx, double wy, int color)
{
	int	sx;
	int	sy;
	int	i;
	int	j;

	sx = MINI_OFFSET + MINI_RAD + (int)((wx - game->player.x) * MINI_PPT);
	sy = MINI_OFFSET + MINI_RAD + (int)((wy - game->player.y) * MINI_PPT);
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

static void	draw_mini_collectibles(t_game *game)
{
	int		i;
	double	dist;

	i = -1;
	while (++i < game->collectibles.count)
	{
		if (game->collectibles.list[i].collected)
			continue ;
		dist = sqrt(pow(game->player.x - game->collectibles.list[i].x, 2)
				+ pow(game->player.y - game->collectibles.list[i].y, 2));
		if (dist < VIS_RANGE && is_visible(game,
				game->collectibles.list[i].x + 0.5,
				game->collectibles.list[i].y + 0.5))
			draw_mini_dot(game, game->collectibles.list[i].x + 0.5,
				game->collectibles.list[i].y + 0.5, MINI_KEY_C);
	}
}

static void	draw_mini_endermen(t_game *game)
{
	int		i;
	double	dist;
	int		color;

	i = -1;
	while (++i < game->endermen.count)
	{
		if (!game->endermen.list[i].is_active)
			continue ;
		dist = sqrt(pow(game->player.x - game->endermen.list[i].x, 2)
				+ pow(game->player.y - game->endermen.list[i].y, 2));
		if (dist >= VIS_RANGE || !is_visible(game,
				game->endermen.list[i].x, game->endermen.list[i].y))
			continue ;
		color = MINI_ENDER_C;
		if (game->endermen.list[i].is_angry)
			color = 0xFF0000;
		draw_mini_dot(game, game->endermen.list[i].x,
			game->endermen.list[i].y, color);
	}
}

static void	draw_mini_player(t_game *game)
{
	int	cx;
	int	cy;
	int	i;
	int	j;

	cx = MINI_OFFSET + MINI_RAD;
	cy = MINI_OFFSET + MINI_RAD;
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			mini_pixel(game, cx + j, cy + i, MINI_PLAYER);
			j++;
		}
		i++;
	}
	i = 0;
	while (++i < 12)
		mini_pixel(game, cx + (int)(game->ray.dir_x * i),
			cy + (int)(game->ray.dir_y * i), MINI_PLAYER);
}

static void	draw_mini_border(t_game *game)
{
	int		a;
	double	angle;
	int		bx;
	int		by;

	a = -1;
	while (++a < 720)
	{
		angle = a * M_PI / 360.0;
		bx = MINI_OFFSET + MINI_RAD + (int)(MINI_RAD * cos(angle));
		by = MINI_OFFSET + MINI_RAD + (int)(MINI_RAD * sin(angle));
		if (bx >= 0 && bx < WIDTH && by >= 0 && by < HEIGHT)
		{
			put_pixel(&game->img, bx, by, MINI_BORDER);
			if (bx + 1 < WIDTH)
				put_pixel(&game->img, bx + 1, by, MINI_BORDER);
			if (by + 1 < HEIGHT)
				put_pixel(&game->img, bx, by + 1, MINI_BORDER);
		}
	}
}

void	render_minimap(t_game *game)
{
	fill_mini_bg(game);
	draw_mini_tiles(game);
	draw_mini_collectibles(game);
	draw_mini_endermen(game);
	draw_mini_player(game);
	draw_mini_border(game);
}
