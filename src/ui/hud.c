/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:16:09 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/11 14:11:36 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_hud_asset(t_game *game, t_img *img,
	char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path,
			&img->width, &img->height);
	if (!img->img)
		return ;
	img->addr = (int *)mlx_get_data_addr(img->img,
			&img->pixel_bits, &img->size_line,
			&img->endian);
}

static void	load_hud_textures(t_game *game)
{
	load_hud_asset(game, &game->hud.hotbar,
		"textures/hud/hotbar.xpm");
	load_hud_asset(game, &game->hud.selector,
		"textures/hud/selector.xpm");
	load_hud_asset(game, &game->hud.offhand,
		"textures/hud/offhand.xpm");
	load_hud_asset(game, &game->hud.torch,
		"textures/hud/torch.xpm");
	load_hud_asset(game, &game->hud.heart_full,
		"textures/hud/heart_full.xpm");
	load_hud_asset(game, &game->hud.heart_empty,
		"textures/hud/heart_empty.xpm");
	load_hud_asset(game, &game->hud.food_full,
		"textures/hud/food_full.xpm");
	load_hud_asset(game, &game->hud.food_empty,
		"textures/hud/food_empty.xpm");
	load_hud_asset(game, &game->hud.hand_empty,
		"textures/hud/empty_hand.xpm");
	load_hud_asset(game, &game->hud.hand_pickaxe,
		"textures/hud/pickaxe.xpm");
	load_hud_asset(game, &game->hud.hand_apple,
		"textures/hud/hand_apple.xpm");
	load_hud_asset(game, &game->hud.hand_egg,
		"textures/hud/hand_egg.xpm");
}

void	init_hud(t_game *game)
{
	game->hud.health = 20;
	game->hud.food = 20;
	game->hud.slot = 0;
	game->hud.food_timer = 0;
	game->hud.no_sprint_timer = 0;
	game->hud.regen_timer = 0;
	load_hud_textures(game);
}

void	draw_scaled_pixel(t_game *game, int x,
	int y, int color)
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
			if (x + j >= 0 && x + j < WIDTH
				&& y + i >= 0 && y + i < HEIGHT)
				put_pixel(&game->img, x + j,
					y + i, color);
			j++;
		}
		i++;
	}
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
	if (game->hud.hand_apple.img)
		mlx_destroy_image(game->mlx, game->hud.hand_apple.img);
	if (game->hud.hand_egg.img)
		mlx_destroy_image(game->mlx, game->hud.hand_egg.img);
}
