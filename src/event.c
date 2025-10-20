/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:53:18 by sberete           #+#    #+#             */
/*   Updated: 2025/10/20 19:03:09 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	hook_func(t_data *ap)
{
	close_mlx(ap);
	return (0);
}

int	key_func(int keycode, t_data *ap)
{
	if (keycode == 65307)
		close_mlx(ap);
	// else if (keycode == 97 || keycode == 119 || keycode == 100
	// 	|| keycode == 115)
	// {
	// 	97 = a;
	// 	119 = w;
	// 	100 = d;
	// 	115 = s;
	// }
	// else if (keycode == 65361 || keycode == 65363)
	// {
	// 	65361 = fleche de gauche;
	// 	65363 = fleche de droit;
	// }
	// else if(keycode == 65505) // Shift pour le sprint [Bonus]
	// else if (keycode == 109) // m pour la map [Bonus]
	// {
	// 	t_data map;
	// 	ft_bzero (&map, sizeof(t_data));
	// 	map.mlx = mlx_init();
	// 	if (!map.mlx)
	// 	{
	// 		printf("Failure mlx\n");
	// 		exit(1);
	// 	}
	// 	map.win = mlx_new_window(map.mlx, 200, 200, map.name);
	// 	mlx_loop(map.mlx);
	// } // une idee a voir
	return (0);
}

void	mlx_hookes(t_data *cub3D)
{
	mlx_key_hook(cub3D->win, key_func, cub3D);
	mlx_hook(cub3D->win, DestroyNotify, StructureNotifyMask, hook_func, cub3D);
	// mlx_mouse_hook(cub3D->win, mouse_func, cub3D);
}