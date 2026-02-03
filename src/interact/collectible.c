/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 19:10:45 by amacaull          #+#    #+#             */
/*   Updated: 2026/02/03 21:42:51 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			if (game->map.grid[y][x] == 'K'
				&& game->collectibles.count < MAX_COLLECTIBLES)
			{
				game->collectibles.list[game->collectibles.count].x = x;
				game->collectibles.list[game->collectibles.count].y = y;
				game->collectibles.list[game->collectibles.count].type
					= ITEM_KEY;
				game->collectibles.list[game->collectibles.count].collected = 0;
				game->collectibles.count++;
				game->map.grid[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

static void	load_collectible_textures(t_game *game)
{
	game->collectibles.key_tex.img = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible/key.xpm",
			&game->collectibles.key_tex.width,
			&game->collectibles.key_tex.height);
	if (game->collectibles.key_tex.img)
		game->collectibles.key_tex.addr = (int *)mlx_get_data_addr(
				game->collectibles.key_tex.img,
				&game->collectibles.key_tex.pixel_bits,
				&game->collectibles.key_tex.size_line,
				&game->collectibles.key_tex.endian);
	game->hud.key_icon.img = mlx_xpm_file_to_image(game->mlx,
			"textures/hud/key_icon.xpm",
			&game->hud.key_icon.width,
			&game->hud.key_icon.height);
	if (game->hud.key_icon.img)
		game->hud.key_icon.addr = (int *)mlx_get_data_addr(
				game->hud.key_icon.img,
				&game->hud.key_icon.pixel_bits,
				&game->hud.key_icon.size_line,
				&game->hud.key_icon.endian);
}

void	init_collectibles(t_game *game)
{
	int	i;

	game->collectibles.count = 0;
	i = 0;
	while (i < HOTBAR_SLOTS)
	{
		game->hud.inventory[i] = ITEM_NONE;
		i++;
	}
	load_collectible_textures(game);
	find_collectibles_in_map(game);
}

void	free_collectibles(t_game *game)
{
	if (game->collectibles.key_tex.img)
		mlx_destroy_image(game->mlx, game->collectibles.key_tex.img);
	if (game->hud.key_icon.img)
		mlx_destroy_image(game->mlx, game->hud.key_icon.img);
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
	return (game->hud.inventory[game->hud.slot] == item_type);
}

void	use_selected_item(t_game *game)
{
	if (game->hud.slot < 0 || game->hud.slot >= HOTBAR_SLOTS)
		return ;
	game->hud.inventory[game->hud.slot] = ITEM_NONE;
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
