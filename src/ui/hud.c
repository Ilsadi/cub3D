/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:16:09 by amacaull          #+#    #+#             */
/*   Updated: 2026/02/06 15:42:09 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_hud_asset(t_game *game, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->width, &img->height);
	if (!img->img)
	{
		printf("Error\nFailed to load HUD texture: %s\n", path);
		return ;
	}
	img->addr = (int *)mlx_get_data_addr(img->img, &img->pixel_bits,
			&img->size_line, &img->endian);
}

void	init_hud(t_game *game)
{
	game->hud.health = 20;
	game->hud.food = 20;
	game->hud.slot = 0;
	game->hud.food_timer = 0;
	game->hud.no_sprint_timer = 0;
	game->hud.regen_timer = 0;
	load_hud_asset(game, &game->hud.hotbar, "textures/hud/hotbar.xpm");
	load_hud_asset(game, &game->hud.selector, "textures/hud/selector.xpm");
	load_hud_asset(game, &game->hud.offhand, "textures/hud/offhand.xpm");
	load_hud_asset(game, &game->hud.torch, "textures/hud/torch.xpm");
	load_hud_asset(game, &game->hud.heart_full, "textures/hud/heart_full.xpm");
	load_hud_asset(game, &game->hud.heart_empty, "textures/hud/heart_empty.xpm");
	load_hud_asset(game, &game->hud.food_full, "textures/hud/food_full.xpm");
	load_hud_asset(game, &game->hud.food_empty, "textures/hud/food_empty.xpm");
	load_hud_asset(game, &game->hud.hand_empty, "textures/hud/no_pickaxe.xpm");
	load_hud_asset(game, &game->hud.hand_pickaxe, "textures/hud/pickaxe.xpm");
}

static void	draw_scaled_pixel(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	if ((color & 0x00FFFFFF) == 0)
		return ;
	i = 0;
	while (i < HUD_SCALE)
	{
		j = 0;
		while (j < HUD_SCALE)
		{
			if (x + j >= 0 && x + j < WIDTH && y + i >= 0 && y + i < HEIGHT)
				put_pixel(&game->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_sprite_scaled(t_game *game, t_img *sprite, int start_x,
	int start_y)
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

static void	draw_sprite_raw(t_game *game, t_img *sprite, int start_x,
	int start_y)
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
				put_pixel(&game->img, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

static void	draw_hand(t_game *game)
{
	t_img	*hand;
	int		current_item;
	int		x;
	int		y;

	current_item = game->hud.inventory[game->hud.slot];
	if (current_item == ITEM_KEY)
		hand = &game->hud.hand_pickaxe;
	else
		hand = &game->hud.hand_empty;
	if (!hand->img)
		return ;
	x = WIDTH - hand->width;
	y = HEIGHT - hand->height;
	draw_sprite_raw(game, hand, x, y);
}

static void	render_stats(t_game *game, int hotbar_x, int y_stats)
{
	int	i;
	int	x;
	int	spacing;
	int	hotbar_width;

	spacing = 8 * HUD_SCALE;
	hotbar_width = 182 * HUD_SCALE;
	i = 0;
	while (i < 10)
	{
		x = hotbar_x + (i * spacing);
		if (game->hud.health > (i * 2) + 1)
			draw_sprite_scaled(game, &game->hud.heart_full, x, y_stats);
		else
			draw_sprite_scaled(game, &game->hud.heart_empty, x, y_stats);
		x = (hotbar_x + hotbar_width) - (9 * HUD_SCALE) - (i * spacing);
		if (game->hud.food > (i * 2) + 1)
			draw_sprite_scaled(game, &game->hud.food_full, x, y_stats);
		else
			draw_sprite_scaled(game, &game->hud.food_empty, x, y_stats);
		i++;
	}
}

static void	draw_crosshair(t_game *game)
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

static void	draw_icon_in_slot(t_game *game, t_img *icon, int slot_x, int slot_y)
{
	int		x;
	int		y;
	int		color;
	int		icon_size;
	int		slot_size;

	if (!icon->img)
		return ;
	slot_size = 16 * HUD_SCALE;
	icon_size = icon->width * HUD_SCALE;
	slot_x += (slot_size - icon_size) / 2;
	slot_y += (slot_size - icon_size) / 2;
	y = 0;
	while (y < icon->height)
	{
		x = 0;
		while (x < icon->width)
		{
			color = icon->addr[y * icon->width + x];
			if ((color & 0x00FFFFFF) != 0)
				draw_scaled_pixel(game, slot_x + x * HUD_SCALE,
					slot_y + y * HUD_SCALE, color);
			x++;
		}
		y++;
	}
}

static void	render_inventory(t_game *game, int hotbar_x, int hotbar_y)
{
	int	i;
	int	slot_x;
	int	slot_y;

	i = 0;
	while (i < HOTBAR_SLOTS)
	{
		if (game->hud.inventory[i] == ITEM_KEY && game->hud.key_icon.img)
		{
			slot_x = hotbar_x + (3 * HUD_SCALE) + (i * 20 * HUD_SCALE);
			slot_y = hotbar_y + (3 * HUD_SCALE);
			draw_icon_in_slot(game, &game->hud.key_icon, slot_x, slot_y);
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
	draw_sprite_scaled(game, &game->hud.hotbar, hotbar_x, hotbar_y);
	draw_sprite_scaled(game, &game->hud.selector,
		hotbar_x - (1 * HUD_SCALE) + (game->hud.slot * 20 * HUD_SCALE),
		hotbar_y - (1 * HUD_SCALE));
	draw_sprite_scaled(game, &game->hud.offhand,
		hotbar_x - offhand_gap, hotbar_y);
	draw_sprite_scaled(game, &game->hud.torch,
		hotbar_x - offhand_gap + (3 * HUD_SCALE),
		hotbar_y + (3 * HUD_SCALE));
	render_inventory(game, hotbar_x, hotbar_y);
	render_stats(game, hotbar_x, hotbar_y - (12 * HUD_SCALE));
	draw_crosshair(game);
}

void	free_hud(t_game *game)
{
	if (game->hud.hotbar.img)
		mlx_destroy_image(game->mlx, game->hud.hotbar.img);
	if (game->hud.selector.img)
		mlx_destroy_image(game->mlx, game->hud.selector.img);
	if (game->hud.offhand.img)
		mlx_destroy_image(game->mlx, game->hud.offhand.img);
	if (game->hud.torch.img)
		mlx_destroy_image(game->mlx, game->hud.torch.img);
	if (game->hud.heart_full.img)
		mlx_destroy_image(game->mlx, game->hud.heart_full.img);
	if (game->hud.heart_empty.img)
		mlx_destroy_image(game->mlx, game->hud.heart_empty.img);
	if (game->hud.food_full.img)
		mlx_destroy_image(game->mlx, game->hud.food_full.img);
	if (game->hud.food_empty.img)
		mlx_destroy_image(game->mlx, game->hud.food_empty.img);
	if (game->hud.hand_empty.img)
		mlx_destroy_image(game->mlx, game->hud.hand_empty.img);
	if (game->hud.hand_pickaxe.img)
		mlx_destroy_image(game->mlx, game->hud.hand_pickaxe.img);
}
