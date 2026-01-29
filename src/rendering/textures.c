/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:50:25 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/29 12:50:38 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_texture(t_game *game, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&game->tex.tex_width, &game->tex.tex_height);
	if (!tex->img)
		return (0);
	tex->addr = (int *)mlx_get_data_addr(tex->img,
			&tex->pixel_bits, &tex->size_line, &tex->endian);
	return (1);
}

int	load_textures(t_game *game)
{
	game->tex.tex_width = 64;
	game->tex.tex_height = 64;
	if (!load_texture(game, &game->tex.north, game->tex.no_path))
		return (error_msg("Failed to load north texture"), 0);
	if (!load_texture(game, &game->tex.south, game->tex.so_path))
		return (error_msg("Failed to load south texture"), 0);
	if (!load_texture(game, &game->tex.west, game->tex.we_path))
		return (error_msg("Failed to load west texture"), 0);
	if (!load_texture(game, &game->tex.east, game->tex.ea_path))
		return (error_msg("Failed to load east texture"), 0);
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
}
