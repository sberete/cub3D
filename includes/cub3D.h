/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:52:23 by sberete           #+#    #+#             */
/*   Updated: 2025/10/21 17:31:03 by sberete          ###   ########.fr       */
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

typedef struct s_img
{
	void		*img_ptr;
	char		*pixels_ptr;
	int			bpp;
	int			endian;
	int			line_len;
}				t_img;

typedef struct s_player
{
	float		x;
	float		y;
}				t_player;

typedef struct s_data
{
	char		*name;
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	player;
}				t_data;

int				parsing(int argc, char **argv);
void			mlx_hookes(t_data *cub3D);
int				close_mlx(t_data *cub3D);
void			param_available(void);
void			mlx_failure(t_data *cub3D, char *str);
void			cub3d_init(t_data *cub3d, char *argv);

#endif