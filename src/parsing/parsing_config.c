/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 03:58:56 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/30 09:32:58 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*extract_path(char *str)
{
	size_t	len;
	char	*path;

	while (*str == ' ' || *str == '\t')
		str++;
	if (!*str)
		return (NULL);
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		len--;
	path = ft_substr(str, 0, len);
	return (path);
}

static int	set_texture(char **dest, char *line, char *name)
{
	if (*dest)
	{
		ft_putstr_fd("Error\nDuplicate ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(" texture\n", 2);
		return (-1);
	}
	*dest = extract_path(line);
	if (!*dest)
		return (-1);
	return (1);
}

int	parse_texture(t_game *game, char *line, int i)
{
	if (line[i] == 'N' && line[i + 1] == 'O'
		&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (set_texture(&game->tex.no_path, line + i + 2, "NO"));
	if (line[i] == 'S' && line[i + 1] == 'O'
		&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (set_texture(&game->tex.so_path, line + i + 2, "SO"));
	if (line[i] == 'W' && line[i + 1] == 'E'
		&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (set_texture(&game->tex.we_path, line + i + 2, "WE"));
	if (line[i] == 'E' && line[i + 1] == 'A'
		&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (set_texture(&game->tex.ea_path, line + i + 2, "EA"));
	return (0);
}

int	parse_color(t_game *game, char *line, int i)
{
	int	color;

	if (line[i] == 'F' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
	{
		if (game->tex.floor_set)
			return (error_msg("Duplicate floor color"), -1);
		color = parse_rgb(game, line + i + 2);
		if (color == -1)
			return (error_msg("Invalid floor color"), -1);
		game->tex.floor = color;
		game->tex.floor_set = 1;
		return (1);
	}
	if (line[i] == 'C' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
	{
		if (game->tex.ceil_set)
			return (error_msg("Duplicate ceiling color"), -1);
		color = parse_rgb(game, line + i + 2);
		if (color == -1)
			return (error_msg("Invalid ceiling color"), -1);
		game->tex.ceil = color;
		game->tex.ceil_set = 1;
		return (1);
	}
	return (0);
}

int	store_map_line(t_game *game, char **tmp, char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	tmp[game->map.rows] = ft_strdup(line);
	if (!tmp[game->map.rows])
		return (0);
	game->map.rows++;
	return (1);
}
