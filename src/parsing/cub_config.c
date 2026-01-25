/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:52:51 by ilsadi            #+#    #+#             */
/*   Updated: 2026/01/23 16:16:43 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_textures(char *str, char **dest)
{
	size_t	len;

	while (*str == ' ' || *str == '\t')
		str++;
	if (!*str)
		return ;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
	if (*dest)
		return ;
	*dest = ft_strdup(str);
}

int	tex_stock(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
			i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		if (game->tex.NO_wall)
			return (error("Duplicate NO texture"), 0);
		return (get_textures(line + i + 2, &game->tex.NO_wall), 1);
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		if (game->tex.EA_wall)
			return (error("Duplicate EA texture"), 0);
		return (get_textures(line + i + 2, &game->tex.EA_wall), 1);
	}
	else if (line[i] == 'W' && line[i + 1] == 'E')
	{
		if (game->tex.WE_wall)
			return (error("Duplicate WE texture"), 0);
		return (get_textures(line + i + 2, &game->tex.WE_wall), 1);
		
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		if (game->tex.SO_wall)
			return (error("Duplicate SO texture"), 0);
		return (get_textures(line + i + 2, &game->tex.SO_wall), 1);
	}
	else if (line[i] == 'F' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
	{
		if (game->tex.floor_set)
			return (error("Duplicate Floor color"), 0);
		game->tex.floor = get_color(game, line + i + 2);
		if (game->tex.floor == -1)
			return (error("Invalid floor color"), 0);
		game->tex.floor_set = 1;
		return (1);
	}
	else if (line[i] == 'C' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
	{
		if (game->tex.ceil_set)
			return (error("Duplicate Ceil color"), 0);
		game->tex.ceil = get_color(game, line + i + 2);
		if (game->tex.ceil == -1)
			return (error("Invalid ceil color"), 0);
		game->tex.ceil_set = 1;
		return (1);
	}
	return (0);
}

int parse_identifiers(char **lines, int *i, t_game *game)
{
	while (lines[*i])
	{
		if (is_blank_line(lines[*i]) == 1)
		{
			(*i)++;
			continue;
		}
		if (is_map_line(lines[*i]))
			break;
		else if (tex_stock(game, lines[*i]) == 0)
			return (-1);
		(*i)++;
	}
	return (0);
}
