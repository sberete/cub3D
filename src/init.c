/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:39:18 by sberete           #+#    #+#             */
/*   Updated: 2025/10/21 18:08:26 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cub3d_init(t_data *cub3d, char *argv)
{
	ft_bzero(cub3d, sizeof(t_data));
	cub3d->name = argv;
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		mlx_failure(cub3d, "Mlx Failure");
	cub3d->win = mlx_new_window(cub3d->mlx, WIDTH, HEIGHT, cub3d->name);
	if (!cub3d->win)
		mlx_failure(cub3d, "Win Failure");
	// cub3d->img.img_ptr = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	// cub3d->img.pixels_ptr = mlx_get_data_addr(cub3d->img.img_ptr,
	// 		&cub3d->img.bpp, &cub3d->img.line_len, &cub3d->img.endian);
	mlx_hookes(cub3d);
}
