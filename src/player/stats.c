/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:51:05 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/30 17:25:14 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_metabolism(t_game *game)
{
	int	is_moving;

	is_moving = (game->keys.w || game->keys.s || game->keys.a || game->keys.d);
	if (is_moving && game->keys.shift && game->hud.food > 0)
	{
		game->hud.food_timer += HUNGER_DRAIN;
		if (game->hud.food_timer >= HUNGER_THRESHOLD)
		{
			game->hud.food--;
			game->hud.food_timer = 0;
		}
	}
	else
	{
		game->hud.food_timer = 0;
	}
	if (game->hud.food < 0)
		game->hud.food = 0;
}
