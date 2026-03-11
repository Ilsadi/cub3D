/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 16:45:44 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/11 14:14:50 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprite_scaled(t_game *game, t_img *sprite,
	int start_x, int start_y)
{
	int	x;
	int	y;
	int	color;

	if (!sprite->img)
		return ;
	y = 0;
	while (y < sprite->height)
	{
		x = 0;
		while (x < sprite->width)
		{
			color = sprite->addr[y * sprite->width + x];
			draw_scaled_pixel(game, start_x + (x * HUD_SCALE),
				start_y + (y * HUD_SCALE), color);
			x++;
		}
		y++;
	}
}

void	draw_sprite_raw(t_game *game, t_img *sprite,
	int start_x, int start_y)
{
	int	x;
	int	y;
	int	color;

	if (!sprite->img)
		return ;
	y = 0;
	while (y < sprite->height)
	{
		x = 0;
		while (x < sprite->width)
		{
			color = sprite->addr[y * sprite->width + x];
			if ((color & 0x00FFFFFF) != 0)
				put_pixel(&game->img, start_x + x,
					start_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_hand(t_game *game)
{
	t_img	*hand;
	int		current_item;
	int		x;
	int		y;

	current_item = game->hud.inventory[game->hud.slot];
	if (current_item == ITEM_KEY)
		hand = &game->hud.hand_pickaxe;
	else if (current_item == ITEM_APPLE)
		hand = &game->hud.hand_apple;
	else if (current_item == ITEM_EGG)
		hand = &game->hud.hand_egg;
	else
		hand = &game->hud.hand_empty;
	if (!hand->img)
		return ;
	x = WIDTH - hand->width;
	y = HEIGHT - hand->height;
	draw_sprite_raw(game, hand, x, y);
}

void	render_stats(t_game *game, int hotbar_x, int y_s)
{
	int	i;
	int	x;
	int	sp;
	int	hw;

	sp = 8 * HUD_SCALE;
	hw = 182 * HUD_SCALE;
	i = 0;
	while (i < 10)
	{
		x = hotbar_x + (i * sp);
		if (game->hud.health > (i * 2) + 1)
			draw_sprite_scaled(game, &game->hud.heart_full, x, y_s);
		else
			draw_sprite_scaled(game, &game->hud.heart_empty, x, y_s);
		x = (hotbar_x + hw) - (9 * HUD_SCALE) - (i * sp);
		if (game->hud.food > (i * 2) + 1)
			draw_sprite_scaled(game, &game->hud.food_full, x, y_s);
		else
			draw_sprite_scaled(game, &game->hud.food_empty, x, y_s);
		i++;
	}
}

void	draw_crosshair(t_game *game)
{
	int	i;
	int	c_x;
	int	c_y;
	int	color;

	color = 0xDDDDDD;
	c_x = (WIDTH / 2) - (HUD_SCALE / 2);
	c_y = (HEIGHT / 2) - (HUD_SCALE / 2);
	i = -4;
	while (i <= 4)
	{
		draw_scaled_pixel(game, c_x, c_y + (i * HUD_SCALE), color);
		draw_scaled_pixel(game, c_x + (i * HUD_SCALE), c_y, color);
		i++;
	}
}
