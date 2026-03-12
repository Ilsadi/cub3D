/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 04:00:13 by ilsadi            #+#    #+#             */
/*   Updated: 2026/03/12 13:51:52 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_msg(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

void	skip_whitespace(char **str)
{
	while (**str && (**str == ' ' || **str == '\t'))
		(*str)++;
}

int	is_blank_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

int	has_cub_extension(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len <= 4)
		return (0);
	return (filename[len - 4] == '.' && filename[len - 3] == 'c'
		&& filename[len - 2] == 'u' && filename[len - 1] == 'b');
}

void	drain_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}
