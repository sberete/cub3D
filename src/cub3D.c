/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxriimu <sxriimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:36:00 by sberete           #+#    #+#             */
/*   Updated: 2025/10/29 21:01:27 by sxriimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_data	cub3d;
	
	ft_bzero(&cub3d, sizeof(t_data));
	if (parsing(&cub3d, argc, argv) != 0)
		param_available();
	cub3d_init(&cub3d);
	mlx_loop(cub3d.mlx.ptr);
}
