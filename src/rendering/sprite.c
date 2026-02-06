/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 08:09:34 by amacaull          #+#    #+#             */
/*   Updated: 2026/02/06 13:37:39 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_sprite_transform(t_game *game, t_sprite_render *sr, int i)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	sprite_scale;

	sprite_x = game->collectibles.list[i].x + 0.5 - game->player.x;
	sprite_y = game->collectibles.list[i].y + 0.5 - game->player.y;
	inv_det = 1.0 / (game->ray.plane_x * game->ray.dir_y
			- game->ray.dir_x * game->ray.plane_y);
	sr->transform_x = inv_det * (game->ray.dir_y * sprite_x
			- game->ray.dir_x * sprite_y);
	sr->transform_y = inv_det * (-game->ray.plane_y * sprite_x
			+ game->ray.plane_x * sprite_y);
	sr->screen_x = (int)((WIDTH / 2) * (1 + sr->transform_x / sr->transform_y));
	sprite_scale = 0.15;
	sr->height = abs((int)(HEIGHT / sr->transform_y * sprite_scale));
	sr->width = abs((int)(HEIGHT / sr->transform_y * sprite_scale));
}

static void	calc_sprite_bounds(t_sprite_render *sr, int pitch)
{
	int	v_offset;

	v_offset = sr->height * 2;
	sr->draw_start_y = -sr->height / 2 + HEIGHT / 2 + pitch + v_offset;
	if (sr->draw_start_y < 0)
		sr->draw_start_y = 0;
	sr->draw_end_y = sr->height / 2 + HEIGHT / 2 + pitch + v_offset;
	if (sr->draw_end_y >= HEIGHT)
		sr->draw_end_y = HEIGHT - 1;
	sr->draw_start_x = -sr->width / 2 + sr->screen_x;
	if (sr->draw_start_x < 0)
		sr->draw_start_x = 0;
	sr->draw_end_x = sr->width / 2 + sr->screen_x;
	if (sr->draw_end_x >= WIDTH)
		sr->draw_end_x = WIDTH - 1;
}

static void	draw_sprite_column(t_game *game, t_sprite_render *sr,
	int x, t_img *tex)
{
	int		y;
	int		tex_x;
	int		tex_y;
	int		color;
	int		sprite_height;

	tex_x = (int)(256 * (x - (-sr->width / 2 + sr->screen_x))
			* tex->width / sr->width) / 256;
	if (tex_x < 0 || tex_x >= tex->width)
		return ;
	sprite_height = sr->draw_end_y - sr->draw_start_y;
	if (sprite_height <= 0)
		return ;
	y = sr->draw_start_y;
	while (y < sr->draw_end_y)
	{
		tex_y = (y - sr->draw_start_y) * tex->height / sprite_height;
		if (tex_y >= 0 && tex_y < tex->height)
		{
			color = tex->addr[tex_y * tex->width + tex_x];
			if ((color & 0x00FFFFFF) != 0)
			{
				color = apply_shading(color, sr->transform_y);
				put_pixel(&game->img, x, y, color);
			}
		}
		y++;
	}
	(void)game;
}

static void	render_single_sprite(t_game *game, int i, double *z_buffer)
{
	t_sprite_render	sr;
	t_img			*tex;
	int				x;

	if (game->collectibles.list[i].collected)
		return ;
	calc_sprite_transform(game, &sr, i);
	if (sr.transform_y <= 0.1)
		return ;
	calc_sprite_bounds(&sr, game->player.pitch);
	tex = &game->collectibles.key_tex;
	if (!tex->img)
		return ;
	x = sr.draw_start_x;
	while (x < sr.draw_end_x)
	{
		if (x >= 0 && x < WIDTH && sr.transform_y < z_buffer[x])
			draw_sprite_column(game, &sr, x, tex);
		x++;
	}
}

static void	sort_sprites_by_distance(t_game *game, int *order, double *dist)
{
	int		i;
	int		j;
	int		tmp_order;
	double	tmp_dist;

	i = 0;
	while (i < game->collectibles.count)
	{
		dist[i] = pow(game->player.x - game->collectibles.list[i].x - 0.5, 2)
			+ pow(game->player.y - game->collectibles.list[i].y - 0.5, 2);
		order[i] = i;
		i++;
	}
	i = 0;
	while (i < game->collectibles.count - 1)
	{
		j = i + 1;
		while (j < game->collectibles.count)
		{
			if (dist[i] < dist[j])
			{
				tmp_dist = dist[i];
				dist[i] = dist[j];
				dist[j] = tmp_dist;
				tmp_order = order[i];
				order[i] = order[j];
				order[j] = tmp_order;
			}
			j++;
		}
		i++;
	}
}

void	render_sprites(t_game *game, double *z_buffer)
{
	int		order[MAX_COLLECTIBLES];
	double	dist[MAX_COLLECTIBLES];
	int		i;

	if (game->collectibles.count == 0)
		return ;
	sort_sprites_by_distance(game, order, dist);
	i = 0;
	while (i < game->collectibles.count)
	{
		render_single_sprite(game, order[i], z_buffer);
		i++;
	}
}
