/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:14:12 by ilsadi            #+#    #+#             */
/*   Updated: 2025/10/21 19:02:30 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	has_cub_extension(char *filename)
{
	int	len;

	len = 0;
	while (filename[len])
		len++;
	if (len <= 4)
		return (0);
	return (filename[len - 4] == '.' && filename[len - 3] == 'c'
		&& filename[len - 2] == 'u' && filename[len - 1] == 'b');
}

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

void	info_cub(t_game *game, char *filename)
{
	char	*line;
	int		fd;
	int		i;
	

	fd = open(filename, O_RDONLY);
	line = ft_get_next_line(fd);
	i = 0;
	while (line)
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		printf("%s", line);
		if (line[i] == 'N' && line[i + 1] == 'O')
		{
			i += 2;
			while (line[i] == ' ' || line[i] == '\t')
				i++;
			game->tex.NO_wall = ft_strdup(line + i);
		}
		else if (line[i] == 'E' && line[i + 1] == 'A')
		{
			i += 2;
			while (line[i] == ' ' || line[i] == '\t')
				i++;
			game->tex.EA_wall = ft_strdup(line + i);
		}
		else if (line[i] == 'W' && line[i + 1] == 'E')
		{
			i += 2;
			while (line[i] == ' ' || line[i] == '\t')
				i++;
			game->tex.WE_wall = ft_strdup(line + i);
		}
		else if (line[i] == 'S' && line[i + 1] == 'O')
		{
			i += 2;
			while (line[i] == ' ' || line[i] == '\t')
				i++;
			game->tex.SO_wall = ft_strdup(line + i);
		}
		line = ft_get_next_line(fd);
	}
	close(fd);
}
