/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:20:42 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/08 19:06:44 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_door	*get_door_at(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->doors.count)
	{
		if (game->doors.list[i].x == x
			&& game->doors.list[i].y == y)
			return (&game->doors.list[i]);
		i++;
	}
	return (NULL);
}

t_img	*get_door_texture(t_game *game, int x, int y)
{
	t_door	*door;

	door = get_door_at(game, x, y);
	if (!door)
		return (&game->doors.frames[0]);
	if (door->state >= DOOR_FRAMES)
		return (&game->doors.frames[DOOR_FRAMES - 1]);
	return (&game->doors.frames[door->state]);
}

int	is_door(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map.width
		|| y >= game->map.height)
		return (0);
	return (game->map.grid[y][x] == 'D');
}
