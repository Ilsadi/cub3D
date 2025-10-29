/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:12:23 by ilsadi            #+#    #+#             */
/*   Updated: 2025/10/29 19:11:46 by ilsadi           ###   ########.fr       */
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

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0 || color < 0)
		return ;
	pixel = y * (img->size_line / 4) + x;
	img->addr[pixel] = color;
}

void	init_background(t_game *game)
{
	int	x;
	int	y;
	int	color;

	color = game->tex.ceil;
	if (!color)
		clean_everything(game);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		if (y > HEIGHT / 2)
		{
			color = game->tex.floor;
			if (!color)
				clean_everything(game);
		}
		while (x < WIDTH)
		{
			put_pixel(&game->img, x, y, color);
			x++;
		}
		y++;
	}
}