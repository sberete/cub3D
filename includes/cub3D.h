/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxriimu <sxriimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:52:23 by sberete           #+#    #+#             */
/*   Updated: 2025/11/10 16:50:55 by sxriimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 720
# define BUFFER_SIZE 42
# define TILE_SIZE 100

# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define YELLOW 0x00FFFF00
# define MAGENTA 0x00FF00FF
# define CYAN 0x0000FFFF
# define GRAY 0x00808080
# define DARKGRAY 0x00404040
# define LIGHTGRAY 0x00C0C0C0

# define COLOR_WALL GRAY
# define COLOR_FLOOR WHITE
# define COLOR_PLAYER RED

typedef struct s_img
{
	void		*img_ptr;
	char		*pixels_ptr;
	int			bpp;
	int			endian;
	int			line_len;
}				t_img;

typedef struct s_texture
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
}				t_texture;

typedef struct s_color
{
	char		*floor;
	char		*ceiling;
}				t_color;

typedef struct s_map
{
	char		*name;
	t_texture	texture;
	t_color		color;
	char		**grid;
	int			width;
	int			height;
}				t_map;

typedef struct s_direction
{
	double		x;
	double		y;
}				t_direction;

typedef struct s_position
{
	double		x;
	double		y;
}				t_position;

typedef struct s_plane
{
	double		x;
	double		y;
}				t_plane;

typedef struct s_move
{
	int			forward;
	int			backward;
	int			left;
	int			right;
	int			rotate_left;
	int			rotate_right;
}				t_move;

typedef struct s_player
{
	t_move		move;
	t_direction	dir;
	t_plane		plane;
	t_position	pos;
}				t_player;

typedef struct s_mlx
{
	void		*ptr;
	void		*win;
}				t_mlx;

typedef struct s_ray
{
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
}				t_ray;

typedef struct s_data
{
	t_mlx		mlx;
	t_map		map;
	t_img		img;
	t_player	player;
	t_ray		ray;
}				t_data;

int				parsing(t_data *cub3d, int argc, char **argv);
void			mlx_hookes(t_data *cub3D);
void			free_all(t_data *cub3D);
int				free_all_and_exit(t_data *cub3D);
void			put_pixel(t_img *img, int x, int y, int color);
void			draw_square(t_img *img, int x, int y, int color);
void			draw_map_2d(t_data *cub3d);
void			draw_player_2d(t_data *cub3d);
void			draw_scene(t_data *cub3d);
void			param_available(void);
void			mlx_failure(t_data *cub3D, char *str);
void			cub3d_init(t_data *cub3d);
char			*get_next_line(int fd);
void			test(t_map *map, char *argv);
void			draw_scene_3d(t_data *cub3d);
void	draw_minimap(t_data *cub3d);

#endif