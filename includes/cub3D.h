/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:52:23 by sberete           #+#    #+#             */
/*   Updated: 2025/10/20 19:27:31 by sberete          ###   ########.fr       */
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

typedef struct s_data
{
	char	*name;
	void	*mlx;
	void	*win;
}			t_data;

void		mlx_hookes(t_data *cub3D);
int			close_mlx(t_data *cub3D);
void	mlx_failure(t_data *cub3D, char *str);

#endif