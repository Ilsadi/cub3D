/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameover_letter2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:10:39 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/08 19:01:18 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_char_o(t_game *game, int x, int y, int c)
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

void	draw_char_v(t_game *game, int x, int y, int c)
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

void	draw_char_r(t_game *game, int x, int y, int c)
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

void	draw_char_i(t_game *game, int x, int y, int c)
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

void	draw_char_c(t_game *game, int x, int y, int c)
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
