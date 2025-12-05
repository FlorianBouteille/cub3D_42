/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:58:24 by fbouteil          #+#    #+#             */
/*   Updated: 2025/08/21 17:06:35 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_door	*get_near_door(t_mapinfo *info)
{
	t_door	*temp;
	int		diff_x;
	int		y;
	int		x;
	int		diff_y;

	y = (int)info->player_x_mini / info->map_scale;
	x = (int)info->player_y_mini / info->map_scale;
	temp = info->doors;
	while (temp)
	{
		diff_x = abs(x - temp->x);
		diff_y = abs(y - temp->y);
		if (diff_x + diff_y <= 2 && temp->state == CLOSED)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	print_door(t_door *door)
{
	t_door	*tmp;

	tmp = door;
	while (tmp)
	{
		printf("x= %d y = %d state = %d\n", tmp->x, tmp->y, tmp->state);
		tmp = tmp->next;
	}
}

void	animate_open(t_mapinfo *info, t_door *door)
{
	static int	tick = 0;

	if (tick % 3 == 0)
	{
		door->anim_frame++;
		if (door->anim_frame == 6)
		{
			door->state = OPEN;
			info->doors_opening--;
			info->map[door->x][door->y] = '0';
		}
	}
	tick++;
}

void	animate_door(t_mapinfo *info)
{
	t_door	*d;

	d = info->doors;
	while (d)
	{
		if (d->state == OPENING)
			animate_open(info, d);
		d = d->next;
	}
}

void	open_door(t_mapinfo *info)
{
	t_door	*near_door;

	near_door = get_near_door(info);
	if (!near_door)
		return ;
	info->doors_opening++;
	if (near_door->state == CLOSED)
		near_door->state = OPENING;
}
