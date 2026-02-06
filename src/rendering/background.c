/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 23:37:29 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/30 17:24:44 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray_dirs(t_game *game, t_floor *fl)
{
	fl->ray_dir_x0 = game->ray.dir_x - game->ray.plane_x;
	fl->ray_dir_y0 = game->ray.dir_y - game->ray.plane_y;
	fl->ray_dir_x1 = game->ray.dir_x + game->ray.plane_x;
	fl->ray_dir_y1 = game->ray.dir_y + game->ray.plane_y;
}

static void	calc_row_dist(t_floor *fl, int p)
{
	fl->pos_z = 0.5 * HEIGHT;
	if (p == 0)
		fl->row_distance = fl->pos_z;
	else
		fl->row_distance = fl->pos_z / abs(p);
	fl->floor_step_x = fl->row_distance
		* (fl->ray_dir_x1 - fl->ray_dir_x0) / WIDTH;
	fl->floor_step_y = fl->row_distance
		* (fl->ray_dir_y1 - fl->ray_dir_y0) / WIDTH;
}

static int	get_pixel_color(t_game *game, t_floor *fl, int is_ceiling)
{
	int		color;
	t_img	*tex;
	int		tx;
	int		ty;

	if (is_ceiling)
	{
		if (!game->tex.use_ceil_tex)
			return (game->tex.ceil);
		tex = &game->tex.ceil_tex;
	}
	else
	{
		if (!game->tex.use_floor_tex)
			return (game->tex.floor);
		tex = &game->tex.floor_tex;
	}
	tx = (int)(tex->width * (fl->floor_x - floor(fl->floor_x)))
		& (tex->width - 1);
	ty = (int)(tex->height * (fl->floor_y - floor(fl->floor_y)))
		& (tex->height - 1);
	color = tex->addr[ty * tex->width + tx];
	return (color);
}

static void	draw_scanline(t_game *game, t_floor *fl, int y, int is_ceiling)
{
	int	x;
	int	color;

	fl->floor_x = game->player.x + fl->row_distance * fl->ray_dir_x0;
	fl->floor_y = game->player.y + fl->row_distance * fl->ray_dir_y0;
	x = 0;
	while (x < WIDTH)
	{
		color = get_pixel_color(game, fl, is_ceiling);
		color = apply_shading(color, fl->row_distance);
		put_pixel(&game->img, x, y, color);
		fl->floor_x += fl->floor_step_x;
		fl->floor_y += fl->floor_step_y;
		x++;
	}
}

void	render_floor_ceiling(t_game *game)
{
	int		y;
	int		horizon;
	int		p;
	t_floor	fl;

	init_ray_dirs(game, &fl);
	horizon = HEIGHT / 2 + game->player.pitch;
	y = 0;
	while (y < HEIGHT)
	{
		p = y - horizon;
		if (p == 0)
		{
			y++;
			continue ;
		}
		calc_row_dist(&fl, p);
		draw_scanline(game, &fl, y, (y < horizon));
		y++;
	}
}
