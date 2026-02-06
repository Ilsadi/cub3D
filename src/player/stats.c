/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:51:05 by amacaull          #+#    #+#             */
/*   Updated: 2026/02/06 15:28:51 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	drain_food(t_game *game)
{
	game->hud.food_timer += HUNGER_DRAIN;
	if (game->hud.food_timer >= HUNGER_THRESHOLD)
	{
		game->hud.food--;
		game->hud.food_timer = 0;
	}
	game->hud.no_sprint_timer = 0;
	game->hud.regen_timer = 0;
}

static void	regen_food(t_game *game)
{
	game->hud.no_sprint_timer++;
	if (game->hud.no_sprint_timer >= REGEN_DELAY)
	{
		game->hud.regen_timer++;
		if (game->hud.regen_timer >= REGEN_RATE)
		{
			if (game->hud.food < FOOD_MAX)
				game->hud.food++;
			game->hud.regen_timer = 0;
		}
	}
}

void	update_metabolism(t_game *game)
{
	int	is_moving;
	int	is_sprinting;

	is_moving = (game->keys.w || game->keys.s || game->keys.a || game->keys.d);
	is_sprinting = (is_moving && game->keys.shift && game->hud.food > 0);
	if (is_sprinting)
		drain_food(game);
	else
	{
		game->hud.food_timer = 0;
		regen_food(game);
	}
	if (game->hud.food < 0)
		game->hud.food = 0;
}
