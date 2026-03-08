/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameover_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:10:59 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/08 19:01:13 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_char_t(t_game *game, int x, int y, int c)
{
	int	i;

	i = -1;
	while (++i < 5)
		draw_letter_pixel(game, x + i * 4, y, c);
	i = -1;
	while (++i < 8)
		draw_letter_pixel(game, x + 8, y + (i + 1) * 4, c);
}

void	draw_char_y(t_game *game, int x, int y, int c)
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

void	draw_game_over_text(t_game *game)
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

void	draw_victory_text(t_game *game)
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
