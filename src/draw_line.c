/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:11:15 by fbouteil          #+#    #+#             */
/*   Updated: 2025/07/10 14:59:14 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_line(t_mapinfo *info, float angle_diff)
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	x0 = info->player_x_mini + info->map_scale / 2;
	y0 = info->player_y_mini + info->map_scale / 2;
	x1 = cos(info->player_direction + angle_diff) * 200 + x0;
	y1 = sin(info->player_direction + angle_diff) * 200 + y0;
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = x0 < x1 ? 1 : -1;
	sy = y0 < y1 ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		my_pixel_put(&info->minimap, x0, y0, 0xFFFFFF);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
int	get_wall_direction(t_mapinfo *info, float ray_x, float ray_y)
{
	float	diff_x;
	float	diff_y;

	(void)info;
	diff_x = ft_min((ray_x - (int)ray_x), ((int)ray_x + 1 - ray_x));
	diff_y = ft_min((ray_y - (int)ray_y), ((int)ray_y + 1 - ray_y));
	if (diff_y > diff_x)
		return (1);
	return (0);
}
void	draw_until_wall(t_mapinfo *info, float angle_diff, int index)
{
	float	ray_x;
	float	ray_y;
	float	dir_x;
	float	dir_y;
	int		map_x;
	int		map_y;

	dir_x = cos(info->player_direction + angle_diff) * 0.1;
	dir_y = sin(info->player_direction + angle_diff) * 0.1;
	ray_x = info->player_x_mini + info->map_scale / 2;
	ray_y = info->player_y_mini + info->map_scale / 2;
	while (1)
	{
		map_x = (int)(ray_x / info->map_scale);
		map_y = (int)(ray_y / info->map_scale);
		if ((!info->map[map_y] || !info->map[map_y][map_x])
			|| info->map[map_y][map_x] == '1')
			break ;
		my_pixel_put(&info->minimap, (int)ray_x, (int)ray_y, 0xFFFFFF);
		ray_x += dir_x;
		ray_y += dir_y;
	}
	info->ray_info[index].vector_len = get_vector_len(ray_x / info->map_scale,
			ray_y / info->map_scale, (info->player_x_mini + info->map_scale / 2)
			/ info->map_scale, (info->player_y_mini + info->map_scale / 2)
			/ info->map_scale);
	info->ray_info[index].direction = get_wall_direction(info, (ray_x
				/ info->map_scale), (ray_y / info->map_scale));
	if (info->ray_info[index].direction % 2 == 0)
		info->ray_info[index].wall_x = (ray_x / info->map_scale) - (int)(ray_x
				/ info->map_scale);
	else
		info->ray_info[index].wall_x = (ray_y / info->map_scale) - (int)(ray_y
				/ info->map_scale);
}
void	draw_until_wall_dda(t_mapinfo *info, float angle_diff, int index)
{
	float	player_x;
	float	player_y;
	float	dir_x;
	float	dir_y;
	float	delta_x;
	float	delta_y;
	int		map_x;
	int		map_y;
	int		step_x;
	float	side_dist_x;
	int		step_y;
	float	side_dist_y;
	int		side;
	float	wall_x;

	dir_x = cos(info->player_direction + angle_diff);
	dir_y = sin(info->player_direction + angle_diff);
	player_x = info->player_x_mini / info->map_scale;
	player_y = info->player_y_mini / info->map_scale;
	map_x = (int)player_x;
	map_y = (int)player_y;
	if (fabs(dir_x) < 1e-6)
		delta_x = 1e30;
	else
		delta_x = fabs(1 / dir_x);
	if (fabs(dir_y) < 1e-6)
		delta_y = 1e30;
	else
		delta_y = fabs(1 / dir_y);
	if (dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (player_x - map_x) * delta_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - player_x) * delta_x;
	}
	if (dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (player_y - map_y) * delta_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - player_y) * delta_y;
	}
	while (info->map[map_y] && info->map[map_y][map_x]
		&& info->map[map_y][map_x] != '1')
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_y;
			map_y += step_y;
			side = 1;
		}
	}
	if (side == 0)
		info->ray_info[index].vector_len = ft_min((side_dist_x - delta_x), 1e29);
	else
		info->ray_info[index].vector_len = ft_min((side_dist_y - delta_y), 1e29);
	if (side == 0)
	{
		if (step_x > 0)
			info->ray_info[index].direction = EA;
		else
			info->ray_info[index].direction = WE;
		wall_x = player_y + info->ray_info[index].vector_len * dir_y;
	}
	else
	{
		if (step_y > 0)
			info->ray_info[index].direction = SO;
		else
			info->ray_info[index].direction = NO;
		wall_x = player_x + info->ray_info[index].vector_len * dir_x;
	}
	wall_x -= floor(wall_x);
	info->ray_info[index].wall_x = wall_x;
}

void	draw_vectors(t_mapinfo *info, int amount, float fov)
{
	int		i;
	float	start_angle;
	float	angle_step;
	float	angle;

	start_angle = info->player_direction - (fov / 2);
	angle_step = fov / amount;
	i = 0;
	while (i < amount)
	{
		angle = start_angle + i * angle_step;
		draw_until_wall_dda(info, angle - info->player_direction, i);
		i++;
	}
}
