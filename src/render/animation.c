/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:12:42 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/30 16:37:56 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_frame(t_game *game, int i, char *base_path)
{
	char	*path;
	char	*num;
	char	*tmp;

	num = ft_itoa(i);
	tmp = ft_strjoin(base_path, num);
	path = ft_strjoin(tmp, ".xpm");
	free(num);
	free(tmp);
	game->wall_anim.frames[i].img = mlx_xpm_file_to_image(game->mlx, path,
			&game->wall_anim.frames[i].width,
			&game->wall_anim.frames[i].height);
	if (game->wall_anim.frames[i].img)
		game->wall_anim.frames[i].addr = (int *)mlx_get_data_addr(
				game->wall_anim.frames[i].img,
				&game->wall_anim.frames[i].pixel_bits,
				&game->wall_anim.frames[i].size_line,
				&game->wall_anim.frames[i].endian);
	else
		printf("Error\nFailed to load anim frame: %s\n", path);
	free(path);
}

void	init_animations(t_game *game)
{
	int	i;

	game->wall_anim.count = ANIM_FRAMES;
	game->wall_anim.current = 0;
	game->wall_anim.timer = 0;
	game->wall_anim.frames = malloc(sizeof(t_img) * ANIM_FRAMES);
	if (!game->wall_anim.frames)
		return ;
	i = 0;
	while (i < ANIM_FRAMES)
	{
		load_frame(game, i, "textures/anim/");
		i++;
	}
}

void	update_animation(t_game *game)
{
	game->wall_anim.timer++;
	if (game->wall_anim.timer >= ANIM_SPEED)
	{
		game->wall_anim.timer = 0;
		game->wall_anim.current++;
		if (game->wall_anim.current >= game->wall_anim.count)
			game->wall_anim.current = 0;
	}
}

void	free_animations(t_game *game)
{
	int	i;

	if (!game->wall_anim.frames)
		return ;
	i = 0;
	while (i < game->wall_anim.count)
	{
		if (game->wall_anim.frames[i].img)
			mlx_destroy_image(game->mlx, game->wall_anim.frames[i].img);
		i++;
	}
	free(game->wall_anim.frames);
}
