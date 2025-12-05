/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:43:38 by fbouteil          #+#    #+#             */
/*   Updated: 2025/08/25 11:30:13 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_for_x(int x, int y, char **map)
{
	int	i;

	i = 0;
	while (map[x][y + i])
	{
		if (map[x][y + i] == ' ' || map[x][y + i] == '\n')
			return (0);
		if (map[x][y + i] == '1')
			break ;
		i++;
	}
	i = 0;
	while (map[x][y - i])
	{
		if (map[x][y - i] == ' ' || map[x][y - i] == '\n')
			return (0);
		if (map[x][y - i] == '1')
			break ;
		i++;
	}
	return (1);
}

int	check_for_y(int x, int y, char **map)
{
	int	i;

	i = 0;
	while (map[x + i][y])
	{
		if (map[x + i][y] == ' ' || map[x + i][y] == '\n')
			return (0);
		if (map[x + i][y] == '1')
			break ;
		i++;
	}
	i = 0;
	while (map[x - i][y])
	{
		if (map[x - i][y] == ' ' || map[x - i][y] == '\n')
			return (0);
		if (map[x - i][y] == '1')
			break ;
		i++;
	}
	return (1);
}

int	check_from_pos(int x, int y, char **map)
{
	if (check_for_x(x, y, map) && check_for_y(x, y, map))
		return (1);
	return (0);
}

void	set_player_direction(t_mapinfo *info, char c)
{
	if (c == 'N')
		info->player_direction = 3 * PI / 2;
	else if (c == 'S')
		info->player_direction = PI / 2;
	else if (c == 'E')
		info->player_direction = 0;
	else if (c == 'W')
		info->player_direction = PI;
}

int	check_walls(char **map, t_mapinfo *info)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW0", map[i][j]))
			{
				if (!check_from_pos(i, j, map))
					return (0);
				if (ft_strchr("NSEW", map[i][j]))
				{
					set_player_direction(info, map[i][j]);
					info->player_x_mini = j * info->map_scale + info->ms;
					info->player_y_mini = i * info->map_scale + info->ms;
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}
