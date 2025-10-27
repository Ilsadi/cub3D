/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:14:12 by ilsadi            #+#    #+#             */
/*   Updated: 2025/10/27 18:06:38 by ilsadi           ###   ########.fr       */
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

static void	parse_line(char *str, char **dest)
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

static int	check_color_value(int value)
{
	if (value < 0 || value > 255)
		return (-1);
	return (value);
}

int	get_color(t_game *game, char *str)
{
	int		r;
	int		g;
	int		b;
	int		color;
	char	*comma;

	if (!str)
		return (0);
	r = check_color_value(ft_atoi(str));
	comma = ft_strchr(str, ',');
	if (!comma)
		return (0);
	str = comma + 1;
	g = check_color_value(ft_atoi(str));
	comma = ft_strchr(str, ',');
	if (!comma)
		return (0);
	str = comma + 1;
	b = check_color_value(ft_atoi(str));
	color = (r << 16 | g << 8 | b);
	return (mlx_get_color_value(game->mlx, color));
}

static void	color_stock(t_game *game, char *line, int i, char flag)
{
	i += 1;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (flag == 'F')
		game->tex.floor = get_color(game, line);
	else if (flag == 'C')
		game->tex.ceil = get_color(game, line);
}

static void	tex_stock(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
			i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
		parse_line(line + i + 2, &game->tex.NO_wall);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		parse_line(line + i + 2, &game->tex.EA_wall);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		parse_line(line + i + 2, &game->tex.WE_wall);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		parse_line(line + i + 2, &game->tex.SO_wall);
	else if (line[i] == 'F')
		color_stock(game, line, i, 'F');
	else if (line[i] == 'C')
		color_stock(game, line, i, 'C');
}

char	*skip_line(int fd, t_game *game)
{
	char	*line;
	int		i;

	line = ft_get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] == '1')
			return (line);
		free(line);
		line = ft_get_next_line(fd);
	}
	return (NULL);
}

int	get_map_size(t_game *game, char *line, int fd)
{
	int		i;
	int		count;
	char	*line;

	i = 0;
	count = 0;
	line = skip_line(fd, game);
	if (!line)
		return (NULL);
	while (line)
	{
		count++;
		free(line);
		line = ft_get_next_line(fd);
	}
	return (count);
}

int	stock_map(t_game *game)
{
	
}

void	info_cub(t_game *game, char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	line = ft_get_next_line(fd);
	if (!line)
	{
		close(fd);
		return ;
	}
	while (line)
	{
		tex_stock(game, line);
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
}
