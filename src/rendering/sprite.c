/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 08:09:34 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/11 14:00:54 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_sprite_transform(t_game *game,
	t_sprite_render *sr, int i, double scale)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = game->collectibles.list[i].x + 0.5
		- game->player.x;
	sprite_y = game->collectibles.list[i].y + 0.5
		- game->player.y;
	inv_det = 1.0 / (game->ray.plane_x * game->ray.dir_y
			- game->ray.dir_x * game->ray.plane_y);
	sr->transform_x = inv_det * (game->ray.dir_y * sprite_x
			- game->ray.dir_x * sprite_y);
	sr->transform_y = inv_det * (-game->ray.plane_y * sprite_x
			+ game->ray.plane_x * sprite_y);
	sr->screen_x = (int)((WIDTH / 2)
			* (1 + sr->transform_x / sr->transform_y));
	sr->height = abs((int)(HEIGHT / sr->transform_y * scale));
	sr->width = sr->height;
}

void	calc_sprite_bounds(t_sprite_render *sr, int pitch,
	double vground, double transform_y)
{
	int	v_screen;

	v_screen = (int)(vground * HEIGHT / transform_y);
	sr->orig_start_y = -sr->height / 2 + HEIGHT / 2
		+ pitch + v_screen;
	sr->draw_start_y = sr->orig_start_y;
	if (sr->draw_start_y < 0)
		sr->draw_start_y = 0;
	sr->draw_end_y = sr->height / 2 + HEIGHT / 2
		+ pitch + v_screen;
	if (sr->draw_end_y >= HEIGHT)
		sr->draw_end_y = HEIGHT - 1;
	sr->draw_start_x = -sr->width / 2 + sr->screen_x;
	if (sr->draw_start_x < 0)
		sr->draw_start_x = 0;
	sr->draw_end_x = sr->width / 2 + sr->screen_x;
	if (sr->draw_end_x >= WIDTH)
		sr->draw_end_x = WIDTH - 1;
}

void	draw_sprite_column(t_game *game,
	t_sprite_render *sr, int x, t_img *tex)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	tex_x = (int)(256 * (x - (-sr->width / 2 + sr->screen_x))
			* tex->width / sr->width) / 256;
	if (tex_x < 0 || tex_x >= tex->width || sr->height <= 0)
		return ;
	y = sr->draw_start_y;
	while (y < sr->draw_end_y)
	{
		tex_y = (y - sr->orig_start_y) * tex->height / sr->height;
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
}

t_img	*get_collectible_tex(t_game *game, int i)
{
	int	type;

	type = game->collectibles.list[i].type;
	if (type == ITEM_APPLE)
		return (&game->collectibles.apple_tex);
	if (type == ITEM_EGG)
		return (&game->collectibles.egg_tex);
	return (&game->collectibles.key_tex);
}
