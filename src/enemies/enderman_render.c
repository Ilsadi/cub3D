/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enderman_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 08:59:58 by amacaull          #+#    #+#             */
/*   Updated: 2026/02/07 16:11:55 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_ender_transform(t_game *game, t_sprite_render *sr,
	t_enderman *ender)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	sprite_scale;

	sprite_x = ender->x - game->player.x;
	sprite_y = ender->y - game->player.y;
	inv_det = 1.0 / (game->ray.plane_x * game->ray.dir_y
			- game->ray.dir_x * game->ray.plane_y);
	sr->transform_x = inv_det * (game->ray.dir_y * sprite_x
			- game->ray.dir_x * sprite_y);
	sr->transform_y = inv_det * (-game->ray.plane_y * sprite_x
			+ game->ray.plane_x * sprite_y);
	sr->screen_x = (int)((WIDTH / 2) * (1 + sr->transform_x / sr->transform_y));
	sprite_scale = 1;
	sr->height = abs((int)(HEIGHT / sr->transform_y * sprite_scale));
	sr->width = abs((int)(HEIGHT / sr->transform_y * sprite_scale * 0.5));
}

static void	calc_ender_bounds(t_game *game, t_sprite_render *sr)
{
	int		v_move_screen;
	double	v_move;

	v_move = 0.02;
	v_move_screen = (int)(v_move * HEIGHT / sr->transform_y);
	sr->orig_start_y = -sr->height / 2 + HEIGHT / 2 + game->player.pitch
		+ v_move_screen;
	sr->draw_start_y = sr->orig_start_y;
	if (sr->draw_start_y < 0)
		sr->draw_start_y = 0;
	sr->draw_end_y = sr->height / 2 + HEIGHT / 2 + game->player.pitch
		+ v_move_screen;
	if (sr->draw_end_y >= HEIGHT)
		sr->draw_end_y = HEIGHT - 1;
	sr->draw_start_x = -sr->width / 2 + sr->screen_x;
	if (sr->draw_start_x < 0)
		sr->draw_start_x = 0;
	sr->draw_end_x = sr->width / 2 + sr->screen_x;
	if (sr->draw_end_x >= WIDTH)
		sr->draw_end_x = WIDTH - 1;
}

static void	draw_ender_column(t_game *game, t_sprite_render *sr,
	int x, t_img *tex)
{
	int		y;
	int		tex_x;
	int		tex_y;
	int		color;

	tex_x = (int)(256 * (x - (-sr->width / 2 + sr->screen_x))
			* tex->width / sr->width) / 256;
	if (tex_x < 0 || tex_x >= tex->width)
		return ;
	if (sr->height <= 0)
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

static void	render_single_enderman(t_game *game, t_enderman *ender,
	double *z_buffer)
{
	t_sprite_render	sr;
	int				x;
	t_img			*tex;

	if (!ender->is_active)
		return ;
	if (ender->is_angry && game->endermen.texture_angry.img)
		tex = &game->endermen.texture_angry;
	else
		tex = &game->endermen.texture;
	if (!tex->img)
		return ;
	calc_ender_transform(game, &sr, ender);
	if (sr.transform_y <= 0.1)
		return ;
	calc_ender_bounds(game, &sr);
	x = sr.draw_start_x;
	while (x < sr.draw_end_x)
	{
		if (x >= 0 && x < WIDTH && sr.transform_y < z_buffer[x])
			draw_ender_column(game, &sr, x, tex);
		x++;
	}
}

static void	sort_endermen(t_game *game)
{
	int			i;
	int			j;
	double		dist_i;
	double		dist_j;
	t_enderman	tmp;

	i = 0;
	while (i < game->endermen.count - 1)
	{
		j = i + 1;
		while (j < game->endermen.count)
		{
			dist_i = pow(game->endermen.list[i].x - game->player.x, 2)
				+ pow(game->endermen.list[i].y - game->player.y, 2);
			dist_j = pow(game->endermen.list[j].x - game->player.x, 2)
				+ pow(game->endermen.list[j].y - game->player.y, 2);
			if (dist_j > dist_i)
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

void	render_endermen(t_game *game, double *z_buffer)
{
	int	i;

	sort_endermen(game);
	i = 0;
	while (i < game->endermen.count)
	{
		render_single_enderman(game, &game->endermen.list[i], z_buffer);
		i++;
	}
}
