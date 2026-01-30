/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:03:57 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/30 16:38:26 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	*get_texture(t_game *game, t_ray *ray)
{
	if (game->map.grid[ray->map_y][ray->map_x] == '2')
		return (&game->wall_anim.frames[game->wall_anim.current]);

	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (&game->tex.east);
		return (&game->tex.west);
	}
	if (ray->step_y > 0)
		return (&game->tex.south);
	return (&game->tex.north);
}

static void	calc_tex_x(t_ray *ray, t_img *tex)
{
	ray->tex_x = (int)(ray->wall_x * tex->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
}

static void	draw_column_loop(t_game *game, int x, int *y, t_img *tex)
{
	int	color;

	while (*y <= game->ray.draw_end)
	{
		game->ray.tex_y = (int)game->ray.tex_pos & (tex->height - 1);
		game->ray.tex_pos += game->ray.tex_step;
		if (game->ray.tex_y >= tex->height)
			game->ray.tex_y = tex->height - 1;
		if (game->ray.tex_y < 0)
			game->ray.tex_y = 0;
		color = tex->addr[game->ray.tex_y * tex->width + game->ray.tex_x];
		if (game->ray.side == 1)
			color = ((color >> 1) & 0x7F7F7F);
		color = apply_shading(color, game->ray.perp_wall_dist);
		put_pixel(&game->img, x, (*y)++, color);
	}
}

static void	draw_column(t_game *game, int x, t_ray *ray)
{
	int		y;
	t_img	*tex;

	y = 0;
	if (!game->tex.use_ceil_tex)
	{
		while (y < ray->draw_start)
			put_pixel(&game->img, x, y++, game->tex.ceil);
	}
	else
		y = ray->draw_start;
	tex = get_texture(game, ray);
	calc_tex_x(ray, tex);
	ray->tex_step = 1.0 * tex->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - HEIGHT / 2
			+ ray->line_height / 2 - game->player.pitch) * ray->tex_step;
	draw_column_loop(game, x, &y, tex);
	if (!game->tex.use_floor_tex)
	{
		while (y < HEIGHT)
			put_pixel(&game->img, x, y++, game->tex.floor);
	}
}

void	render_frame(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(game, &game->ray, x);
		init_step(game, &game->ray);
		perform_dda(game, &game->ray);
		calc_wall_params(game, &game->ray);
		draw_column(game, x, &game->ray);
		x++;
	}
}
