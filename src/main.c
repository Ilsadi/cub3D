/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:37:11 by ilsadi            #+#    #+#             */
/*   Updated: 2025/10/27 16:29:26 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;
	int		x;
	int		y;

	(void)ac;
	(void)av;
	x = 0;
	y = 0;
	ft_bzero(&game, sizeof(t_game));
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
	mlx_key_hook(game.win, handle_key, &game);
	mlx_hook(game.win, 17, 0, clean_everything, &game);
	info_cub(&game, av[1]);
	// display_background(&game);
	mlx_loop(game.mlx);
	return (0);
}
