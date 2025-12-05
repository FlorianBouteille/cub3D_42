/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouteil <fbouteil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:17:57 by fbouteil          #+#    #+#             */
/*   Updated: 2025/08/25 12:47:00 by fbouteil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_door	*new_door(int x, int y)
{
	t_door	*door;

	door = malloc(sizeof(t_door));
	if (!door)
		return (NULL);
	door->x = x;
	door->y = y;
	door->state = CLOSED;
	door->anim_frame = 0;
	door->anim_time = 300;
	door->next = NULL;
	return (door);
}

t_door	*get_door_at(t_door *doors, int x, int y)
{
	t_door	*temp;

	temp = doors;
	while (temp)
	{
		if (temp->x == x && temp->y == y)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	add_door(t_mapinfo *info, int x, int y)
{
	t_door	*temp;

	if (info->doors == NULL)
	{
		info->doors = new_door(x, y);
		return ;
	}
	temp = info->doors;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_door(x, y);
}
