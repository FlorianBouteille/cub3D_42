/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:13:09 by fbouteil          #+#    #+#             */
/*   Updated: 2025/08/21 11:36:56 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_in_map(int x, int y, t_mapinfo *info)
{
	int	x_coord;
	int	y_coord;

	x_coord = x / info->map_scale;
	y_coord = y / info->map_scale;
	if (!ft_strchr("0NSEW", info->map[y_coord][x_coord]))
		return (0);
	return (1);
}

void	move_player(t_mapinfo *info, float delta_y, float delta_x)
{
	if (is_in_map(info->player_x_mini, info->player_y_mini + delta_y, info))
		info->player_y_mini += (info->player_speed * delta_y) / 2;
	if (is_in_map(info->player_x_mini + delta_x, info->player_y_mini, info))
		info->player_x_mini += (info->player_speed * delta_x) / 2;
}

void	turn_player(t_mapinfo *info, int rotation)
{
	if (rotation)
		info->player_direction -= 0.06;
	else
		info->player_direction += 0.06;
	if (info->player_direction > 2.0 * PI)
		info->player_direction = 0;
	else if (info->player_direction <= 0)
		info->player_direction = 2.0 * PI;
}

int	update(t_mapinfo *info)
{
	float	dirx;
	float	diry;

	dirx = cos(info->player_direction);
	diry = sin(info->player_direction);
	if (info->key_w)
		move_player(info, diry, dirx);
	if (info->key_s)
		move_player(info, -diry, -dirx);
	if (info->key_d)
		move_player(info, dirx, -diry);
	if (info->key_a)
		move_player(info, -dirx, diry);
	if (info->look_right)
		turn_player(info, 0);
	if (info->look_left)
		turn_player(info, 1);
	draw_frame(info);
	draw_minimap(info, 0);
	return (1);
}
