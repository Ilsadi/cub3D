/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:14:12 by ilsadi            #+#    #+#             */
/*   Updated: 2026/01/23 01:10:58 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	has_only_valid_chars(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] != '0' && game->map.map[i][j] != '1'
				&& game->map.map[i][j] != 'N' && game->map.map[i][j] != 'S'
				&& game->map.map[i][j] != 'E' && game->map.map[i][j] != 'W'
				&& game->map.map[i][j] != ' ' && game->map.map[i][j] != '\t')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}


char	*skip_line(int fd)
{
	char	*line;
	int		i;

	line = ft_get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '1')
			return (line);
		free(line);
		line = ft_get_next_line(fd);
	}
	return (NULL);
}

int	get_map_size(t_game *game, char *filename)
{
	char	*line;
	int		fd;
	int		in_map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	game->map.map_size = 0;
	line = skip_line(fd);
	if (!line)
	{
		close(fd);
		error("Missing map");
		return (0);
	}
	in_map = 1;
	while (line)
	{
		if (in_map && is_map_line(line))
			game->map.map_size++;
		else if (in_map && is_blank_line(line))
			in_map = 0;
		else if (!in_map && !is_blank_line(line))
			return (free(line), close(fd), error("Garbage after map"), 0);
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
	return (1);
}

void	stock_map(t_game *game, int fd, char *filename)
{
	int		i;
	char	*line;
	int		in_map;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	line = skip_line(fd);
	if (!line)
		return (close(fd), (void)0);
	game->map.map = malloc(sizeof(char *) * (game->map.map_size + 1));
	if (!game->map.map)
		return (free(line), close(fd), (void)0);
	in_map = 1;
	while (line)
	{
		if (in_map && is_map_line(line))
		{
			line[ft_strcspn(line, "\n")] = '\0';
			game->map.map[i++] = ft_strdup(line);
		}
		else if (in_map && is_blank_line(line))
			in_map = 0;
		free(line);
		line = ft_get_next_line(fd);
	}
	game->map.map[i] = NULL;
	close(fd);
}

static int	is_map_tile(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

void	trim_left_map(t_game *game)
{
	int		i;
	int		j;
	char	*new_line;

	if (!game->map.map)
		return ;
	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j] == ' ' || game->map.map[i][j] == '\t')
			j++;
		if (game->map.map[i][j] && is_map_tile(game->map.map[i][j]))
		{
			new_line = ft_strdup(game->map.map[i] + j);
			if (!new_line)
				return ;
			free(game->map.map[i]);
			game->map.map[i] = new_line;
		}
		i++;
	}
}

int	info_cub(t_game *game, char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		error("Cannot open file");
		return (0);
	}
	line = ft_get_next_line(fd);
	if (!line)
	{
		close(fd);
		error("Empty file");
		return (0);
	}
	while (line)
	{
		if (is_blank_line(line))
		{
			free(line);
			line = ft_get_next_line(fd);
			continue ;
		}
		if (is_map_line(line))
		{
			free(line);
			break ;
		}
		if (tex_stock(game, line) == 0)
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
	if (!game->tex.NO_wall || !game->tex.SO_wall
		|| !game->tex.WE_wall || !game->tex.EA_wall
		|| !game->tex.floor_set || !game->tex.ceil_set)
	{
		error("Missing identifier(s)");
		return (0);
	}
	if (!get_map_size(game, filename))
		return (0);
	if (game->map.map_size <= 0)
	{
		error("Missing map");
		return (0);
	}
	stock_map(game, -1, filename);
	if (!game->map.map)
	{
		error("Map allocation failed");
		return (0);
	}
	trim_left_map(game);
	if (!has_only_valid_chars(game))
	{
		error("Invalid map char");
		return (0);
	}
	compute_map_dims(game);
	if (!normalize_map(game))
	{
		error("Malloc failed while normalizing map");
		return (0);
	}
	if (!parse_player(game))
	{
		error("Invalid player count");
		return (0);
	}
	if (!check_map_closed(game))
	{
		error("Map is not closed");
		return (0);
	}
	return (1);
}


int only_one_player(t_game *game)
{
	int	x;
	int	y;
	int	player;

	x = 0;
	player = 0;
	while (game->map.map[x])
	{
		y = 0;
		while(game->map.map[x][y])
		{
			if (game->map.map[x][y] == 'N' || game->map.map[x][y] == 'S' || game->map.map[x][y] == 'E' || game->map.map[x][y] == 'W')
				player++;
			y++;
		}
		x++;
	}
	if (player == 1)
		return (1);
	return (0);
}

void	compute_map_dims(t_game *game)
{
	int	i;
	int	len;

	if (!game->map.map)
		return ;
	game->map.height = game->map.map_size;
	game->map.width = 0;
	i = 0;
	while (game->map.map[i])
	{
		len = ft_strlen(game->map.map[i]);
		if (len > game->map.width)
			game->map.width = len;
		i++;
	}
}

int	normalize_map(t_game *game)
{
	char	**new_map;
	char	*new_line;
	int		i;
	int		j;
	int		len;

	if (!game->map.map || game->map.width <= 0 || game->map.height <= 0)
		return (0);
	new_map = malloc(sizeof(char *) * (game->map.height + 1));
	if (!new_map)
		return (0);
	i = 0;
	while (i < game->map.height)
	{
		new_line = malloc(sizeof(char) * (game->map.width + 1));
		if (!new_line)
			return (ft_free_tab(new_map), 0);
		j = 0;
		while (j < game->map.width)
		{
			new_line[j] = ' ';
			j++;
		}
		new_line[game->map.width] = '\0';
		len = ft_strlen(game->map.map[i]);
		j = 0;
		while (j < len && j < game->map.width)
		{
			if (game->map.map[i][j] == '\t')
				new_line[j] = ' ';
			else
				new_line[j] = game->map.map[i][j];
			j++;
		}
		new_map[i] = new_line;
		i++;
	}
	new_map[i] = NULL;
	ft_free_tab(game->map.map);
	game->map.map = new_map;
	return (1);
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

int	parse_player(t_game *game)
{
	int		y;
	int		x;
	int		count;
	char	c;

	y = 0;
	count = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			c = game->map.map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				count++;
				game->player_x = x + 0.5f;
				game->player_y = y + 0.5f;
				game->angle = get_start_angle(c);
				game->map.map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	if (count != 1)
		return (0);
	return (1);
}

static int	flood_fill_check(char **map, int x, int y, int width, int height)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return (0);
	if (map[y][x] == ' ')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (1);
	map[y][x] = 'V';
	if (!flood_fill_check(map, x + 1, y, width, height))
		return (0);
	if (!flood_fill_check(map, x - 1, y, width, height))
		return (0);
	if (!flood_fill_check(map, x, y + 1, width, height))
		return (0);
	if (!flood_fill_check(map, x, y - 1, width, height))
		return (0);
	return (1);
}

static void	restore_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.map[i][j] == 'V')
				game->map.map[i][j] = '0';
			j++;
		}
		i++;
	}
}

int	check_map_closed(t_game *game)
{
	int		result;

	result = flood_fill_check(game->map.map, 
		(int)game->player_x, (int)game->player_y,
		game->map.width, game->map.height);
	restore_map(game);
	return (result);
}