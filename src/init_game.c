/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:12:23 by ilsadi            #+#    #+#             */
/*   Updated: 2025/10/21 19:01:21 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT || x <= 0 || y <= 0 || color < 0)
		return ;
	pixel = y * (image->size_line / 4) + x;
	image->address[pixel] = color;
}

// void	display_background(t_game *game)
// {
// 	int	x;
// 	int	y;
// 	int	color;

// 	color = 0x00FF00;
// 	y = 0;
// 	while (y < SCREEN_HEIGHT)
// 	{
// 		x = 0;
// 		if (y > SCREEN_HEIGHT / 2)
// 		{
// 			color = 0xFF0000;
			
// 		}
// 		while (x < SCREEN_WIDTH)
// 		{
// 			put_pixel(game->img, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }