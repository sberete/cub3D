/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:36:04 by sberete           #+#    #+#             */
/*   Updated: 2025/10/21 16:03:55 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	mlx_failure(t_data *cub3D, char *str)
{
	printf("%s\n", str);
	close_mlx(cub3D);
}

void	param_available(void)
{
	printf("\n");
	exit(1);
}
