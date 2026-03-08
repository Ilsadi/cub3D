/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameover.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:01:01 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/08 19:00:13 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
