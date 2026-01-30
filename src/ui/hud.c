/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:16:09 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/30 16:52:33 by amacaull         ###   ########.fr       */
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
	load_hud_asset(game, &game->hud.hotbar, "textures/hud/hotbar.xpm");
	load_hud_asset(game, &game->hud.selector, "textures/hud/selector.xpm");
	load_hud_asset(game, &game->hud.offhand, "textures/hud/offhand.xpm");
	load_hud_asset(game, &game->hud.torch, "textures/hud/torch.xpm");
	load_hud_asset(game, &game->hud.heart_full, "textures/hud/heart_full.xpm");
	load_hud_asset(game, &game->hud.heart_empty, "textures/hud/heart_empty.xpm");
	load_hud_asset(game, &game->hud.food_full, "textures/hud/food_full.xpm");
	load_hud_asset(game, &game->hud.food_empty, "textures/hud/food_empty.xpm");
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

static void	draw_sprite_scaled(t_game *game, t_img *sprite, int start_x, int start_y)
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
	draw_sprite_scaled(game, &game->hud.hotbar, hotbar_x, hotbar_y);
	draw_sprite_scaled(game, &game->hud.selector,
		hotbar_x - (1 * HUD_SCALE) + (game->hud.slot * 20 * HUD_SCALE),
		hotbar_y - (1 * HUD_SCALE));
	draw_sprite_scaled(game, &game->hud.offhand,
		hotbar_x - offhand_gap, hotbar_y);
	draw_sprite_scaled(game, &game->hud.torch,
		hotbar_x - offhand_gap + (3 * HUD_SCALE),
		hotbar_y + (3 * HUD_SCALE));
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
}
