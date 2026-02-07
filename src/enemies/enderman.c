/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enderman.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 08:59:27 by amacaull          #+#    #+#             */
/*   Updated: 2026/02/07 11:11:28 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_tp_pos(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
		return (0);
	if (game->map.grid[y][x] != '0' && game->map.grid[y][x] != 'M'
		&& game->map.grid[y][x] != 'K')
		return (0);
	return (1);
}

static int	has_clear_path(t_game *game, double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;
	double	dist;
	int		steps;
	int		i;

	dx = x2 - x1;
	dy = y2 - y1;
	dist = sqrt(dx * dx + dy * dy);
	steps = (int)(dist * 4);
	if (steps < 1)
		steps = 1;
	i = 0;
	while (i <= steps)
	{
		dx = x1 + (x2 - x1) * i / steps;
		dy = y1 + (y2 - y1) * i / steps;
		if (game->map.grid[(int)dy][(int)dx] == '1'
			|| game->map.grid[(int)dy][(int)dx] == 'D')
			return (0);
		i++;
	}
	return (1);
}

static void	teleport_enderman(t_game *game, t_enderman *ender)
{
	int		range;
	int		attempts;
	int		new_x;
	int		new_y;
	double	dist;

	if (ender->is_angry)
		range = ENDER_RANGE_ANGRY;
	else
		range = ENDER_RANGE_NORMAL;
	attempts = 50;
	while (attempts-- > 0)
	{
		new_x = (int)ender->x + (rand() % (range * 2 + 1)) - range;
		new_y = (int)ender->y + (rand() % (range * 2 + 1)) - range;
		if (is_valid_tp_pos(game, new_x, new_y))
		{
			dist = sqrt(pow(new_x - ender->x, 2) + pow(new_y - ender->y, 2));
			if (dist <= range && dist > 0.5
				&& has_clear_path(game, ender->x, ender->y,
					new_x + 0.5, new_y + 0.5))
			{
				ender->x = new_x + 0.5;
				ender->y = new_y + 0.5;
				return ;
			}
		}
	}
}

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

void	update_endermen(t_game *game)
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

void	init_endermen(t_game *game)
{
	game->endermen.texture.img = mlx_xpm_file_to_image(game->mlx,
			"textures/enemies/enderman.xpm",
			&game->endermen.texture.width,
			&game->endermen.texture.height);
	if (game->endermen.texture.img)
		game->endermen.texture.addr = (int *)mlx_get_data_addr(
				game->endermen.texture.img,
				&game->endermen.texture.pixel_bits,
				&game->endermen.texture.size_line,
				&game->endermen.texture.endian);
	game->endermen.texture_angry.img = mlx_xpm_file_to_image(game->mlx,
			"textures/enemies/enderman_angry.xpm",
			&game->endermen.texture_angry.width,
			&game->endermen.texture_angry.height);
	if (game->endermen.texture_angry.img)
		game->endermen.texture_angry.addr = (int *)mlx_get_data_addr(
				game->endermen.texture_angry.img,
				&game->endermen.texture_angry.pixel_bits,
				&game->endermen.texture_angry.size_line,
				&game->endermen.texture_angry.endian);
	game->hud.invincibility = 0;
	srand((unsigned int)time(NULL));
}

void	free_endermen(t_game *game)
{
	if (game->endermen.texture.img)
		mlx_destroy_image(game->mlx, game->endermen.texture.img);
	if (game->endermen.texture_angry.img)
		mlx_destroy_image(game->mlx, game->endermen.texture_angry.img);
}
