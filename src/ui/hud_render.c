/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 16:45:59 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/11 14:15:21 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_icon_in_slot(t_game *game, t_img *icon,
	int slot_x, int slot_y)
{
	int	x;
	int	y;
	int	color;

	if (!icon->img)
		return ;
	slot_x += (16 * HUD_SCALE - icon->width * HUD_SCALE) / 2;
	slot_y += (16 * HUD_SCALE - icon->width * HUD_SCALE) / 2;
	y = 0;
	while (y < icon->height)
	{
		x = 0;
		while (x < icon->width)
		{
			color = icon->addr[y * icon->width + x];
			if ((color & 0x00FFFFFF) != 0)
				draw_scaled_pixel(game,
					slot_x + x * HUD_SCALE,
					slot_y + y * HUD_SCALE, color);
			x++;
		}
		y++;
	}
}

static t_img	*get_slot_icon(t_game *game, int slot)
{
	int	item;

	item = game->hud.inventory[slot];
	if (item == ITEM_KEY)
		return (&game->hud.key_icon);
	if (item == ITEM_APPLE)
		return (&game->hud.apple_icon);
	if (item == ITEM_EGG)
		return (&game->hud.egg_icon);
	return (NULL);
}

static void	render_inventory(t_game *game, int hotbar_x,
	int hotbar_y)
{
	int		i;
	int		slot_x;
	int		slot_y;
	t_img	*icon;

	i = 0;
	while (i < HOTBAR_SLOTS)
	{
		icon = get_slot_icon(game, i);
		if (icon)
		{
			slot_x = hotbar_x + (3 * HUD_SCALE)
				+ (i * 20 * HUD_SCALE);
			slot_y = hotbar_y + (3 * HUD_SCALE);
			draw_icon_in_slot(game, icon, slot_x, slot_y);
		}
		i++;
	}
}

void	render_hud(t_game *game)
{
	int	hotbar_x;
	int	hotbar_y;
	int	hotbar_width;
	int	offhand_gap;

	hotbar_width = 182 * HUD_SCALE;
	offhand_gap = 29 * HUD_SCALE;
	hotbar_x = (WIDTH - hotbar_width) / 2;
	hotbar_y = HEIGHT - (22 * HUD_SCALE);
	draw_hand(game);
	draw_sprite_scaled(game, &game->hud.hotbar,
		hotbar_x, hotbar_y);
	draw_sprite_scaled(game, &game->hud.selector,
		hotbar_x - HUD_SCALE
		+ (game->hud.slot * 20 * HUD_SCALE),
		hotbar_y - HUD_SCALE);
	draw_sprite_scaled(game, &game->hud.offhand,
		hotbar_x - offhand_gap, hotbar_y);
	draw_sprite_scaled(game, &game->hud.torch,
		hotbar_x - offhand_gap + (3 * HUD_SCALE),
		hotbar_y + (3 * HUD_SCALE));
	render_inventory(game, hotbar_x, hotbar_y);
	render_stats(game, hotbar_x,
		hotbar_y - (12 * HUD_SCALE));
	draw_crosshair(game);
}
