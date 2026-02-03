/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 04:00:13 by amacaull          #+#    #+#             */
/*   Updated: 2026/02/03 21:07:34 by amacaull         ###   ########.fr       */
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

static int	is_map_start_char(char c)
{
	if (c == '0' || c == '1' || c == '2')
		return (1);
	if (c == 'D' || c == 'K')
		return (1);
	return (0);
}

static int	is_player_followed_by_map(char c, char next)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (0);
	if (next == '0' || next == '1' || next == '2')
		return (1);
	if (next == 'D' || next == 'K')
		return (1);
	if (next == ' ' || next == '\t' || next == '\n' || next == '\0')
		return (1);
	return (0);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (is_map_start_char(line[i]))
		return (1);
	if (is_player_followed_by_map(line[i], line[i + 1]))
		return (1);
	return (0);
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
