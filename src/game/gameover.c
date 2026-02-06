/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameover.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:01:01 by amacaull          #+#    #+#             */
/*   Updated: 2026/02/06 14:59:51 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_letter_pixel(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	scale;

	scale = 4;
	i = 0;
	while (i < scale)
	{
		j = 0;
		while (j < scale)
		{
			put_pixel(&game->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_char_g(t_game *game, int x, int y, int c)
{
	int	i;

	i = -1;
	while (++i < 5)
		draw_letter_pixel(game, x + i * 4, y, c);
	i = -1;
	while (++i < 7)
		draw_letter_pixel(game, x, y + (i + 1) * 4, c);
	i = -1;
	while (++i < 5)
		draw_letter_pixel(game, x + i * 4, y + 28, c);
	i = 2;
	while (++i < 7)
		draw_letter_pixel(game, x + 16, y + i * 4, c);
	draw_letter_pixel(game, x + 8, y + 16, c);
	draw_letter_pixel(game, x + 12, y + 16, c);
}

static void	draw_char_a(t_game *game, int x, int y, int c)
{
	int	i;

	i = -1;
	while (++i < 5)
		draw_letter_pixel(game, x + i * 4, y, c);
	i = -1;
	while (++i < 7)
	{
		draw_letter_pixel(game, x, y + (i + 1) * 4, c);
		draw_letter_pixel(game, x + 16, y + (i + 1) * 4, c);
	}
	i = -1;
	while (++i < 5)
		draw_letter_pixel(game, x + i * 4, y + 12, c);
}

static void	draw_char_m(t_game *game, int x, int y, int c)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		draw_letter_pixel(game, x, y + (i + 1) * 4, c);
		draw_letter_pixel(game, x + 16, y + (i + 1) * 4, c);
	}
	draw_letter_pixel(game, x + 4, y + 4, c);
	draw_letter_pixel(game, x + 8, y + 8, c);
	draw_letter_pixel(game, x + 12, y + 4, c);
}

static void	draw_char_e(t_game *game, int x, int y, int c)
{
	int	i;

	i = -1;
	while (++i < 5)
		draw_letter_pixel(game, x + i * 4, y, c);
	i = -1;
	while (++i < 7)
		draw_letter_pixel(game, x, y + (i + 1) * 4, c);
	i = -1;
	while (++i < 4)
		draw_letter_pixel(game, x + i * 4, y + 12, c);
	i = -1;
	while (++i < 5)
		draw_letter_pixel(game, x + i * 4, y + 28, c);
}

static void	draw_char_o(t_game *game, int x, int y, int c)
{
	int	i;

	i = -1;
	while (++i < 5)
		draw_letter_pixel(game, x + i * 4, y, c);
	i = -1;
	while (++i < 7)
	{
		draw_letter_pixel(game, x, y + (i + 1) * 4, c);
		draw_letter_pixel(game, x + 16, y + (i + 1) * 4, c);
	}
	i = -1;
	while (++i < 5)
		draw_letter_pixel(game, x + i * 4, y + 28, c);
}

static void	draw_char_v(t_game *game, int x, int y, int c)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		draw_letter_pixel(game, x, y + i * 4, c);
		draw_letter_pixel(game, x + 16, y + i * 4, c);
	}
	draw_letter_pixel(game, x + 4, y + 20, c);
	draw_letter_pixel(game, x + 12, y + 20, c);
	draw_letter_pixel(game, x + 8, y + 24, c);
	draw_letter_pixel(game, x + 8, y + 28, c);
}

static void	draw_char_r(t_game *game, int x, int y, int c)
{
	int	i;

	i = -1;
	while (++i < 5)
		draw_letter_pixel(game, x + i * 4, y, c);
	i = -1;
	while (++i < 8)
		draw_letter_pixel(game, x, y + (i + 1) * 4, c);
	i = -1;
	while (++i < 3)
		draw_letter_pixel(game, x + 16, y + i * 4 + 4, c);
	i = -1;
	while (++i < 4)
		draw_letter_pixel(game, x + i * 4, y + 12, c);
	draw_letter_pixel(game, x + 8, y + 16, c);
	draw_letter_pixel(game, x + 12, y + 20, c);
	draw_letter_pixel(game, x + 16, y + 24, c);
	draw_letter_pixel(game, x + 16, y + 28, c);
}

static void	draw_game_over_text(t_game *game)
{
	int	start_x;
	int	start_y;
	int	color;

	color = 0xFF0000;
	start_x = WIDTH / 2 - 120;
	start_y = HEIGHT / 2 - 50;
	draw_char_g(game, start_x, start_y, color);
	draw_char_a(game, start_x + 25, start_y, color);
	draw_char_m(game, start_x + 50, start_y, color);
	draw_char_e(game, start_x + 75, start_y, color);
	start_y += 50;
	draw_char_o(game, start_x + 25, start_y, color);
	draw_char_v(game, start_x + 50, start_y, color);
	draw_char_e(game, start_x + 75, start_y, color);
	draw_char_r(game, start_x + 100, start_y, color);
}

void	render_gameover(t_game *game)
{
	int	x;
	int	y;
	int	color;

	if (!game->gameover.active)
		return ;
	color = 0x80000000;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(&game->img, x, y, color);
			x++;
		}
		y++;
	}
	draw_game_over_text(game);
}

void	check_gameover(t_game *game)
{
	if (game->hud.health <= 0 && !game->gameover.active)
	{
		game->gameover.active = 1;
		game->gameover.timer = GAMEOVER_DELAY;
	}
	if (game->gameover.active)
	{
		game->gameover.timer--;
		if (game->gameover.timer <= 0)
			clean_everything(game);
	}
}
