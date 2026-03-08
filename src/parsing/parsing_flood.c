/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_flood.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:13:34 by ilsadi            #+#    #+#             */
/*   Updated: 2026/03/08 19:14:48 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_blocking_tile(char c)
{
	if (c == '1' || c == '2' || c == 'D')
		return (1);
	return (0);
}

static int	is_visited(char c)
{
	if (c == 'f' || c == 'k' || c == 'm'
		|| c == 'a' || c == 'g')
		return (1);
	return (0);
}

static char	get_visited_marker(char c)
{
	if (c == 'K')
		return ('k');
	if (c == 'M')
		return ('m');
	if (c == 'A')
		return ('a');
	if (c == 'V')
		return ('g');
	return ('f');
}

int	flood_fill(char **map, int x, int y, t_game *game)
{
	char	c;

	if (x < 0 || y < 0 || x >= game->map.width
		|| y >= game->map.height)
		return (0);
	c = map[y][x];
	if (c == ' ')
		return (0);
	if (is_blocking_tile(c))
		return (1);
	if (is_visited(c))
		return (1);
	map[y][x] = get_visited_marker(c);
	if (!flood_fill(map, x + 1, y, game))
		return (0);
	if (!flood_fill(map, x - 1, y, game))
		return (0);
	if (!flood_fill(map, x, y + 1, game))
		return (0);
	if (!flood_fill(map, x, y - 1, game))
		return (0);
	return (1);
}
