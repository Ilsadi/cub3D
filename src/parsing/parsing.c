/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:14:12 by ilsadi            #+#    #+#             */
/*   Updated: 2026/03/12 13:56:04 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_identifier(t_game *game, char *line)
{
	int	i;
	int	ret;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	ret = parse_texture(game, line, i);
	if (ret != 0)
		return (ret);
	ret = parse_color(game, line, i);
	if (ret != 0)
		return (ret);
	return (error_msg("Unknown identifier"), -1);
}

static int	check_config_complete(t_game *game)
{
	if (!game->tex.no_path || !game->tex.so_path
		|| !game->tex.we_path || !game->tex.ea_path)
		return (error_msg("Missing texture path(s)"), 0);
	if (!game->tex.floor_set || !game->tex.ceil_set)
		return (error_msg("Missing floor or ceiling color"), 0);
	return (1);
}

static char	*read_config(t_game *game, int fd)
{
	char	*line;
	int		ret;

	line = get_next_line(fd);
	while (line)
	{
		if (is_blank_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (is_map_line(line))
			return (line);
		ret = parse_identifier(game, line);
		free(line);
		if (ret == -1)
			return (NULL);
		line = get_next_line(fd);
	}
	error_msg("Missing map");
	return (NULL);
}

static int	handle_map_storage(t_game *game, int fd,
	char *first, char **tmp)
{
	char	*line;
	int		in_map;

	game->map.rows = 0;
	in_map = 1;
	if (!store_map_line(game, tmp, first))
		return (free(first), free(tmp), 0);
	free(first);
	line = get_next_line(fd);
	while (line)
	{
		if (in_map && is_map_line(line))
			store_map_line(game, tmp, line);
		else if (in_map && is_blank_line(line))
			in_map = 0;
		else if (!in_map && !is_blank_line(line))
			return (free(line), ft_free_tab(tmp),
				error_msg("Garbage after map"), 0);
		free(line);
		line = get_next_line(fd);
	}
	tmp[game->map.rows] = NULL;
	game->map.grid = tmp;
	return (1);
}

int	parse_cub_file(t_game *game, char *filename)
{
	int		fd;
	char	*first_line;
	char	**tmp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg("Cannot open file"), 0);
	first_line = read_config(game, fd);
	if (!first_line)
		return (drain_gnl(fd), close(fd), 0);
	if (!check_config_complete(game))
		return (free(first_line), drain_gnl(fd),
			close(fd), 0);
	tmp = ft_calloc(1024, sizeof(char *));
	if (!tmp)
		return (free(first_line), drain_gnl(fd),
			close(fd), 0);
	if (!handle_map_storage(game, fd, first_line, tmp))
		return (drain_gnl(fd), close(fd), 0);
	close(fd);
	if (game->map.rows <= 0)
		return (error_msg("Missing map"), 0);
	if (!validate_map(game))
		return (0);
	return (1);
}
