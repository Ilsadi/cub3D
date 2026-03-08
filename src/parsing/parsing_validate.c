/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_validate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 03:59:30 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/08 13:59:44 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == '2')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (c == ' ' || c == '\t')
		return (1);
	if (c == 'D' || c == 'K' || c == 'M')
		return (1);
	if (c == 'A' || c == 'V')
		return (1);
	return (0);
}

static int	has_valid_chars(t_game *game)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	while (game->map.grid[++i])
	{
		j = -1;
		while (game->map.grid[i][++j])
		{
			c = game->map.grid[i][j];
			if (!is_valid_map_char(c))
				return (error_msg("Invalid character in map"), 0);
		}
	}
	return (1);
}

static void	compute_dimensions(t_game *game)
{
	int	i;
	int	len;

	game->map.height = game->map.rows;
	game->map.width = 0;
	i = -1;
	while (game->map.grid[++i])
	{
		len = ft_strlen(game->map.grid[i]);
		if (len > game->map.width)
			game->map.width = len;
	}
}

static float	get_start_angle(char c)
{
	if (c == 'N')
		return (3 * M_PI / 2);
	if (c == 'S')
		return (M_PI / 2);
	if (c == 'E')
		return (0);
	return (M_PI);
}

static int	find_player(t_game *game)
{
	int		x;
	int		y;
	int		count;
	char	c;

	count = 0;
	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < (int)ft_strlen(game->map.grid[y]))
		{
			c = game->map.grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				count++;
				game->player.x = x + 0.5f;
				game->player.y = y + 0.5f;
				game->player.angle = get_start_angle(c);
				game->map.grid[y][x] = '0';
			}
		}
	}
	return (count == 1);
}

static void	find_endermen(t_game *game)
{
	int		x;
	int		y;
	char	c;

	game->endermen.count = 0;
	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < (int)ft_strlen(game->map.grid[y]))
		{
			c = game->map.grid[y][x];
			if (c == 'M' && game->endermen.count < MAX_ENDERMEN)
			{
				game->endermen.list[game->endermen.count].x = x + 0.5;
				game->endermen.list[game->endermen.count].y = y + 0.5;
				game->endermen.list[game->endermen.count].is_active = 1;
				game->endermen.list[game->endermen.count].is_angry = 0;
				game->endermen.list[game->endermen.count].angry_timer = 0;
				game->endermen.list[game->endermen.count].tp_timer = 0;
				game->endermen.count++;
			}
		}
	}
}

int	validate_map(t_game *game)
{
	if (!has_valid_chars(game))
		return (0);
	compute_dimensions(game);
	if (!find_player(game))
		return (error_msg("Map must have exactly one player (N/S/E/W)"), 0);
	find_endermen(game);
	if (!normalize_map(game))
		return (error_msg("Memory allocation failed"), 0);
	if (!check_map_closed(game))
		return (error_msg("Map is not closed by walls"), 0);
	return (1);
}
