/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:15:35 by ilsadi            #+#    #+#             */
/*   Updated: 2025/10/30 16:35:23 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <stdio.h>
# include <stdarg.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/wait.h>
# include <X11/Xlib.h>
# include <math.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define SIZE 64
# define HEIGHT 1080
# define WIDTH 1920

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

typedef	struct s_raycast
{
	double	dir_x;
	double	dir_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	plane_x;
	double	plane_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
}	t_raycast;


typedef struct s_textures
{
	char	*NO_wall;
	char	*WE_wall;
	char	*EA_wall;
	char	*SO_wall;
	int		ceil;
	int		floor;
}	t_textures;


typedef struct s_map
{
	char	**map;
	int		map_size;
}	t_map;

typedef struct s_game
{
	t_map		map;
	t_img		img;
	t_textures	tex;
	t_raycast	ray;
	void		*win;
	void		*mlx;
	int			width;
	int			height;
	float		player_x;
	float		player_y;
	float		angle;
	
}	t_game;
// Handle_keys.c

int		handle_key(int keycode, t_game *game);

// Clean.c

int		clean_everything(t_game *game);

// init_game.c

void	put_pixel(t_img *image, int x, int y, int color);
void	init_background(t_game *game);


void	info_cub(t_game *game, char *filename);
void	stock_map(t_game *game, int fd, char *filename);
void	get_map_size(t_game *game, char *filename);
char	*skip_line(int fd);
void	set_img(t_game *game);




#endif