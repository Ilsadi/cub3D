/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 09:59:09 by amacaull          #+#    #+#             */
/*   Updated: 2026/01/30 15:36:55 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	apply_shading(int color, double distance)
{
	int		r;
	int		g;
	int		b;
	double	factor;

	if (distance < 0)
		distance = 0;
	if (distance >= MAX_VIEW_DIST)
		return (0);
	factor = 1.0 - (distance / MAX_VIEW_DIST);
	if (factor < 0.0)
		factor = 0.0;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (int)(r * factor);
	g = (int)(g * factor);
	b = (int)(b * factor);
	return ((r << 16) | (g << 8) | b);
}
