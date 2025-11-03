/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxriimu <sxriimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:53:18 by sberete           #+#    #+#             */
/*   Updated: 2025/11/01 16:02:05 by sxriimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int keycode, t_data *cub3d)
{
	if (keycode == XK_Escape)
		free_all_and_exit(cub3d);
	if (keycode == XK_w)
		cub3d->player.move.forward = 1;
	if (keycode == XK_s)
		cub3d->player.move.backward = 1;
	if (keycode == XK_a)
		cub3d->player.move.left = 1;
	if (keycode == XK_d)
		cub3d->player.move.right = 1;
	/*
	if (keycode == XK_Left)
		cub3d->player.move.rotate_left = 1;
	if (keycode == XK_Right)
		cub3d->player.move.rotate_right = 1;
	*/
	// else if(keycode == 65505) // Shift pour le sprint [Bonus]
	return (0);
}

int	key_release(int keycode, t_data *cub3d)
{
	if (keycode == XK_w)
		cub3d->player.move.forward = 0;
	if (keycode == XK_s)
		cub3d->player.move.backward = 0;
	if (keycode == XK_a)
		cub3d->player.move.left = 0;
	if (keycode == XK_d)
		cub3d->player.move.right = 0;
	/*
	if (keycode == XK_Left)
		cub3d->player.move.rotate_left = 0;
	if (keycode == XK_Right)
		cub3d->player.move.rotate_right = 0;
	*/
	return (0);
}

void	update_player_position(t_data *cub3d)
{
	double	speed;

	speed = 0.1;
	if (cub3d->player.move.forward)
		cub3d->player.pos.y -= speed;
	if (cub3d->player.move.backward)
		cub3d->player.pos.y += speed;
	if (cub3d->player.move.left)
		cub3d->player.pos.x -= speed;
	if (cub3d->player.move.right)
		cub3d->player.pos.x += speed;
	// ex : vérifier que cub3d->map.grid[(int)player.pos.y][(int)player.pos.x] != '1'
}

int	render_loop(t_data *cub3d)
{
	update_player_position(cub3d);
	draw_scene(cub3d);
	return (0);
}

void	mlx_hookes(t_data *cub3D)
{
	mlx_hook(cub3D->mlx.win, 2, 1L << 0, key_press, cub3D);
	mlx_hook(cub3D->mlx.win, 3, 1L << 1, key_release, cub3D);
	mlx_hook(cub3D->mlx.win, 17, 0, free_all_and_exit, cub3D);
	mlx_loop_hook(cub3D->mlx.ptr, render_loop, cub3D);
	// mlx_mouse_hook(cub3D->win, mouse_func, cub3D);
}
