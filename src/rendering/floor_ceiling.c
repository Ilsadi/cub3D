/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 23:37:29 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/29 23:54:00 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_floor_ray(t_game *game, t_floor *fl, int y)
{
	fl->ray_dir_x0 = game->ray.dir_x - game->ray.plane_x;
	fl->ray_dir_y0 = game->ray.dir_y - game->ray.plane_y;
	fl->ray_dir_x1 = game->ray.dir_x + game->ray.plane_x;
	fl->ray_dir_y1 = game->ray.dir_y + game->ray.plane_y;
	fl->p = y - HEIGHT / 2;
	fl->pos_z = 0.5 * HEIGHT;
	fl->row_distance = fl->pos_z / fl->p;
	fl->floor_step_x = fl->row_distance * (fl->ray_dir_x1 - fl->ray_dir_x0)
		/ WIDTH;
	fl->floor_step_y = fl->row_distance * (fl->ray_dir_y1 - fl->ray_dir_y0)
		/ WIDTH;
	fl->floor_x = game->player.x + fl->row_distance * fl->ray_dir_x0;
	fl->floor_y = game->player.y + fl->row_distance * fl->ray_dir_y0;
}

static int	get_floor_color(t_game *game, t_floor *fl)
{
	int	tx;
	int	ty;
	int	w;
	int	h;

	w = game->tex.floor_tex.width;
	h = game->tex.floor_tex.height;
	tx = (int)(w * (fl->floor_x - floor(fl->floor_x))) & (w - 1);
	ty = (int)(h * (fl->floor_y - floor(fl->floor_y))) & (h - 1);
	return (game->tex.floor_tex.addr[ty * w + tx]);
}

static int	get_ceiling_color(t_game *game, t_floor *fl)
{
	int	tx;
	int	ty;
	int	w;
	int	h;

	w = game->tex.ceil_tex.width;
	h = game->tex.ceil_tex.height;
	tx = (int)(w * (fl->floor_x - floor(fl->floor_x))) & (w - 1);
	ty = (int)(h * (fl->floor_y - floor(fl->floor_y))) & (h - 1);
	return (game->tex.ceil_tex.addr[ty * w + tx]);
}

void	render_floor_ceiling(t_game *game)
{
	int		y;
	int		x;
	t_floor	fl;
	int		color;

	y = HEIGHT / 2 + 1;
	while (y < HEIGHT)
	{
		init_floor_ray(game, &fl, y);
		x = 0;
		while (x < WIDTH)
		{
			if (game->tex.use_floor_tex)
				color = get_floor_color(game, &fl);
			else
				color = game->tex.floor;
			put_pixel(&game->img, x, y, color);
			if (game->tex.use_ceil_tex)
				color = get_ceiling_color(game, &fl);
			else
				color = game->tex.ceil;
			put_pixel(&game->img, x, HEIGHT - y - 1, color);
			fl.floor_x += fl.floor_step_x;
			fl.floor_y += fl.floor_step_y;
			x++;
		}
		y++;
	}
}
