/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameover.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:01:01 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/08 14:14:57 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_letter_pixel(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	scale;

	scale = 6;
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

static void	draw_char_i(t_game *game, int x, int y, int c)
{
	int	i;

	i = -1;
	while (++i < 5)
		draw_letter_pixel(game, x + i * 4, y, c);
	i = -1;
	while (++i < 7)
		draw_letter_pixel(game, x + 8, y + (i + 1) * 4, c);
	i = -1;
	while (++i < 5)
		draw_letter_pixel(game, x + i * 4, y + 28, c);
}

static void	draw_char_c(t_game *game, int x, int y, int c)
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
}

static void	draw_char_t(t_game *game, int x, int y, int c)
{
	int	i;

	i = -1;
	while (++i < 5)
		draw_letter_pixel(game, x + i * 4, y, c);
	i = -1;
	while (++i < 8)
		draw_letter_pixel(game, x + 8, y + (i + 1) * 4, c);
}

static void	draw_char_y(t_game *game, int x, int y, int c)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		draw_letter_pixel(game, x, y + i * 4, c);
		draw_letter_pixel(game, x + 16, y + i * 4, c);
	}
	i = -1;
	while (++i < 5)
		draw_letter_pixel(game, x + 8, y + (i + 3) * 4, c);
	draw_letter_pixel(game, x + 4, y + 8, c);
	draw_letter_pixel(game, x + 12, y + 8, c);
}

static void	draw_game_over_text(t_game *game)
{
	int	start_x;
	int	start_y;
	int	color;

	color = 0xFF0000;
	start_x = WIDTH / 2 - 65;
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

static void	draw_victory_text(t_game *game)
{
	int	start_x;
	int	start_y;
	int	color;

	color = 0x00FF00;
	start_x = WIDTH / 2 - 100;
	start_y = HEIGHT / 2 - 20;
	draw_char_v(game, start_x, start_y, color);
	draw_char_i(game, start_x + 25, start_y, color);
	draw_char_c(game, start_x + 50, start_y, color);
	draw_char_t(game, start_x + 75, start_y, color);
	draw_char_o(game, start_x + 100, start_y, color);
	draw_char_r(game, start_x + 125, start_y, color);
	draw_char_y(game, start_x + 150, start_y, color);
}

static void	draw_solid_overlay(t_game *game, int color)
{
	int	x;
	int	y;

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
}

void	render_gameover(t_game *game)
{
	if (!game->gameover.active)
		return ;
	draw_solid_overlay(game, 0x80000000);
	draw_game_over_text(game);
}

void	render_victory(t_game *game)
{
	if (!game->gameover.victory)
		return ;
	draw_solid_overlay(game, 0x000000);
	draw_victory_text(game);
}

void	trigger_victory(t_game *game)
{
	if (game->gameover.active || game->gameover.victory)
		return ;
	game->gameover.victory = 1;
	game->gameover.timer = VICTORY_DELAY;
}

void	check_gameover(t_game *game)
{
	if (game->hud.health <= 0 && !game->gameover.active
		&& !game->gameover.victory)
	{
		game->gameover.active = 1;
		game->gameover.timer = GAMEOVER_DELAY;
	}
	if (game->gameover.active || game->gameover.victory)
	{
		game->gameover.timer--;
		if (game->gameover.timer <= 0)
			clean_everything(game);
	}
}
