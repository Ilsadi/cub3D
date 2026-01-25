/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:50:03 by ilsadi            #+#    #+#             */
/*   Updated: 2026/01/23 16:16:15 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int parse_rgb_value(char **str, int *out)
{
	int value;

	value = 0;
	skip_whitespace(str);
	if (!ft_isdigit(**str))
		return (0);
	while (ft_isdigit(**str))
	{
		value = value * 10 + (**str - '0');
		(*str)++;
	}
	if (value <= 255)
	{
		*out = value;
		return (1);
	}
	return (0);
}

static int	parse_rgb_triple(char *str, int *r, int *g, int *b)
{
	if (!parse_rgb_value(&str, r))
		return (0);
	skip_whitespace(&str);
	if (*str != ',')
		return (0);
	str++;
	if (!parse_rgb_value(&str, g))
		return (0);
	skip_whitespace(&str);
	if (*str != ',')
		return (0);
	str++;
	if (!parse_rgb_value(&str, b))
		return (0);
	skip_whitespace(&str);
	if (*str != '\0' && *str != '\n')
		return (0);
	return (1);
}

int	get_color(t_game *game, char *str)
{
	int		r;
	int		g;
	int		b;

	(void)game;
	if (!str)
		return (-1);
	if (!parse_rgb_triple(str, &r, &g, &b))
		return (-1);
	return (r << 16 | g << 8 | b);
}
