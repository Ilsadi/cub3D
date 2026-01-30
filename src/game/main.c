/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:37:11 by ilsadi            #+#    #+#             */
/*   Updated: 2026/01/30 11:25:55 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_args(int ac, char **av)
{
	if (ac != 2)
	{
		error_msg("Usage: ./cub3D <map.cub>");
		return (0);
	}
	if (!has_cub_extension(av[1]))
	{
		error_msg("File must have .cub extension");
		return (0);
	}
	return (1);
}

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error_msg("MLX init failed"), 0);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
		return (error_msg("Window creation failed"), 0);
	return (1);
}

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->win, 17, 0, clean_everything, game);
	mlx_hook(game->win, 6, 1L << 6, handle_mouse, game);
	mlx_mouse_hide();
	mlx_mouse_move(game->win, WIDTH / 2, HEIGHT / 2);
	mlx_loop_hook(game->mlx, game_loop, game);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (!check_args(ac, av))
		return (1);
	ft_bzero(&game, sizeof(t_game));
	if (!parse_cub_file(&game, av[1]))
		return (1);
	if (!init_mlx(&game))
		return (1);
	if (!load_textures(&game))
		return (clean_everything(&game), 1);
	set_img(&game);
	init_player_direction(&game);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
