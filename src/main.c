/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:37:11 by ilsadi            #+#    #+#             */
/*   Updated: 2026/01/23 01:24:08 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	(void)ac;
	ft_bzero(&game, sizeof(t_game));
	if (!info_cub(&game, av[1]))
		return (1);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Cub3d");
	if (!game.win)
		return (1);
	set_img(&game);
	mlx_key_hook(game.win, handle_key, &game);
	mlx_hook(game.win, 17, 0, clean_everything, &game);
	init_background(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);
	mlx_loop(game.mlx);
	return (0);
}
