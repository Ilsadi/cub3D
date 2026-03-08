/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 19:03:03 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/08 19:07:17 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_door_frame(t_game *game, int i)
{
	char	*path;
	char	*num;
	char	*tmp;

	num = ft_itoa(i);
	tmp = ft_strjoin("textures/door/", num);
	path = ft_strjoin(tmp, ".xpm");
	free(num);
	free(tmp);
	game->doors.frames[i].img = mlx_xpm_file_to_image(game->mlx,
			path, &game->doors.frames[i].width,
			&game->doors.frames[i].height);
	if (game->doors.frames[i].img)
		game->doors.frames[i].addr = (int *)mlx_get_data_addr(
				game->doors.frames[i].img,
				&game->doors.frames[i].pixel_bits,
				&game->doors.frames[i].size_line,
				&game->doors.frames[i].endian);
	free(path);
}

static void	find_doors_in_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == 'D'
				&& game->doors.count < MAX_DOORS)
			{
				game->doors.list[game->doors.count].x = x;
				game->doors.list[game->doors.count].y = y;
				game->doors.list[game->doors.count].state = 0;
				game->doors.list[game->doors.count].open = 0;
				game->doors.count++;
			}
			x++;
		}
		y++;
	}
}

void	init_doors(t_game *game)
{
	int	i;

	game->doors.count = 0;
	i = 0;
	while (i < DOOR_FRAMES)
	{
		load_door_frame(game, i);
		i++;
	}
	find_doors_in_map(game);
}

void	free_doors(t_game *game)
{
	int	i;

	i = 0;
	while (i < DOOR_FRAMES)
	{
		if (game->doors.frames[i].img)
			mlx_destroy_image(game->mlx,
				game->doors.frames[i].img);
		i++;
	}
}
