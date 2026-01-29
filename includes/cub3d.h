/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:15:35 by ilsadi            #+#    #+#             */
/*   Updated: 2026/01/29 14:58:54 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "../libft/include/libft_ultimate.h"

# define WIDTH 1280
# define HEIGHT 720

/* Keycodes Mac 
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53*/

//Keycodes Linux (décommenter si besoin)
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307


/* ************************************************************************** */
/*                                 STRUCTURES                                 */
/* ************************************************************************** */

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_tex
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor;
	int		ceil;
	int		floor_set;
	int		ceil_set;
	t_img	north;
	t_img	south;
	t_img	east;
	t_img	west;
	int		tex_width;
	int		tex_height;
}	t_tex;

typedef struct s_map
{
	char	**grid;
	int		rows;
	int		width;
	int		height;
}	t_map;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	tex_step;
	double	tex_pos;
}	t_ray;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	int		move_forward;
	int		move_backward;
	int		move_left;
	int		move_right;
	int		rotate_left;
	int		rotate_right;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_tex		tex;
	t_map		map;
	t_ray		ray;
	t_player	player;
}	t_game;

/* ************************************************************************** */
/*                                 GAME                                       */
/* ************************************************************************** */

/* main.c */
int		main(int ac, char **av);

/* init.c */
void	set_img(t_game *game);
void	put_pixel(t_img *img, int x, int y, int color);

/* clean.c */
int		clean_everything(t_game *game);

/* keys.c */
int		handle_keypress(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);

/* game_loop.c */
int		game_loop(t_game *game);

/* player.c */
void	init_player_direction(t_game *game);
void	update_player(t_game *game);

/* ************************************************************************** */
/*                                 PARSING                                    */
/* ************************************************************************** */

/* parsing.c */
int		parse_cub_file(t_game *game, char *filename);

/* parsing_config.c */
int		parse_texture(t_game *game, char *line, int i);
int		parse_color(t_game *game, char *line, int i);

/* parsing_validate.c */
int		validate_map(t_game *game);

/* parsing_walls.c */
int		normalize_map(t_game *game);
int		check_map_closed(t_game *game);

/* parsing_utils.c */
int		error_msg(char *msg);
void	skip_whitespace(char **str);
int		is_map_line(char *line);
int		is_blank_line(char *line);
int		has_cub_extension(char *filename);

/* color.c */
int		parse_rgb(t_game *game, char *str);

/* ************************************************************************** */
/*                                 RENDERING                                  */
/* ************************************************************************** */

/* raycasting.c */
void	render_frame(t_game *game);

/* textures.c */
int		load_textures(t_game *game);

/* minimap.c */
void	render_minimap(t_game *game);

#endif
