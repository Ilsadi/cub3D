/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:15:46 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/30 17:25:34 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_game *game)
{
	update_player(game);
	update_metabolism(game);
	update_animation(game);
	if (game->tex.use_floor_tex || game->tex.use_ceil_tex)
		render_floor_ceiling(game);
	render_frame(game);
	render_minimap(game);
	render_hud(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
