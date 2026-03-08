/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameover_letter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:10:21 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/08 19:00:31 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_letter_pixel(t_game *game, int x, int y, int color)
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

void	draw_char_g(t_game *game, int x, int y, int c)
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

void	draw_char_a(t_game *game, int x, int y, int c)
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

void	draw_char_m(t_game *game, int x, int y, int c)
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

void	draw_char_e(t_game *game, int x, int y, int c)
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
