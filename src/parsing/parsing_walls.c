/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 03:59:44 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/08 14:07:27 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*create_normalized_line(t_game *game, int row)
{
	char	*line;
	int		j;
	int		len;

	line = malloc(sizeof(char) * (game->map.width + 1));
	if (!line)
		return (NULL);
	j = -1;
	while (++j < game->map.width)
		line[j] = ' ';
	line[game->map.width] = '\0';
	len = ft_strlen(game->map.grid[row]);
	j = -1;
	while (++j < len && j < game->map.width)
	{
		if (game->map.grid[row][j] == '\t')
			line[j] = ' ';
		else
			line[j] = game->map.grid[row][j];
	}
	return (line);
}

int	normalize_map(t_game *game)
{
	char	**new_grid;
	int		i;

	if (!game->map.grid || game->map.width <= 0 || game->map.height <= 0)
		return (0);
	new_grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!new_grid)
		return (0);
	i = -1;
	while (++i < game->map.height)
	{
		new_grid[i] = create_normalized_line(game, i);
		if (!new_grid[i])
			return (ft_free_tab(new_grid), 0);
	}
	new_grid[i] = NULL;
	ft_free_tab(game->map.grid);
	game->map.grid = new_grid;
	return (1);
}

static int	is_blocking_tile(char c)
{
	if (c == '1' || c == '2' || c == 'D')
		return (1);
	return (0);
}

static int	is_visited(char c)
{
	if (c == 'f' || c == 'k' || c == 'm' || c == 'a' || c == 'g')
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

static int	flood_fill(char **map, int x, int y, t_game *game)
{
	char	c;

	if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
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

static void	restore_visited(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
		{
			if (game->map.grid[y][x] == 'f')
				game->map.grid[y][x] = '0';
			else if (game->map.grid[y][x] == 'k')
				game->map.grid[y][x] = 'K';
			else if (game->map.grid[y][x] == 'm')
				game->map.grid[y][x] = 'M';
			else if (game->map.grid[y][x] == 'a')
				game->map.grid[y][x] = 'A';
			else if (game->map.grid[y][x] == 'g')
				game->map.grid[y][x] = 'V';
		}
	}
}

int	check_map_closed(t_game *game)
{
	int	result;
	int	start_x;
	int	start_y;

	start_x = (int)game->player.x;
	start_y = (int)game->player.y;
	result = flood_fill(game->map.grid, start_x, start_y, game);
	restore_visited(game);
	return (result);
}
