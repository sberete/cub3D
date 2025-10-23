/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:23:15 by sberete           #+#    #+#             */
/*   Updated: 2025/10/21 17:16:05 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_mlx(t_data *cub3D)
{
	if (cub3D->win)
		mlx_destroy_window(cub3D->mlx, cub3D->win);
	// mlx_destroy_image(cub3D->mlx, cub3D->img.img_ptr);
	if (cub3D->mlx)
	{
		mlx_destroy_display(cub3D->mlx);
		free(cub3D->mlx);
	}
	exit(1);
}
