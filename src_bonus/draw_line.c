/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:11:15 by fbouteil          #+#    #+#             */
/*   Updated: 2025/08/21 16:19:18 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_vectordata
{
	float		player_x;
	float		player_y;
	float		dir_x;
	float		dir_y;
	float		delta_x;
	float		delta_y;
	int			map_x;
	int			map_y;
	int			step_x;
	float		side_dist_x;
	int			step_y;
	float		side_dist_y;
	int			side;
	float		wall_x;
}				t_vectordata;

void	init_side_dist(t_vectordata *vector)
{
	if (vector->dir_x < 0)
	{
		vector->step_x = -1;
		vector->side_dist_x = (vector->player_x - vector->map_x)
			* vector->delta_x;
	}
	else
	{
		vector->step_x = 1;
		vector->side_dist_x = (vector->map_x + 1.0 - vector->player_x)
			* vector->delta_x;
	}
	if (vector->dir_y < 0)
	{
		vector->step_y = -1;
		vector->side_dist_y = (vector->player_y - vector->map_y)
			* vector->delta_y;
	}
	else
	{
		vector->step_y = 1;
		vector->side_dist_y = (vector->map_y + 1.0 - vector->player_y)
			* vector->delta_y;
	}
}

t_vectordata	*init_vector(t_mapinfo *info, float angle_diff)
{
	t_vectordata	*vector;

	vector = malloc(sizeof(t_vectordata));
	if (!vector)
		return (NULL);
	ft_memset(vector, 0, sizeof(t_vectordata));
	vector->dir_x = cos(info->player_direction + angle_diff);
	vector->dir_y = sin(info->player_direction + angle_diff);
	vector->player_x = info->player_x_mini / info->map_scale;
	vector->player_y = info->player_y_mini / info->map_scale;
	vector->map_x = (int)vector->player_x;
	vector->map_y = (int)vector->player_y;
	if (fabs(vector->dir_x) < 1e-6)
		vector->delta_x = 1e30;
	else
		vector->delta_x = fabs(1 / vector->dir_x);
	if (fabs(vector->dir_y) < 1e-6)
		vector->delta_y = 1e30;
	else
		vector->delta_y = fabs(1 / vector->dir_y);
	init_side_dist(vector);
	return (vector);
}

void	get_ray_info(t_mapinfo *info, int index, t_vectordata *vector)
{
	if (vector->side == 0)
	{
		info->ray_info[index].vector_len = ft_min((vector->side_dist_x
					- vector->delta_x), 1e29);
		if (vector->step_x > 0)
			info->ray_info[index].direction = EA;
		else
			info->ray_info[index].direction = WE;
		vector->wall_x = vector->player_y + info->ray_info[index].vector_len
			* vector->dir_y;
	}
	else
	{
		info->ray_info[index].vector_len = ft_min((vector->side_dist_y
					- vector->delta_y), 1e29);
		if (vector->step_y > 0)
			info->ray_info[index].direction = SO;
		else
			info->ray_info[index].direction = NO;
		vector->wall_x = vector->player_x + info->ray_info[index].vector_len
			* vector->dir_x;
	}
	vector->wall_x -= floor(vector->wall_x);
	info->ray_info[index].wall_x = vector->wall_x;
}

void	draw_until_wall_dda(t_mapinfo *info, float angle_diff, int index)
{
	t_vectordata	*vector;

	vector = init_vector(info, angle_diff);
	while (info->map[vector->map_y] && info->map[vector->map_y][vector->map_x]
		&& info->map[vector->map_y][vector->map_x] != '1'
		&& info->map[vector->map_y][vector->map_x] != 'D')
	{
		if (vector->side_dist_x < vector->side_dist_y)
		{
			vector->side_dist_x += vector->delta_x;
			vector->map_x += vector->step_x;
			vector->side = 0;
		}
		else
		{
			vector->side_dist_y += vector->delta_y;
			vector->map_y += vector->step_y;
			vector->side = 1;
		}
	}
	info->ray_info[index].door = NULL;
	if (info->map[vector->map_y][vector->map_x] == 'D')
		info->ray_info[index].door = get_door_at(info->doors, vector->map_y,
				vector->map_x);
	(get_ray_info(info, index, vector), free(vector));
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
