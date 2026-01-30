/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:13:26 by ilsadi            #+#    #+#             */
/*   Updated: 2026/01/30 16:40:24 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_texture_paths(t_game *game)
{
	if (game->tex.no_path)
		free(game->tex.no_path);
	if (game->tex.so_path)
		free(game->tex.so_path);
	if (game->tex.we_path)
		free(game->tex.we_path);
	if (game->tex.ea_path)
		free(game->tex.ea_path);
}

static void	free_texture_images(t_game *game)
{
	if (game->tex.north.img)
		mlx_destroy_image(game->mlx, game->tex.north.img);
	if (game->tex.south.img)
		mlx_destroy_image(game->mlx, game->tex.south.img);
	if (game->tex.west.img)
		mlx_destroy_image(game->mlx, game->tex.west.img);
	if (game->tex.east.img)
		mlx_destroy_image(game->mlx, game->tex.east.img);
}

int	clean_everything(t_game *game)
{
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	free_hud(game);
	free_animations(game);
	free_texture_images(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
// 	if (game->mlx)
// 	{
// 		mlx_destroy_display(game->mlx);
// 		free(game->mlx);
// 	}
	free_texture_paths(game);
	if (game->map.grid)
		ft_free_tab(game->map.grid);
	exit(0);
	return (0);
}
