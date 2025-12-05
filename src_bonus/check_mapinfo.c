/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mapinfo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:10:28 by fbouteil          #+#    #+#             */
/*   Updated: 2025/08/25 16:20:35 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_color(char *color)
{
	int	color_int;
	int	i;

	i = 0;
	color_int = 0;
	while (!ft_isdigit(color[i]))
		i++;
	color_int += ft_atoi(color + i) * 256 * 256;
	while (ft_isdigit(color[i]))
		i++;
	i++;
	color_int += ft_atoi(color + i) * 256;
	while (ft_isdigit(color[i]))
		i++;
	i++;
	color_int += ft_atoi(color + i);
	return (color_int);
}

int	check_color(char *str)
{
	int			i;
	int			count;
	static int	color = 0;

	if (ft_strlen(str) > 14)
		return (-1);
	i = 2;
	count = 0;
	color++;
	if ((str[0] != 'F' && color == 1) || (str[0] != 'C' && color == 2))
		return (-1);
	if (str[1] && str[1] != ' ')
		return (-1);
	while (str[i] && str[i] != '\n')
	{
		if (ft_atoi(str + i) > 255 || ft_atoi(str + i) < 0)
			return (-1);
		if (!ft_isdigit(str[i]) && str[i] != ',')
			return (-1);
		if (str[i] == ',' && str[i + 1] && str[i + 1] != '\n')
			count++;
		i++;
	}
	return (count);
}

void	check_direction(char *str, char *direction, t_mapinfo *info)
{
	if (!str)
	{
		printf("Error\nDirection : %s", direction);
		exit_clean("Wrong direction info", info, NULL);
	}
	if (ft_strncmp(str, direction, 3) != 0)
	{
		printf("Error\nDirection : %s", direction);
		exit_clean("Wrong direction info", info, NULL);
	}
	if (ft_strlen(str) < 4 || !str[3] || str[3] == '\n')
	{
		printf("Error\nDirection : %s", direction);
		exit_clean("Wrong direction info", info, NULL);
	}
}

void	trim_color(char **color, char *to_add)
{
	char	*tmp;

	if (!*color || !(*color)[1])
		return ;
	tmp = ft_strtrim(*color + 1, " ");
	free(*color);
	*color = ft_strjoin(to_add, tmp);
	free(tmp);
}

void	check_mapinfo(t_mapinfo *info)
{
	trim_color(&info->ceiling_color, "C ");
	trim_color(&info->floor_color, "F ");
	if (check_color(info->floor_color) != 2
		|| check_color(info->ceiling_color) != 2)
	{
		if (info->north)
			free_texture(info, info->north);
		exit_clean("Error\nWrong Floor or Ceiling color", info, NULL);
	}
	info->floor_color_int = get_color(info->floor_color);
	info->ceiling_color_int = get_color(info->ceiling_color);
	check_map(info);
	info->tiles_x = get_map_width(info->map);
	info->tiles_y = get_map_height(info->map);
}
