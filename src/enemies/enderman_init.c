/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enderman_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 13:35:10 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/08 18:59:09 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	ender_dist(t_game *game, int idx)
{
	return (pow(game->endermen.list[idx].x - game->player.x, 2)
		+ pow(game->endermen.list[idx].y - game->player.y, 2));
}

void	sort_enderman(t_game *game)
{
	int			i;
	int			j;
	t_enderman	tmp;

	i = 0;
	while (i < game->endermen.count - 1)
	{
		j = i + 1;
		while (j < game->endermen.count)
		{
			if (ender_dist(game, j) > ender_dist(game, i))
			{
				tmp = game->endermen.list[i];
				game->endermen.list[i] = game->endermen.list[j];
				game->endermen.list[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	init_enderman(t_game *game)
{
	game->endermen.texture.img = mlx_xpm_file_to_image(game->mlx,
			"textures/enemies/enderman.xpm",
			&game->endermen.texture.width,
			&game->endermen.texture.height);
	if (game->endermen.texture.img)
		game->endermen.texture.addr = (int *)mlx_get_data_addr(
				game->endermen.texture.img,
				&game->endermen.texture.pixel_bits,
				&game->endermen.texture.size_line,
				&game->endermen.texture.endian);
	game->endermen.texture_angry.img = mlx_xpm_file_to_image(
			game->mlx,
			"textures/enemies/enderman_angry.xpm",
			&game->endermen.texture_angry.width,
			&game->endermen.texture_angry.height);
	if (game->endermen.texture_angry.img)
		game->endermen.texture_angry.addr = (int *)mlx_get_data_addr(
				game->endermen.texture_angry.img,
				&game->endermen.texture_angry.pixel_bits,
				&game->endermen.texture_angry.size_line,
				&game->endermen.texture_angry.endian);
	game->hud.invincibility = 0;
	srand((unsigned int)time(NULL));
}

void	free_enderman(t_game *game)
{
	if (game->endermen.texture.img)
		mlx_destroy_image(game->mlx, game->endermen.texture.img);
	if (game->endermen.texture_angry.img)
		mlx_destroy_image(game->mlx,
			game->endermen.texture_angry.img);
}
