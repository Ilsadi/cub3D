/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 19:00:55 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/08 13:58:44 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_facing_cell(t_game *game, int *target_x, int *target_y)
{
	double	check_x;
	double	check_y;

	check_x = game->player.x + game->ray.dir_x * DOOR_RANGE;
	check_y = game->player.y + game->ray.dir_y * DOOR_RANGE;
	*target_x = (int)check_x;
	*target_y = (int)check_y;
	if (*target_x < 0 || *target_x >= game->map.width)
		return (0);
	if (*target_y < 0 || *target_y >= game->map.height)
		return (0);
	return (1);
}

static void	interact_with_door(t_game *game, t_door *door)
{
	if (door->open)
		return ;
	if (!has_item_selected(game, ITEM_KEY))
		return ;
	use_selected_item(game);
	door->state++;
	if (door->state >= DOOR_FRAMES)
	{
		door->open = 1;
		game->map.grid[door->y][door->x] = '0';
	}
}

static int	handle_item_use(t_game *game)
{
	int	slot;
	int	item;

	slot = game->hud.slot;
	if (slot < 0 || slot >= HOTBAR_SLOTS)
		return (0);
	item = game->hud.inventory[slot];
	if (item == ITEM_APPLE || item == ITEM_EGG)
	{
		use_selected_item(game);
		return (1);
	}
	return (0);
}

void	handle_interaction(t_game *game)
{
	int		target_x;
	int		target_y;
	t_door	*door;

	if (handle_item_use(game))
		return ;
	if (!get_facing_cell(game, &target_x, &target_y))
		return ;
	if (game->map.grid[target_y][target_x] == 'D')
	{
		door = get_door_at(game, target_x, target_y);
		if (door)
			interact_with_door(game, door);
	}
}
