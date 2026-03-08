/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mapline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:12:28 by ilsadi            #+#    #+#             */
/*   Updated: 2026/03/08 19:14:56 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (next == ' ' || next == '\t'
		|| next == '\n' || next == '\0')
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
