/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enderman.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 08:59:27 by amacaull          #+#    #+#             */
/*   Updated: 2026/03/08 18:58:50 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_looking_at_enderman(t_game *game, t_enderman *ender)
{
	double	dx;
	double	dy;
	double	dist;
	double	angle_to_ender;
	double	angle_diff;

	dx = ender->x - game->player.x;
	dy = ender->y - game->player.y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist > 4.0)
		return (0);
	angle_to_ender = atan2(dy, dx);
	if (angle_to_ender < 0)
		angle_to_ender += 2 * M_PI;
	angle_diff = fabs(game->player.angle - angle_to_ender);
	if (angle_diff > M_PI)
		angle_diff = 2 * M_PI - angle_diff;
	if (angle_diff < 0.3)
		return (1);
	return (0);
}

static void	check_anger(t_game *game, t_enderman *ender)
{
	if (!ender->is_angry && is_looking_at_enderman(game, ender))
	{
		ender->is_angry = 1;
		ender->angry_timer = ENDER_ANGRY_DURATION;
	}
	if (ender->is_angry)
	{
		ender->angry_timer--;
		if (ender->angry_timer <= 0)
		{
			ender->is_angry = 0;
			ender->angry_timer = 0;
		}
	}
}

static void	check_damage(t_game *game, t_enderman *ender)
{
	double	dist;

	if (game->hud.invincibility > 0)
		return ;
	dist = sqrt(pow(game->player.x - ender->x, 2)
			+ pow(game->player.y - ender->y, 2));
	if (dist <= ENDER_DAMAGE_RANGE)
	{
		game->hud.health -= ENDER_DAMAGE;
		game->hud.invincibility = ENDER_INVINCIBILITY;
		if (game->hud.health < 0)
			game->hud.health = 0;
	}
}

static void	update_single_enderman(t_game *game, t_enderman *ender)
{
	int	tp_interval;

	if (!ender->is_active)
		return ;
	check_anger(game, ender);
	check_damage(game, ender);
	if (ender->is_angry)
		tp_interval = ENDER_TP_ANGRY;
	else
		tp_interval = ENDER_TP_NORMAL;
	ender->tp_timer++;
	if (ender->tp_timer >= tp_interval)
	{
		ender->tp_timer = 0;
		teleport_enderman(game, ender);
	}
}

void	update_enderman(t_game *game)
{
	int	i;

	if (game->hud.invincibility > 0)
		game->hud.invincibility--;
	i = 0;
	while (i < game->endermen.count)
	{
		update_single_enderman(game, &game->endermen.list[i]);
		i++;
	}
}
