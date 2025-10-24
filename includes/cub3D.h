/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:52:23 by sberete           #+#    #+#             */
/*   Updated: 2025/10/24 16:47:47 by sberete          ###   ########.fr       */
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

# define WIDTH 800
# define HEIGHT 800
# define BUFFER_SIZE 42

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

typedef struct s_player
{
	t_direction	dir;
	t_position	pos;
}				t_player;

typedef struct s_mlx
{
	void		*ptr;
	void		*win;
}				t_mlx;

typedef struct s_data
{
	t_mlx		mlx;
	t_map		map;
	t_img		img;
	t_player	player;
}				t_data;

int				parsing(int argc, char **argv);
void			mlx_hookes(t_data *cub3D);
void			free_all(t_data *cub3D);
void			free_all_and_exit(t_data *cub3D);

void			param_available(void);
void			mlx_failure(t_data *cub3D, char *str);
void			cub3d_init(t_data *cub3d, char *argv);
char			*get_next_line(int fd);
void			test(t_map *map, char *argv);

#endif