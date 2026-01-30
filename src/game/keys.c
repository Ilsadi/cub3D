/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:16:45 by ilsadi            #+#    #+#             */
/*   Updated: 2026/01/30 09:46:13 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		clean_everything(game);
	if (keycode == KEY_W)
		game->player.move_forward = 1;
	if (keycode == KEY_S)
		game->player.move_backward = 1;
	if (keycode == KEY_A)
		game->player.move_left = 1;
	if (keycode == KEY_D)
		game->player.move_right = 1;
	if (keycode == KEY_LEFT)
		game->player.rotate_left = 1;
	if (keycode == KEY_RIGHT)
		game->player.rotate_right = 1;
	if (keycode == KEY_SHIFT)
		game->player.is_sprinting = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player.move_forward = 0;
	if (keycode == KEY_S)
		game->player.move_backward = 0;
	if (keycode == KEY_A)
		game->player.move_left = 0;
	if (keycode == KEY_D)
		game->player.move_right = 0;
	if (keycode == KEY_LEFT)
		game->player.rotate_left = 0;
	if (keycode == KEY_RIGHT)
		game->player.rotate_right = 0;
	if (keycode == KEY_SHIFT)
		game->player.is_sprinting = 0;
	return (0);
}
