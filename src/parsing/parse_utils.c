/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:48:54 by ilsadi            #+#    #+#             */
/*   Updated: 2025/12/29 01:20:10 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int error(char *error_msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

void skip_whitespace(char **str)
{
	while (**str && (**str == ' ' || **str == '\t'))
		(*str)++;
}

int is_map_line(char *line)
{
	int	i;
	int	has_tile;

	i = 0;
	has_tile = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else if (line[i] == 'N' || line[i] == 'W' || line[i] == 'S' || line[i] == 'E' || line[i] == '1' || line[i] == '0')
		{
			has_tile = 1;
			i++;
		}
		else
			return (0);
	}
	if (!has_tile)
		return (0);
	return (1);
}

int	is_blank_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
		else
			return (0);
	}
	return (1);
}

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