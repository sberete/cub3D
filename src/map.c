/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:55:57 by sberete           #+#    #+#             */
/*   Updated: 2025/10/24 18:00:30 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	test(t_map *map, char *argv)
{
	int	fd;
	// char *line;
	
	(void)map;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		exit(1);
	// while (condition)
	// {
	// 	/* code */
	// }
	
	// map->grid = ft_split(, '\n');
	printf("%d\n", fd);
}
