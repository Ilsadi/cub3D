/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:15:46 by amacaull          #+#    #+#             */
/*   Updated: 2026/02/06 14:59:27 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_game *game)
{
	if (game->gameover.active)
	{
		check_gameover(game);
		render_gameover(game);
		mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
		return (0);
	}
	update_player(game);
	update_metabolism(game);
	update_animation(game);
	update_collectibles(game);
	update_endermen(game);
	check_gameover(game);
	if (game->tex.use_floor_tex || game->tex.use_ceil_tex)
		render_floor_ceiling(game);
	render_frame(game);
	render_minimap(game);
	render_hud(game);
	if (game->gameover.active)
		render_gameover(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
