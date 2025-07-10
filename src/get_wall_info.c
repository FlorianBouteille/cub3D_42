/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:14:38 by mhanarte          #+#    #+#             */
/*   Updated: 2025/07/04 14:17:35 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_wallinfo	*get_wall_info(char **map)
{
	int			i;
	int			j;
	t_wallinfo	*wall;

	wall = NULL;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				wall = init_wallinfo(j, i, wall);
			j++;
		}
		i++;
	}
	return (wall);
}
