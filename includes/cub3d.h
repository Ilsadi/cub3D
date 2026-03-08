/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacaull <amacaull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:15:35 by ilsadi            #+#    #+#             */
/*   Updated: 2026/03/08 14:33:30 by amacaull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <mlx.h>
# include "../libft/include/libft_ultimate.h"

// CORE
# define WIDTH 1280
# define HEIGHT 720

// PLAYER
# define MOVE_SPEED 0.025
# define SPRINT_SPEED 0.040
# define ROT_SPEED 0.03
# define HUNGER_DRAIN 5
# define HUNGER_THRESHOLD 200
# define FOOD_MAX 20
# define REGEN_DELAY 300
# define REGEN_RATE 180

// MOUSE
# define MOUSE_SENSITIVITY 0.001

// RENDER & SHADING
# define MAX_VIEW_DIST 3.5

// ANIMATION
# define ANIM_SPEED 10
# define ANIM_FRAMES 120

// UI
# define HUD_SCALE 2.5
# define MINI_OFFSET 8
# define MINI_PLAYER 0xFF0000
# define MINI_WALL 0x000000
# define MINI_FLOOR 0xFFFFFF
# define MINI_BG 0x000000
# define MINI_BORDER 0xFFFFFF
# define MINI_SIZE    200
# define MINI_RAD     100
# define MINI_VIEW    6.5
# define MINI_PPT     15.384615
# define MINI_DOOR_C  0x8B4513
# define MINI_KEY_C   0xFFD700
# define MINI_ENDER_C 0xFF00FF
# define VIS_RANGE    4
# define SCALE_DEFAULT  0.2
# define SCALE_EGG      0.5
# define VGROUND_DEFAULT 0.4
# define VGROUND_EGG     0.35

// DOORS
# define DOOR_FRAMES 5
# define DOOR_RANGE 1.5
# define MAX_DOORS 64

// ITEMS
# define MAX_COLLECTIBLES 64
# define ITEM_NONE 0
# define ITEM_KEY 1
# define ITEM_APPLE 2
# define ITEM_EGG 3
# define KEY_USES 5
# define HOTBAR_SLOTS 9
# define APPLE_HP 6

// ENDERMAN
# define MAX_ENDERMEN 32
# define ENDER_TP_NORMAL 300
# define ENDER_TP_ANGRY 120
# define ENDER_ANGRY_DURATION 600
# define ENDER_RANGE_NORMAL 7
# define ENDER_RANGE_ANGRY 5
# define ENDER_DAMAGE_RANGE 1.0
# define ENDER_DAMAGE 2
# define ENDER_INVINCIBILITY 60
# define GAMEOVER_DELAY 450
# define VICTORY_DELAY 180

// KEYS
# ifdef __linux__
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_E 101
#  define KEY_SHIFT 65505
#  define KEY_1 49
#  define KEY_2 50
#  define KEY_3 51
#  define KEY_4 52
#  define KEY_5 53
#  define KEY_6 54
#  define KEY_7 55
#  define KEY_8 56
#  define KEY_9 57
# else
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_E 14
#  define KEY_SHIFT 257
#  define KEY_1 18
#  define KEY_2 19
#  define KEY_3 20
#  define KEY_4 21
#  define KEY_5 23
#  define KEY_6 22
#  define KEY_7 26
#  define KEY_8 28
#  define KEY_9 25
# endif

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

typedef struct s_anim
{
	t_img	*frames;
	int		count;
	int		current;
	int		timer;
}	t_anim;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		rows;
}	t_map;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	shift;
}	t_keys;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	int		pitch;
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

typedef struct s_sprite_render
{
	double	transform_x;
	double	transform_y;
	int		screen_x;
	int		height;
	int		width;
	int		draw_start_x;
	int		draw_end_x;
	int		draw_start_y;
	int		draw_end_y;
	int		orig_start_y;
}	t_sprite_render;

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

typedef struct s_hud
{
	t_img	hotbar;
	t_img	selector;
	t_img	offhand;
	t_img	heart_full;
	t_img	heart_empty;
	t_img	food_full;
	t_img	food_empty;
	t_img	torch;
	t_img	key_icon;
	t_img	apple_icon;
	t_img	egg_icon;
	t_img	hand_empty;
	t_img	hand_pickaxe;
	t_img	hand_apple;
	t_img	hand_egg;
	int		health;
	int		food;
	int		slot;
	int		food_timer;
	int		inventory[HOTBAR_SLOTS];
	int		key_uses[HOTBAR_SLOTS];
	int		invincibility;
	int		no_sprint_timer;
	int		regen_timer;
}	t_hud;

typedef struct s_door
{
	int		x;
	int		y;
	int		state;
	int		open;
}	t_door;

typedef struct s_doors
{
	t_img	frames[DOOR_FRAMES];
	t_door	list[MAX_DOORS];
	int		count;
}	t_doors;

typedef struct s_collectible
{
	int		x;
	int		y;
	int		type;
	int		collected;
}	t_collectible;

typedef struct s_collectibles
{
	t_collectible	list[MAX_COLLECTIBLES];
	int				count;
	t_img			key_tex;
	t_img			apple_tex;
	t_img			egg_tex;
}	t_collectibles;

typedef struct s_enderman
{
	double	x;
	double	y;
	int		is_angry;
	int		angry_timer;
	int		tp_timer;
	int		is_active;
}	t_enderman;

typedef struct s_endermen
{
	t_enderman	list[MAX_ENDERMEN];
	int			count;
	t_img		texture;
	t_img		texture_angry;
}	t_endermen;

typedef struct s_gameover
{
	int		active;
	int		victory;
	int		timer;
}	t_gameover;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_map			map;
	t_player		player;
	t_ray			ray;
	t_tex			tex;
	t_hud			hud;
	t_anim			wall_anim;
	t_keys			keys;
	t_doors			doors;
	t_collectibles	collectibles;
	t_endermen		endermen;
	t_gameover		gameover;
}	t_game;

// CORE
int		game_loop(t_game *game);
void	set_img(t_game *game);
void	put_pixel(t_img *img, int x, int y, int color);
int		clean_everything(t_game *game);
void	ft_free_tab(char **tab);

// INPUT
void	init_keys(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);
int		handle_mouse(int x, int y, t_game *game);

// PLAYER
void	init_player_direction(t_game *game);
void	update_player(t_game *game);
int		is_wall(t_game *game, double x, double y);
void	update_metabolism(t_game *game);

// RAYCAST
void	render_frame(t_game *game);
void	init_ray(t_game *game, t_ray *ray, int x);
void	init_step(t_game *game, t_ray *ray);
void	perform_dda(t_game *game, t_ray *ray);
void	calc_wall_params(t_game *game, t_ray *ray);

// RENDER
int		load_textures(t_game *game);
void	free_textures(t_game *game);
void	init_animations(t_game *game);
void	update_animation(t_game *game);
void	free_animations(t_game *game);
void	render_floor_ceiling(t_game *game);
int		apply_shading(int color, double distance);

// SPRITES (Billboarding)
void	render_sprites(t_game *game, double *z_buffer);

// UI
void	init_hud(t_game *game);
void	render_hud(t_game *game);
void	free_hud(t_game *game);
void	render_minimap(t_game *game);

// PARSING
int		parse_cub_file(t_game *game, char *filename);
int		parse_texture(t_game *game, char *line, int i);
int		parse_color(t_game *game, char *line, int i);
int		parse_rgb(t_game *game, char *str);
int		validate_map(t_game *game);
int		normalize_map(t_game *game);
int		check_map_closed(t_game *game);
int		store_map_line(t_game *game, char **tmp, char *line);
int		error_msg(char *msg);
void	skip_whitespace(char **str);
int		is_map_line(char *line);
int		is_blank_line(char *line);
int		has_cub_extension(char *filename);

// DOORS
void	init_doors(t_game *game);
void	free_doors(t_game *game);
t_img	*get_door_texture(t_game *game, int x, int y);
t_door	*get_door_at(t_game *game, int x, int y);
int		is_door(t_game *game, int x, int y);

// COLLECTIBLES
void	init_collectibles(t_game *game);
void	free_collectibles(t_game *game);
void	update_collectibles(t_game *game);
int		add_item_to_inventory(t_game *game, int item_type);
int		has_item_selected(t_game *game, int item_type);
void	use_selected_item(t_game *game);

// INTERACTION
void	handle_interaction(t_game *game);

// ENDERMEN
void	init_endermen(t_game *game);
void	update_endermen(t_game *game);
void	render_endermen(t_game *game, double *z_buffer);
void	free_endermen(t_game *game);

// GAME STATE
void	check_gameover(t_game *game);
void	render_gameover(t_game *game);
void	trigger_victory(t_game *game);
void	render_victory(t_game *game);

#endif
