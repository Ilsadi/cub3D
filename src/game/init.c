/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:12:23 by ilsadi            #+#    #+#             */
/*   Updated: 2026/01/28 10:01:08 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_img(t_game *game)
{
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	game->img.img = NULL;
	game->img.addr = NULL;
	game->img.pixel_bits = 0;
	game->img.size_line = 0;
	game->img.endian = 0;
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = (int *)mlx_get_data_addr(game->img.img,
			&game->img.pixel_bits, &game->img.size_line, &game->img.endian);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	int	pixel;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	pixel = y * (img->size_line / 4) + x;
	img->addr[pixel] = color;
}
