/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 19:10:45 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/08 13:57:54 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	add_collectible(t_game *game, int x, int y, int type)
{
	int	idx;

	if (game->collectibles.count >= MAX_COLLECTIBLES)
		return ;
	idx = game->collectibles.count;
	game->collectibles.list[idx].x = x;
	game->collectibles.list[idx].y = y;
	game->collectibles.list[idx].type = type;
	game->collectibles.list[idx].collected = 0;
	game->collectibles.count++;
	game->map.grid[y][x] = '0';
}

static void	find_collectibles_in_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == 'K')
				add_collectible(game, x, y, ITEM_KEY);
			else if (game->map.grid[y][x] == 'A')
				add_collectible(game, x, y, ITEM_APPLE);
			else if (game->map.grid[y][x] == 'V')
				add_collectible(game, x, y, ITEM_EGG);
			x++;
		}
		y++;
	}
}

static void	load_img(t_game *game, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path,
			&img->width, &img->height);
	if (img->img)
		img->addr = (int *)mlx_get_data_addr(img->img, &img->pixel_bits,
				&img->size_line, &img->endian);
}

static void	load_collectible_textures(t_game *game)
{
	load_img(game, &game->collectibles.key_tex,
		"textures/collectible/key.xpm");
	load_img(game, &game->collectibles.apple_tex,
		"textures/collectible/apple.xpm");
	load_img(game, &game->collectibles.egg_tex,
		"textures/collectible/egg.xpm");
	load_img(game, &game->hud.key_icon,
		"textures/hud/key_icon.xpm");
	load_img(game, &game->hud.apple_icon,
		"textures/hud/apple_icon.xpm");
	load_img(game, &game->hud.egg_icon,
		"textures/hud/egg_icon.xpm");
}

void	init_collectibles(t_game *game)
{
	int	i;

	game->collectibles.count = 0;
	i = 0;
	while (i < HOTBAR_SLOTS)
	{
		game->hud.inventory[i] = ITEM_NONE;
		game->hud.key_uses[i] = 0;
		i++;
	}
	load_collectible_textures(game);
	find_collectibles_in_map(game);
}

void	free_collectibles(t_game *game)
{
	if (game->collectibles.key_tex.img)
		mlx_destroy_image(game->mlx, game->collectibles.key_tex.img);
	if (game->collectibles.apple_tex.img)
		mlx_destroy_image(game->mlx, game->collectibles.apple_tex.img);
	if (game->collectibles.egg_tex.img)
		mlx_destroy_image(game->mlx, game->collectibles.egg_tex.img);
	if (game->hud.key_icon.img)
		mlx_destroy_image(game->mlx, game->hud.key_icon.img);
	if (game->hud.apple_icon.img)
		mlx_destroy_image(game->mlx, game->hud.apple_icon.img);
	if (game->hud.egg_icon.img)
		mlx_destroy_image(game->mlx, game->hud.egg_icon.img);
}

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
	if (game->hud.slot < 0 || game->hud.slot >= HOTBAR_SLOTS)
		return (0);
	if (game->hud.inventory[game->hud.slot] != item_type)
		return (0);
	if (item_type == ITEM_KEY && game->hud.key_uses[game->hud.slot] <= 0)
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

void	update_collectibles(t_game *game)
{
	int		i;
	double	dx;
	double	dy;
	double	dist;

	i = 0;
	while (i < game->collectibles.count)
	{
		if (!game->collectibles.list[i].collected)
		{
			dx = game->player.x - (game->collectibles.list[i].x + 0.5);
			dy = game->player.y - (game->collectibles.list[i].y + 0.5);
			dist = sqrt(dx * dx + dy * dy);
			if (dist < 0.9)
			{
				if (add_item_to_inventory(game,
						game->collectibles.list[i].type))
					game->collectibles.list[i].collected = 1;
			}
		}
		i++;
	}
}
