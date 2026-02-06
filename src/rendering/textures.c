/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:50:25 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/29 23:53:34 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_texture(t_game *game, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (0);
	tex->addr = (int *)mlx_get_data_addr(tex->img,
			&tex->pixel_bits, &tex->size_line, &tex->endian);
	return (1);
}

static void	load_floor_ceil_textures(t_game *game)
{
	game->tex.use_floor_tex = 0;
	game->tex.use_ceil_tex = 0;
	if (!game->tex.floor_path)
		game->tex.floor_path = ft_strdup("./textures/floor.xpm");
	if (!game->tex.ceil_path)
		game->tex.ceil_path = ft_strdup("./textures/ceiling.xpm");
	if (game->tex.floor_path)
	{
		if (load_texture(game, &game->tex.floor_tex, game->tex.floor_path))
			game->tex.use_floor_tex = 1;
	}
	if (game->tex.ceil_path)
	{
		if (load_texture(game, &game->tex.ceil_tex, game->tex.ceil_path))
			game->tex.use_ceil_tex = 1;
	}
}

int	load_textures(t_game *game)
{
	if (!load_texture(game, &game->tex.north, game->tex.no_path))
		return (error_msg("Failed to load north texture"), 0);
	if (!load_texture(game, &game->tex.south, game->tex.so_path))
		return (error_msg("Failed to load south texture"), 0);
	if (!load_texture(game, &game->tex.west, game->tex.we_path))
		return (error_msg("Failed to load west texture"), 0);
	if (!load_texture(game, &game->tex.east, game->tex.ea_path))
		return (error_msg("Failed to load east texture"), 0);
	load_floor_ceil_textures(game);
	return (1);
}

void	free_textures(t_game *game)
{
	if (game->tex.north.img)
		mlx_destroy_image(game->mlx, game->tex.north.img);
	if (game->tex.south.img)
		mlx_destroy_image(game->mlx, game->tex.south.img);
	if (game->tex.west.img)
		mlx_destroy_image(game->mlx, game->tex.west.img);
	if (game->tex.east.img)
		mlx_destroy_image(game->mlx, game->tex.east.img);
	if (game->tex.floor_tex.img)
		mlx_destroy_image(game->mlx, game->tex.floor_tex.img);
	if (game->tex.ceil_tex.img)
		mlx_destroy_image(game->mlx, game->tex.ceil_tex.img);
}
