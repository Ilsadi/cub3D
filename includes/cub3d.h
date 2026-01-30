/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:15:35 by ilsadi            #+#    #+#             */
/*   Updated: 2026/01/30 10:35:18 by amacaull         ###   ########.fr       */
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

// PLAYER
# define MOVE_SPEED 0.025
# define SPRINT_SPEED 0.05
# define ROT_SPEED 0.03

// MINIMAP
#define MINI_SCALE 8
#define MINI_OFFSET 8
#define MINI_PLAYER 0xFF0000
#define MINI_WALL 0x000000
#define MINI_FLOOR 0xFFFFFF
#define MINI_BG 0x000000
#define MINI_BORDER 0xFFFFFF

// SHADING
# define MAX_VIEW_DIST 3.0

// KEYCODES (MacOS)
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53
# define KEY_SHIFT 257

// // KEYCODES (Linux)
// # define KEY_W 119
// # define KEY_A 97
// # define KEY_S 115
// # define KEY_D 100
// # define KEY_LEFT 65361
// # define KEY_RIGHT 65363
// # define KEY_ESC 65307

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		rows;
}	t_map;

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
	int		pitch;
	int     is_sprinting;
}	t_player;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
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

typedef struct s_floor
{
	float	ray_dir_x0;
	float	ray_dir_y0;
	float	ray_dir_x1;
	float	ray_dir_y1;
	int		p;
	float	pos_z;
	float	row_distance;
	float	floor_step_x;
	float	floor_step_y;
	float	floor_x;
	float	floor_y;
}	t_floor;

typedef struct s_tex
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*floor_path;
	char	*ceil_path;
	t_img	north;
	t_img	south;
	t_img	west;
	t_img	east;
	t_img	floor_tex;
	t_img	ceil_tex;
	int		floor;
	int		ceil;
	int		floor_set;
	int		ceil_set;
	int		use_floor_tex;
	int		use_ceil_tex;
}	t_tex;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_map		map;
	t_player	player;
	t_ray		ray;
	t_tex		tex;
}	t_game;

// GAME INIT & LOOP
int		game_loop(t_game *game);
void	set_img(t_game *game);
void	put_pixel(t_img *img, int x, int y, int color);
int		clean_everything(t_game *game);

// INPUT HANDLING
int		handle_keypress(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);
int		handle_mouse(int x, int y, t_game *game);

// PARSING
int		parse_cub_file(t_game *game, char *filename);
int		parse_texture(t_game *game, char *line, int i);
int		parse_color(t_game *game, char *line, int i);
int		parse_rgb(t_game *game, char *str);
int		validate_map(t_game *game);
int		normalize_map(t_game *game);
int		check_map_closed(t_game *game);
int		store_map_line(t_game *game, char **tmp, char *line);

// PARSING UTILS
int		error_msg(char *msg);
void	skip_whitespace(char **str);
int		is_map_line(char *line);
int		is_blank_line(char *line);
int		has_cub_extension(char *filename);

// PLAYER
void	init_player_direction(t_game *game);
void	update_player(t_game *game);
int		is_wall(t_game *game, double x, double y);

// RAYCASTING
void	render_frame(t_game *game);
void	init_ray(t_game *game, t_ray *ray, int x);
void	init_step(t_game *game, t_ray *ray);
void	perform_dda(t_game *game, t_ray *ray);
void	calc_wall_params(t_game *game, t_ray *ray);

// TEXTURES
int		load_textures(t_game *game);
void	free_textures(t_game *game);

// FLOORS & CEILINGS
void	render_floor_ceiling(t_game *game);

// MINIMAP
void	render_minimap(t_game *game);

// SHADING
int     apply_shading(int color, double distance);

// UTILS
void	ft_free_tab(char **tab);

#endif
