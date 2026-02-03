/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:16:45 by ilsadi            #+#    #+#             */
/*   Updated: 2026/02/03 21:07:00 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_hotbar_keys(int keycode, t_game *game)
{
	if (keycode == KEY_1)
		game->hud.slot = 0;
	else if (keycode == KEY_2)
		game->hud.slot = 1;
	else if (keycode == KEY_3)
		game->hud.slot = 2;
	else if (keycode == KEY_4)
		game->hud.slot = 3;
	else if (keycode == KEY_5)
		game->hud.slot = 4;
	else if (keycode == KEY_6)
		game->hud.slot = 5;
	else if (keycode == KEY_7)
		game->hud.slot = 6;
	else if (keycode == KEY_8)
		game->hud.slot = 7;
	else if (keycode == KEY_9)
		game->hud.slot = 8;
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		clean_everything(game);
	if (keycode == KEY_W)
		game->keys.w = 1;
	if (keycode == KEY_S)
		game->keys.s = 1;
	if (keycode == KEY_A)
		game->keys.a = 1;
	if (keycode == KEY_D)
		game->keys.d = 1;
	if (keycode == KEY_LEFT)
		game->keys.left = 1;
	if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	if (keycode == KEY_SHIFT)
		game->keys.shift = 1;
	if (keycode == KEY_E)
		handle_interaction(game);
	handle_hotbar_keys(keycode, game);
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	if (keycode == KEY_S)
		game->keys.s = 0;
	if (keycode == KEY_A)
		game->keys.a = 0;
	if (keycode == KEY_D)
		game->keys.d = 0;
	if (keycode == KEY_LEFT)
		game->keys.left = 0;
	if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	if (keycode == KEY_SHIFT)
		game->keys.shift = 0;
	return (0);
}
