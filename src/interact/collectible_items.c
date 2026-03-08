/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_items.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:20:06 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/08 19:06:18 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	add_item_to_inventory(t_game *game, int item_type)
{
	int	i;

	i = 0;
	while (i < HOTBAR_SLOTS)
	{
		if (game->hud.inventory[i] == ITEM_NONE)
		{
			game->hud.inventory[i] = item_type;
			if (item_type == ITEM_KEY)
				game->hud.key_uses[i] = KEY_USES;
			return (1);
		}
		i++;
	}
	return (0);
}

int	has_item_selected(t_game *game, int item_type)
{
	if (game->hud.slot < 0
		|| game->hud.slot >= HOTBAR_SLOTS)
		return (0);
	if (game->hud.inventory[game->hud.slot] != item_type)
		return (0);
	if (item_type == ITEM_KEY
		&& game->hud.key_uses[game->hud.slot] <= 0)
		return (0);
	return (1);
}

static void	consume_slot(t_game *game, int slot)
{
	game->hud.inventory[slot] = ITEM_NONE;
	game->hud.key_uses[slot] = 0;
}

void	use_selected_item(t_game *game)
{
	int	slot;
	int	item;

	slot = game->hud.slot;
	if (slot < 0 || slot >= HOTBAR_SLOTS)
		return ;
	item = game->hud.inventory[slot];
	if (item == ITEM_KEY)
	{
		game->hud.key_uses[slot]--;
		if (game->hud.key_uses[slot] <= 0)
			consume_slot(game, slot);
	}
	else if (item == ITEM_APPLE)
	{
		game->hud.health += APPLE_HP;
		if (game->hud.health > 20)
			game->hud.health = 20;
		consume_slot(game, slot);
	}
	else if (item == ITEM_EGG)
	{
		consume_slot(game, slot);
		trigger_victory(game);
	}
}
