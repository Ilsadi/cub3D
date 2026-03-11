/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:23:27 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/11 14:08:46 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_sprite_params(t_game *game, int i,
	double *scale, double *vground)
{
	*scale = SCALE_DEFAULT;
	*vground = VGROUND_DEFAULT;
	if (game->collectibles.list[i].type == ITEM_EGG)
	{
		*scale = SCALE_EGG;
		*vground = VGROUND_EGG;
	}
}

static void	render_single_sprite(t_game *game, int i,
	double *z_buffer)
{
	t_sprite_render	sr;
	t_img			*tex;
	int				x;
	double			scale;
	double			vground;

	if (game->collectibles.list[i].collected)
		return ;
	get_sprite_params(game, i, &scale, &vground);
	calc_sprite_transform(game, &sr, i, scale);
	if (sr.transform_y <= 0.1)
		return ;
	calc_sprite_bounds(&sr, game->player.pitch,
		vground, sr.transform_y);
	tex = get_collectible_tex(game, i);
	if (!tex->img)
		return ;
	x = sr.draw_start_x;
	while (x < sr.draw_end_x)
	{
		if (x >= 0 && x < WIDTH
			&& sr.transform_y < z_buffer[x])
			draw_sprite_column(game, &sr, x, tex);
		x++;
	}
}

static void	init_sprite_order(t_game *game, int *order,
	double *dist)
{
	int	i;

	i = 0;
	while (i < game->collectibles.count)
	{
		dist[i] = pow(game->player.x
				- game->collectibles.list[i].x - 0.5, 2)
			+ pow(game->player.y
				- game->collectibles.list[i].y - 0.5, 2);
		order[i] = i;
		i++;
	}
}

static void	sort_sprites_by_distance(t_game *game,
	int *order, double *dist)
{
	int		i;
	int		j;
	int		tmp_o;
	double	tmp_d;

	init_sprite_order(game, order, dist);
	i = 0;
	while (i < game->collectibles.count - 1)
	{
		j = i + 1;
		while (j < game->collectibles.count)
		{
			if (dist[i] < dist[j])
			{
				tmp_d = dist[i];
				dist[i] = dist[j];
				dist[j] = tmp_d;
				tmp_o = order[i];
				order[i] = order[j];
				order[j] = tmp_o;
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
