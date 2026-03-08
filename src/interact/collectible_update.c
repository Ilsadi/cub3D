/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:20:20 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/08 19:06:32 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_collectibles(t_game *game)
{
	if (game->collectibles.key_tex.img)
		mlx_destroy_image(game->mlx,
			game->collectibles.key_tex.img);
	if (game->collectibles.apple_tex.img)
		mlx_destroy_image(game->mlx,
			game->collectibles.apple_tex.img);
	if (game->collectibles.egg_tex.img)
		mlx_destroy_image(game->mlx,
			game->collectibles.egg_tex.img);
	if (game->hud.key_icon.img)
		mlx_destroy_image(game->mlx, game->hud.key_icon.img);
	if (game->hud.apple_icon.img)
		mlx_destroy_image(game->mlx,
			game->hud.apple_icon.img);
	if (game->hud.egg_icon.img)
		mlx_destroy_image(game->mlx, game->hud.egg_icon.img);
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
			dx = game->player.x
				- (game->collectibles.list[i].x + 0.5);
			dy = game->player.y
				- (game->collectibles.list[i].y + 0.5);
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
