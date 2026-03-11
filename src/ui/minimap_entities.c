/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_entities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 16:44:43 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/11 14:15:13 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_mini_collectibles(t_game *game)
{
	int		i;
	double	dist;

	i = -1;
	while (++i < game->collectibles.count)
	{
		if (game->collectibles.list[i].collected)
			continue ;
		dist = sqrt(pow(game->player.x
					- game->collectibles.list[i].x, 2)
				+ pow(game->player.y
					- game->collectibles.list[i].y, 2));
		if (dist < VIS_RANGE && mini_is_visible(game,
				game->collectibles.list[i].x + 0.5,
				game->collectibles.list[i].y + 0.5))
			draw_mini_dot(game,
				game->collectibles.list[i].x + 0.5,
				game->collectibles.list[i].y + 0.5,
				MINI_KEY_C);
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
		dist = sqrt(pow(game->player.x
					- game->endermen.list[i].x, 2)
				+ pow(game->player.y
					- game->endermen.list[i].y, 2));
		if (dist >= VIS_RANGE || !mini_is_visible(game,
				game->endermen.list[i].x,
				game->endermen.list[i].y))
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
		bx = MINI_OFFSET + MINI_RAD
			+ (int)(MINI_RAD * cos(angle));
		by = MINI_OFFSET + MINI_RAD
			+ (int)(MINI_RAD * sin(angle));
		if (bx >= 0 && bx < WIDTH
			&& by >= 0 && by < HEIGHT)
		{
			put_pixel(&game->img, bx, by, MINI_BORDER);
			if (bx + 1 < WIDTH)
				put_pixel(&game->img, bx + 1,
					by, MINI_BORDER);
			if (by + 1 < HEIGHT)
				put_pixel(&game->img, bx,
					by + 1, MINI_BORDER);
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
