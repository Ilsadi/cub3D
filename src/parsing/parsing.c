/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:14:12 by ilsadi            #+#    #+#             */
/*   Updated: 2025/12/29 01:14:29 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	has_only_valid_chars(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (game->map.map[x])
	{
		y = 0;
		while (game->map.map[x][y])
		{
			if (game->map.map[x][y] != '0' && game->map.map[x][y] != '1'
				&& game->map.map[x][y] != 'N' && game->map.map[x][y] != 'S'
				&& game->map.map[x][y] != 'E' && game->map.map[x][y] != 'W'
				&& game->map.map[x][y] != '\n')
				return (0);
			y++;
		}
		x++;
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

void	get_map_size(t_game *game, char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	game->map.map_size = 0;
	line = skip_line(fd);
	if (!line)
		return ;
	while (line)
	{
		game->map.map_size++;
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
}

void	stock_map(t_game *game, int fd, char *filename)
{
	int		i;
	char	*line;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	line = skip_line(fd);
	if (!line)
	{
		close(fd);
		return ;
	}
	game->map.map = malloc(sizeof(char *) * (game->map.map_size + 1));
	if (!game->map.map)
	{
		free(line);
		close(fd);
		return ;
	}
	while (line)
	{
		line[ft_strcspn(line, "\n")] = '\0';
		game->map.map[i] = ft_strdup(line);
		i++;
		free(line);
		line = ft_get_next_line(fd);
	}
	game->map.map[i] = NULL;
	close(fd);
}

void	info_cub(t_game *game, char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		error("Cannot open file");
		return ;
	}
	line = ft_get_next_line(fd);
	if (!line)
	{
		close(fd);
		error("Empty file");
		return ;
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
			error("Invalid identifier line");
			return ;
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
		return ;
	}
	get_map_size(game, filename);
	stock_map(game, -1, filename);
}
