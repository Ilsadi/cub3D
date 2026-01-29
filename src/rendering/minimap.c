/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 09:23:50 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/29 15:07:07 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MINI_SCALE 8
#define MINI_OFFSET 8
#define MINI_PLAYER 0xFF0000
#define MINI_WALL 0x444444
#define MINI_FLOOR 0xAAAAAA
#define MINI_BG 0x222222

static void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	px;
	int	py;

	i = 0;
	while (i < MINI_SCALE)
	{
		j = 0;
		while (j < MINI_SCALE)
		{
			px = x + j;
			py = y + i;
			put_pixel(&game->img, px, py, color);
			j++;
		}
		i++;
	}
}

static void	draw_map_tiles(t_game *game)
{
	int		x;
	int		y;
	int		color;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			c = game->map.grid[y][x];
			if (c == '1')
				color = MINI_WALL;
			else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
				color = MINI_FLOOR;
			else
				color = MINI_BG;
			draw_square(game, MINI_OFFSET + x * MINI_SCALE,
				MINI_OFFSET + y * MINI_SCALE, color);
			x++;
		}
		y++;
	}
}

static void	draw_player_dot(t_game *game)
{
	int	px;
	int	py;
	int	i;
	int	j;

	px = MINI_OFFSET + (int)(game->player.x * MINI_SCALE);
	py = MINI_OFFSET + (int)(game->player.y * MINI_SCALE);
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			put_pixel(&game->img, px + j, py + i, MINI_PLAYER);
			j++;
		}
		i++;
	}
}

static void	draw_player_direction(t_game *game)
{
	int		i;
	int		px;
	int		py;
	double	dx;
	double	dy;

	px = MINI_OFFSET + (int)(game->player.x * MINI_SCALE);
	py = MINI_OFFSET + (int)(game->player.y * MINI_SCALE);
	dx = game->ray.dir_x;
	dy = game->ray.dir_y;
	i = 0;
	while (i < 10)
	{
		put_pixel(&game->img, px + (int)(dx * i), py + (int)(dy * i),
			MINI_PLAYER);
		i++;
	}
}

void	render_minimap(t_game *game)
{
	draw_map_tiles(game);
	draw_player_dot(game);
	draw_player_direction(game);
}
