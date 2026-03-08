/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 19:10:45 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/08 19:07:04 by amacaull         ###   ########.fr       */
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
		img->addr = (int *)mlx_get_data_addr(img->img,
				&img->pixel_bits, &img->size_line,
				&img->endian);
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
