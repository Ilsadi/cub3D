/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:12:23 by ilsadi            #+#    #+#             */
/*   Updated: 2025/12/29 09:08:50 by ilsadi           ###   ########.fr       */
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

	if (game->tex.ceil_set == 0 || game->tex.floor_set == 0)
		clean_everything(game);
	color = game->tex.ceil; 
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		if (y > HEIGHT / 2)
		{
			color = game->tex.floor;
		}
		while (x < WIDTH)
		{
			put_pixel(&game->img, x, y, color);
			x++;
		}
		y++;
	}
}

// void	find_player_position(t_game *game)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < game->map.map_size)
// 	{
// 		j = 0;
// 		while (j < (int)ft_strlen(game->map.map[i]))
// 		{
// 			if (game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S' ||
// 				game->map.map[i][j] == 'E' || game->map.map[i][j] == 'W')
// 			{
// 				game->player_x = j + 0.5;
// 				game->player_y = i + 0.5;
// 				game->map.map[i][j] = '0';
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	find_angle(t_game *game, int i, int j)
// {
// 	if (game->map.map[i][j] == 'N')
// 		game->angle = M_PI / 2;
// 	else if (game->map.map[i][j] == 'S')
// 		game->angle = 3 * M_PI / 2;
// 	else if (game->map.map[i][j] == 'E')
// 		game->angle = 0;
// 	else if (game->map.map[i][j] == 'W')
// 		game->angle = M_PI;
// }

// void	init_pov(t_game *game)
// {
// 	game->ray.dir_x = cos(game->angle);
// 	game->ray.dir_y = -sin(game->angle);
// 	game->ray.plane_x = sin(game->angle) * 0.66;
// 	game->ray.plane_y = cos(game->angle) * 0.66;
// }

// void	init_raycast(t_raycast *ray, t_game *game, int x)
// {
// 	double	camera_x;
	
// 	camera_x = 2 * x / (double)WIDTH - 1;
// 	ray->ray_dir_x = ray->dir_x + ray->plane_x
// 		* camera_x;
// 	ray->ray_dir_y = ray->dir_y + ray->plane_y
// 		* camera_x;
// 	ray->map_x = game->player_x;
// 	ray->map_y = game->player_y;
// 	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
// 	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
// }