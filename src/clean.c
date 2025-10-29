/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:13:26 by ilsadi            #+#    #+#             */
/*   Updated: 2025/10/29 21:33:44 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	clean_everything(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game->tex.NO_wall);
	free(game->tex.SO_wall);
	free(game->tex.WE_wall);
	free(game->tex.EA_wall);
	ft_free_tab(game->map.map);
	exit(0);
	return (0);
}


