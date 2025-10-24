/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:36:04 by sberete           #+#    #+#             */
/*   Updated: 2025/10/24 17:50:04 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	mlx_failure(t_data *cub3D, char *str)
{
	printf("Error\n%s\n", str);
	free_all_and_exit(cub3D);
}

void	param_available(void)
{
	ft_putstr_fd("Error\nUsage: ./cub3D <map_path.cub>\n", 2);
	exit(1);
}
