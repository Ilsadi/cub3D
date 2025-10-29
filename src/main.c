/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:37:11 by ilsadi            #+#    #+#             */
/*   Updated: 2025/10/29 14:30:42 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;
	int		i;

	i = 0;
	(void)ac;
	(void)av;
	ft_bzero(&game, sizeof(t_game));
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
	mlx_key_hook(game.win, handle_key, &game);
	mlx_hook(game.win, 17, 0, clean_everything, &game);
	info_cub(&game, av[1]);
	printf("%d\n", game.tex.ceil);
	printf("%d\n", game.tex.floor);
	printf("%s\n", game.tex.SO_wall);
	printf("%s\n", game.tex.NO_wall);
	printf("%s\n", game.tex.EA_wall);
	printf("%s\n", game.tex.WE_wall);
	while (game.map.map[i])
	{
		printf("%s\n", game.map.map[i]);
		i++;
	}
	// display_background(&game);
	mlx_loop(game.mlx);
	return (0);
}
